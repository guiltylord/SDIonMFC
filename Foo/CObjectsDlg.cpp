// CLineDlg.cpp: файл реализации
//

#include "pch.h"
#include "Foo.h"
#include "afxdialogex.h"
#include "CObjectsDlg.h"
#include "FooDoc.h"


// Диалоговое окно CLineDlg

IMPLEMENT_DYNAMIC(CObjectsDlg, CDialog)

CObjectsDlg::CObjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OBJECTS_DLG, pParent)
	, m_dCoord(FALSE)
	, m_dSinus(FALSE)
	, m_dStreaks(FALSE)
	, m_dStreaks45(FALSE)
	, m_dBrush(FALSE)
{

}

CObjectsDlg::~CObjectsDlg()
{
}

void CObjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_OBJECTS_DLG_COORDS, m_dCoord);
	DDX_Check(pDX, IDC_OBJECTS_DLG_SINUS, m_dSinus);
	DDX_Check(pDX, IDC_OBJECTS_DLG_STREAKS, m_dStreaks);
	DDX_Check(pDX, IDC_OBJECTS_DLG_STREAKS45, m_dStreaks45);
	DDX_Check(pDX, IDC_OBJECTS_DLG_BRUSH, m_dBrush);
}


BEGIN_MESSAGE_MAP(CObjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK2, &CObjectsDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// Обработчики сообщений CLineDlg


void CObjectsDlg::OnBnClickedCheck2()
{
	// TODO: добавьте свой код обработчика уведомлений
	flag = !flag;

	m_pDoc->m_bStreaks;
}


BOOL CObjectsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(flag);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
