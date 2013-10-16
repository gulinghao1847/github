// CS580HWDoc.cpp : implementation of the CCS580HWDoc class
//

#include "stdafx.h"
#include "CS580HW.h"

#include "CS580HWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCS580HWDoc

IMPLEMENT_DYNCREATE(CCS580HWDoc, CDocument)

BEGIN_MESSAGE_MAP(CCS580HWDoc, CDocument)
	//{{AFX_MSG_MAP(CCS580HWDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCS580HWDoc construction/destruction

CCS580HWDoc::CCS580HWDoc()
{
	// TODO: add one-time construction code here

}

CCS580HWDoc::~CCS580HWDoc()
{
}

BOOL CCS580HWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCS580HWDoc serialization

void CCS580HWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCS580HWDoc diagnostics

#ifdef _DEBUG
void CCS580HWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCS580HWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCS580HWDoc commands
