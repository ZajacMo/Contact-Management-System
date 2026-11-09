#pragma once
#include "afxdialogex.h"

// DIALOG_ADD dialog

class DIALOG_ADD : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_ADD)

public:
	DIALOG_ADD(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~DIALOG_ADD();
// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CEdit Name;
	CEdit Phone;
	CEdit Sex;
	CEdit Age;
	CEdit Adress;
	CButton Add;
	virtual void OnOK();
	afx_msg void OnBnClickedOk();
};
