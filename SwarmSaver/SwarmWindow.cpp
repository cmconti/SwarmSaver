// SwarmWindow.cpp : implementation file
//

#include "pch.h"
#include "SwarmWindow.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define X(t,b)	(x[t*m_Numbees + b])		/* addressing into dynamic array */
#define Y(t,b)	(y[t*m_Numbees + b])		/* addressing into dynamic array */
#define RAND(v)	((rand() % v) - (v/2)) /* random number around 0 */

LPCTSTR CSwarmWindow::m_lpszClassName = NULL;

/////////////////////////////////////////////////////////////////////////////
// CSwarmWindow

CSwarmWindow::CSwarmWindow(bool bPreview /*= false*/) : m_BkBrush(RGB(0, 0, 0)), m_WaspColor(RGB(255, 255, 255)),
m_BeeColor(RGB(254, 254, 0)), m_OldBeeColor(RGB(254, 254, 0)), m_BlackPen(PS_SOLID, 1, COLORREF(0))
{
    m_AnimateID = 0;
    m_ColorID = 0;
    m_ClearID = 0;

    m_times = 3;
    m_Numbees = 100;
    m_wasp_acc = 5;//5
    m_bee_acc = 5;//3
    m_ClearMS = 60000;
    if (bPreview)
    {
        m_wasp_vel = 13;//12
        m_bee_vel = 12;//11
        m_delay = 45;
        m_border = 5;
    }
    else
    {
        m_wasp_vel = 26;//12
        m_bee_vel = 25;//11
        m_delay = 15;
        m_border = 50;
    }

    m_bFollowPointer = FALSE;
    NextColor = Green;
    m_bTrails = TRUE;
    m_bShowWasp = FALSE;
}

CSwarmWindow::~CSwarmWindow()
{
}

BEGIN_MESSAGE_MAP(CSwarmWindow, CWnd)
    //{{AFX_MSG_MAP(CSwarmWindow)
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwarmWindow message handlers

int CSwarmWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    Initialize();

    return 0;
}

void CSwarmWindow::Initialize()
{
    // Get the random number generator ready.
    srand((UINT)time(NULL));
    init = TRUE;

    SetSizeData();

    Find95Desktop();

    m_AnimateID = SetTimer(1, m_delay, NULL);
    m_ColorID = SetTimer(2, 20, NULL);
    m_ClearID = SetTimer(3, m_ClearMS, NULL);
}

void CSwarmWindow::SetSizeData()
{
    CRect rectWin;
    GetClientRect(&rectWin);
    ClientToScreen(&rectWin);

    m_Width = rectWin.Width();
    m_Height = rectWin.Height();
}

void CSwarmWindow::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    SetSizeData();
}

BOOL CSwarmWindow::OnEraseBkgnd(CDC* pDC)
{
    // Save the old brush
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&m_BkBrush);

    // Get the current clipping boundary
    CRect rect;
    GetClientRect(&rect);

    // Erase the area needed
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),
        PATCOPY);

    pDC->SelectObject(pOldBrush); // Select the old brush back
    return FALSE;  // message handled
}

void CSwarmWindow::OnDestroy()
{
    KillTimer(m_AnimateID);
    KillTimer(m_ColorID);

    free(m_psegPoints);
    free(segs);
    free(old_segs);
    free(x);
    free(y);
    free(xv);
    free(yv);

    CWnd::OnDestroy();
}
void CSwarmWindow::Find95Desktop()
{
    m_hWndExplorer = ::GetDesktopWindow();

    HWND hProgman = ::FindWindowEx(::GetDesktopWindow(), NULL, _T("Progman"), NULL);
    if (hProgman != NULL)
    {
        HWND hShellDLL = ::FindWindowEx(hProgman, NULL, _T("SHELLDLL_DefView"), NULL);
        if (hShellDLL != NULL)
        {
            HWND hSysList = ::FindWindowEx(hShellDLL, NULL, _T("SysListView32"), NULL);
            if (hSysList != NULL)
                m_hWndExplorer = hSysList;
        }
    }
}

