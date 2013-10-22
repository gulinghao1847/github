// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580HW.h"
#include "RotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog


CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateDlg)
	m_fRot = 0.0f;
	//}}AFX_DATA_INIT
}


void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateDlg)
	DDX_Text(pDX, IDC_EDIT_ROT, m_fRot);
	DDV_MinMaxFloat(pDX, m_fRot, -360.f, 360.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	//{{AFX_MSG_MAP(CRotateDlg)
	ON_BN_CLICKED(IDC_RADIO_ROTX, OnRadioRotx)
	ON_BN_CLICKED(IDC_RADIO_ROTY, OnRadioRoty)
	ON_BN_CLICKED(IDC_RADIO_ROTZ, OnRadioRotz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg message handlers

void CRotateDlg::OnRadioRotx() 
{
	// TODO: Add your control notification handler code here
	m_nAxis = 0;
	m_fRot = m_fRx;
	UpdateData(false);
}

void CRotateDlg::OnRadioRoty() 
{
	// TODO: Add your control notification handler code here
	m_nAxis = 1;
	m_fRot = m_fRy;
	UpdateData(false);
}

void CRotateDlg::OnRadioRotz() 
{
	// TODO: Add your control notification handler code here
	m_nAxis = 2;
	m_fRot = m_fRz;
	UpdateData(false);
}

void CRotateDlg::Initialize(float rx, float ry, float rz)
{
	m_fRx = rx;
	m_fRy = ry;
	m_fRz = rz;
}

BOOL CRotateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton *pButton1;
	pButton1 = (CButton*)GetDlgItem(IDC_RADIO_ROTX);
	pButton1->SetCheck(1);

	m_nAxis = 0;
	m_fRot = m_fRx;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
