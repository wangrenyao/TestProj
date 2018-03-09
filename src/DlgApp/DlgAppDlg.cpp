
// DlgAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgApp.h"
#include "DlgAppDlg.h"
#include "afxdialogex.h"

#include "../dlgAppDll/dlgappdll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDlgAppDlg dialog



CDlgAppDlg::CDlgAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BASE, m_btnBase);
	DDX_Control(pDX, IDC_BUTTON_UP, m_btnUp);
}

BEGIN_MESSAGE_MAP(CDlgAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CDlgAppDlg::OnBnClickedButtonBase)
	ON_BN_CLICKED(IDOK, &CDlgAppDlg::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_UP, &CDlgAppDlg::OnBnClickedButtonUp)
END_MESSAGE_MAP()


// CDlgAppDlg message handlers

BOOL CDlgAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_btnBase.SetButtonName(L"Base");
	//m_btnBase.ModifyStyle(0, WS_CLIPSIBLINGS);
	m_btnBase.SetBkgColor(RGB(100, 200, 0));
	m_btnUp.SetButtonName(L"Up");
	m_btnUp.SetBkgColor(RGB(200, 100, 0));

	m_btnBase.SetWindowPos(&m_btnUp, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);;
	//ModifyStyle(0, WS_CLIPCHILDREN);


	fnDlgAppDll();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}

	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, RGB(240, 240, 240));

	CDC *pDc = GetDC();
	pDc->TextOut(40, 40, L"This is TextOut String!");



	WCHAR szBuf[512];
	LARGE_INTEGER llCounter;

	ZeroMemory(szBuf, sizeof(szBuf));
	QueryPerformanceCounter(&llCounter);

	wsprintf(szBuf, L"Dialog	%IA64d\n", llCounter.QuadPart);
	OutputDebugString(szBuf);

	//RedrawWindow(0, 0, RDW_UPDATENOW);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlgAppDlg::OnBnClickedButtonBase()
{
	// TODO: Add your control notification handler code here
	MessageBox(L"Button Base clicked!");
}


void CDlgAppDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();


	//RedrawWindow(0, 0, RDW_UPDATENOW);

	Invalidate(TRUE);
	UpdateWindow();
}


BOOL CDlgAppDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	OutputDebugString(L"CDlgAppDlg::OnEraseBkgnd called.\n");
	//return CDialogEx::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(150, 150, 0));


	return TRUE;
}


void CDlgAppDlg::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here

	MessageBox(L"Button Up clicked!");
}
