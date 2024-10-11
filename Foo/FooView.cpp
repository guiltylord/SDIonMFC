
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

	float height = rc.Height();
	float width = rc.Width();
	float step = PI / width;
	float kx = width / (2 * PI);
	float ky = height / 2;
	float stepShtrih = 50 * step;

	for (int x = 0; x < width; x++)
	{
		double phase = x; // смещение
		double frequency = (2 * PI * x) / width; // частота
		double amplitude = sin(frequency); // амплитуда
		int y = (height/2 + height / 2 * amplitude);
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

	pDC->MoveTo(0, height / 2);
	for (float i = 0; i < PI; i += stepShtrih)
	{
		pDC->MoveTo(i * kx, height / 2);
		pDC->LineTo(i * kx, sin(i) * ky + height / 2);
	}

	pDC->MoveTo(width / 2, height / 2);
	for (float i = PI; i < 2 * PI; i += stepShtrih)
	{
		pDC->MoveTo(i * kx, height / 2);
		float tmpX = findIntersections(-i + PI,1,1,1,1,1) + PI;
		pDC->LineTo(tmpX * kx, sin(tmpX) * ky + height / 2);
	}


	pDC->SelectObject(&penYellow);

	//for (int x = halfX; x < rc.Width(); x++)
	//{
	//	pDC->MoveTo(x, halfY);
	//	if(x % step == 0 && x > rc.Width()/2)
	//	{
	//		double b = x - halfX; // Смещение прямой
	//		int a = -(halfY-halfX); // Начало интервала

	//		std::vector<double> res = findIntersections(halfY, halfX, b, a, halfX, 10); //+

	//		// Множество для хранения уникальных значений
	//		std::set<int> uniq(res.begin(), res.end());

	//		auto it = uniq.begin();


	//		if(res.size() == 1)
	//		{
	//			double root = *it;
	//			advance(it, 0);
	//			double y = halfY * sin(PI / halfX * root);
	//			double Y = height - halfY - y;
	//			double X = halfX + root;
	//			pDC->LineTo(X, Y);
	//		}
	//		if (res.size() == 2)
	//		{
	//			advance(it, 0);
	//			double root = *it;
	//			double y = halfY * sin(PI / halfX * root);
	//			double Y = height - halfY - y;
	//			pDC->MoveTo(root, Y);

	//			advance(it, 1);
	//			root = *it;
	//			y = halfY * sin(PI / halfX * root);
	//			Y = height - halfY - y;
	//			pDC->LineTo(root, Y);
	//		}
	//	}
	//}

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
	return x - sin(x) + A;
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
	return 1;
}

double CFooView::findIntersections(double A, double T, double rt5r, double startX, double endX, double step)
{
	float a = 0, b = PI;
	const float eps = 0.0001;
	float c = (a + b) / 2;
	while (abs(b - a) > eps)
	{
		if (sineWave(a, A, 1) * sineWave(c, A, 1) < 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
		c = (a + b) / 2;
	}
	return c;
}