void CSwarmWindow::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == m_AnimateID)
    {
        if (init)
        {
            InitMemory();
        }
        else
        {
            // Make sure the wasp is within the window.
            //if (wasp_x[0] < m_border) wasp_x[0] = m_border;
            //if (wasp_x[0] > m_Width-m_border-1) wasp_x[0] = m_Width-m_border-1;
            //if (wasp_y[0] < m_border) wasp_y[0] = m_border;
            //if (wasp_y[0] > m_Height-m_border-1) wasp_y[0] = m_Height-m_border-1;
        }

        // <=- Wasp -=>
        // Age the position arrays.
        wasp_x[2] = wasp_x[1];
        wasp_x[1] = wasp_x[0];
        wasp_y[2] = wasp_y[1];
        wasp_y[1] = wasp_y[0];

        wasp_target_x[2] = wasp_target_x[1];
        wasp_target_x[1] = wasp_target_x[0];
        wasp_target_y[2] = wasp_target_y[1];
        wasp_target_y[1] = wasp_target_y[0];

        if (m_bFollowPointer)
        {
            POINT mousept;
            GetCursorPos(&mousept);
            ScreenToClient(&mousept);
            wasp_x[0] = mousept.x;
            wasp_y[0] = mousept.y;

            // Position Checks
            if (wasp_x[0] < m_border)
            {
                wasp_x[0] = m_border;
            }
            if (wasp_x[0] > m_Width - m_border - 1)
            {
                wasp_x[0] = m_Width - m_border - 1;
            }
            if (wasp_y[0] < m_border)
            {
                wasp_y[0] = m_border;
            }
            if (wasp_y[0] > m_Height - m_border - 1)
            {
                wasp_y[0] = m_Height - m_border - 1;
            }
        }
        else
        {
            // Accelerate
            wasp_xvel += RAND(m_wasp_acc);
            wasp_yvel += RAND(m_wasp_acc);

            // Speed Limit Checks
            if (wasp_xvel > m_wasp_vel) wasp_xvel = m_wasp_vel;
            if (wasp_xvel < -m_wasp_vel) wasp_xvel = -m_wasp_vel;
            if (wasp_yvel > m_wasp_vel) wasp_yvel = m_wasp_vel;
            if (wasp_yvel < -m_wasp_vel) wasp_yvel = -m_wasp_vel;

            // Move
            wasp_x[0] = wasp_x[1] + wasp_xvel;
            wasp_y[0] = wasp_y[1] + wasp_yvel;

            // Bounce Checks
            if ((wasp_x[0] < m_border) || (wasp_x[0] > m_Width - m_border - 1))
            {
                wasp_xvel = -wasp_xvel;
                wasp_x[0] += wasp_xvel << 1;
            }
            if ((wasp_y[0] < m_border) || (wasp_y[0] > m_Height - m_border - 1))
            {
                wasp_yvel = -wasp_yvel;
                wasp_y[0] += wasp_yvel << 1;
            }
            /*
            //move the target
            // Accelerate
            wasp_target_xvel += RAND(m_wasp_acc);
            wasp_target_yvel += RAND(m_wasp_acc);

            // Speed Limit Checks
            if (wasp_target_xvel > (m_wasp_vel/2)) wasp_target_xvel = (m_wasp_vel/2);
            if (wasp_target_xvel < (-m_wasp_vel/2)) wasp_target_xvel = (-m_wasp_vel/2);
            if (wasp_target_yvel > (m_wasp_vel/2)) wasp_target_yvel = (m_wasp_vel/2);
            if (wasp_target_yvel < (-m_wasp_vel/2)) wasp_target_yvel = (-m_wasp_vel/2);

            // Move
            wasp_target_x[0] = wasp_target_x[1] + wasp_target_xvel;
            wasp_target_y[0] = wasp_target_y[1] + wasp_target_yvel;

            // Bounce Checks
            if ((wasp_target_x[0] < m_border*2) || (wasp_target_x[0] > m_Width-(m_border*2)-1))
            {
            wasp_target_xvel = -wasp_target_xvel;
            wasp_target_x[0] += wasp_target_xvel<<1;
            }
            if ((wasp_target_y[0] < m_border*2) || (wasp_target_y[0] > m_Height-(m_border*2)-1))
            {
            wasp_target_yvel = -wasp_target_yvel;
            wasp_target_y[0] += wasp_target_yvel<<1;
            }

            //move the wasp
            // Accelerate
            dx = wasp_target_x[1] - wasp_x[1];
            dy = wasp_target_y[1] - wasp_y[1];
            distance = abs(dx)+abs(dy); // approximation
            if (distance == 0) distance = 1;
            wasp_xvel += (dx*m_wasp_acc)/distance;
            wasp_yvel += (dy*m_wasp_acc)/distance;

            // Speed Limit Checks
            if (wasp_xvel > m_wasp_vel) wasp_xvel = m_wasp_vel;
            if (wasp_xvel < -m_wasp_vel) wasp_xvel = -m_wasp_vel;
            if (wasp_yvel > m_wasp_vel) wasp_yvel = m_wasp_vel;
            if (wasp_yvel < -m_wasp_vel) wasp_yvel = -m_wasp_vel;

            // Move
            wasp_x[0] = wasp_x[1] + wasp_xvel;
            wasp_y[0] = wasp_y[1] + wasp_yvel;
            */
        }

        /* Don't let things settle down. */
        xv[rand() % m_Numbees] += RAND(m_bee_acc + m_bee_acc / 2);
        yv[rand() % m_Numbees] += RAND(m_bee_acc + m_bee_acc / 2);

        /* <=- Bees -=> */
        for (int b = 0; b < m_Numbees; b++)
        {
            /* Age the arrays. */
            X(2, b) = X(1, b);
            X(1, b) = X(0, b);
            Y(2, b) = Y(1, b);
            Y(1, b) = Y(0, b);

            /* Accelerate */
            dx = wasp_x[1] - X(1, b);
            dy = wasp_y[1] - Y(1, b);
            distance = abs(dx) + abs(dy); /* approximation */
            if (distance == 0) distance = 1;
            xv[b] += (dx * m_bee_acc) / distance;
            yv[b] += (dy * m_bee_acc) / distance;

            /* Speed Limit Checks */
            if (xv[b] > m_bee_vel) xv[b] = m_bee_vel;
            if (xv[b] < -m_bee_vel) xv[b] = -m_bee_vel;
            if (yv[b] > m_bee_vel) yv[b] = m_bee_vel;
            if (yv[b] < -m_bee_vel) yv[b] = -m_bee_vel;

            /* Move */
            X(0, b) = X(1, b) + xv[b];
            Y(0, b) = Y(1, b) + yv[b];

            /* Fill the segment lists. */
            segs[b * 2].x = X(0, b);
            segs[b * 2].y = Y(0, b);
            segs[b * 2 + 1].x = X(1, b);
            segs[b * 2 + 1].y = Y(1, b);
            old_segs[b * 2].x = X(1, b);
            old_segs[b * 2].y = Y(1, b);
            old_segs[b * 2 + 1].x = X(2, b);
            old_segs[b * 2 + 1].y = Y(2, b);
        }

        DrawData();

        init = FALSE;
    }

    if (nIDEvent == m_ColorID)
    {
        m_OldBeeColor = m_BeeColor;
        BYTE RedValue = GetRValue(m_BeeColor);
        BYTE GreenValue = GetGValue(m_BeeColor);
        BYTE BlueValue = GetBValue(m_BeeColor);

        switch (NextColor)
        {
        case Red:
            BlueValue -= 2;
            break;
        case Yellow:
            GreenValue += 2;
            break;
        case Green:
            RedValue -= 2;
            break;
        case Cyan:
            BlueValue += 2;
            break;
        case Blue:
            GreenValue -= 2;
            break;
        case Magenta:
            RedValue += 2;
            break;
        }

        if ((NextColor == Red) && (BlueValue == 0))
            NextColor = Yellow;
        else if ((NextColor == Yellow) && (GreenValue == 254))
            NextColor = Green;
        else if ((NextColor == Green) && (RedValue == 0))
            NextColor = Cyan;
        else if ((NextColor == Cyan) && (BlueValue == 254))
            NextColor = Blue;
        else if ((NextColor == Blue) && (GreenValue == 0))
            NextColor = Magenta;
        else if ((NextColor == Magenta) && (RedValue == 254))
            NextColor = Red;

        m_BeeColor = RGB(RedValue, GreenValue, BlueValue);
    }

    if (nIDEvent == m_ClearID)
    {
        Invalidate();
    }

    CWnd::OnTimer(nIDEvent);
}

