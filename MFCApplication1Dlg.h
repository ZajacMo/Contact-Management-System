
// MFCApplication1Dlg.h: Header file
//

#pragma once


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
	// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// Standard constructor

	// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNINPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedSignin();
	afx_msg void OnBnClickedExit();

	CEdit code;
	CStatic failuretip;
	CButton signin;
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCodefogotten();
	afx_msg void OnDoubleclickedCodefogotten();

};
