#pragma once
#include "afxdialogex.h"


// DIALOG_DETAIL 对话框

class DIALOG_DETAIL : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_DETAIL)

public:
	DIALOG_DETAIL(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG_DETAIL();
	virtual void OnOK();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
