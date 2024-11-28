#include "pch.h"
#include "Square.h"

bool Square::ValidatePlacement(int x, int y, CFooDoc* pDoc)
{
    int side = 50; // Размер стороны квадрата, можно изменить при необходимости

    for (auto& object : pDoc->m_vObjects)
    {
        if (object->type == SQUARE)
        {
            Square* s = (Square*)object;
            // Проверка пересечения с другими квадратами
            if (abs(s->X - x) < side && abs(s->Y - y) < side)
                return true; // Пересечение найдено
        }
    }
    return false; // Нет пересечений
}

void Square::CheckIntersection(const POINT p1, const POINT p2)
{
}

bool Square::CheckCollision(POINT p, CFooDoc* pDoc)
{
    return false;
}

void Square::CheckPoint(POINT pt)
{
}

void Square::WriteCoords(int x, int y)
{
    this->X = x;
    this->Y = y;
}

void Square::OnDraw(CDC* pDC)
{
    CRgn region;

    CPen pen;
    pen.CreatePen(PS_SOLID, 0, RGB(102, 0, 204));
    CPen* oldPen = (CPen*)pDC->SelectObject(pen);

    CBrush brush;
    brush.CreateSolidBrush(RGB(255, 255, 0));
    CBrush* pOrigBrush = (CBrush*)pDC->SelectObject(&brush);

    int side = 50; // Размер стороны квадрата

    // Убедитесь, что координаты квадрата заданы корректно
    if (X <= side / 2 && Y <= side / 2)
        return;

    // Рисуем квадрат
    pDC->Rectangle(
        X - side / 2,
        Y - side / 2,
        X + side / 2,
        Y + side / 2
    );

    region.CreateFromPath(pDC);
    pDC->PaintRgn(&region);

    pDC->SelectObject(pOrigBrush);
    pDC->SelectObject(&oldPen);
}


void Square::Serialize(CArchive& ar)
{
}
