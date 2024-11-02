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
	: CDialog(IDD_DIALOG1, pParent)
{

}

CObjectsDlg::~CObjectsDlg()
{
}

void CObjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
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
