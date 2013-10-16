#if !defined(AFX_TRANSLATEDLG_H__6A9F2403_0CB5_43AD_8F54_0DEB8C3A1A5A__INCLUDED_)
#define AFX_TRANSLATEDLG_H__6A9F2403_0CB5_43AD_8F54_0DEB8C3A1A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TranslateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg dialog

class CTranslateDlg : public CDialog
{
// Construction
public:
	CTranslateDlg(CWnd* pParent = NULL);   // standard constructor
	void Initialize(float tx, float ty, float tz);


// Dialog Data
	//{{AFX_DATA(CTranslateDlg)
	enum { IDD = IDD_TRANSLATE };
	float	m_fTx;
	float	m_fTy;
	float	m_fTz;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTranslateDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLATEDLG_H__6A9F2403_0CB5_43AD_8F54_0DEB8C3A1A5A__INCLUDED_)
