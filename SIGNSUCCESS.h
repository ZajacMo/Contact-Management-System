#pragma once
#include "afxdialogex.h"


// SIGNSUCCESS 对话框

class SIGNSUCCESS : public CDialogEx
{
	DECLARE_DYNAMIC(SIGNSUCCESS)

public:
	SIGNSUCCESS(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SIGNSUCCESS();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNSUCCEEDED };
#endif
	void settext(CString str)
	{
		Information.SetWindowTextW(str);
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic Information;
	afx_msg void OnStnClickedInformation();
	CString tip;
};

