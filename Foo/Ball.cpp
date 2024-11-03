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

Ball::~Ball()
{
}

BEGIN_MESSAGE_MAP(Ball, CView)
END_MESSAGE_MAP()


// Ball drawing

void Ball::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

bool Ball::isIntersected(const POINT p1, const POINT p2)
{
	float v1Lenth = sqrtf(pow(X - p1.x, 2) + pow(Y - p1.y, 2));

	float v1NormX = (p1.x - X) / v1Lenth;
	float v1NormY = (p1.y - Y) / v1Lenth;

	float proektV2V1 = ((p1.x - X) * (p2.x - X) + (p1.y - Y) * (p2.y - Y)) / v1Lenth;

	float v2Lenth = sqrtf(pow(X - p2.x, 2) + pow(Y - p2.y, 2));


	float perpX = v1NormX * proektV2V1 + X;
	float perpY = v1NormY * proektV2V1 + Y;
	

	float d = sqrtf(pow(perpX - p2.x, 2) + pow(perpY - p2.y, 2));

	if (d >= R || proektV2V1 < 0 || sqrtf(pow(X - p2.x, 2) + pow(Y - p2.y, 2)) > R)
	{
		//m_bIsInCollision = false;
		return true;
	}
	else
	{
		//m_bIsInCollision = true;
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