void CSwarmWindow::DrawData(bool bEraseOnly /*= false*/)
{
    if (m_hWnd != NULL)
    {
        HDC hdcScreen = NULL;

        CDC* pDC = new CWindowDC(this);

        CPen* pOldPen;
        CPen WaspPen(PS_SOLID, 1, m_WaspColor);
        CPen BeePenOldColor(PS_SOLID, 1, m_OldBeeColor);
        CPen BeePen(PS_SOLID, 1, m_BeeColor);

        bool bUseGDI = m_bShowWasp || !m_bTrails;

        // Erase previous, draw current.

        // Wasp
        pOldPen = (CPen*)pDC->SelectObject(&m_BlackPen);

        if (!m_bFollowPointer && m_bShowWasp)
        {
            if (init == FALSE)
            {
                //erase old line
                if (!bEraseOnly)
                {
                    pDC->MoveTo(wasp_x[1], wasp_y[1]);
                    pDC->LineTo(wasp_x[2], wasp_y[2]);
                }
                else
                {
                    pDC->MoveTo(wasp_x[0], wasp_y[0]);
                    pDC->LineTo(wasp_x[1], wasp_y[1]);
                }
            }

            if (!bEraseOnly)
            {
                pDC->SelectObject(&WaspPen);

                pDC->MoveTo(wasp_x[0], wasp_y[0]);
                pDC->LineTo(wasp_x[1], wasp_y[1]);
            }
        }

        // Bees
        pDC->SelectObject(&m_BlackPen);

        if (init == FALSE && !m_bTrails)
        {
            //erase old lines
            if (!bEraseOnly)
            {
                pDC->PolyPolyline(old_segs, m_psegPoints, m_Numbees);
            }
            else
            {
                pDC->PolyPolyline(segs, m_psegPoints, m_Numbees);
            }
        }

        if (!bEraseOnly)
        {
            //GDI
            if (bUseGDI)
            {
                pDC->SelectObject(&BeePen);
                pDC->PolyPolyline(segs, m_psegPoints, m_Numbees);
            }
            else //GDI+
            {
                Graphics graphics(*pDC);
                graphics.SetSmoothingMode(SmoothingModeAntiAlias);

                BYTE r = GetRValue(m_BeeColor);
                BYTE g = GetGValue(m_BeeColor);
                BYTE b = GetBValue(m_BeeColor);

                Gdiplus::Color argb(255, r, g, b);
                Pen pen(argb);
                for (int idx = 0; idx < m_Numbees; idx++)
                {
                    Point pt[2] =
                    {
                        *reinterpret_cast<Point*>(segs + (idx * 2)),
                        *reinterpret_cast<Point*>(segs + (idx * 2) + 1),
                    };
                    graphics.DrawLines(&pen, pt, 2);
                }
            }
        }

        // Clean up.
        pDC->SelectObject(pOldPen);

        delete pDC;
    }
}

