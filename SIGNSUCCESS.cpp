// SIGNSUCCESS.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SIGNSUCCESS.h"


// SIGNSUCCESS 对话框

IMPLEMENT_DYNAMIC(SIGNSUCCESS, CDialogEx)

SIGNSUCCESS::SIGNSUCCESS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGNSUCCEEDED, pParent)
{
}

SIGNSUCCESS::~SIGNSUCCESS()
{
}

void SIGNSUCCESS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFORMATION, Information);
	settext(tip);
}


BEGIN_MESSAGE_MAP(SIGNSUCCESS, CDialogEx)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_INFORMATION, &SIGNSUCCESS::OnStnClickedInformation)
END_MESSAGE_MAP()


// SIGNSUCCESS 消息处理程序


void SIGNSUCCESS::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnCancel();
	CDialogEx::OnTimer(nIDEvent);
}


void SIGNSUCCESS::OnStnClickedInformation()
{
	// TODO: 在此添加控件通知处理程序代码
}
