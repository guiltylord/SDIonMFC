#pragma once
#include "afxdialogex.h"

class CFooDoc;

// Диалоговое окно CLineDlg

class CObjectsDlg : public CDialog
{
	DECLARE_DYNAMIC(CObjectsDlg)

public:
	CObjectsDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CObjectsDlg();

	CFooDoc* m_pDoc;


// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
	bool flag;
	virtual BOOL OnInitDialog();

	BOOL m_dCoord;
	BOOL m_dSinus;
	BOOL m_dStreaks;
	BOOL m_dStreaks45;
	BOOL m_dBrush;
};
