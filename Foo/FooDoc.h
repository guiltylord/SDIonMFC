
// FooDoc.h: интерфейс класса CFooDoc 
//


#pragma once

#include "CMyTreeview.h"

#include "CLineDlg.h"

class CFooView;
class cl
{
public:
	int x;
	float y;
	void Serialize(CArchive& ar) {};
};

class CFooDoc : public CDocument
{
protected: // создать только из сериализации
	CFooDoc() noexcept;
	DECLARE_DYNCREATE(CFooDoc)

// Атрибуты
public:
	bool m_bCoord, m_bSinus, m_bHatch, m_bHatch45, m_bBrush;

	int iVer = 1;
	int Px, Py, Pz;

	cl data;

	CMyTreeView* m_pTree;

	CFooView* m_pView;

	CLineDlg m_setupDlg;
// Операции
public:
// Переопределение
public:
	virtual BOOL OnNewDocument(); // тут карочи задать можно чето при инициализации
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CFooDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnMymenuSetup();
	afx_msg void OnMymenuSetupNotmodal();
};
