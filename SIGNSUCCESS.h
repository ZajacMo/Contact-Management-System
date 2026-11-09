#pragma once
#include "afxdialogex.h"


// SIGNSUCCESS dialog

class SIGNSUCCESS : public CDialogEx
{
	DECLARE_DYNAMIC(SIGNSUCCESS)

public:
	SIGNSUCCESS(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~SIGNSUCCESS();
// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNSUCCEEDED };
#endif
	void settext(CString str)
	{
		Information.SetWindowTextW(str);
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic Information;
	afx_msg void OnStnClickedInformation(NMHDR* pNMHDR, LRESULT* pResult);
	CString tip;
};
