// DIALOG_ADD.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DIALOG_ADD.h"

// DIALOG_ADD 对话框

IMPLEMENT_DYNAMIC(DIALOG_ADD, CDialogEx)
DIALOG_ADD::DIALOG_ADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{
}
DIALOG_ADD::~DIALOG_ADD()
{
}

void DIALOG_ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME_ADD, Name);
	DDX_Control(pDX, IDC_PHONE_ADD, Phone);
	DDX_Control(pDX, IDC_SEX_ADD, Sex);
	DDX_Control(pDX, IDC_AGE_ADD, Age);
	DDX_Control(pDX, IDC_ADDRESS_ADD, Adress);
	DDX_Control(pDX, IDOK, Add);
}
BEGIN_MESSAGE_MAP(DIALOG_ADD, CDialogEx)
	/*ON_EN_CHANGE(IDC_NAME_ADD, &DIALOG_ADD::OnEnChangeNameAdd)
	ON_EN_CHANGE(IDC_PHONE_ADD, &DIALOG_ADD::OnEnChangePhoneAdd)
	ON_EN_CHANGE(IDC_SEX_ADD, &DIALOG_ADD::OnEnChangeSexAdd)
	ON_EN_CHANGE(IDC_AGE_ADD, &DIALOG_ADD::OnEnChangeAgeAdd)
	ON_EN_CHANGE(IDC_ADDRESS_ADD, &DIALOG_ADD::OnEnChangeAddressAdd)*/
	ON_BN_CLICKED(IDOK, &DIALOG_ADD::OnBnClickedOk)
END_MESSAGE_MAP()
// DIALOG_ADD 消息处理程序

//修改回车键
void DIALOG_ADD::OnOK()
{
	DIALOG_ADD::OnBnClickedOk();
}
//确定键
void DIALOG_ADD::OnBnClickedOk()
{
	contact TempPerson;
	TempPerson.readedit(Name, Phone, Age ,Sex, Adress);
	int test = List.search(TempPerson.f_name(), TempPerson.f_phonenumber());
	if (TempPerson.f_name() == "\0" || TempPerson.f_phonenumber() == "\0")
	{
		Tip_m(TEXT("请输入完整信息！"));
	}
	else if (test==-1)
	{
		List.input(TempPerson);
		Tip_m(TEXT("新建成功！"));
		OnCancel();
	}
	else
	{
		Tip_m( TEXT("联系人已存在！添加失败！"));
	}
}
