// Saverdlg.cpp : implementation file
//

#include "stdafx.h"
#include "drawwnd.h"
#include "Saver.h"
#include "Saverdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	// TODO: Add extra about dlg initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CSaverDlg dialog

CSaverDlg::CSaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaverDlg::IDD, pParent), m_wndPreview(true)
{
	//{{AFX_DATA_INIT(CSaverDlg)
	m_TrailLength = 30;
	m_bShowWasp = FALSE;
	m_bShowTrails = FALSE;
	m_NumBees = 10;
	m_WaspVelText = _T("");
	m_BeeVelText = _T("");
	m_BeeVel = 25;
	m_WaspVel = 26;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bVerifyNumbers = false;
}

void CSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaverDlg)
	DDX_Control(pDX, IDC_SCROLL_WASP, m_ctrlWaspVel);
	DDX_Control(pDX, IDC_SCROLL_BEE, m_ctrlBeeVel);
	DDX_Control(pDX, IDC_SPIN_TRAILLEN, m_TrailSpinCtrl);
	DDX_Control(pDX, IDC_SPIN_BEES, m_BeesSpinCtrl);
	DDX_Text(pDX, IDC_TRAILLEN, m_TrailLength);
	DDX_Check(pDX, IDC_SHOWWASP, m_bShowWasp);
	DDX_Check(pDX, IDC_SHOWTRAILS, m_bShowTrails);
	DDX_Text(pDX, IDC_NUM_BEES, m_NumBees);
	DDX_Text(pDX, IDC_STATIC_WASP_VELOCITY, m_WaspVelText);
	DDX_Text(pDX, IDC_STATIC_BEE_VELOCITY, m_BeeVelText);
	//}}AFX_DATA_MAP

    if (!pDX->m_bSaveAndValidate)
    {
        if (::IsWindow(m_ctrlBeeVel.m_hWnd)) m_ctrlBeeVel.SetPos(m_BeeVel);
        if (::IsWindow(m_ctrlWaspVel.m_hWnd)) m_ctrlWaspVel.SetPos(m_WaspVel);
    }
    else
    {
        if (::IsWindow(m_ctrlBeeVel.m_hWnd)) m_BeeVel = m_ctrlBeeVel.GetPos();
        if (::IsWindow(m_ctrlWaspVel.m_hWnd)) m_WaspVel = m_ctrlWaspVel.GetPos();
    }

    if (m_bVerifyNumbers)
    {
	    DDV_MinMaxUInt(pDX, m_TrailLength, 1, 60);
	    DDV_MinMaxUInt(pDX, m_NumBees, 10, 100);
    }
}

BEGIN_MESSAGE_MAP(CSaverDlg, CDialog)
	//{{AFX_MSG_MAP(CSaverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_SHOWTRAILS, OnShowtrails)
	ON_BN_CLICKED(IDC_SHOWWASP, OnShowwasp)
	ON_EN_CHANGE(IDC_NUM_BEES, OnChangeNumBees)
	ON_EN_CHANGE(IDC_TRAILLEN, OnChangeTraillen)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_DEFAULTS, OnDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaverDlg message handlers

BOOL CSaverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_PREVIEW)->GetWindowRect(&rect);
	ScreenToClient(&rect);

    m_wndPreview.m_bTrails = m_bShowTrails;
    m_wndPreview.m_bShowWasp = m_bShowWasp;
    m_wndPreview.SetClearTimer(m_TrailLength);
    m_wndPreview.SetNumBees(m_NumBees);
    m_wndPreview.m_wasp_vel = m_WaspVel/2;
    m_wndPreview.m_bee_vel = m_BeeVel/2;

    CWnd* pWnd = (CWnd*)&m_wndPreview;
	pWnd->Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rect, this, 0);

	CenterWindow();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}
	
	// TODO: Add extra initialization here
    m_TrailSpinCtrl.SetRange(1,60);
    m_BeesSpinCtrl.SetRange(10,100);

    m_ctrlBeeVel.SetRange(10,80);
    m_ctrlWaspVel.SetRange(10,80);

    m_ctrlBeeVel.SetPos(m_BeeVel);
    m_ctrlWaspVel.SetPos(m_WaspVel);

    m_BeeVelText.Format("%d",m_BeeVel);
    m_WaspVelText.Format("%d",m_WaspVel);

    UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSaverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSaverDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSaverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSaverDlg::OnAbout() 
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}

