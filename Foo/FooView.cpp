
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
	ON_WM_RBUTTONDOWN()
//	ON_COMMAND(IDD_COLOR_DLG, &CFooView::OnIddColorDlg)
ON_COMMAND(ID_OBJECTS_COLOR, &CFooView::OnObjectsColor)
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

double CFooView::f(double x, double m, double b, double amplitude, double period) {
	double frequency = PI / period * x; // Частота
	return amplitude * sin(frequency) - (1 * x + b); // Разность между синусом и уравнением прямой
}


double CFooView::bisection(double a, double b, double m, double b_const, double amplitude, double period)
{
	double c;
	while ((b - a) >= 1e-6)
	{
		c = (a + b) / 2; // Средняя точка
		if (f(c, m, b_const, amplitude, period) == 0.0)
		{
			break; // c является корнем
		}
		else if (f(c, m, b_const, amplitude, period) * f(a, m, b_const, amplitude, period) < 0)
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

	if (pDoc->m_bCoord)
	{
		pDC->MoveTo(0, rc.Height() / 2);
		pDC->LineTo(rc.Width(), rc.Height() / 2);
		pDC->MoveTo(0, rc.Height() / 2);
	}

	if (pDoc->m_bStreaks)
	{
		for (int x = 0; x < rc.Width()-1; x++)
		{
			double phase = x; // смещение
			double frequency = (2 * PI * phase) / rc.Width(); // частота
			double amplitude = -sin(frequency); // амплитуда
			int y = (halfY + halfY * amplitude);

			if (x % step == 0 && x > width / 2)
			{
				pDC->MoveTo(x, halfY); // перемещаемся на новую точку
				pDC->LineTo(x, y); // рисуем линию
			}
		}
	}

	if (pDoc->m_bStreaks45)
	{
		for (int x = halfX; x < rc.Width(); x++)
		{
			pDC->MoveTo(x, halfY);
			if (x % step == 0 && x > rc.Width() / 2)
			{
				double b = x - halfX; // Смещение прямой

				double a = -width; // Начало интервала
				double b_val = width; // Конец интервала

				double root = bisection(a, b_val, 1, b, halfY, halfX);
				double y = halfY * sin(PI / halfX * root);

				double Y = height - halfY + y;
				double X = halfX + root;
				pDC->LineTo(X, Y);
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


void CFooView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	ClientToScreen(&point);

	CCmdUI state;

	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonDown(nFlags, point);
}


void CFooView::OnObjectsColor()
{
	if (m_ColorDlg == nullptr)
	{
		m_ColorDlg = new CColorDlg(this);
		m_ColorDlg->Create(IDD_COLOR_DLG, this);
	}

	m_ColorDlg->m_ColorCtrl.SetColor(m_Color);
	m_ColorDlg->m_pView = this;
	m_ColorDlg->ShowWindow(SW_SHOW);
}
