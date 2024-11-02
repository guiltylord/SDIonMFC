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
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
	bool flag;
	virtual BOOL OnInitDialog();

};
