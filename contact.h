#pragma once
#include "lock.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

// Maximum number of contacts the application can hold.
const int ContactCapacity = 1000;

// Splits a tab separated record into its fields.
inline std::vector<std::string> SplitRecord(const std::string& line)
{
	std::vector<std::string> fields;
	std::string current;
	for (char ch : line)
	{
		if (ch == '\t')
		{
			fields.push_back(current);
			current.clear();
		}
		else
		{
			current.push_back(ch);
		}
	}
	fields.push_back(current);
	return fields;
}

// Returns the field at index, or an empty string when the record is short.
inline std::string FieldAt(const std::vector<std::string>& fields, size_t index)
{
	return index < fields.size() ? fields[index] : std::string();
}

// Removes leading and trailing whitespace.
inline std::string TrimSpaces(const std::string& text)
{
	size_t begin = text.find_first_not_of(" \t\r\n");
	if (begin == std::string::npos)
		return std::string();
	size_t end = text.find_last_not_of(" \t\r\n");
	return text.substr(begin, end - begin + 1);
}

// True when text is a valid age: a non-negative whole number.
//
// Ages are stored in the contact list as -1 to mark a free slot, so a
// negative age would be indistinguishable from "no contact here".
inline bool IsValidAge(const std::string& text)
{
	if (text.empty())
		return false;
	for (char ch : text)
		if (ch < '0' || ch > '9')
			return false;
	return true;
}

// A single contact.
//
// Fields are private and reached through the f_*() accessors. ContactList is
// a friend so it can fill records directly while reading from disk.
class contact
{
public:
	// Value equality over every field.
	bool operator==(contact Right)
	{
		if (this->name == Right.name && this->address == Right.address && this->age == Right.age
			&& this->phonenumber == Right.phonenumber && this->sex == Right.sex)
			return 1;
		return 0;
	}

	// Copies the current contents of the given edit controls into this record.
	// The age control is read as an integer; an empty or non numeric field
	// yields 0, so callers validate the text before calling this.
	void readedit(CEdit& Name, CEdit& Phone, CEdit& Age, CEdit& Sex, CEdit& Adress)
	{
		sex = informationget(Sex);
		phonenumber = informationget(Phone);
		CString s;
		Age.GetWindowTextW(s);
		age = _ttoi(s);
		address = informationget(Adress);
		name = informationget(Name);
	}

	string& f_name() { return name; }
	string& f_phonenumber() { return phonenumber; }
	int& f_age() { return age; }
	string& f_sex() { return sex; }
	string& f_address() { return address; }

	friend class ContactList;

private:
	string name;
	string phonenumber;
	int age = -1;
	string sex;
	string address;
};

// The contact list.
//
// Contacts occupy the front of a fixed size array. A free slot is marked by
// age == Initate_Int (-1), which is why age is validated as non-negative
// when a contact is created.
//
// The list is kept sorted by descending age. That ordering is what the list
// view shows and what SaveContact() writes to disk, so it is part of the
// observable behaviour rather than an implementation detail.
class ContactList
{
public:
	string& f_name(int Order) { return Person[Order].name; }
	string& f_phonenumber(int Order) { return Person[Order].phonenumber; }
	int& f_age(int Order) { return Person[Order].age; }
	string& f_sex(int Order) { return Person[Order].sex; }
	string& f_address(int Order) { return Person[Order].address; }

public:
	// Sorts the contacts by descending age and returns the number of slots
	// currently in use.
	//
	// Free slots carry age -1 and therefore sort to the end, so the occupied
	// contacts always occupy indices [0, count).
	//
	// The previous implementation used a hand written bubble sort over 999
	// elements and ran it on every search, insert and save. std::stable_sort
	// keeps the same ordering for a fraction of the work.
	int line()
	{
		std::stable_sort(Person, Person + ContactCapacity,
			[](const contact& a, const contact& b) { return a.age > b.age; });

		int Count = 0;
		while (Count < ContactCapacity && Person[Count].age != Initate_Int)
			Count++;
		return Count;
	}

	// Clears the contact at index a6, turning the slot back into a free one.
	void del(int a6)
	{
		if (a6 < 0 || a6 >= ContactCapacity)
			return;
		Person[a6].address = Blank_string;
		Person[a6].age = Initate_Int;
		Person[a6].name = Blank_string;
		Person[a6].phonenumber = Blank_string;
		Person[a6].sex = Blank_string;
	}

