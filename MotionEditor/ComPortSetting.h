#pragma once
#include "afxwin.h"


// ComPortSetting dialog

class ComPortSetting : public CDialog 
{
	DECLARE_DYNAMIC(ComPortSetting)

public:
	ComPortSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~ComPortSetting();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ComPortSetting::chosePort(int iPort);
	int m_iPortNumber;

private:
	// Control variable for combo box to select com port
	CComboBox m_ctlComboPort;
	
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedOk();
};
