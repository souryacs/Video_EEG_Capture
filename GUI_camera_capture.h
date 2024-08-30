// GUI_camera_capture.h : main header file for the GUI_CAMERA_CAPTURE application
//

#if !defined(AFX_GUI_CAMERA_CAPTURE_H__72AE5855_7AA3_4216_AB1E_8C31AA3A8E49__INCLUDED_)
#define AFX_GUI_CAMERA_CAPTURE_H__72AE5855_7AA3_4216_AB1E_8C31AA3A8E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGUI_camera_captureApp:
// See GUI_camera_capture.cpp for the implementation of this class
//

class CGUI_camera_captureApp : public CWinApp
{
public:
	CGUI_camera_captureApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_camera_captureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGUI_camera_captureApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_CAMERA_CAPTURE_H__72AE5855_7AA3_4216_AB1E_8C31AA3A8E49__INCLUDED_)
