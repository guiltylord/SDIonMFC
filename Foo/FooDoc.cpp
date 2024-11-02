
// FooDoc.cpp: реализация класса CFooDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Foo.h"

#include"MainFrm.h"
#endif

#include "FooDoc.h"
#include "FooView.h"
#include "CLineDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFooDoc

IMPLEMENT_DYNCREATE(CFooDoc, CDocument)

BEGIN_MESSAGE_MAP(CFooDoc, CDocument)
	ON_COMMAND(MYMENU_SETUP, &CFooDoc::OnMymenuSetup)
	ON_COMMAND(MYMENU_SETUP_NOTMODAL, &CFooDoc::OnMymenuSetupNotmodal)
	ON_COMMAND(ID_OBJECTS_SINUS, &CFooDoc::OnObjectsSinus)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_SINUS, &CFooDoc::OnUpdateObjectsSinus)
	ON_COMMAND(ID_OBJECTS_COORDINATES, &CFooDoc::OnObjectsCoordinates)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_COORDINATES, &CFooDoc::OnUpdateObjectsCoordinates)
	ON_COMMAND(ID_OBJECTS_STREAKS, &CFooDoc::OnObjectsStreaks)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_STREAKS, &CFooDoc::OnUpdateObjectsStreaks)
	ON_COMMAND(ID_OBJECTS_STREAKS45, &CFooDoc::OnObjectsStreaks45)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_STREAKS45, &CFooDoc::OnUpdateObjectsStreaks45)
	ON_COMMAND(ID_OBJECTS_BRUSH, &CFooDoc::OnObjectsBrush)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_BRUSH, &CFooDoc::OnUpdateObjectsBrush)
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

	CWnd* MainWnd = AfxGetMainWnd();

	m_pTree->m_pDoc = this;
	m_pTree->FillTree();
	m_bStreaks45 = m_bCoord = m_bSinus = m_bStreaks = m_bBrush = false;
	return TRUE;
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


void CFooDoc::OnMymenuSetup()
{
	// TODO: добавьте свой код обработчика команд
	CLineDlg dlg;
	dlg.flag = m_bStreaks;

	if (dlg.DoModal() == IDOK)
	{
		m_bStreaks = dlg.flag;
		
		UpdateAllViews(NULL);
	}
}


void CFooDoc::OnMymenuSetupNotmodal()
{
	// TODO: добавьте свой код обработчика команд

	if(!m_setupDlg)
		m_setupDlg.Create(IDD_DIALOG1);

	m_setupDlg.flag = m_bStreaks;

	m_setupDlg.m_pDoc = this;

	m_setupDlg.ShowWindow(SW_SHOW);
}


void CFooDoc::OnObjectsCoordinates()
{
	m_bCoord = !m_bCoord;
	CTreeCtrl& tree = m_pTree->GetTreeCtrl();
	tree.SetCheck(m_pTree->m_hCoord, m_bCoord);
	m_pView->Invalidate();
}

void CFooDoc::OnUpdateObjectsCoordinates(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bCoord);
}


void CFooDoc::OnObjectsSinus()
{
	m_bSinus = !m_bSinus;
	CTreeCtrl& tree = m_pTree->GetTreeCtrl();
	tree.SetCheck(m_pTree->m_hSinus, m_bSinus);
	m_pView->Invalidate();
}

void CFooDoc::OnUpdateObjectsSinus(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bSinus);
}


void CFooDoc::OnObjectsStreaks()
{
	m_bStreaks = !m_bStreaks;
	CTreeCtrl& tree = m_pTree->GetTreeCtrl();
	tree.SetCheck(m_pTree->m_hStreaks, m_bStreaks);
	m_pView->Invalidate();
}

void CFooDoc::OnUpdateObjectsStreaks(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bStreaks);
}


void CFooDoc::OnObjectsStreaks45()
{
	m_bStreaks45 = !m_bStreaks45;
	CTreeCtrl& tree = m_pTree->GetTreeCtrl();
	tree.SetCheck(m_pTree->m_hStreaks45, m_bStreaks45);
	m_pView->Invalidate();
}

void CFooDoc::OnUpdateObjectsStreaks45(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bStreaks45);
}


void CFooDoc::OnObjectsBrush()
{
	m_bBrush = !m_bBrush;
	CTreeCtrl& tree = m_pTree->GetTreeCtrl();
	tree.SetCheck(m_pTree->m_hBrush, m_bBrush);
	m_pView->Invalidate();
}

void CFooDoc::OnUpdateObjectsBrush(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bBrush);
}
