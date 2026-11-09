
// MFCApplication1.cpp: Defines the class behaviour of the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "SIGNSUCCESS.h"
#include "MENU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The single, application wide contact list.
//
// The declaration lives in contact.h and the definition here, so that every
// translation unit shares one instance. Defining it in a header would give
// each translation unit its own copy, which is what the linker used to
// complain about with LNK4006.
ContactList List;

// CMFCApplication1App

BEGIN_MESSAGE_MAP(CMFCApplication1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CMFCApplication1App construction

CMFCApplication1App::CMFCApplication1App()
{
	// Support for the Restart Manager.
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: Add construction code here,
	// place all important initialization in InitInstance
}

// The only CMFCApplication1App object

CMFCApplication1App theApp;

// CMFCApplication1App initialization

BOOL CMFCApplication1App::InitInstance()
{
	freopen("CON", "w", stdout);

	AfxOleInit();
	// If the application manifest of Windows XP specifies ComCtl32.dll
	// version 6 or later to enable visual styles, InitCommonControlsEx()
	// is required. Without it, no window can be created.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Designate the common control classes to use, so the Windows common
	// controls are available to the dialogs.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// Show the sign-in dialog.
	CMFCApplication1Dlg dlg;
	dlg.DoModal();

	// Confirm a successful sign-in.
	SIGNSUCCESS tip;
	Tip_s(tip, TEXT("Signed in! Opening the contact manager......"));

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Create the shell manager in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager* pShellManager = new CShellManager;

	// Activate the "Windows Native" visual manager so that MFC controls
	// use the current Windows theme.
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you do not use these features and want to reduce
	// the size of your executable, remove the following
	// unneeded initialization routines
	// Change the registry key used to store settings
	// TODO: Modify this string to be the company or organization name
	SetRegistryKey(_T("Contact Management System"));

	// Create the main dialog.
	MENU menu;
	m_pMainWnd = &menu;
	INT_PTR nResponse = menu.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is accepted
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is cancelled
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: the dialog failed to create, the application will terminate unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you use MFC controls in the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, FALSE is returned so that the
	// application does not start the application's message pump.
	return FALSE;
}