void CSaverDlg::OnShowtrails() 
{
    if (m_wndPreview.GetSafeHwnd() != NULL)
    {
        UpdateData(TRUE);
        m_wndPreview.m_bTrails = m_bShowTrails;
        m_wndPreview.Invalidate();
    }
}

void CSaverDlg::OnShowwasp() 
{
    if (m_wndPreview.GetSafeHwnd() != NULL)
    {
        UpdateData(TRUE);
        m_wndPreview.m_bShowWasp = m_bShowWasp;
        m_wndPreview.Invalidate();
    }
}

void CSaverDlg::OnChangeNumBees() 
{
    if (m_wndPreview.GetSafeHwnd() != NULL)
    {
        int oldnum = m_NumBees;
        UpdateData(TRUE);

        if (m_NumBees < 10 || m_NumBees > 100)
            m_NumBees = oldnum;
        m_wndPreview.SetNumBees(m_NumBees);
        m_wndPreview.Invalidate();
    }
}

void CSaverDlg::OnChangeTraillen() 
{
    if (m_wndPreview.GetSafeHwnd() != NULL)
    {
        int oldnum = m_TrailLength;
        UpdateData(TRUE);

        if (m_TrailLength < 1 || m_TrailLength > 60)
            m_TrailLength = oldnum;
        m_wndPreview.SetClearTimer(m_TrailLength);
        m_wndPreview.Invalidate();
    }
}

void CSaverDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    CWnd* pBar = (CWnd*)pScrollBar;
    if (nSBCode == SB_THUMBTRACK)
    {
        if (pBar == &m_ctrlWaspVel)
        {
            m_WaspVelText.Format("%d", nPos);
            m_WaspVel = nPos;
        }
        else if (pBar == &m_ctrlBeeVel)
        {
            m_BeeVelText.Format("%d", nPos);
            m_BeeVel = nPos;
        }

        UpdateData(FALSE);
    }
    else if ( (SB_LINERIGHT == nSBCode) && (m_WaspVel < 80) && (m_BeeVel < 80) )
    {
        if (pBar == &m_ctrlWaspVel)
        {
            m_WaspVel++;
            m_WaspVelText.Format("%d", m_WaspVel);
        }
        else if (pBar == &m_ctrlBeeVel)
        {
            m_BeeVel++;
            m_BeeVelText.Format("%d", m_BeeVel);
        }

        UpdateData(FALSE);
    }
    else if ( (SB_LINELEFT == nSBCode) && (m_WaspVel > 10) && (m_BeeVel > 10) )
    {
        if (pBar == &m_ctrlWaspVel)
        {
            m_WaspVel--;
            m_WaspVelText.Format("%d", m_WaspVel);
        }
        else if (pBar == &m_ctrlBeeVel)
        {
            m_BeeVel--;
            m_BeeVelText.Format("%d", m_BeeVel);
        }

        UpdateData(FALSE);
    }

    m_wndPreview.m_wasp_vel = m_WaspVel/2;
    m_wndPreview.m_bee_vel = m_BeeVel/2;
    m_wndPreview.Invalidate();
    
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSaverDlg::OnDefaults() 
{
    m_bShowTrails = false;
    m_bShowWasp = true;
    m_TrailLength = 30;
    m_NumBees = 10;
    m_WaspVel = 26;
    m_BeeVel = 25;

    m_wndPreview.m_bTrails = m_bShowTrails;
    m_wndPreview.m_bShowWasp = m_bShowWasp;
    m_wndPreview.SetClearTimer(m_TrailLength);
    m_wndPreview.SetNumBees(m_NumBees);
    m_wndPreview.m_wasp_vel = m_WaspVel/2;
    m_wndPreview.m_bee_vel = m_BeeVel/2;
    m_wndPreview.Invalidate();	

    m_ctrlBeeVel.SetPos(m_BeeVel);
    m_ctrlWaspVel.SetPos(m_WaspVel);

    m_BeeVelText.Format("%d",m_BeeVel);
    m_WaspVelText.Format("%d",m_WaspVel);

    UpdateData(FALSE);
}

void CSaverDlg::OnOK() 
{
	m_bVerifyNumbers = true;
	
	CDialog::OnOK();

    m_bVerifyNumbers = false;
}
