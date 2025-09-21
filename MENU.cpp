// MENU.cpp: 实现文件
//

#include"pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#ifndef MENU_CPP
#define MENU_CPP
#include "MENU.h"
#include"DIALOG_ADD.h"
#include"DIALOG_DETAIL.h"
#include"DIALOG_CODE.h"
#endif
// MENU 对话框

IMPLEMENT_DYNAMIC(MENU, CDialogEx)

MENU::MENU(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENU, pParent)
{
	
}
//析构函数
MENU::~MENU()
{
}

void MENU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_NUMBER, Number);

	//表头
	MENU::m_List.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 60);
	CString Head[2] = { TEXT("姓名"),TEXT("电话") };
	for (int i = 1; i < 3; i++)
		MENU::m_List.InsertColumn(i, Head[i-1], LVCFMT_CENTER, 130);
	//表内
	List.ContactList::ReadContact();//从文件中读取
	List.OutputList(m_List , Number);//输出列表
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//整行选中效果	
}
BEGIN_MESSAGE_MAP(MENU, CDialogEx)
	ON_BN_CLICKED(IDC_DETAIL, &MENU::OnBnClickedDetail)
	ON_BN_CLICKED(IDC_SAVED, &MENU::OnBnClickedSaved)
	ON_BN_CLICKED(IDC_SWEAP, &MENU::OnBnClickedSweap)
	ON_BN_CLICKED(IDC_ADD, &MENU::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_CODE, &MENU::OnBnClickedCode)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &MENU::OnNMClickList2)
END_MESSAGE_MAP()
// MENU 消息处理程序
//添加
void MENU::OnBnClickedAdd()
{
	DIALOG_ADD dlg;
	dlg.DoModal();
	m_List.DeleteAllItems();
	List.OutputList(m_List, Number);
}
//保存
void MENU::OnBnClickedSaved()
{
	List.SaveContact();
	Tip_m(TEXT("保存成功！欢迎下次使用！"));
	exit(0);
}
//详细
void MENU::OnBnClickedDetail()
{
	if (List.position != -1)
	{
		DIALOG_DETAIL dlg;
		dlg.DoModal();
		m_List.DeleteAllItems();
		List.OutputList(m_List , Number);
	}
	else
	{
		Tip_m(TEXT("请选择则联系人！"));
	}
}
//清空
void MENU::OnBnClickedSweap()
{
	if (List.line() == 0)
		Tip_m(TEXT("您还没有联系人！"));
	else
	{
		for (int Order = 0; Order < 1000; Order++)
		{
			List.del(Order);
		}
		Tip_m(TEXT("清空成功！"));
	}
	m_List.DeleteAllItems();
	List.OutputList(m_List, Number);
}

//密码管理
void MENU::OnBnClickedCode()
{
	DIALOG_CODE dlg;
	dlg.DoModal();
}

//光标位置
void MENU::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	List.position=-1;
	POSITION p;
	p = m_List.GetFirstSelectedItemPosition();
	List.position = m_List.GetNextSelectedItem(p);
	*pResult = 0;
}
