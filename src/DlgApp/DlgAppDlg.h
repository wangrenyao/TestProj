
// DlgAppDlg.h : header file
//

#pragma once
#include "MyButton.h"


// CDlgAppDlg dialog
class CDlgAppDlg : public CDialogEx
{
// Construction
public:
	CDlgAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyButton m_btnBase;
	afx_msg void OnBnClickedButtonBase();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CMyButton m_btnUp;
	afx_msg void OnBnClickedButtonUp();
};
