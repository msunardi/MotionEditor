// WMPWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MotionEditor.h"
#include "WMPWindow.h"
#include "afxdialogex.h"
#include "MotionEditorDlg.h"
#include "listData.h"
// CWMPWindow dialog

IMPLEMENT_DYNAMIC(CWMPWindow, CDialog)

CWMPWindow::CWMPWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CWMPWindow::IDD, pParent) 
{
	
	// m_ctlMP.put_URL(L"C:\\Isobot Videos\\1.3gp");
	
}


CWMPWindow::~CWMPWindow()
{
}

void CWMPWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MP, m_ctlMP);
}


BEGIN_MESSAGE_MAP(CWMPWindow, CDialog)
	ON_BN_CLICKED(ID_MPClose, &CWMPWindow::OnBnClickedMpclose)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CWMPWindow message handlers

void CWMPWindow::OnBnClickedMpclose()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CWMPWindow::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	// TODO: Add your message handler code here
	//m_ctlMP.put_URL(L"C:\\Users\\Public\\Videos\\Sample Videos\\Wildlife.wmv");

	CString path, extention, video_filename;

	path = L"C:\\tt\\";
	extention = L".wmv";
	//video_filename = L"Demo";

	CMotionEditorDlg dt;
	
	
	//m_iVideoNumber = dt.getCommandNumber();

	//video_filename = dt.IntToCstring( m_iVideoNumber);
	//TRACE("%d",m_iVideoNumber);
	//m_ctlMP.put_URL(L"C:\\Isobot Videos\\1.3gp");
	CString str;
	str.Format(L"%d",m_iVideoNumber);

	m_ctlMP.put_URL(path+str+extention);


}
//
//BEGIN_EVENTSINK_MAP(CWMPWindow, CDialog)
//END_EVENTSINK_MAP()


