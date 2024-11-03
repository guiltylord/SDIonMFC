// Ball.cpp : implementation file
//

#include "pch.h"
#include "Foo.h"
#include "Ball.h"


// Ball

IMPLEMENT_DYNCREATE(Ball, CView)
Ball::Ball()
{
}

Ball::Ball(const Ball& toCopy) //toCopy null
{
	this->X = toCopy.X;
	this->Y = toCopy.Y;
}

Ball::Ball(int X, int Y)
{
	this->X = X; 
	this->Y = Y;
}

Ball::Ball(int x, int y, int radius)
{
	this->X = x;
	this->Y = y;
	R = radius;
}

Ball::~Ball()
{
}

BEGIN_MESSAGE_MAP(Ball, CView)
END_MESSAGE_MAP()


// Ball drawing

void Ball::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CRgn region;
	// TODO: добавьте специализированный код или вызов базового класса

	CBrush brush;
	brush.CreateSolidBrush(RGB(52, 252, 52));
	CBrush* pOrigBrush = (CBrush*)pDC->SelectObject(&brush);

	if (X <= R && Y <= R)
		return;

	pDC->Ellipse(
		X - R / 2, 
		Y - R / 2, 
		X + R / 2, 
		Y + R / 2);
	

	region.CreateFromPath(pDC);
	pDC->PaintRgn(&region);

	pDC->SelectObject(pOrigBrush);
}


bool Ball::isIntersected(const POINT p1, const POINT p2)
{
	float v1Length = sqrtf(pow(X - p1.x, 2) + pow(Y - p1.y, 2));

	float v1NormX = (p1.x - X) / v1Length;
	float v1NormY = (p1.y - Y) / v1Length;
	
	
	double one = (p1.x - X) * (p2.x - X);
	double two = (p1.y - Y) * (p2.y - Y);
	
	float proektV2V1 = (one + two) / v1Length;

	float perpX = v1NormX * proektV2V1 + X;
	float perpY = v1NormY * proektV2V1 + Y;

	float d = sqrtf(pow(perpX - p2.x, 2) + pow(perpY - p2.y, 2));
	float distanceToP2 = sqrtf(pow(X - p2.x, 2) + pow(Y - p2.y, 2));

	if (d >= R || proektV2V1 < 0 || sqrtf(pow(X - p2.x, 2) + pow(Y - p2.y, 2)) > R)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ball::IsActive(POINT p)
{
	if (abs(p.x - X) <=R && abs(p.y - Y) <= R)
		return true;
	else
		return false;
}

POINT Ball::GetCoord()
{
	POINT p;
	p.x = X;
	p.y = Y;
	return p;
}


// Ball diagnostics

#ifdef _DEBUG
void Ball::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void Ball::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// Ball message handlers
