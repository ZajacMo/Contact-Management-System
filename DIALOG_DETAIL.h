#pragma once
#include "afxdialogex.h"


// DIALOG_DETAIL dialog

class DIALOG_DETAIL : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_DETAIL)

public:
	DIALOG_DETAIL(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~DIALOG_DETAIL();
	virtual void OnOK();
// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit Name;
	CEdit Sex;
	CEdit Phonenumber;
	CEdit Age;
	CEdit Address;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
