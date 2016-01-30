#pragma once
#include "CWMPPlayer4.h"

// CWMPWindow dialog

class CWMPWindow : public CDialog
{
	DECLARE_DYNAMIC(CWMPWindow)

public:
	CWMPWindow(CWnd* pParent = NULL);   // standard constructor

	virtual ~CWMPWindow();

// Dialog Data
	enum { IDD = IDD_MPWINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMpclose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	// Control variable for Windows Media Player
	CWMPPlayer4 m_ctlMP;
	int m_iVideoNumber;
	
	
};
