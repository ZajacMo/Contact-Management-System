#pragma once
#include "afxdialogex.h"


// DIALOG_CODE dialog

class DIALOG_CODE : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_CODE)

public:
	DIALOG_CODE(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~DIALOG_CODE();

	// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODEMANAGEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit OLD_CODE;
	CEdit NEW_CODE;
	CEdit AGAIN_CODE;
	CStatic TIP_OLD;
	CStatic TIP_NEW;
	virtual void OnOK();
	afx_msg void OnBnClickedOk();
};
