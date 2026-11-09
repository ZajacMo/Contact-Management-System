
// DIALOG_CODE.cpp: Implementation file for the password management dialog.
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DIALOG_CODE.h"


// DIALOG_CODE dialog

IMPLEMENT_DYNAMIC(DIALOG_CODE, CDialogEx)

DIALOG_CODE::DIALOG_CODE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CODEMANAGEMENT, pParent)
{
}

DIALOG_CODE::~DIALOG_CODE()
{
}

void DIALOG_CODE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, OLD_CODE);
	DDX_Control(pDX, IDC_EDIT2, NEW_CODE);
	DDX_Control(pDX, IDC_EDIT3, AGAIN_CODE);
	DDX_Control(pDX, IDC_OLD, TIP_OLD);
	DDX_Control(pDX, IDC_NEW, TIP_NEW);
}


BEGIN_MESSAGE_MAP(DIALOG_CODE, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG_CODE::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG_CODE message handlers

// Converts an edit control's text to a plain char buffer.
//
// Returns an empty string when the control holds no text. The caller owns
// the returned buffer and must delete[] it.
//
// The previous implementation allocated this buffer with new[] and never
// freed it, leaking memory on every use of the dialog.
static bool GetControlText(CEdit& control, std::string& out)
{
	out.clear();
	CString str;
	control.GetWindowTextW(str);
	if (str.IsEmpty())
		return false;

	LPCTSTR p = str.GetBuffer(0);
	str.ReleaseBuffer();
	char* buffer = new char[str.GetLength() + 1];
	strcpy_s(buffer, str.GetLength() + 1, CT2CA(p));
	out = buffer;
	delete[] buffer;
	return true;
}

// Change the password
void DIALOG_CODE::OnBnClickedOk()
{
	bool b = 1;

	std::string oldPassword;
	GetControlText(OLD_CODE, oldPassword);
	if (!checkcode(oldPassword.c_str()))
	{
		b = 0;
		TIP_OLD.SetWindowTextW(TEXT("The old password is wrong!"));
	}

	std::string newPassword;
	GetControlText(NEW_CODE, newPassword);

	CString newText;
	NEW_CODE.GetWindowTextW(newText);
	CString againText;
	AGAIN_CODE.GetWindowTextW(againText);
	if (newText != againText)
	{
		b = 0;
		TIP_NEW.SetWindowTextW(TEXT("The two new passwords differ!"));
	}

	if (newPassword.empty())
	{
		b = 0;
		TIP_NEW.SetWindowTextW(TEXT("The new password must not be empty!"));
	}

	if (b)
	{
		if (!setcode(newPassword.c_str()))
		{
			TIP_NEW.SetWindowTextW(TEXT("Unsupported password. Use letters, digits and the symbols . , ? { } | ;"));
			return;
		}
		Tip_m(TEXT("Password changed! Remember your new password."));
		OnCancel();
	}
}

void DIALOG_CODE::OnOK()
{
	DIALOG_CODE::OnBnClickedOk();
}
