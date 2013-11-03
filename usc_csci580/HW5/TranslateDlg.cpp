// TranslateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580HW.h"
#include "TranslateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg dialog


CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTranslateDlg)
	m_fTx = 0.0f;
	m_fTy = 0.0f;
	m_fTz = 0.0f;
	//}}AFX_DATA_INIT
}


void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranslateDlg)
	DDX_Text(pDX, IDC_EDIT_TX, m_fTx);
	DDX_Text(pDX, IDC_EDIT_TY, m_fTy);
	DDX_Text(pDX, IDC_EDIT_TZ, m_fTz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialog)
	//{{AFX_MSG_MAP(CTranslateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg message handlers

void CTranslateDlg::Initialize(float tx, float ty, float tz)
{
	m_fTx = tx;
	m_fTy = ty;
	m_fTz = tz;
}