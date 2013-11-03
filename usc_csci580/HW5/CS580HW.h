// CS580HW.h : main header file for the CS580HW application
//

#if !defined(AFX_CS580HW_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_)
#define AFX_CS580HW_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCS580HWApp:
// See CS580HW.cpp for the implementation of this class
//

class CCS580HWApp : public CWinApp
{
public:
	CCS580HWApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS580HWApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCS580HWApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS580HW_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_)
