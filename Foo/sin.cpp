//void CYourView::OnPaint()
//{
//    CPaintDC dc(this); // ���������� ��������� ��� ���������
//
//    // �������� ������� ���������� �������
//    CRect rect;
//    GetClientRect(&rect);
//
//    // ������������� ��������� ���������
//    int amplitude = 50; // ���������
//    int frequency = 2;  // �������
//    int centerY = rect.Height() / 2; // ������������ �����
//
//    // ������ ���������
//    for (int x = 0; x < rect.Width(); ++x)
//    {
//        int y = centerY + static_cast<int>(amplitude * sin(frequency * 2 * M_PI * x / rect.Width()));
//        if (x == 0)
//            dc.MoveTo(x, y);
//        else
//            dc.LineTo(x, y);
//    }
//}