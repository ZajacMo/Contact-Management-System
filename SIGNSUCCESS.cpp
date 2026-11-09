
// SIGNSUCCESS.cpp: Implementation file for the notification dialog.
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SIGNSUCCESS.h"


// SIGNSUCCESS dialog

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


// SIGNSUCCESS message handlers

// The dialog closes itself when the timer set by Tip_s() fires.
void SIGNSUCCESS::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
	OnCancel();
}

void SIGNSUCCESS::OnStnClickedInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
}
