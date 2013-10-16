// Application3.h: interface for the Application3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATION3_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
#define AFX_APPLICATION3_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Application.h"

class Application3 : public Application  
{
public:
	Application3();
	virtual ~Application3();
	
	int	Initialize();
	virtual int Render(); 
	int Clean();
};

#endif // !defined(AFX_APPLICATION3_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
