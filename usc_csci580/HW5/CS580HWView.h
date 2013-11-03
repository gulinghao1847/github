// CS580HWView.h : interface of the CCS580HWView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CS580HWVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_)
#define AFX_CS580HWVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Application.h"
#include "Gz.h"

class CCS580HWView : public CView
{
protected: // create from serialization only
	CCS580HWView();
	DECLARE_DYNCREATE(CCS580HWView)

// Attributes
public:
	CCS580HWDoc* GetDocument();

// Operations
public:
	Application* m_pApplication;
	void DrawFrameBuffer(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS580HWView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCS580HWView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCS580HWView)
	afx_msg void OnRender();
	afx_msg void OnRotate();
	afx_msg void OnTranslate();
	afx_msg void OnScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CS580HWView.cpp
inline CCS580HWDoc* CCS580HWView::GetDocument()
   { return (CCS580HWDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS580HWVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_)
