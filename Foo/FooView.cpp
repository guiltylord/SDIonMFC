﻿
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

#include "FooDoc.h"
#include "FooView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double PI = 3.141592653589793;


// CFooView

IMPLEMENT_DYNCREATE(CFooView, CView)

BEGIN_MESSAGE_MAP(CFooView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Создание или уничтожение CFooView

CFooView::CFooView() noexcept
{
	// TODO: добавьте код создания

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

	CRect rc;
	GetClientRect(&rc);
	CPen pen(PS_SOLID, 1, RGB(50, 200, 140));

	CPen penBlue(PS_SOLID, 1, RGB(0, 0, 255));
	CPen penYellow(PS_SOLID, 1, RGB(150, 50, 200));
	CPen * oldPen = pDC->SelectObject(&pen);

	double frequency = 2 * 3.14 / rc.Width();


	int height = rc.Height();
	int halfY = height/2;
	int width = rc.Width();
	int halfX = width/2;


	double my = 2.f / rc.Height();

	if (pDoc->m_bSinus)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));

		for (int x = 0; x < rc.Width(); x++)
		{
			double phase = x; // смещение
			double frequency = (2 * PI * phase) / rc.Width(); // частота
			double amplitude = -sin(frequency); // амплитуда
			int y = (halfY + halfY * amplitude);

			if (x == 0) {
				pDC->MoveTo(x, y);
			}
			else
			{
				pDC->SelectObject(&pen);
				pDC->LineTo(x, y);
			}
		}
	}

	if (pDoc->m_bCoord)
	{
		pDC->MoveTo(0, rc.Height() / 2);
		pDC->LineTo(rc.Width(), rc.Height() / 2);
		
		pDC->MoveTo(0, rc.Height() / 2);
	}

	if (pDoc->m_bHatch)
	{

		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));

		for (int x = 0; x < rc.Width()-1; x++)
		{
			double phase = x; // смещение
			double frequency = (2 * PI * phase) / rc.Width(); // частота
			double amplitude = -sin(frequency); // амплитуда
			int y = (halfY + halfY * amplitude);

			if (x % 20 == 0 && x > width / 2)
			{
				pDC->SelectObject(&penYellow);
				pDC->MoveTo(x, halfY); // перемещаемся на новую точку
				pDC->LineTo(x, y); // рисуем линию
			}
		}

	}

	if (pDoc->m_bHatch45)
	{
	}

	if (pDoc->m_bBrush)
	{
	}



	// TODO: добавьте здесь код отрисовки для собственных данных

	pDC->LineTo(rc.Width() / 2, rc.Height() / 2);
	
	pDC->SelectObject(&oldPen);
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
