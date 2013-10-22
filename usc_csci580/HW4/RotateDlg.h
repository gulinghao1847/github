#if !defined(AFX_ROTATEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_)
#define AFX_ROTATEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog

class CRotateDlg : public CDialog
{
// Construction
public:
	int m_nAxis;	// x=0, y=1, z=2
	float m_fRx;
	float m_fRy;
	float m_fRz;

	CRotateDlg(CWnd* pParent = NULL);   // standard constructor
	void Initialize(float rx, float ry, float rz);

// Dialog Data
	//{{AFX_DATA(CRotateDlg)
	enum { IDD = IDD_ROTATE };
	float	m_fRot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateDlg)
	afx_msg void OnRadioRotx();
	afx_msg void OnRadioRoty();
	afx_msg void OnRadioRotz();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_)
