
// DIALOG_ADD.cpp: Implementation file for the "new contact" dialog.
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DIALOG_ADD.h"

// DIALOG_ADD dialog

IMPLEMENT_DYNAMIC(DIALOG_ADD, CDialogEx)

DIALOG_ADD::DIALOG_ADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{
}

DIALOG_ADD::~DIALOG_ADD()
{
}

void DIALOG_ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME_ADD, Name);
	DDX_Control(pDX, IDC_PHONE_ADD, Phone);
	DDX_Control(pDX, IDC_SEX_ADD, Sex);
	DDX_Control(pDX, IDC_AGE_ADD, Age);
	DDX_Control(pDX, IDC_ADDRESS_ADD, Adress);
	DDX_Control(pDX, IDOK, Add);
}
BEGIN_MESSAGE_MAP(DIALOG_ADD, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG_ADD::OnBnClickedOk)
END_MESSAGE_MAP()
// DIALOG_ADD message handlers

// Enter key handling
void DIALOG_ADD::OnOK()
{
	DIALOG_ADD::OnBnClickedOk();
}

// OK button handler
void DIALOG_ADD::OnBnClickedOk()
{
	contact TempPerson;
	TempPerson.readedit(Name, Phone, Age, Sex, Adress);

	// Name and phone number are mandatory.
	if (TempPerson.f_name().empty() || TempPerson.f_phonenumber().empty())
	{
		Tip_m(TEXT("Please enter a name and a phone number!"));
		return;
	}

	// The age is optional, but when present it must be a whole number.
	// A free slot in the list is marked with age -1, so a negative age could
	// not be told apart from "no contact here".
	CString ageText;
	Age.GetWindowTextW(ageText);
	ageText.Trim();
	if (!ageText.IsEmpty() && !IsValidAge((CStringA)ageText))
	{
		Tip_m(TEXT("The age must be a whole number!"));
		return;
	}

	// Reject a contact that already exists, matching on name or phone number.
	int test = List.search(TempPerson.f_name(), TempPerson.f_phonenumber());
	if (test != -1)
	{
		Tip_m(TEXT("This contact already exists. Add failed!"));
		return;
	}

	if (!List.input(TempPerson))
	{
		Tip_m(TEXT("The contact list is full!"));
		return;
	}

	Tip_m(TEXT("Contact created!"));
	OnCancel();
}
