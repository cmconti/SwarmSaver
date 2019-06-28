// Saverdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaverDlg dialog

class CSaverDlg : public CDialog
{
// Construction
public:
	CSaverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSaverDlg)
	enum { IDD = IDD_SAVER_DIALOG };
	CSliderCtrl	m_ctrlBeeVel;
	CSliderCtrl	m_ctrlWaspVel;
	CSpinButtonCtrl	m_TrailSpinCtrl;
	CSpinButtonCtrl	m_BeesSpinCtrl;
	UINT	m_TrailLength;
	BOOL	m_bShowWasp;
	BOOL	m_bShowTrails;
	UINT	m_NumBees;
	CString	m_WaspVelText;
	CString	m_BeeVelText;
	int		m_BeeVel;
	int		m_WaspVel;
	//}}AFX_DATA

    bool m_bVerifyNumbers;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSwarmWindow m_wndPreview; // don't autodelete

	// Generated message map functions
	//{{AFX_MSG(CSaverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnShowtrails();
	afx_msg void OnShowwasp();
	afx_msg void OnChangeNumBees();
	afx_msg void OnChangeTraillen();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDefaults();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
