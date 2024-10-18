// CLineDlg.cpp: файл реализации
//

#include "pch.h"
#include "Foo.h"
#include "afxdialogex.h"
#include "CLineDlg.h"
#include "FooDoc.h"


// Диалоговое окно CLineDlg

IMPLEMENT_DYNAMIC(CLineDlg, CDialog)

CLineDlg::CLineDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CLineDlg::~CLineDlg()
{
}

void CLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLineDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK2, &CLineDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// Обработчики сообщений CLineDlg


void CLineDlg::OnBnClickedCheck2()
{
	// TODO: добавьте свой код обработчика уведомлений
	flag != flag;

	m_pDoc->m_bHatch;
}


BOOL CLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(flag);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
