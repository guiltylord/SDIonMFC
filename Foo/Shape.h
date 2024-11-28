#pragma once

#define BALL 0
#define SQUARE 1
// Shape view

class Shape {
public:
    int type;
    bool m_bActive = false;

    Shape() { type = -1; }
    virtual ~Shape() {}

    virtual void OnDraw(CDC* pDC) = 0;
    virtual void Serialize(CArchive& ar) = 0;

    bool IsActive() { return m_bActive; }

    virtual void CheckPoint(POINT pt) = 0;

    virtual void WriteCoords(int x, int y) = 0;
};
