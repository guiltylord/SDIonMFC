// CMyTreeview.cpp: файл реализации
//

#include "pch.h"
#include "Foo.h"
#include "CMyTreeview.h"
#include "Fooview.h"
#include "FooDoc.h"


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
	ON_WM_LBUTTONDOWN()
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
	m_hMain = tree.InsertItem(L"Дерево построений", -1, -1, NULL, TVI_FIRST);

	m_hCoord = tree.InsertItem(L"Систем коорд", -1, -1, m_hMain, TVI_FIRST);
	m_hSinus = tree.InsertItem(L"Синус", -1, -1, m_hMain, TVI_ROOT);
	m_hHatch = tree.InsertItem(L"Штриховка", -1, -1, m_hMain, TVI_ROOT);
	m_hStreaks45 = tree.InsertItem(L"45", -1, -1, m_hMain, TVI_ROOT);
	m_hBrush = tree.InsertItem(L"Bruh", -1, -1, m_hMain, TVI_ROOT);
	
	tree.Expand(m_hMain, TVE_EXPAND);

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


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	//CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	CTreeView::OnLButtonDown(nFlags, point);

	CRect rc;/*
	tree.GetItemRect(m_hCoord, &rc, false);*/

	if (rc.PtInRect(point))
		tree.SelectItem(m_hCoord);
	tree.GetItemRect(m_hCoord, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hSinus);
	tree.GetItemRect(m_hSinus, &rc, false);

	if (rc.PtInRect(point))
		tree.SelectItem(m_hHatch);
	tree.GetItemRect(m_hHatch, &rc, false);
	
	if (rc.PtInRect(point))
		tree.SelectItem(m_hStreaks45);
	tree.GetItemRect(m_hStreaks45, &rc, false);
	
	if (rc.PtInRect(point))
		tree.SelectItem(m_hBrush);
	tree.GetItemRect(m_hBrush, &rc, false);


	if (tree.GetSelectedItem() == m_hMain)
	{
		bool check = tree.GetCheck(m_hMain);
		tree.SetCheck(m_hCoord, check);
		tree.SetCheck(m_hSinus, check);
		tree.SetCheck(m_hHatch, check);
		tree.SetCheck(m_hStreaks45, check);
		tree.SetCheck(m_hBrush, check);
	}
	else
		tree.SetCheck(m_hMain, false);

	m_pDoc->m_bCoord = tree.GetCheck(m_hCoord);
	m_pDoc->m_bSinus = tree.GetCheck(m_hSinus);
	m_pDoc->m_bHatch = tree.GetCheck(m_hHatch);
	m_pDoc->m_bHatch = tree.GetCheck(m_hStreaks45);
	m_pDoc->m_bHatch = tree.GetCheck(m_hBrush);

	m_pDoc->m_pView->Invalidate();
}