	// Finds the first contact whose name or phone number matches.
	//
	// The "/0" default means "do not search by this field"; it is a value
	// that cannot occur in a contact entered through the dialog.
	// Returns the index of the match, or -1 when there is none.
	int search(string Unsearched_Name = "/0", string Unsearched_Phonenumber = "/0")
	{
		int MAX = line();
		for (int Order = 0; Order < MAX; Order++)
		{
			if (Person[Order].name == Unsearched_Name || Person[Order].phonenumber == Unsearched_Phonenumber)
				return Order;
		}
		return -1;
	}

	// Loads the contacts from contact.txt.
	//
	// File format: one record per line, tab separated, in the order
	//   name <TAB> phone <TAB> sex <TAB> age <TAB> address
	// The list is terminated by a sentinel record whose first field is "off".
	// A sex or address of "-1" means "not set" and is loaded as an empty
	// string. Fields may contain spaces; only the tab is a separator.
	//
	// A missing or unreadable file is treated as "no contacts yet" so a
	// fresh checkout starts with an empty list instead of failing.
	// Returns the number of contacts loaded.
	int ReadContact()
	{
		for (int i = 0; i < ContactCapacity; i++)
			del(i);

		std::ifstream file("contact.txt");
		if (!file.is_open())
			return 0;

		int loaded = 0;
		std::string line;
		while (loaded < ContactCapacity && std::getline(file, line))
		{
			// Strip the carriage return of files written on Windows.
			if (!line.empty() && line.back() == '\r')
				line.pop_back();
			if (line.empty())
				continue;

			std::vector<std::string> fields = SplitRecord(line);
			if (fields.empty() || fields[0] == "off")
				break;

			Person[loaded].name = fields[0];
			Person[loaded].phonenumber = FieldAt(fields, 1);

			Person[loaded].sex = FieldAt(fields, 2);
			if (Person[loaded].sex == "-1")
				Person[loaded].sex = Blank_string;

			Person[loaded].age = atoi(FieldAt(fields, 3).c_str());
			if (Person[loaded].age < 0)
				Person[loaded].age = Initate_Int;

			Person[loaded].address = FieldAt(fields, 4);
			if (Person[loaded].address == "-1")
				Person[loaded].address = Blank_string;

			loaded++;
		}

		return loaded;
	}

	// Inserts a contact into the first free slot.
	// Returns false when the list is already full.
	bool input(contact temp)
	{
		int slot = line();
		if (slot >= ContactCapacity)
			return false;
		Person[slot] = temp;
		return true;
	}

	// True when the slot at order holds a contact.
	bool isexist(int order)
	{
		if (order < 0 || order >= ContactCapacity)
			return false;
		return Person[order].age != Initate_Int;
	}

	// Returns a copy of the contact at order.
	contact output(int order)
	{
		return Person[order];
	}

	// Fills the list control with the current contacts and updates the
	// counter label.
	void OutputList(CListCtrl& m_List, CStatic& Number)
	{
		int count = line();
		if (count != 0)
		{
			// Fill in the list rows.
			for (int Order = 0; Order < count; Order++)
			{
				CString tempcstr;
				tempcstr.Format(_T("%d"), Order + 1);
				m_List.InsertItem(Order, tempcstr);
				tempcstr.Format(_T("%s"), (CString)Person[Order].name.c_str());
				m_List.SetItemText(Order, 1, tempcstr);
				tempcstr.Format(_T("%s"), (CString)Person[Order].phonenumber.c_str());
				m_List.SetItemText(Order, 2, tempcstr);
			}
		}
		CString num;
		num.Format(_T("%d"), count);
		Number.SetWindowTextW(num);
	}

	// Writes every contact back to contact.txt, followed by the "off"
	// sentinel record.
	//
	// Returns false when the file could not be opened for writing, so the
	// caller can warn instead of silently losing the data.
	bool SaveContact()
	{
		std::ofstream file("contact.txt");
		if (!file.is_open())
			return false;

		int Count = line();
		for (int Order = 0; Order < Count; Order++)
		{
			std::string sex = Person[Order].sex.empty() ? Initate_string : Person[Order].sex;
			std::string address = Person[Order].address.empty() ? Initate_string : Person[Order].address;
			file << Person[Order].name << "\t" << Person[Order].phonenumber << "\t"
				<< sex << "\t" << Person[Order].age << "\t" << address << "\n";
		}
		file << "off\t1\t1\t-1\t1\n";

		file.flush();
		return file.good();
	}

public:
	static const int Initate_Int = -1;
	const string Blank_string = "\0";
	const string Initate_string = "-1";
	int position = -1;

private:
	contact Person[ContactCapacity] = { };
};

// The single, application wide contact list.
//
// Defined in MFCApplication1.cpp and declared here so that every
// translation unit shares one instance. Keeping the definition in the
// precompiled header instead would create a separate copy per translation
// unit, which breaks the dialogs that add and edit contacts.
extern ContactList List;
