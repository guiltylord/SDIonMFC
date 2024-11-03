#pragma once


// Ball view

class Ball : public CView
{
	DECLARE_DYNCREATE(Ball)

protected:
	Ball();           // protected constructor used by dynamic creation

public:
	Ball(const Ball&);
	Ball(int X, int Y); //useless?
	Ball(int x, int y, int radius = 50);
	virtual ~Ball();

	int R = 50;
	int X, Y;

	bool isIntersected(const POINT p1, const POINT p2);
	bool IsActive(POINT p);

	POINT GetCoord();

	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


