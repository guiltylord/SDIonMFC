#pragma once


// Ball view

class Ball : public CView
{
	DECLARE_DYNCREATE(Ball)

protected:
	Ball();           // protected constructor used by dynamic creation

public:
	Ball(const Ball&);
	Ball(int iX, int iY);
	virtual ~Ball();


	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

	int R = 50;
	int X, Y;

	Ball(int x, int y, int radius = 50);
	int m_iX, m_iY;

	bool isIntersected(const POINT p1, const POINT p2);
	bool IsActive(POINT p);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


