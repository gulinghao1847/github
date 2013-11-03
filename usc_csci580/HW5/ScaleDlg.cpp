// ScaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580HW.h"
#include "ScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg dialog


CScaleDlg::CScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleDlg)
	m_fSx = 0.0f;
	m_fSy = 0.0f;
	m_fSz = 0.0f;
	//}}AFX_DATA_INIT
}


void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg)
	DDX_Text(pDX, IDC_EDIT_SX, m_fSx);
	DDX_Text(pDX, IDC_EDIT_SY, m_fSy);
	DDX_Text(pDX, IDC_EDIT_SZ, m_fSz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleDlg, CDialog)
	//{{AFX_MSG_MAP(CScaleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg message handlers

void CScaleDlg::Initialize(float sx, float sy, float sz)
{
	m_fSx = sx;
	m_fSy = sy;
	m_fSz = sz;
}