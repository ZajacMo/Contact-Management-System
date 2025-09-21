// DIALOG_CODE.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DIALOG_CODE.h"


// DIALOG_CODE 对话框

IMPLEMENT_DYNAMIC(DIALOG_CODE, CDialogEx)

DIALOG_CODE::DIALOG_CODE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CODEMANAGEMENT, pParent)
{

}

DIALOG_CODE::~DIALOG_CODE()
{
}

void DIALOG_CODE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDOK, CHAGE_CODE);
	DDX_Control(pDX, IDC_EDIT1, OLD_CODE);
	DDX_Control(pDX, IDC_EDIT2, NEW_CODE);
	DDX_Control(pDX, IDC_EDIT3, AGAIN_CODE);
	//  DDX_Control(pDX, IDCANCEL, TIP_OLD);
	//  DDX_Control(pDX, IDCANCEL, TIP_NEW);
	DDX_Control(pDX, IDC_OLD, TIP_OLD);
	DDX_Control(pDX, IDC_NEW, TIP_NEW);
}


BEGIN_MESSAGE_MAP(DIALOG_CODE, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG_CODE::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG_CODE 消息处理程序

//修改密码
void DIALOG_CODE::OnBnClickedOk()
{
	CString cstr1 , cstr2 ;
	bool b = 1;
	OLD_CODE.GetWindowTextW(cstr1);
	char* temp;
	LPCTSTR p = cstr1.GetBuffer(0);
	cstr1.ReleaseBuffer();
	temp = new char[cstr1.GetLength() + 1];
	strcpy_s(temp, cstr1.GetLength() + 1, CT2CA(p));
	char result[50];
	memset(result, '\0', sizeof(result));
	strcpy_s(result, (char*)temp);
	if (!checkcode(result))
	{
		b = 0;
		TIP_OLD.SetWindowTextW(TEXT("原密码错误！"));
	}
	NEW_CODE.GetWindowTextW(cstr1);
	AGAIN_CODE.GetWindowTextW(cstr2);
	if (cstr1 != cstr2)
	{
		b = 0;
		TIP_NEW.SetWindowTextW(TEXT("两次输入密码不同！"));
	}
	if (b)
	{
		p = cstr2.GetBuffer(0);
		cstr2.ReleaseBuffer();
		temp = new char[cstr2.GetLength() + 1];
		strcpy_s(temp, cstr2.GetLength() + 1, CT2CA(p));
		char result[50];
		memset(result, '\0', sizeof(result));
		strcpy_s(result, (char*)temp);
		setcode(result);
		//cout << result;
		Tip_m(TEXT("修改成功！请牢记您的新密码！"));
		OnCancel();
	}
}
void DIALOG_CODE::OnOK()
{
	DIALOG_CODE::OnBnClickedOk();
}
