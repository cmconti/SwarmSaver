// SwarmWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwarmWindow window

class CSwarmWindow : public CWnd
{
// Construction
public:
	CSwarmWindow(bool bPreview = false);

// Attributes
public:
    BOOL m_bTrails;     // Erase trails or not
    BOOL m_bShowWasp;
    BOOL m_bFollowPointer; // control wasp with mouse
    int	m_wasp_vel;	    // maximum wasp speed
    int	m_bee_vel;	    // maximum bee speed

// Operations
public:
    void SetClearTimer(int nSeconds);
    void SetNumBees(int numBees);
    //void EscapeToScreen(bool bEscape);

    void Initialize(); //If the window is subclassed instead of Created
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwarmWindow)
	virtual BOOL Create(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwarmWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwarmWindow)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
    HWND m_hWndExplorer;
    void SetSizeData();
    void Find95Desktop();
    void InitMemory();
    void DrawData(bool bEraseOnly = false);

    CBrush m_BkBrush;
    COLORREF m_WaspColor;
    COLORREF m_OldBeeColor;
    CPen m_BlackPen;
    COLORREF m_BeeColor;

    UINT_PTR m_AnimateID;
    UINT_PTR m_ColorID;
    UINT_PTR m_ClearID;

    long m_ClearMS;

    CPoint m_Origin;
    int m_Width;
    int m_Height;

    int	m_times;		// number of time steps recorded 
    int	m_Numbees;		// number of bees
    int	m_wasp_acc;	    // maximum wasp acceleration
    int	m_bee_acc;	    // bee acceleration
    int	m_delay;	    // delay between updates, in milliseconds
    int	m_border;	    // border limiting wasp travel

    DWORD*      m_psegPoints;
    POINT*		segs;		/* bee lines */
    POINT*      old_segs;	/* old bee lines */
    int			*x, *y;		/* bee positions x[time][bee#] */
    int			*xv, *yv;	/* bee velocities xv[bee#] */
    int			wasp_x[3], wasp_y[3];	// wasp positions
    int			wasp_xvel, wasp_yvel;	// wasp velocity
    int			wasp_target_x[3], wasp_target_y[3];	// wasp target positions
    int			wasp_target_xvel, wasp_target_yvel;	// wasp target velocity
    int			dx,dy,distance;
    int			init;

    enum Color
    {
        Red = 0, // 255, 0 , 0
        Yellow = 1, //255, 255, 0
        Green = 2, //0, 255, 0
        Cyan = 3, //0, 255, 255
        Blue = 4, //0, 0, 255
        Magenta = 5 //255, 0, 255
    };

    Color NextColor;

	static LPCTSTR m_lpszClassName;
};

/////////////////////////////////////////////////////////////////////////////