BOOL CSwarmWindow::Create(DWORD dwExStyle, DWORD dwStyle, const RECT& rect,
    CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    // Register a class with no cursor
    if (m_lpszClassName == NULL)
    {
        m_lpszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
            ::LoadCursor(AfxGetResourceHandle(),
                MAKEINTRESOURCE(IDC_NULLCURSOR)));
    }

    // TODO: Add your specialized code here and/or call the base class
    return CreateEx(dwExStyle, m_lpszClassName, _T(""), dwStyle,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
        pParentWnd->GetSafeHwnd(), NULL, NULL);
}

void CSwarmWindow::SetClearTimer(int nSeconds)
{
    m_ClearMS = 1000;
    if (nSeconds > 60)
        m_ClearMS = 60000;
    else if (nSeconds > 1)
        m_ClearMS = nSeconds * 1000;

    if (m_hWnd != NULL)
    {
        KillTimer(m_ClearID);
        m_ClearID = SetTimer(3, m_ClearMS, NULL);
    }
}

void CSwarmWindow::SetNumBees(int numBees)
{
    if (m_hWnd != NULL)
    {
        if (numBees != m_Numbees)
        {
            DrawData(true);

            m_Numbees = numBees;

            free(m_psegPoints);
            free(segs);
            free(old_segs);
            free(x);
            free(y);
            free(xv);
            free(yv);

            init = TRUE;
        }
    }
    else
    {
        m_Numbees = numBees;
    }
}

