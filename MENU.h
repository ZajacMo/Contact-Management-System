#pragma once
#include "afxdialogex.h"


// MENU dialog

class MENU : public CDialogEx
{
	DECLARE_DYNAMIC(MENU)

public:
	MENU(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~MENU();

// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_List;
public:
	CStatic Number;
	afx_msg void OnBnClickedDetail();
	afx_msg void OnBnClickedSaved();
	afx_msg void OnBnClickedSweap();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedCode();
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
};
