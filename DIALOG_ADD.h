#pragma once
#include "afxdialogex.h"

// DIALOG_ADD 对话框

class DIALOG_ADD : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_ADD)

public:
	DIALOG_ADD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG_ADD();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CEdit Name;
	CEdit Phone;
	CEdit Sex;
	CEdit Age;
	CEdit Adress;
	CButton Add;
	virtual void OnOK();
	/*afx_msg void OnEnChangeNameAdd();
	afx_msg void OnEnChangePhoneAdd();
	afx_msg void OnEnChangeSexAdd();
	afx_msg void OnEnChangeAgeAdd();
	afx_msg void OnEnChangeAddressAdd();*/
	afx_msg void OnBnClickedOk();
};
