
// MFCApplication1.h: Main header file for the PROJECT_NAME application.
//
// The application object and the two shared helper functions used by the
// dialogs to show a transient message box.

#pragma once

#ifndef __AFXWIN_H__
	#error "Include 'pch.h' before including this file to generate the PCH"
#endif

#include "resource.h"		// Main symbols
#include "SIGNSUCCESS.h"

// Shows a modeless notification dialog that closes itself after three seconds.
//
// The text is assigned both to the member and to the control, because
// DoDataExchange() is not guaranteed to run for a modeless dialog created
// with Create() rather than DoModal().
inline void Tip_s(SIGNSUCCESS& Dialog, CString tip)
{
	Dialog.tip = tip;
	Dialog.Create(IDD_SIGNSUCCEEDED);
	Dialog.ShowWindow(SW_SHOWNORMAL);
	Dialog.Information.SetWindowTextW(tip);
	SetTimer(Dialog, 1, 3000, NULL);
}

// Shows a modal notification dialog that closes itself after three seconds.
inline void Tip_m(CString tip)
{
	SIGNSUCCESS Dialog;
	Dialog.tip = tip;
	Dialog.DoModal();
}

// CMFCApplication1App:
// See MFCApplication1.cpp for the implementation of this class.
class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
