
// SaverDlg.h : header file
//

#pragma once

// CSaverDlg dialog
class CSaverDlg : public CDialogEx
{
    // Construction
public:
    CSaverDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SAVER_DIALOG };
#endif
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

    bool m_bVerifyNumbers;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
    HICON m_hIcon;
    CSwarmWindow m_wndPreview; // don't autodelete

    // Generated message map functions
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
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedDefaults2();
};
