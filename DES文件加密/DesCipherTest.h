// NDes.h : main header file for the NDES application
//

#if !defined(AFX_NDES_H__FBD19634_7F6F_42AB_BF63_2C439C7611D0__INCLUDED_)
#define AFX_NDES_H__FBD19634_7F6F_42AB_BF63_2C439C7611D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDesCipherTestApp:
// See NDes.cpp for the implementation of this class
//

class CDesCipherTestApp : public CWinApp
{
public:
	CDesCipherTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesCipherTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDesCipherTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NDES_H__FBD19634_7F6F_42AB_BF63_2C439C7611D0__INCLUDED_)
