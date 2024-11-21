
// FooView.h: интерфейс класса CFooView
//

#pragma once


class CFooDoc;
class Ball;

class CFooView : public CView
{
protected: // создать только из сериализации
	CFooView() noexcept;
	DECLARE_DYNCREATE(CFooView)

// Атрибуты
public:
	CFooDoc* GetDocument() const;
	int step = 50;

	Ball* m_pCurBall;
	bool activeBall = FALSE;
	bool isNew = TRUE;
// Операции
public:
	void CreateBalls(CFooDoc* pDoc);
	bool ValidPlacement(int x, int y, CFooDoc* pDoc);
	bool CheckCollision(POINT p, CFooDoc* pDoc);
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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в FooView.cpp
inline CFooDoc* CFooView::GetDocument() const
   { return reinterpret_cast<CFooDoc*>(m_pDocument); }
#endif

