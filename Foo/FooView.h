
// FooView.h: интерфейс класса CFooView
//

#pragma once

//#include "FooDoc.h"

class CFooDoc;

class CFooView : public CView
{
protected: // создать только из сериализации
	CFooView() noexcept;
	DECLARE_DYNCREATE(CFooView)

// Атрибуты
public:
	CFooDoc* GetDocument() const;
	int step = 50;
// Операции
public:

	double CFooView::f(double x, double m, double b, double amplitude, double period);
	double CFooView::bisection(double a, double b, double m, double b_const, double amplitude, double period);
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CFooView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в FooView.cpp
inline CFooDoc* CFooView::GetDocument() const
   { return reinterpret_cast<CFooDoc*>(m_pDocument); }
#endif

