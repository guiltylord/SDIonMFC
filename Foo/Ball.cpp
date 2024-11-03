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


Ball::Ball(int x, int y)
{
	this->X = x;
	this->Y = y;
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

	CPen pen;
	pen.CreatePen(PS_SOLID, 0, RGB(0, 128, 255));
	CPen* oldPen = (CPen*)pDC->SelectObject(pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 128, 0));
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
	pDC->SelectObject(&oldPen);
}


bool Ball::isIntersected(const POINT p1, const POINT p2)
{
	float vectorFirst = sqrt(pow(X - p1.x, 2) + pow(Y - p1.y, 2));

	float vectorFirstNormalX = (p1.x - X) / vectorFirst;
	float vectorFirstNormalY = (p1.y - Y) / vectorFirst;

	float projection = ((p1.x - X) * (p2.x - X) + (p1.y - Y) * (p2.y - Y)) / vectorFirst;

	float perpX = vectorFirstNormalX * projection + X;
	float perpY = vectorFirstNormalY * projection + Y;

	float distanceToProjection = sqrt(pow(perpX - p2.x, 2) + pow(perpY - p2.y, 2));

	if (distanceToProjection >= R || projection < 0 || sqrt(pow(X - p2.x, 2) + pow(Y - p2.y, 2)) > R)
		return true;

	return false;
}

bool Ball::IsActive(POINT p)
{
	if (abs(p.x - X) <=R && abs(p.y - Y) <= R)
		return true;
	else
		return false;
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
