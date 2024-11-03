// CColorDlg.cpp : implementation file
//

#include "pch.h"
#include "Foo.h"
#include "afxdialogex.h"
#include "CColorDlg.h"
#include "FooView.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_COLOR_DLG, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorCtrl);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_BN_CLICKED(IDC_COLOR_DLG_BTN_APPLY, &CColorDlg::OnBnClickedColorDlgBtnApply)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CColorDlg::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// CColorDlg message handlers


void CColorDlg::OnBnClickedColorDlgBtnApply()
{
	// TODO: Add your control notification handler code here
}


void CColorDlg::OnBnClickedMfccolorbutton1()
{
	m_pView->m_Color = m_ColorCtrl.GetColor();

	m_pView->Invalidate();
}
