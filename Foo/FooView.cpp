﻿
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
	CPen penYellow(PS_SOLID, 1, RGB(0, 180, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlue);

	int acc = rc.Width();
	int height = rc.Height() / 2;
	int x0 = acc / 2;
	int y0 = height;

	for (int x = 0; x < acc; x++) 
	{
		double phase = x; // смещение
		double frequency = (2 * PI * phase) / acc; // частота
		double amplitude = sin(frequency); // амплитуда
		int y = (height + height * amplitude);
		int currX = x;
		if (x == 0) {
			pDC->MoveTo(x, y); 
		}
		else 
		{
			pDC->SelectObject(&penBlue);
			pDC->LineTo(x, y);
		}

		//auto sum{ [](int a, int b) {return a + b; } };
		auto sinus{ [](double x, double acc) { return  sin((2 * PI * x) / acc); } };

		//if (x % 50 == 0 && x > acc / 2) 
		//{
		//	pDC->SelectObject(&penYellow);	
		//	pDC->MoveTo(x, y); // +
		//	pDC->LineTo(x+50, y+50); // рисуем линию

		//	pDC->MoveTo(x, y); // +
		//}

		

	}

	/*double mx = 2 * 3.14 / rc.Width();
	double my = 2.f / rc.Height();*/

	pDC->SelectObject(&penYellow);

	for (int x = 0; x < rc.Width(); x++)
	{
		pDC->MoveTo(x, height);
		if(x % 50 == 0 && x > rc.Width()/2)
		{
			int xz = x - (x0 - x);
			pDC->LineTo(x + height*2, -rc.Height());
		}
	}

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


// Метод бисекции
double bisection(double a, double b, double m, double b_const) {
	/*if (f(a, m, b_const) * f(b, m, b_const) >= 0)
	{
		std::cerr << "Неверный интервал: f(a) и f(b) должны иметь разные знаки." << std::endl;
		return NAN;
	}*/

	double c;
	while ((b - a) >= 1e-6) 
	{
		c = (a + b) / 2; // Средняя точка
		if (f(c, m, b_const) == 0.0) 
		{
			break; // c является корнем
		}
		else if (f(c, m, b_const) * f(a, m, b_const) < 0) 
		{
			b = c; // Корень находится в левой части
		}
		else 
		{
			a = c; // Корень находится в правой части
		}
	}
	return (a + b) / -2; // Возвращаем среднюю точку как приближенную к корню
}

double f(double x, double m, double b) {
	return sin(x) - (m * x + b);
}