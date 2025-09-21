#pragma once
#include"lock.h"
class contact
{
public:
	bool operator==(contact Right)
	{
		if (this->name == Right.name && this->address == Right.address && this->age==Right.age && this->phonenumber==Right.phonenumber && this->sex==Right.sex)
			return 1;
		return 0;
	}

	void readedit(CEdit &Name,CEdit &Phone, CEdit &Age,CEdit &Sex,CEdit &Adress)
	{
		sex = informationget(Sex);
		phonenumber = informationget(Phone);
		CString s;
		Age.GetWindowTextW(s);
		age = _ttoi(s);
		address = informationget(Adress);
		name = informationget(Name);
	}
	string& f_name()
	{
		return name;
	}
	string& f_phonenumber()
	{
		return phonenumber;
	}
	int& f_age()
	{
		return age;
	}
	string& f_sex()
	{
		return sex;
	}
	string& f_address()
	{
		return address;
	}
	friend class ContactList;
private:
	string name;
	string phonenumber;
	int age=-1;
	string sex;
	string address;
};

class ContactList
{
public:
	string& f_name(int Order)
	{
		return Person[Order].name;
	}
	string& f_phonenumber(int Order)
	{
		return Person[Order].phonenumber;
	}
	int& f_age(int Order)
	{
		return Person[Order].age;
	}
	string& f_sex(int Order)
	{
		return Person[Order].sex;
	}
	string& f_address(int Order)
	{
		return Person[Order].address;
	}
public:
	//按照年龄排列联系人 并 输出最近的空联系人下标 （待优化）
	int line()
	{
		//按照年龄从大到小冒泡排序
		for (int Order = 0; Order < 999; Order++)
			for (int j1 = 0; j1 < 999 - Order; j1++)
				//两两交换
				if (Person[j1].age < Person[j1 + 1].age)
				{
					contact temp = Person[j1];
					Person[j1] = Person[j1 + 1];
					Person[j1 + 1] = temp;
				}
		//找到最近的空联系人下标 并赋给Count
		int  Count = 0;
		for (Count; Count < 999; Count++)
			if (Person[Count].age == Initate_Int)
				break;
		return Count;
	}
	
	//删除联系人信息
	void del(int a6)
	{
		Person[a6].address = Blank_string;
		Person[a6].age = Initate_Int;
		Person[a6].name = Blank_string;
		Person[a6].phonenumber = Blank_string;
		Person[a6].sex = Blank_string;
	}

	//电话或姓名查找联系人		返回下标	否则返回-1
	int search(string Unsearched_Name="/0", string Unsearched_Phonenumber = "/0")
	{
		int MAX = line();
		for (int Order = 0; Order <MAX; Order++)
		{
			if (Person[Order].name == Unsearched_Name || Person[Order].phonenumber == Unsearched_Phonenumber)
			{
				output(Order);
				return Order;
			}
		}
		return -1;
	}

	//从文件读取联系人
	void ReadContact()
	{
		int c = 0;
		freopen("contact.txt", "r", stdin);
		while(1)
		{
			cin >> Person[c].name;
			if ((Person[c].name == "off"))
			{
				Person[c].name = "\0";
				break;
			}
			cin >> Person[c].phonenumber;
			cin >> Person[c].sex;
			if (Person[c].sex == "-1")
				Person[c].sex = "\0";
			cin >> Person[c].age;
			cin >> Person[c].address;
			if (Person[c].address == "-1")
				Person[c].address = "\0";
			c++;
		} 
		freopen("CON", "r", stdin);
	}

	//联系人输入
	void input(contact temp)
	{
		Person[line()] = temp;
	}

	//判断联系人是否存在
	bool isexist(int order)
	{
		if (Person[order].age == -1)
			return 0;
		return 1;
	}

	//联系人输出
	contact output(int order)
	{
		return Person[order];
	}

	//列表输出
	void OutputList(CListCtrl& m_List, CStatic &Number)
	{
		int count = line();
		if (count!= 0)
		{
			//填入列表信息
			for (int Order = 0; Order < count; Order++)
			{
				CString tempcstr;
				tempcstr.Format(_T("%d"), Order+1);
				m_List.InsertItem(Order, tempcstr);
				/*tempcstr(Person[Order].f_name().c_str());*/
				tempcstr.Format(_T("%s"),(CString) Person[Order].name.c_str());
				m_List.SetItemText(Order, 1, tempcstr);
				tempcstr.Format(_T("%s"), (CString)Person[Order].phonenumber.c_str());
				m_List.SetItemText(Order, 2, tempcstr);
			}
		}
		CString num;
		num.Format(_T("%d"), count);
		Number.SetWindowTextW(num);
	}

