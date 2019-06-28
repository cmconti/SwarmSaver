// Saver.h : main header file for the SAVER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaverApp:
// See Saver.cpp for the implementation of this class
//

class CSaverApp : public CWinApp
{
public:
	CSaverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaverApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	void DoConfig(CWnd* pParent);

	//{{AFX_MSG(CSaverApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CSwarmWindow* m_pSwarm;
};


/////////////////////////////////////////////////////////////////////////////
