
// FooDoc.cpp: реализация класса CFooDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Foo.h"
#endif

#include "FooDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const double PI = 3.141592653589793;

// CFooDoc

IMPLEMENT_DYNCREATE(CFooDoc, CDocument)

BEGIN_MESSAGE_MAP(CFooDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CFooDoc

CFooDoc::CFooDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CFooDoc::~CFooDoc()
{
}

BOOL CFooDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	Px = 500;
	Py = 500;
	return TRUE;
}

void CFooDoc::drawSin(CDC* pDC, CRect rc)
{
	int acc = rc.Width(); 
	int height = rc.Height()/2;

	CPen pen(PS_SOLID, 2, RGB(0, 0, 255)); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	for (int x = 0; x < acc; x++) 
	{
		double phase = x + 0; //смещение
		double frequency = (2 * PI * phase) / acc; //частота
		double amplitude = -sin(frequency); // амплитуда; 
		int y = (height + height * amplitude);  

		if (x > 0) 
			pDC->LineTo(x, y);
		else 
			pDC->MoveTo(x, y);
	}

	pDC->SelectObject(pOldPen);
}

void CFooDoc::drawLine(CDC* pDC, CRect rc)
{

	int height = rc.Height();

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0)); // Красный цвет
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(0, height / 2);
	pDC->LineTo(rc.Width(), height / 2);

	pDC->SelectObject(pOldPen);
}


// Сериализация CFooDoc

void CFooDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
		ar << iVer;

		ar << Px;
		ar << Py;
		ar << Pz;

		data.Serialize(ar);
	}
	else
	{
		// TODO: добавьте код загрузки
		ar >> iVer;

		if (iVer != 1)
			return;
		ar >> Px;
		ar >> Py;
		ar >> Pz;
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CFooDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CFooDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CFooDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CFooDoc

#ifdef _DEBUG
void CFooDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFooDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CFooDoc
