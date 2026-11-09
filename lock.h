#pragma once
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

// Maximum accepted password length (including the terminating null).
const int LenthMAX = 30;
// Size of the substitution alphabet.
const int ListLenth = 62;

// Monalphabetic substitution tables used to obfuscate the login password on disk.
//
// ArrSecret[i] <-> ArrObvious[i]. The two strings are permutations of each
// other, so the mapping is reversible: setcode() encrypts, checkcode() decrypts.
//
// NOTE: this is obfuscation, not encryption. The key is compiled into the
// binary and both tables are readable in the source, so anyone who can read
// the executable can recover the password. Its purpose is to keep the plain
// text out of secret.txt, nothing more.
const char ArrSecret[] = "qwertyuiHIJKLMNop[ABCDEFG]asdUVWXYZfghjkOPQRSTl;zxcvbnm,.?{}:|";
const char ArrObvious[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";

// True when ch belongs to the supported password alphabet.
//
// Passwords are restricted to this alphabet on purpose. The stored form is
// read back with a whitespace-delimited scan, so a password containing a space
// could never be read back correctly. Characters outside the alphabet are
// rejected when the password is set instead of being silently dropped: a
// dropped character would produce a stored password that no longer matches
// what the user typed, locking the user out of their own data.
inline bool IsSupportedPasswordChar(char ch)
{
	for (int i = 0; i < ListLenth; i++)
		if (ArrObvious[i] == ch)
			return true;
	return false;
}

// Reads the text of an MFC edit control into a std::string.
//
// NOTE: this converts through the system ANSI code page, so non-ASCII names
// depend on the machine's regional settings. See "Known limitations" in
// README.md.
inline string informationget(CEdit& tempedit)
{
	CString s;
	tempedit.GetWindowTextW(s);
	string result = (CStringA)s;
	return result;
}

// Writes the obfuscated form of ArrCIN to secret.txt.
//
// Returns false, leaving any existing file untouched, when the password is
// empty, too long, or contains a character outside the supported alphabet.
inline bool setcode(const char* ArrCIN)
{
	int l = (int)strlen(ArrCIN);
	if (l == 0 || l >= LenthMAX)
		return false;
	for (int i = 0; i < l; i++)
		if (!IsSupportedPasswordChar(ArrCIN[i]))
			return false;

	FILE* txt = fopen("secret.txt", "w+");
	if (txt == nullptr)
		return false;

	for (int Order = 0; Order < l; Order++)
	{
		for (int CheckTimes = 0; CheckTimes < ListLenth; CheckTimes++)
		{
			if (ArrCIN[Order] == ArrObvious[CheckTimes])
			{
				fprintf(txt, "%c", ArrSecret[CheckTimes]);
				break;
			}
		}
	}

	fclose(txt);
	return true;
}

// Verifies the plain text ArrCIN against the obfuscated password stored in
// secret.txt.
//
// Returns false when secret.txt is missing, empty, or unreadable. A missing
// file is reported through HasStoredPassword() so the caller can offer a
// first-run setup instead of treating it as a wrong password.
inline bool checkcode(const char* ArrCIN)
{
	FILE* txt = fopen("secret.txt", "r");
	if (txt == nullptr)
		return false;

	char ArrFIN[LenthMAX] = "\0";
	if (fscanf_s(txt, "%s", ArrFIN, LenthMAX) != 1)
	{
		fclose(txt);
		return false;
	}
	fclose(txt);

	int LenthArrFIN = (int)strlen(ArrFIN);
	int LenthArrCIN = (int)strlen(ArrCIN);
	if (LenthArrFIN == 0 || LenthArrFIN != LenthArrCIN)
		return false;

	int CorrectTimes = 0;
	for (int Order = 0; Order < LenthArrFIN; Order++)
	{
		for (int CheckTimes = 0; CheckTimes < ListLenth; CheckTimes++)
		{
			if (ArrFIN[Order] == ArrSecret[CheckTimes])
			{
				if (ArrCIN[Order] == ArrObvious[CheckTimes])
					CorrectTimes++;
				break;
			}
		}
	}

	return CorrectTimes == LenthArrFIN;
}

// True when a password file already exists on disk.
//
// Used to detect a first run: with no secret.txt the login screen offers to
// create the initial password instead of rejecting every attempt.
inline bool HasStoredPassword()
{
	FILE* txt = fopen("secret.txt", "r");
	if (txt == nullptr)
		return false;
	fclose(txt);
	return true;
}
