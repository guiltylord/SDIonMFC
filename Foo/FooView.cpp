﻿
// FooView.cpp: реализация класса CFooView
//

#include "pch.h"
#include "framework.h"
#include <cmath>
#include <vector>
#include <set>
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
	CPen penIs(PS_SOLID, 1, RGB(204, 0, 204));
	CPen* pOldPen = pDC->SelectObject(&penBlue);

	int width = rc.Width();
	int height = rc.Height();

	int halfY = height / 2;
	int halfX = width / 2;
	
	auto sinus{ [](double x, double acc) { return  sin((2 * PI * x) / acc); } };


	for (int x = 0; x < width; x++) 
	{
		double phase = x; // смещение
		double frequency = (2 * PI * x) / width; // частота
		double amplitude = sin(frequency); // амплитуда
		int y = (halfY + halfY * amplitude);
		int currX = x;
		if (x == 0) {
			pDC->MoveTo(x, y); 
		}
		else 
		{
			pDC->SelectObject(&penBlue);
			pDC->LineTo(x, y);
		}
	}

	pDC->SelectObject(&penYellow);

	int step = 10;
	for (int x = halfX; x < rc.Width(); x++)
	{
		pDC->MoveTo(x, halfY);
		if(x % step == 0 && x > rc.Width()/2)
		{
			double b = x - halfX; // Смещение прямой
			int a = -(halfY-halfX); // Начало интервала

			std::vector<double> res = findIntersections(halfY, halfX, b, a, halfX, 10); //+

			// Множество для хранения уникальных значений
			std::set<int> uniq(res.begin(), res.end());

			auto it = uniq.begin();


			if(res.size() == 1)
			{
				double root = *it;
				advance(it, 0);
				double y = halfY * sin(PI / halfX * root);
				double Y = height - halfY - y;
				double X = halfX + root;
				pDC->LineTo(X, Y);
			}
			if (res.size() == 2)
			{
				advance(it, 0);
				double root = *it;
				double y = halfY * sin(PI / halfX * root);
				double Y = height - halfY - y;
				pDC->MoveTo(root, Y);

				advance(it, 1);
				root = *it;
				y = halfY * sin(PI / halfX * root);
				Y = height - halfY - y;
				pDC->LineTo(root, Y);
			}
		}
	}

	pDC->SelectObject(&penIs);
	/*for (int x = halfX; x < rc.Width(); x++)
	{
		pDC->MoveTo(x, halfY);
		if (x % step == 0 && x >= rc.Width() / 2)
		{
			pDC->LineTo(x, -height);
		}
	}*/

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



double CFooView::sineWave(double x, double A, double period) {
	return A * sin(PI / period * x);
}

//
//// Метод бисекции
//double CFooView::bisection(double a, double b, double m, double b_const, double amplitude, double period) {
//	/*if (f(a, m, b_const) * f(b, m, b_const) >= 0)
//	{
//		std::cerr << "Неверный интервал: f(a) и f(b) должны иметь разные знаки." << std::endl;
//		return NAN;
//	}*/
//
//	double c;
//	while ((b - a) >= 1e-6) 
//	{
//		c = (a + b) / 2; // Средняя точка
//		if (sineWave(c, m, b_const, amplitude, period) == 0.0)
//		{
//			break; // c является корнем
//		}
//		else if (sineWave(c, m, b_const, amplitude, period) * sineWave(a, m, b_const, amplitude, period) < 0)
//		{
//			b = c; // Корень находится в левой части
//		}
//		else 
//		{
//			a = c; // Корень находится в правой части
//		}
//	}
//	return (a + b) / -2; // Возвращаем среднюю точку как приближенную к корню
//}

int CFooView::customRound(double num)
{
	double fractionalPart = num - std::floor(num);
	return (fractionalPart >= 0.5) ? std::ceil(num) : std::floor(num);
}

std::vector<double> CFooView::findIntersections(double A, double T, double b, double startX, double endX, double step)
{
	std::vector<double> intersections;

	for (double x = startX; x <= endX; x += step) {
		double ySine = sineWave(x, A, T);
		double yLine = x + b;

		// Проверяем на пересечение
		if (std::abs(ySine - yLine) < step) { // Погрешность
			intersections.push_back(abs(x));
		}
	}

	return intersections;
}
