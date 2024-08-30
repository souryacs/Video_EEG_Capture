// GUI_camera_captureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_camera_capture.h"
#include "GUI_camera_captureDlg.h"
#include "cv.h"
#include "highgui.h"



#include <windows.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include <float.h>
#include <vector>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTHBYTES(bits) ((((bits) + 31) / 32) * 4)   

int video_flag;
int session_count = 0;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUI_camera_captureDlg dialog

CGUI_camera_captureDlg::CGUI_camera_captureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGUI_camera_captureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGUI_camera_captureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGUI_camera_captureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGUI_camera_captureDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGUI_camera_captureDlg, CDialog)
	//{{AFX_MSG_MAP(CGUI_camera_captureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, OnStart)
	ON_BN_CLICKED(ID_END, OnEnd)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUI_camera_captureDlg message handlers

BOOL CGUI_camera_captureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGUI_camera_captureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

/*void CGUI_camera_captureDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}*/

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGUI_camera_captureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGUI_camera_captureDlg::OnStart() 
{
	// TODO: Add your control notification handler code here

	stop_flag=1;
	video_flag=1;
	CButton *v2 = (CButton*) this->GetDlgItem(ID_START);
	v2->EnableWindow(FALSE);
	v2->ShowWindow(TRUE);

	CButton *v1 = (CButton*) this->GetDlgItem(ID_END);
	v1->ShowWindow(TRUE);
	v1->EnableWindow(TRUE);

	session_count = session_count+1;
	h_WinThread = CreateThread(NULL, 0, SaveVideo, (LPVOID)this, 0, &dwThreadId);
	if(h_WinThread == NULL)
	{
		::AfxMessageBox("Failed to Initialize Camera");
	}


	/*
	CBitmap Bmp1;
	Bmp1.LoadBitmap(IDB_BITMAP2);

	CStatic *pic = (CStatic *) this->GetDlgItem(IDC_STATIC);
	pic->SetBitmap(Bmp1);*/

}

void CGUI_camera_captureDlg::OnEnd() 
{
	// TODO: Add your control notification handler code here
	video_flag=0;
	stop_flag=0;
	cvWaitKey(100);

	CButton *v2 = (CButton*) this->GetDlgItem(ID_START);
	v2->EnableWindow(TRUE);
	v2->ShowWindow(TRUE);

	CButton *v1 = (CButton*) this->GetDlgItem(ID_END);
	v1->ShowWindow(TRUE);
	v1->EnableWindow(FALSE);

	//m_pThread->SuspendThread();
	//::AfxMessageBox("Hello");
	CloseHandle(h_WinThread);
	//::AfxMessageBox("Hello 32");
}

void CGUI_camera_captureDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	exit(0);
}



