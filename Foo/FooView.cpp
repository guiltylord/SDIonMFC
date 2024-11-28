
// FooView.cpp: реализация класса CFooView
//

#include "pch.h"
#include "framework.h"
#include <cmath>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Foo.h"
#endif

#include "Shape.h"
#include "Ball.h"
#include "FooDoc.h"
#include "FooView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>

const double PI = 3.141592653589793;


// CFooView

IMPLEMENT_DYNCREATE(CFooView, CView)

BEGIN_MESSAGE_MAP(CFooView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CFooView

CFooView::CFooView() noexcept
{
	// TODO: добавьте код создания

	//pDoc = GetDocument();
}

CFooView::~CFooView()
{
}

BOOL CFooView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}





// Рисование CFooView
void CFooView::OnDraw(CDC* pDC)
{
	CFooDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;		

	CPen pen(PS_SOLID, 3, RGB(100,100,100));
	
	CPen* oldPen = pDC->SelectObject(&pen);

	CRect rc;
	GetClientRect(&rc);
	
	
	if (pDoc->m_vObjects.empty()) {
		pDoc->CreateBalls();
		pDoc->CreateSquares();
	}

	for (auto& object : pDoc->m_vObjects) {
		object->OnDraw(pDC);
	}
}


// Печать CFooView

BOOL CFooView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CFooView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CFooView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CFooView

#ifdef _DEBUG
void CFooView::AssertValid() const
{
	CView::AssertValid();
}

void CFooView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFooDoc* CFooView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFooDoc)));
	return (CFooDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CFooView
void CFooView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFooDoc* pDoc = GetDocument();

	if (!pDoc)
		return;

	for (auto& object : pDoc->m_vObjects)
	{
		if (object->type == BALL) {

			auto b = (Ball*)object;
			b->CheckPoint(point);
			if (b->m_bActive) {
				activeBall = true;
				pDoc->m_pCurBall = object;
				break;
			}
		}
	}
}


void CFooView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (activeBall) {
		CFooDoc* pDoc = GetDocument();

		if (!pDoc)
			return;
		
		Ball* b2 = (Ball*)pDoc->m_pCurBall;

		if (b2->CheckCollision(point, pDoc)) {
			b2->WriteCoords(point.x, point.y);
			b2->X = point.x;/*
			b2->Y = point.y;*/
		}
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}


void CFooView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	activeBall = false;
	GetDocument()->m_pCurBall = nullptr;
	CView::OnLButtonUp(nFlags, point);
}

void CFooView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	pDoc = GetDocument();
	pDoc->m_pView = this;
}
