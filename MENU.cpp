
// MENU.cpp: Implementation file for the main menu dialog.
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#ifndef MENU_CPP
#define MENU_CPP
#include "MENU.h"
#include "DIALOG_ADD.h"
#include "DIALOG_DETAIL.h"
#include "DIALOG_CODE.h"
#endif
// MENU dialog

IMPLEMENT_DYNAMIC(MENU, CDialogEx)

MENU::MENU(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENU, pParent)
{
}

MENU::~MENU()
{
}

void MENU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_NUMBER, Number);

	// Column headers
	MENU::m_List.InsertColumn(0, TEXT("No."), LVCFMT_CENTER, 60);
	CString Head[2] = { TEXT("Name"), TEXT("Phone") };
	for (int i = 1; i < 3; i++)
		MENU::m_List.InsertColumn(i, Head[i - 1], LVCFMT_CENTER, 130);
	// Rows
	List.ContactList::ReadContact();	// Load the contacts from the file
	List.OutputList(m_List, Number);	// Fill the list
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// Full row selection
}
BEGIN_MESSAGE_MAP(MENU, CDialogEx)
	ON_BN_CLICKED(IDC_DETAIL, &MENU::OnBnClickedDetail)
	ON_BN_CLICKED(IDC_SAVED, &MENU::OnBnClickedSaved)
	ON_BN_CLICKED(IDC_SWEAP, &MENU::OnBnClickedSweap)
	ON_BN_CLICKED(IDC_ADD, &MENU::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_CODE, &MENU::OnBnClickedCode)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &MENU::OnNMClickList2)
END_MESSAGE_MAP()
// MENU message handlers

// Add a contact
void MENU::OnBnClickedAdd()
{
	DIALOG_ADD dlg;
	dlg.DoModal();
	m_List.DeleteAllItems();
	List.OutputList(m_List, Number);
}

// Save and exit
void MENU::OnBnClickedSaved()
{
	if (!List.SaveContact())
	{
		Tip_m(TEXT("Save failed. The contact list could not be written to contact.txt."));
		return;
	}
	Tip_m(TEXT("Saved. See you next time!"));
	CDialogEx::OnCancel();
}

// View, modify or delete a contact
void MENU::OnBnClickedDetail()
{
	if (List.position == -1)
	{
		Tip_m(TEXT("Please select a contact first!"));
		return;
	}
	DIALOG_DETAIL dlg;
	dlg.DoModal();
	m_List.DeleteAllItems();
	List.OutputList(m_List, Number);
}

// Delete all contacts
void MENU::OnBnClickedSweap()
{
	if (List.line() == 0)
	{
		Tip_m(TEXT("There are no contacts yet!"));
	}
	else
	{
		for (int Order = 0; Order < 1000; Order++)
		{
			List.del(Order);
		}
		Tip_m(TEXT("All contacts deleted!"));
	}
	m_List.DeleteAllItems();
	List.OutputList(m_List, Number);
}

// Password management
void MENU::OnBnClickedCode()
{
	DIALOG_CODE dlg;
	dlg.DoModal();
}

// Records the row the user clicked
void MENU::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	List.position = -1;
	POSITION p;
	p = m_List.GetFirstSelectedItemPosition();
	if (p != nullptr)
		List.position = m_List.GetNextSelectedItem(p);
	*pResult = 0;
}
