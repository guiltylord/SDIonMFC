
// FooView.cpp: реализация класса CFooView
//

#include "pch.h"
#include "framework.h"
#include <cmath>
#include <vector>
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
using namespace std;


__declspec(dllexport)

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
	
	drawSin();
	drawLine();
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

void CFooView::drawSin()
{
	CRect rc;
	GetClientRect(&rc);

	CDC* pDC = this->GetWindowDC();

	CPen penBlue (PS_SOLID, 1, RGB(0, 0, 255));
	CPen penGreen(PS_SOLID, 1, RGB(0, 255, 0));
	CBrush brush(HS_DIAGCROSS, RGB(255, 0, 0));

	CPen* pOldPen = pDC->SelectObject(&penBlue);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	vector <POINT> pointsVec;

	int acc = rc.Width();
	int height = rc.Height() / 2;

	for (int x = 0; x < acc; x++) 
	{
		double phase = x; // смещение
		double frequency = (2 * PI * phase) / acc; // частота
		double amplitude = -sin(frequency); // амплитуда
		int y = (height + height * amplitude);

		if (x == 0) 
		{
			pDC->MoveTo(x, y); 
		}
		else 
		{
			pDC->SelectObject(&penBlue);
			pDC->LineTo(x, y);
		}
		
		if (x > acc / 2) 
		{
			POINT point =
			{ x = x,
			y = y };

			pointsVec.push_back(point);
		}
	}

	POINT* pointsArr = new POINT[pointsVec.size()];
	for (int i = 0; i < pointsVec.size(); i++)
		pointsArr[i] = pointsVec[i];

	pDC->Polygon(pointsArr, pointsVec.size());

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


void CFooView::drawLine()
{
	CRect rc;
	GetClientRect(&rc);

	CDC* pDC = this->GetWindowDC();

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0)); // Красный цвет
	CPen* pOldPen = pDC->SelectObject(&pen);

	int height = rc.Height();

	pDC->MoveTo(0, height / 2);
	pDC->LineTo(rc.Width(), height / 2);

	pDC->SelectObject(pOldPen);
}
