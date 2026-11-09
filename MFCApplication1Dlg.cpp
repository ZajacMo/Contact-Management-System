
// MFCApplication1Dlg.cpp: Implementation file for the sign-in dialog.
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Dialog for the application "About" box
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// Binds the member variables to the controls
void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODEIN, code);
	DDX_Control(pDX, IDC_FAILURETIP, failuretip);
	DDX_Control(pDX, IDC_SIGNIN, signin);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SIGNIN, &CMFCApplication1Dlg::OnBnClickedSignin)
	ON_BN_CLICKED(IDC_EXIT, &CMFCApplication1Dlg::OnBnClickedExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CODEFOGOTTEN, &CMFCApplication1Dlg::OnBnClickedCodefogotten)
	ON_BN_DOUBLECLICKED(IDC_CODEFOGOTTEN, &CMFCApplication1Dlg::OnDoubleclickedCodefogotten)
END_MESSAGE_MAP()

// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add the "About..." menu item to the system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog.
	SetIcon(m_hIcon, TRUE);			// Big icon
	SetIcon(m_hIcon, FALSE);		// Small icon

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Paints the dialog's icon when the dialog is minimized.
void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Draw the icon at the center of the client area.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor when the user drags
// the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Enter key handling
void CMFCApplication1Dlg::OnOK()
{
	CMFCApplication1Dlg::OnBnClickedSignin();
}

// Converts an edit control's text to a plain char buffer.
//
// Returns an empty string when the control holds no text. The caller owns
// the returned buffer and must delete[] it.
//
// The previous implementation allocated this buffer with new[] and never
// freed it, leaking memory on every sign-in attempt.
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

// Sign-in button handler
void CMFCApplication1Dlg::OnBnClickedSignin()
{
	CButton* CheckStatu = (CButton*)GetDlgItem(IDC_NOTEREADED);
	if (CheckStatu->GetCheck() != 1)
	{
		Tip_m(TEXT("Please read the security agreement first!"));
		return;
	}

	// No password has been set yet: treat the first entry as the initial
	// password rather than rejecting it as wrong.
	if (!HasStoredPassword())
	{
		std::string entered;
		if (!GetControlText(code, entered) || entered.empty())
		{
			failuretip.SetWindowTextW(TEXT("Please enter a password!"));
			return;
		}
		if (!setcode(entered.c_str()))
		{
			failuretip.SetWindowTextW(TEXT("Unsupported password. Use letters, digits and the symbols . , ? { } | ;"));
			return;
		}
		failuretip.SetWindowTextW(TEXT("Password set. Signed in!"));
		OnCancel();
		return;
	}

	std::string entered;
	if (!GetControlText(code, entered) || entered.empty())
	{
		failuretip.SetWindowTextW(TEXT("Please enter a password!"));
		return;
	}

	if (checkcode(entered.c_str()))
	{
		failuretip.SetWindowTextW(TEXT("Signed in successfully!"));
		OnCancel();
	}
	else
	{
		failuretip.SetWindowTextW(TEXT("Wrong password! Please try again."));
	}
}

// Exit button and window close handler
void CMFCApplication1Dlg::OnBnClickedExit()
{
	// The contact list has not been modified yet at this point, so there is
	// nothing to save.
	CDialogEx::OnCancel();
}

void CMFCApplication1Dlg::OnClose()
{
	CDialogEx::OnCancel();
}

// "Forgot password" link.
//
// There is no recovery path: the stored password is obfuscated, not
// encrypted, and the only way to reset it is to delete secret.txt and set a
// new password on the next run.
void CMFCApplication1Dlg::OnBnClickedCodefogotten()
{
	Tip_m(TEXT("The password cannot be recovered. Delete secret.txt to set a new one."));
	CDialogEx::OnCancel();
}

// Double clicking the link is treated as a deliberate attempt to get in.
void CMFCApplication1Dlg::OnDoubleclickedCodefogotten()
{
	Tip_m(TEXT("There is no password recovery. Delete secret.txt to set a new one."));
	CDialogEx::OnCancel();
}
