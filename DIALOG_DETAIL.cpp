// DIALOG_DETAIL.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DIALOG_DETAIL.h"


// DIALOG_DETAIL 对话框

IMPLEMENT_DYNAMIC(DIALOG_DETAIL, CDialogEx)

DIALOG_DETAIL::DIALOG_DETAIL(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
{

}

DIALOG_DETAIL::~DIALOG_DETAIL()
{
}

void DIALOG_DETAIL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME_ADD, Name);
	DDX_Control(pDX, IDC_SEX_ADD, Sex);
	DDX_Control(pDX, IDC_PHONE_ADD, Phonenumber);
	DDX_Control(pDX, IDC_AGE_ADD, Age);
	DDX_Control(pDX, IDC_ADDRESS_ADD, Address);
	CString tempcstr;
	if (List.f_age(List.position) != 0)
	{
		tempcstr.Format(_T("%d"), List.f_age(List.position));
		Age.SetWindowTextW(tempcstr);
	}
	tempcstr.Format(_T("%s"), (CString)List.f_name(List.position).c_str());
	Name.SetWindowTextW(tempcstr);
	tempcstr.Format(_T("%s"), (CString)List.f_phonenumber(List.position).c_str());
	Phonenumber.SetWindowTextW(tempcstr);
	tempcstr.Format(_T("%s"), (CString)List.f_address(List.position).c_str());
	Address.SetWindowTextW(tempcstr);
	tempcstr.Format(_T("%s"), (CString)List.f_sex(List.position).c_str());
	Sex.SetWindowTextW(tempcstr);
}


BEGIN_MESSAGE_MAP(DIALOG_DETAIL, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &DIALOG_DETAIL::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG_DETAIL::OnBnClickedButton1)
END_MESSAGE_MAP()


// DIALOG_DETAIL 消息处理程序

//修改
void DIALOG_DETAIL::OnBnClickedButton2()
{
	contact TempPerson;
	TempPerson.readedit(Name, Phonenumber, Age, Sex, Address);
	if (TempPerson == List.output(List.position))
		Tip_m(TEXT("请先修改再点击！"));
	else
	{
		List.del(List.position);
		List.input(TempPerson);
		Tip_m(TEXT("修改成功！"));
		List.position=List.search(TempPerson.f_name());
		OnCancel();
	}
}

//删除
void DIALOG_DETAIL::OnBnClickedButton1()
{
	List.del(List.position);
	Tip_m(TEXT("删除成功！"));
	OnCancel();
}
void DIALOG_DETAIL::OnOK()
{
	contact tempPerson;
	tempPerson.readedit(Name, Phonenumber, Age, Sex, Address);
	if (List.output(List.position) == tempPerson)
		OnCancel();
	else
		DIALOG_DETAIL::OnBnClickedButton2();
}
