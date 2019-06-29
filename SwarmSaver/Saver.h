// Saver.h : main header file for the SAVER application
//

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CSaverApp:
// See Saver.cpp for the implementation of this class
//

class CSaverApp : public CWinApp
{
public:
	CSaverApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	void DoConfig(CWnd* pParent);

	DECLARE_MESSAGE_MAP()

    CSwarmWindow* m_pSwarm;
};


extern CSaverApp theApp;
