// CMyTreeview.cpp: файл реализации
//

#include "pch.h"
#include "Foo.h"
#include "CMyTreeview.h"


// CMyTreeview

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
END_MESSAGE_MAP()




// Диагностика CMyTreeview

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}


#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeview

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hCoord = tree.InsertItem(L"Систем коорд", -1, -1, NULL, TVI_FIRST);
	m_hSinus = tree.InsertItem(L"Синус", -1, -1, NULL, TVI_ROOT);
	m_hHatch = tree.InsertItem(L"Штриховка", -1, -1, NULL, TVI_ROOT);
	

}

int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES
		| TVS_HASBUTTONS
		| TVS_LINESATROOT
		| TVS_SHOWSELALWAYS
		| TVS_CHECKBOXES;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}
