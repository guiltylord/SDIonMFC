#pragma once

//
//#include "FooDoc.h"
//#include "FooView.h"
//
//
//class Shape
//{
//public:
//	int type;
//	bool m_bActive = false;
//	//virtual Shape(const Shape&) = 0;
//	
//	Shape() { type = -1; } // Default constructor should initialize type to some value
//
//	virtual ~Shape();
//
//	virtual void OnDraw(CDC* pDC) = 0;      // overridden to draw this view
//	virtual void Serialize(CArchive& ar) = 0;
//
//	//virtual bool isIntersected(const Shape *sh)=0;
//	
//	bool IsActive();
//	
//	virtual void CheckPoint(POINT pt); //проверяет точку если да меняет m_bactive
//
//	void WriteCoords(int x, int y);
//};
//
//
//
//class Ball : public Shape
//{
//public:
//	Ball(int x, int y) { X = x; Y = y; };
//	Ball() {
//		type = BALL;
//	};
//
//	int R = 50;
//	int X, Y;
//
//	bool IsNotIntersected;
//	bool ValidatePlacement(int x, int y, CFooDoc* pDoc);
//	void CheckIntersection(const POINT p1, const POINT p2);
//	bool IsActive();
//
//	bool isCollisioned;
//	bool CheckCollision(POINT p, CFooDoc* pDoc);
//	void CheckPoint(POINT pt);
//
//	void WriteCoords(int x, int y);
//
//	virtual void OnDraw(CDC* pDC);
//	virtual void Serialize(CArchive& ar);
////private:
////	Ball() {};
//};
//


#include "FooDoc.h"


class Ball : public Shape {
public:
    Ball(int x, int y) : Shape() { 
        X = x;
        Y = y;
        type = BALL; 
    }

    Ball() {
        type = BALL;
    }

    int R = 50;
    int X{}, Y{};

    bool ValidatePlacement(int x, int y, CFooDoc* pDoc);
    void CheckIntersection(const POINT p1, const POINT p2);
    bool CheckCollision(POINT p, CFooDoc* pDoc);
    void CheckPoint(POINT pt);
    void WriteCoords(int x, int y);

    virtual void OnDraw(CDC* pDC);
    virtual void Serialize(CArchive& ar);
protected:
    bool IsNotIntersected;
};
