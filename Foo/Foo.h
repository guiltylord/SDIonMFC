
// Foo.h: основной файл заголовка для приложения Foo
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CFooApp:
// Сведения о реализации этого класса: Foo.cpp
//

class CFooApp : public CWinApp
{
public:
	CFooApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFooApp theApp;
