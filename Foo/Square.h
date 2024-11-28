#pragma once
#include "Shape.h"
#include "FooDoc.h"

class Square :
    public Shape
{
public:
    Square(int x, int y) : Shape() {
        X = x;
        Y = y;
        type = SQUARE;
    }

    Square() {
        type = SQUARE;
    }

    int X,Y;

    bool ValidatePlacement(int x, int y, CFooDoc* pDoc);
    void CheckIntersection(const POINT p1, const POINT p2);
    bool CheckCollision(POINT p, CFooDoc* pDoc);
    void CheckPoint(POINT pt);
    void WriteCoords(int x, int y);

    virtual void OnDraw(CDC* pDC);
    virtual void Serialize(CArchive& ar);
};

