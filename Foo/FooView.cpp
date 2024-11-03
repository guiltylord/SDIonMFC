
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
#include <vector>

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



	CPen pen(PS_SOLID, 3, m_Color);
	
	CPen* oldPen = pDC->SelectObject(&pen);

	CRect rc;
	GetClientRect(&rc);
	double frequency = 2 * 3.14 / rc.Width();

	int height = rc.Height();
	int halfY = height/2;
	int width = rc.Width();
	int halfX = width/2;

	double my = 2.f / rc.Height();

	if (pDoc->m_bSinus)
	{
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
				pDC->LineTo(x, y);
			}
		}
	}

	if (pDoc->m_bBrush)
	{
		
		CBrush brush(HS_FDIAGONAL, m_Color);
		//brush.CreateHatchBrush(;

		CBrush* pOldBrush = pDC->SelectObject(&brush);

		std::vector<POINT> pointsVec;
		int width = rc.Width();
		int height = rc.Height();

		for (int x = 0; x < width; x++)
		{
			double phase = x;
			double frequency = (2 * PI * phase) / width;
			double amplitude = -sin(frequency);
			int y = (height / 2) + (height / 2 * amplitude);

			if (x > width / 2)
			{
				POINT point = { x, y };
				pointsVec.push_back(point);
			}
		}

		if (!pointsVec.empty())
		{
			POINT* pointsArr = new POINT[pointsVec.size()];
			for (size_t i = 0; i < pointsVec.size(); i++)
				pointsArr[i] = pointsVec[i];

			pDC->Polygon(pointsArr, pointsVec.size());
			delete[] pointsArr;
		}
		pDC->SelectObject(pOldBrush);
	}
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