	//存回文件
	void SaveContact()
	{
		int Order = 0;
		int Count = line();
		freopen("contact.txt", "w", stdout);
		while (Order < Count)
		{
			if (Person[ Order].sex == "\0")
				Person[Order].sex = "-1";
			if (Person[Order].address == "\0")
				Person[Order].address = "-1";
			cout << Person[Order].name << "\t" << Person[Order].phonenumber << "\t" << Person[Order].sex << "\t" << Person[Order].age << "\t" << Person[Order].address << endl;
			Order++;
		}
		cout << "off\t1\t1\t-1\t1" << endl;
		freopen("CON", "w", stdout);
	}

	void test01()
	{
		cout << "联系人列表：" << endl;
		cout << "\t编号" << "\t姓名" << "\t电话" << endl;

		for (int b4 = 0; b4 < 10; b4++)
		{
			cout << "\t" << b4 + 1 << "\t" << Person[b4].name << " \t" << Person[b4].phonenumber << "\t" << Person[b4].age << endl;
		}

	}

public:
	static const int Initate_Int = -1;
	const	string Blank_string ="\0";
	const string Initate_string = "-1";
	int position =-1;
private:
	contact Person[1000] = { };
};


/*//登陆成功
	if(b)
	{
		int c = 0;
		freopen("contact.txt", "r", stdin);
		while (Person[c - 1].name != "off")
		{
			cin >> Person[c].name;
			cin >> Person[c].phonenumber;
			cin >> Person[c].sex;
			cin >> Person[c].age;
			cin >> Person[c].address;
			c++;
		}
		freopen("CON", "r", stdin);
		//int
		c = -1;
		while (c != 0)
		{
			system("cls");
			menu0();
			cin >> c;
			system("cls");
			string name2, name3, name4;
			switch (c)
			{
				//新建联系人
			case 1:
				cout << "新建联系人：\n" << endl;
				input();
				break;

				//查找联系人
			case 2:
				if (line() == 0)
				{
					empty();
				}
				else
				{
					cout << "查找联系人：\n" << endl
						<< "请输入联系人姓名或电话：" << endl;
					cin >> name2;
					search(name2);
				}
				break;

				//修改联系人
			case 3:
				if (line() == 0)
				{
					empty();
				}
				else
				{
					cout << "修改联系人:\n" << endl
						<< "请输入联系人姓名或电话：" << endl;
					cin >> name3;
					search(name3);
					if (a7 != 999)
					{
						cout << "以上为该联系人原信息。" << endl;
						cout << "请确认是否修改：" << endl;
						YoN();
						if (b2 == 2)
						{
							break;
						}
						del(a7);
						cout << "请输入新的信息：" << endl;
						input();
					}
				}
				break;

				//删除联系人
			case 4:
				if (line() == 0)
				{
					empty();
				}
				else
				{
					cout << "删除联系人" << endl
						<< "请输入联系人姓名或电话：" << endl;
					cin >> name4;
					search(name4);
					if (a7 != 999)
					{
						cout << endl << "请确认是否删除：" << endl;
						YoN();
						if (b2 == 2)
						{
							break;
						}
						del(a7);
						cout << "删除成功！" << endl;
						system("pause");
					}
				}
				break;

				//清空联系人
			case 5:
				cout << "清空联系人" << endl;
				if (line() == 0)
				{
					empty();
				}
				else
				{
					cout << endl << "请确认是否清空：" << endl;
					YoN();
					if (b2 == 2)
					{
						break;
					}
					for (int b3 = 0; b3 < 1000; b3++)
					{
						del(b3);
					}
					cout << "清空成功！";
					system("pause");
				}
				break;

				//联系人列表
			case 6:
				cout << "联系人列表：" << endl;
				if (line() == 0)
				{
					empty();
				}
				else
				{
					cout << "\t编号" << "\t姓名" << "\t电话" << endl;

					for (int b4 = 0; b4 < line(); b4++)
					{
						cout << "\t" << b4 + 1 << "\t" << Person[b4].name << " \t" << Person[b4].phonenumber << endl;
					}
					cout << "输入 编号 查看具体信息，或输入 0 返回主菜单：" << endl;
					do
					{
						cout << "\n请输入对应数字：";
						cin >> b2;
						output(b2 - 1);
					} while (b2 != 0);
				}
				break;

				//设置密码
			case 7:
				setcode();
				break;
			case 0:
				break;
			default:
				cout << "请选择正确的序号！" << endl;
				system("pause");
			}
			system("cls");
		}
		c = 0;
		int Count = line();
		freopen("contact.txt", "w", stdout);
		while (c < Count)
		{
			cout << Person[c].name << "\t" << Person[c].phonenumber << "\t" << Person[c].sex << "\t" << Person[c].age << "\t" << Person[c].address << endl;
			c++;
		}
		cout << "off 1 1 0 1" << endl;
		freopen("CON", "w", stdout);
	}*/