DWORD CGUI_camera_captureDlg::SaveVideo(LPVOID lParam) 
{   
	CvCapture* cv_cap = 0;
	CGUI_camera_captureDlg *pThis = (CGUI_camera_captureDlg *)lParam;
	
	int CUTOFF = 30;    //85;
    double ALPHA = .1; //.05;
    double THRESHOLD_RATIO = .002;  //.06;
    
	
    int motion_interval_array [100][2]; 
    int motion_interval_count = 0;
   
    int video_display = 1;
    //char * video_file_name = filename;
     
    
	int c, i, j;
	IplImage* cap_frame=0;
	IplImage* mod_frame = 0;
	IplImage* ref_frame = 0;
	IplImage* ext_frame = 0;

	//char* save_filename = "captured_video_";

	// file open
	std::string save_metadata_filename = "metadata//output_session";
	std::string session_count_str;
	std::stringstream session_count_out;
	session_count_out << session_count;
	session_count_str = session_count_out.str();
	save_metadata_filename = save_metadata_filename.append(session_count_str);
	save_metadata_filename = save_metadata_filename.append(".txt");
	char *save_metadata_filename_ary = new char[save_metadata_filename.length()+1];
	strcpy ( save_metadata_filename_ary, save_metadata_filename.c_str() ); // that is correct
				
	FILE *fid = fopen(save_metadata_filename_ary,"w");

    if (fid == NULL)
        printf("\n cannot open out file");
    
	/* capture from web cam */

	cv_cap = cvCaptureFromCAM(1);

    if( !cv_cap )
    {
		cv_cap = cvCaptureFromCAM(0);
		 if( !cv_cap )
		 {
	
			::AfxMessageBox("No Camera found");
			return 1;
		 }
    }
		
	/* Allocate space for other images */
	cap_frame = cvQueryFrame(cv_cap);
	IplImage *resize=cvCreateImage(cvSize(cap_frame->width, cap_frame->height),8,3);
	
	if(!cap_frame)
		::AfxMessageBox("cap_frame NULL");

	mod_frame = cvCreateImage(cvSize(cap_frame->width,cap_frame->height),IPL_DEPTH_8U, 3);
	ref_frame = cvCreateImage(cvSize(cap_frame->width,cap_frame->height),IPL_DEPTH_8U, 1);
	ext_frame = cvCreateImage(cvSize(cap_frame->width,cap_frame->height),IPL_DEPTH_8U, 1);

	mod_frame->origin = cap_frame->origin;
	ref_frame->origin = cap_frame->origin;
	ext_frame->origin = cap_frame->origin;

	
	cvCopy(cap_frame, mod_frame, 0);


	int state = 0;  //motion defining variable
    int count = 0;
	int frame_count = 1;
	

	CStatic *cs = (CStatic *) pThis->GetDlgItem(IDC_STATIC);
	HBITMAP hBitmap;
		
	CvVideoWriter *writer = 0;
	int isColor = 1;
	int fps     = 5;
	int frameW  = cap_frame->width; // 744 for firewire cameras
	int frameH  = cap_frame->height; // 480 for firewire cameras
	
	char dateStr [9];
    char timeStr [9];
    _strdate( dateStr);
	fprintf(fid, "fps, date, time, start frame number (global), frame count in the segment... \n");
    fprintf(fid, "%d \n", fps);
    fprintf(fid, "%s \n", dateStr);
    _strtime( timeStr );
    fprintf(fid, "%s \n", timeStr);
	//fprintf(fid, "fps = %d, posMsec = %f, posFrames = %d, posRatio = %f \n", fps, cvGetCaptureProperty(cv_cap, CV_CAP_PROP_POS_MSEC), (int) cvGetCaptureProperty(cv_cap, CV_CAP_PROP_POS_FRAMES), cvGetCaptureProperty(cv_cap, CV_CAP_PROP_POS_AVI_RATIO));
	//hBitmap =pThis->CreateRGBBitmap(cap_frame->imageData, cap_frame->width, cap_frame->height); 
	//cs->SetBitmap(hBitmap);
	int segment_frame_count = 0;
	
    while(video_flag)
    {
		cvCopy(ext_frame, ref_frame, 0);
      
        cap_frame = cvQueryFrame( cv_cap );
        if(!cap_frame){
			cvReleaseCapture( &cv_cap );
			//cvReleaseVideoWriter(&writer);
			cvReleaseImage(&cap_frame);
			::AfxMessageBox("Vidoe Input Not Found");
			break;
		}
		else
			frame_count++;
         
	   	cvResize(cap_frame, resize,CV_INTER_NN);
		hBitmap =pThis->CreateRGBBitmap(resize->imageData, resize->width, resize->height); 
		cs->SetBitmap(hBitmap);
		
		// compare the current frame vs the background reference frame pixel by pixel comparison 
        for(j = 0; j < cap_frame->width; j++){
			for(i = 0; i < cap_frame->height; i++){
				int tot = 0;
                for(int k = 1; k<3; k++){
                        tot = tot + abs((mod_frame->imageData + i*cap_frame->widthStep)[j*cap_frame->nChannels + k] 
										- (cap_frame->imageData + i*cap_frame->widthStep)[j*cap_frame->nChannels + k]);
                }
                // if the difference is greater than cutoff then we store the 
				// pixel as black in the corresponding stored binary image

				if ((tot/3) > CUTOFF){
					((uchar *)(ext_frame->imageData + i*cap_frame->width))[j] = 255;
				}
                else{    // white pixel
					((uchar *)(ext_frame->imageData + i*cap_frame->width))[j] = 0;
					
					// update the background model
                    for(int k = 1; k<3; k++){
                            (mod_frame->imageData + i*cap_frame->widthStep)[j*cap_frame->nChannels + k] = 
								(1-ALPHA) * (mod_frame->imageData + i*cap_frame->widthStep)[j*cap_frame->nChannels + k] 
								+ ALPHA * (cap_frame->imageData + i*cap_frame->widthStep)[j*cap_frame->nChannels + k];
					}
                } 
			}
		}
		
		// if (fps/5)th frame has significant difference corresponding to the background 
		// reference frame then update the state variable

		int eq = 0; 
		int neq = 0;
        for(j = 0; j < cap_frame->width; j++){
			for(i = 0; i < cap_frame->height; i++){
				
				if ((ref_frame->imageData + i*cap_frame->width)[j] != (ext_frame->imageData + i*cap_frame->width)[j]){
					eq = eq + 1;
				}
                else{
					neq = neq + 1;
				}
			}
		}
        double matching_index = (double)((double)eq /(double) neq);
        
		//fprintf(fid, "\n -- eq : %d  neq : %d  matching index : %f   frame_count : %d", eq, neq, matching_index, frame_count);      
        //printf("\n -- eq : %d  neq : %d  matching index : %f   frame_count : %d", eq, neq, matching_index, frame_count);      
       
	    
		if ( matching_index > THRESHOLD_RATIO ){
			count = 1;
				
			if (state == 0){
				state = 1;
				fprintf(fid, "\n%d", (frame_count));
				segment_frame_count = 1;
                //printf("\n ***************   motion start - frame no : %d", (frame_count));
                //graph_data = [graph_data 1];
                motion_interval_array[motion_interval_count][0] = frame_count;

							
				std::string save_filename = "video//video_session";
				/*std::string session_count_str;
				std::stringstream session_count_out;
				session_count_out << session_count;
				session_count_str = session_count_out.str();*/
				save_filename = save_filename.append(session_count_str);
				std::string count_str = "_segment";
				std::stringstream out;
				out << motion_interval_count;
				count_str = count_str.append(out.str());
				save_filename = save_filename.append(count_str);				
				save_filename = save_filename.append(".avi");
				char *save_filename_ary = new char[save_filename.length()+1];
				strcpy ( save_filename_ary, save_filename.c_str() ); // that is correct
				
				
			//	writer=cvCreateVideoWriter(save_filename_ary,-1,fps,cvSize(frameW,frameH),isColor);
				 
			/*	writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('D','I','V','X'),fps,cvSize(frameW,frameH),isColor);
				if(writer==NULL){
					::AfxMessageBox("DIVX writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('M','J','P','G'),fps,cvSize(frameW,frameH),isColor);
				}
				if (writer == NULL){
					::AfxMessageBox("MJPG writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('P','I','M','1'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("PIMI writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('P','I','C','1'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("PICI writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('M','P','4','2'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("MP42 writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('D','I','V','3'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){ 
					::AfxMessageBox("DIV3 writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('V','P','3','1'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("VP31 writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('V','P','3','0'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("VP30 writer == NULL");*/
					writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('C','V','I','D'),fps,cvSize(frameW,frameH),isColor);
				//}
				if(writer==NULL){
					::AfxMessageBox("CVID writer == NULL");
					}
				/*	writer = cvCreateVideoWriter(save_filename_ary,CV_FOURCC('f','f','d','s'),fps,cvSize(frameW,frameH),isColor);
				}
				if(writer==NULL){
					::AfxMessageBox("ffds writer == NULL");
					writer = cvCreateVideoWriter(save_filename_ary,-1,fps,cvSize(frameW,frameH),isColor); // ask usr to choose
				}*/
				
				cvWriteFrame(writer,cap_frame);
				
			}
            else if (state ==1){
				state = 1;
				segment_frame_count++;
                //fprintf(fid, "\n ***************   continue motion - frame no : %d", (frame_count));
                //printf("\n ***************   continue motion - frame no : %d", (frame_count));
				cvWriteFrame(writer,cap_frame);
				
                //graph_data = [graph_data 1];
            }
		}
        else{
			if (state ==1){
				state = 0;
                ref_frame = cvCreateImage(cvSize(cap_frame->width,cap_frame->height),IPL_DEPTH_8U, 1);
				ext_frame = cvCreateImage(cvSize(cap_frame->width,cap_frame->height),IPL_DEPTH_8U, 1);
				ref_frame->origin = cap_frame->origin;
				ext_frame->origin = cap_frame->origin;

				cvCopy(cap_frame, mod_frame, 0);
				segment_frame_count++;
                fprintf(fid, " %d", segment_frame_count);
				segment_frame_count = 0;
                //printf("\n end motion - frame no : %d **************", (frame_count));
                motion_interval_array[motion_interval_count][1] = frame_count;
                motion_interval_count = motion_interval_count+1;
				cvReleaseVideoWriter(&writer);
			}
					
        }
		

		if(pThis->stop_flag==0)
		{
			if (fid != NULL)
				fclose(fid);
							
			for(int kk = 0; kk<motion_interval_count; kk++){
				printf("\n motion_interval_array[%d][0] = %d, \t motion_interval_array[%d][1] = %d ", kk, motion_interval_array[kk][0], kk, motion_interval_array[kk][1]);
			}
			//fprintf(fid, "\n end motion - frame no : %d  time : %f *****************", (frame_count), (frame_count)/25);
            //printf("\n end motion - frame no : %d  time : %f **************", (frame_count), (frame_count)/25);
			if(motion_interval_array[motion_interval_count][1] == 0){
			   motion_interval_array[motion_interval_count][1] = frame_count;
			}
			
			//dlmwrite(motion_interval_file,motion_interval_array);
			   
			//::AfxMessageBox("Video saved");
			cvReleaseCapture( &cv_cap );
			cvReleaseVideoWriter(&writer);
			break;

		}

    }

	return 1;
}




 HBITMAP CGUI_camera_captureDlg::CreateRGBBitmap(char* pImage, int nWidth, int nHeight)
 {
			 LPBITMAPINFO lpbi = new BITMAPINFO;
             lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
             lpbi->bmiHeader.biWidth = nWidth;
             lpbi->bmiHeader.biHeight = nHeight;
             lpbi->bmiHeader.biPlanes = 1;
             lpbi->bmiHeader.biBitCount = 24;
             lpbi->bmiHeader.biCompression = BI_RGB;
             lpbi->bmiHeader.biSizeImage = WIDTHBYTES((DWORD)nWidth * 8) * nHeight;
             lpbi->bmiHeader.biXPelsPerMeter = 0;
             lpbi->bmiHeader.biYPelsPerMeter = 0;
             lpbi->bmiHeader.biClrUsed = 0;
             lpbi->bmiHeader.biClrImportant = 0;        

             void* pBits;

             HBITMAP hBitmap = CreateDIBSection(NULL,lpbi,DIB_RGB_COLORS,(void **)&pBits,NULL,0 );

             delete lpbi;

             if ( hBitmap )
                SetBitmapBits(hBitmap, nWidth*nHeight*3, pImage);

             return hBitmap;
 }
