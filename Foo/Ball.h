#pragma once


// Ball view
class CFooDoc;
class CFooView;

class Ball : public CView
{
	DECLARE_DYNCREATE(Ball)

protected:
	Ball();           // protected constructor used by dynamic creation

public:
	/*CFooDoc* pDoc;
	CFooView* pView;*/
	
	Ball(const Ball&);
	Ball(int x, int y);
	virtual ~Ball();

	int R = 50;
	int X, Y;
	
	bool isIntersected(const POINT p1, const POINT p2);
	bool IsActive(POINT p);

	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void Serialize(CArchive& ar);
};


