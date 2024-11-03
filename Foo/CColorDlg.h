#pragma once
#include "afxdialogex.h"

class CFooView;


// CColorDlg dialog

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CColorDlg();

	CFooView* m_pView;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLOR_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton m_ColorCtrl;
	afx_msg void OnBnClickedColorDlgBtnApply();
	afx_msg void OnBnClickedMfccolorbutton1();
};
