#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKICT_MPApp:
// See KICT_MP.cpp for the implementation of this class
//

class CKICT_MPApp : public CWinApp
{
public:
	CKICT_MPApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CKICT_MPApp theApp;