#pragma once


// CMyButton

class CMyButton : public CButton
{
	//DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();


	VOID SetButtonName(IN LPCWSTR szBtnName)
	{
		wcscpy_s(m_szBtnName, _countof(m_szBtnName), szBtnName);
	}

	afx_msg VOID OnPaint(VOID);

protected:
	DECLARE_MESSAGE_MAP()


private:
	WCHAR m_szBtnName[64];
public:
	afx_msg void OnNcPaint();
	
	VOID SetBkgColor(IN COLORREF bkgColor);
	COLORREF m_bkgColor;
	BOOL OnEraseBkgnd(CDC* pDC);
};


