#include "pch.h"
#include "Ball.h"
#include "FooDoc.h"
class CFooDoc;

void Ball::OnDraw(CDC* pDC)
{
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

void Ball::Serialize(CArchive& ar)
{

	if (ar.IsStoring()) {

		ar << X << Y;
	}
	else {
		int x, y;

		ar >> X >> Y;
	}
}

bool Ball::ValidatePlacement(int x, int y, CFooDoc* pDoc)
{
	for (auto& ball : pDoc->m_vObjects)
	{
		if (ball->type == BALL)
		{
			Ball* b = (Ball*)ball;
			if (abs(b->X - x) < b->R * 2 && abs(b->Y - y) < R * 2)
				return true;
		}
		return false;
	}
}

bool Ball::CheckCollision(POINT p, CFooDoc* pDoc)
{
	for (auto object : pDoc->m_vObjects) {
		if (object->type == BALL) {
			auto ball = (Ball*)object;
			auto ball2 = (Ball*)pDoc->m_pCurBall;
			if (ball2->X == ball->X && ball2->Y == ball->Y) 
				continue;

			POINT p2;
			p2.x = ball2->X;
			p2.y = ball2->Y;

			ball2->CheckIntersection(p, p2);

			if (ball2->IsNotIntersected)
				return false;
		}
	}
	return true;
}

void Ball::CheckPoint(POINT pt)
{
	if (abs(pt.x - X) <= R && abs(pt.y - Y) <= R) {
		m_bActive = true;
		return;
	}
	m_bActive = false;
}

void Ball::WriteCoords(int x, int y)
{
	X = x;
	Y = y;
}

void Ball::CheckIntersection(const POINT p1, const POINT p2)
{
	float vectorFirst = sqrt(pow(X - p1.x, 2) + pow(Y - p1.y, 2));

	float vectorFirstNormalX = (p1.x - X) / vectorFirst;
	float vectorFirstNormalY = (p1.y - Y) / vectorFirst;

	float projection = ((p1.x - X) * (p2.x - X) + (p1.y - Y) * (p2.y - Y)) / vectorFirst;

	float perpX = vectorFirstNormalX * projection + X;
	float perpY = vectorFirstNormalY * projection + Y;

	float distanceToProjection = sqrt(pow(perpX - p2.x, 2) + pow(perpY - p2.y, 2));

	if (distanceToProjection >= R || projection < 0 || sqrt(pow(X - p2.x, 2) + pow(Y - p2.y, 2)) > R)
		this->IsNotIntersected =  true;

	this->IsNotIntersected = false;
}