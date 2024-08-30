// GUI_camera_captureDlg.h : header file
//

#if !defined(AFX_GUI_CAMERA_CAPTUREDLG_H__B26F69EE_F637_4413_9547_85037747EA4E__INCLUDED_)
#define AFX_GUI_CAMERA_CAPTUREDLG_H__B26F69EE_F637_4413_9547_85037747EA4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGUI_camera_captureDlg dialog

class CGUI_camera_captureDlg : public CDialog
{
// Construction
public:
	CGUI_camera_captureDlg(CWnd* pParent = NULL);	// standard constructor
	
	HANDLE h_WinThread;
	DWORD dwThreadId;

	static DWORD __stdcall SaveVideo(LPVOID lParam);
	HBITMAP CreateRGBBitmap(char* pImage, int nWidth, int nHeight);
// Dialog Data
	//{{AFX_DATA(CGUI_camera_captureDlg)
	enum { IDD = IDD_GUI_CAMERA_CAPTURE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_camera_captureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	int stop_flag;
	
	// Generated message map functions
	//{{AFX_MSG(CGUI_camera_captureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnEnd();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_CAMERA_CAPTUREDLG_H__B26F69EE_F637_4413_9547_85037747EA4E__INCLUDED_)
