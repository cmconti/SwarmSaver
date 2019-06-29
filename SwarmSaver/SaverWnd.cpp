// saverwnd.cpp : implementation file
//

#include "pch.h"
#include "drawwnd.h"
#include "Saver.h"
#include "saverwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaverWnd

CSaverWnd::CSaverWnd()
{
	m_ptLast = CPoint(-1, -1);
}

CSaverWnd::~CSaverWnd()
{
}


BEGIN_MESSAGE_MAP(CSaverWnd, CSwarmWindow)
	//{{AFX_MSG_MAP(CSaverWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_NCACTIVATE()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSaverWnd message handlers

BOOL CSaverWnd::Create() 
{
	//CRect rect(0, 0, ::GetSystemMetrics(SM_CXSCREEN),
	//	::GetSystemMetrics(SM_CYSCREEN));
	CRect rect;
	rect.left = ::GetSystemMetrics(SM_XVIRTUALSCREEN);
	rect.top = ::GetSystemMetrics(SM_YVIRTUALSCREEN);
	rect.right = rect.left + ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
	rect.bottom = rect.top + ::GetSystemMetrics(SM_CYVIRTUALSCREEN);

	return CSwarmWindow::Create(WS_EX_TOPMOST, WS_VISIBLE|WS_POPUP, rect, NULL, 
		0, NULL);
}

void CSaverWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID == SC_SCREENSAVE) || (nID == SC_CLOSE))
		return;
	CSwarmWindow::OnSysCommand(nID, lParam);
}

void CSaverWnd::OnDestroy() 
{
	PostQuitMessage(0);
	CSwarmWindow::OnDestroy();
}

BOOL CSaverWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(NULL);
	return TRUE;
}

BOOL CSaverWnd::OnNcActivate(BOOL bActive) 
{
	if (!bActive)
		return FALSE;
	return CSwarmWindow::OnNcActivate(bActive);
}

void CSaverWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if (nState == WA_INACTIVE)
		PostMessage(WM_CLOSE);
	CSwarmWindow::OnActivate(nState, pWndOther, bMinimized);
}

void CSaverWnd::OnActivateApp(BOOL bActive, DWORD dwThreadID) 
{
	if (!bActive)
		PostMessage(WM_CLOSE);
	CSwarmWindow::OnActivateApp(bActive, dwThreadID);
}

void CSaverWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_ptLast == CPoint(-1,-1))
		m_ptLast = point;
	else if (m_ptLast != point)
		PostMessage(WM_CLOSE);
	CSwarmWindow::OnMouseMove(nFlags, point);
}

void CSaverWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CSwarmWindow::OnLButtonDown(nFlags, point);
}

void CSaverWnd::OnMButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CSwarmWindow::OnMButtonDown(nFlags, point);
}

void CSaverWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CSwarmWindow::OnRButtonDown(nFlags, point);
}

void CSaverWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	PostMessage(WM_CLOSE);
	CSwarmWindow::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSaverWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	PostMessage(WM_CLOSE);
	CSwarmWindow::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
