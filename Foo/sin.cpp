//void CYourView::OnPaint()
//{
//    CPaintDC dc(this); // устройство контекста дл€ рисовани€
//
//    // ѕолучаем размеры клиентской области
//    CRect rect;
//    GetClientRect(&rect);
//
//    // ”станавливаем параметры синусоиды
//    int amplitude = 50; // амплитуда
//    int frequency = 2;  // частота
//    int centerY = rect.Height() / 2; // вертикальный центр
//
//    // –исуем синусоиду
//    for (int x = 0; x < rect.Width(); ++x)
//    {
//        int y = centerY + static_cast<int>(amplitude * sin(frequency * 2 * M_PI * x / rect.Width()));
//        if (x == 0)
//            dc.MoveTo(x, y);
//        else
//            dc.LineTo(x, y);
//    }
//}