#include "stdafx.h"

#include "MyButton.h"


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CMyButton::CMyButton()
{
	(*(DWORD*)&m_bkgColor) = 0;

}

CMyButton::~CMyButton()
{

}


VOID CMyButton::OnPaint(VOID)
{
	WCHAR szBuf[512];
	LARGE_INTEGER llCounter;
	
	ZeroMemory(szBuf, sizeof(szBuf));
	QueryPerformanceCounter(&llCounter);

	wsprintf(szBuf, L"CMyButton	%s	%IA64d\n", m_szBtnName, llCounter.QuadPart);
	OutputDebugString(szBuf);


	CButton::OnPaint();
}


void CMyButton::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CButton::OnNcPaint() for painting messages

	return CButton::OnNcPaint();
}


VOID CMyButton::SetBkgColor(IN COLORREF bkgColor)
{
	m_bkgColor = bkgColor;
}

BOOL CMyButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, (COLORREF)m_bkgColor);

	//return CButton::OnEraseBkgnd(pDC);

	return TRUE;
}
