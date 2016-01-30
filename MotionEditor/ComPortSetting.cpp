// ComPortSetting.cpp : implementation file
//

#include "stdafx.h"
#include "MotionEditor.h"
#include "ComPortSetting.h"
#include "afxdialogex.h"


// ComPortSetting dialog

IMPLEMENT_DYNAMIC(ComPortSetting, CDialog)

ComPortSetting::ComPortSetting(CWnd* pParent /*=NULL*/)
	: CDialog(ComPortSetting::IDD, pParent)
{
	
}

ComPortSetting::~ComPortSetting()
{
}

void ComPortSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctlComboPort);
}


BEGIN_MESSAGE_MAP(ComPortSetting, CDialog)
	
	
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDOK, &ComPortSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// ComPortSetting message handlers

void ComPortSetting::chosePort(int iPort)
{
	m_ctlComboPort.SetCurSel(iPort);
}


void ComPortSetting::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	m_ctlComboPort.SetCurSel(m_iPortNumber);

	

	UpdateData(FALSE);
	// TODO: Add your message handler code here
}


void ComPortSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_iPortNumber = m_ctlComboPort.GetCurSel();
	CDialog::OnOK();
}