void CSwarmWindow::InitMemory()
{
    /* Allocate memory. */
    m_psegPoints = (DWORD*)malloc(sizeof(DWORD) * m_Numbees);
    segs = (POINT*)malloc(sizeof(POINT) * m_Numbees * 2);
    old_segs = (POINT*)malloc(sizeof(POINT) * m_Numbees * 2);
    x = (int*)malloc(sizeof(int) * m_Numbees * m_times);
    y = (int*)malloc(sizeof(int) * m_Numbees * m_times);
    xv = (int*)malloc(sizeof(int) * m_Numbees);
    yv = (int*)malloc(sizeof(int) * m_Numbees);

    // Initialize point positions, velocities, etc.

    // wasp
    if (m_bFollowPointer)
    {
        POINT mousept;
        GetCursorPos(&mousept);
        ScreenToClient(&mousept);
        wasp_x[0] = mousept.x;
        wasp_y[0] = mousept.y;

        // Position Checks
        if (wasp_x[0] < m_border)
        {
            wasp_x[0] = m_border;
        }
        if (wasp_x[0] > m_Width - m_border - 1)
        {
            wasp_x[0] = m_Width - m_border - 1;
        }
        if (wasp_y[0] < m_border)
        {
            wasp_y[0] = m_border;
        }
        if (wasp_y[0] > m_Height - m_border - 1)
        {
            wasp_y[0] = m_Height - m_border - 1;
        }
    }
    else
    {
        wasp_x[0] = m_border + rand() % (m_Width - 2 * m_border);
        wasp_y[0] = m_border + rand() % (m_Height - 2 * m_border);
    }
    wasp_x[1] = wasp_x[0];
    wasp_y[1] = wasp_y[0];
    wasp_xvel = 0;
    wasp_yvel = 0;

    //target properties
    wasp_target_x[1] = wasp_target_x[0] = wasp_x[0];
    wasp_target_y[1] = wasp_target_y[0] = wasp_y[0];
    wasp_target_xvel = 0;
    wasp_target_yvel = 0;

    /* bees */
    for (int b = 0; b < m_Numbees; b++)
    {
        m_psegPoints[b] = 2;
        X(0, b) = rand() % m_Width;
        X(1, b) = X(0, b);
        Y(0, b) = rand() % m_Height;
        Y(1, b) = Y(0, b);
        xv[b] = RAND(7);
        yv[b] = RAND(7);
    }
}
