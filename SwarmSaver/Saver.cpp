// Saver.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "SwarmWindow.h"
#include "Saver.h"
#include "SaverDlg.h"
#include "SaverWnd.h"

#ifdef _DEBUG
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaverApp

BEGIN_MESSAGE_MAP(CSaverApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

TCHAR szConfig[]=_T("Config");
ULONG_PTR           gdiplusToken;

/////////////////////////////////////////////////////////////////////////////
// CSaverApp construction

CSaverApp::CSaverApp()
{
    m_pSwarm = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSaverApp object

CSaverApp theApp;

BOOL MatchOption(LPTSTR lpsz, LPTSTR lpszOption)
{
    if (lpsz != NULL)
    {
	    if (lpsz[0] == _T('-') || lpsz[0] == _T('/'))
		    lpsz++;
	    if (lstrcmpi(lpsz, lpszOption) == 0)
		    return TRUE;
    }
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSaverApp initialization

BOOL CSaverApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetRegistryKey(_T("PretzelSoft"));

    GdiplusStartupInput gdiplusStartupInput;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //this is necessary because the application may be launched with an 8.3 module name
    BOOL bEnable = AfxEnableMemoryTracking(FALSE);
	free((void*)m_pszProfileName);
	m_pszProfileName = _tcsdup(_T("SwarmSaver"));
	AfxEnableMemoryTracking(bEnable);

    TRACE(_T("arg 1 = %s\n"), __targv[1]);

	if (__argc == 1 || MatchOption(__targv[1], _T("c")))
		DoConfig(CWnd::GetActiveWindow());
    else if ( (__targv[1][1] == _T('c') || __targv[1][1] == _T('C')) && __targv[1][2] == _T(':'))
    {
#ifdef _WIN64
        HWND hWndParent = (HWND)_ttoll(__targv[1] + 3);
#else
        HWND hWndParent = (HWND)_ttol(__targv[1] + 3);
#endif
        CWnd wndParent;
        wndParent.Attach(hWndParent);
        DoConfig(&wndParent);
        wndParent.Detach();
    }
	else if (MatchOption(__targv[1], _T("p")))
	{
#ifdef _WIN64
        CWnd* pParent = CWnd::FromHandle((HWND)_ttoll(__targv[2]));
#else
        CWnd* pParent = CWnd::FromHandle((HWND)_ttol(__targv[2]));
#endif
		ASSERT(pParent != NULL);
		m_pSwarm = new CSwarmWindow(true);

        int numbees = GetProfileInt(szConfig, _T("NumBees"), 10);
        int trailtime = GetProfileInt(szConfig, _T("TrailTime"), 30);
	    m_pSwarm->SetNumBees(numbees);
	    m_pSwarm->m_bShowWasp = GetProfileInt(szConfig, _T("ShowWasp"), 1);
	    m_pSwarm->m_bTrails = GetProfileInt(szConfig, _T("ShowTrails"), 0);
	    m_pSwarm->SetClearTimer(trailtime);
	    m_pSwarm->m_bee_vel = (GetProfileInt(szConfig, _T("BeeVelocity"), 25))/2;
	    m_pSwarm->m_wasp_vel = (GetProfileInt(szConfig, _T("WaspVelocity"), 26))/2;

        CRect rect;
		pParent->GetClientRect(&rect);
        CWnd* pWnd = (CWnd*)m_pSwarm;
	    pWnd->Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rect, pParent, 0);

		m_pMainWnd = m_pSwarm;
		return TRUE;
	}
	else if (MatchOption(__targv[1], _T("s")))
	{
		CSaverWnd* pWnd = new CSaverWnd;

        int numbees = GetProfileInt(szConfig, _T("NumBees"), 10);
        int trailtime = GetProfileInt(szConfig, _T("TrailTime"), 30);
	    pWnd->SetNumBees(numbees);
	    pWnd->m_bShowWasp = GetProfileInt(szConfig, _T("ShowWasp"), 1);
	    pWnd->m_bTrails = GetProfileInt(szConfig, _T("ShowTrails"), 0);
	    pWnd->SetClearTimer(trailtime);
	    pWnd->m_bee_vel = GetProfileInt(szConfig, _T("BeeVelocity"), 25);
	    pWnd->m_wasp_vel = GetProfileInt(szConfig, _T("WaspVelocity"), 26);

		pWnd->Create();
		m_pMainWnd = pWnd;
        m_pSwarm = pWnd;
		return TRUE;
	}
	return FALSE;
}

int CSaverApp::ExitInstance() 
{
	if (m_pSwarm != NULL)
        delete m_pSwarm;
	
    GdiplusShutdown(gdiplusToken);

	return CWinApp::ExitInstance();
}

void CSaverApp::DoConfig(CWnd* pParent)
{
	CSaverDlg dlg(pParent);

	dlg.m_NumBees = GetProfileInt(szConfig, _T("NumBees"), 10);
	dlg.m_bShowWasp = GetProfileInt(szConfig, _T("ShowWasp"), 1);
	dlg.m_bShowTrails = GetProfileInt(szConfig, _T("ShowTrails"), 0);
	dlg.m_TrailLength = GetProfileInt(szConfig, _T("TrailTime"), 30);
    dlg.m_BeeVel = GetProfileInt(szConfig, _T("BeeVelocity"), 25);
    dlg.m_WaspVel = GetProfileInt(szConfig, _T("WaspVelocity"), 26);

    m_pMainWnd = &dlg;
	if (dlg.DoModal() == IDOK)
	{
        WriteProfileInt(szConfig, _T("NumBees"), dlg.m_NumBees);
        WriteProfileInt(szConfig, _T("ShowWasp"), dlg.m_bShowWasp);
        WriteProfileInt(szConfig, _T("ShowTrails"), dlg.m_bShowTrails);
        WriteProfileInt(szConfig, _T("TrailTime"), dlg.m_TrailLength);
        WriteProfileInt(szConfig, _T("BeeVelocity"), dlg.m_BeeVel);
        WriteProfileInt(szConfig, _T("WaspVelocity"), dlg.m_WaspVel);
	}
}
