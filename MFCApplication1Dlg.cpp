
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
	
public:
//	afx_msg void OnClose();
//	afx_msg void OnClose();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CLOSE()
//ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//变量和按钮匹配
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
//	ON_EN_CHANGE(IDC_CODEIN, &CMFCApplication1Dlg::OnEnChangeCodein)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CODEFOGOTTEN, &CMFCApplication1Dlg::OnBnClickedCodefogotten)
	ON_BN_DOUBLECLICKED(IDC_CODEFOGOTTEN, &CMFCApplication1Dlg::OnBnDoubleclickedCodefogotten)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//回车键修改
void CMFCApplication1Dlg::OnOK()
{
	CMFCApplication1Dlg::OnBnClickedSignin();
}

//登陆键触发
void CMFCApplication1Dlg::OnBnClickedSignin()
{
	CButton *CheckStatu = (CButton*)GetDlgItem(IDC_NOTEREADED);
	if (CheckStatu->GetCheck() == 1)
	{
		CString  str;
		code.GetWindowTextW(str);
		//cout << CStringTOchar(str);
		char* temp;
		LPCTSTR p = str.GetBuffer(0);
		str.ReleaseBuffer();
		temp = new char[str.GetLength() + 1];
		strcpy_s(temp, str.GetLength() + 1, CT2CA(p));
		char result[50];
		memset(result, '\0', sizeof(result));
		strcpy_s(result, (char*)temp);
		if (checkcode(result) == 1)
		{
			failuretip.SetWindowTextW(TEXT("登陆成功！"));
			OnCancel();
		}
		else
			failuretip.SetWindowTextW(TEXT("密码错误！ 请重试！"));
	}
	else
	{
		Tip_m(TEXT("请先阅读安全协议！"));
	}
}

//登录界面退出键和关闭键
void CMFCApplication1Dlg::OnBnClickedExit()
{
	exit(0);
}
void CMFCApplication1Dlg::OnClose()
{
	exit(0);
}

//忘记密码
void CMFCApplication1Dlg::OnBnClickedCodefogotten()
{
	exit(0);
}
void CMFCApplication1Dlg::OnBnDoubleclickedCodefogotten()
{
	Tip_m(TEXT("不知道密码您偷看什么?"));
	Tip_m(TEXT("去跪求解码吧！"));
	exit(0);
}

