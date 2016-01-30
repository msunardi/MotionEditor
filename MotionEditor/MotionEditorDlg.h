
// MotionEditorDlg.h : header file
//

#pragma once

#include "Expression.h"
#include "MIDI.h"
#include "CSV_Reader.h"
#include "listData.h"
#include "SerialPort.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "wmpwindow.h"
#include "SaveLoad.h"
#include "ComPortSetting.h"

// CMotionEditorDlg dialog
class CMotionEditorDlg : public CDialogEx
{
// Construction
public:
	CMotionEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MOTIONEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
	enum {
		iSobotA = 0,
		iSobotB = 1
	};

	enum {
		COMPOSE_MODE = 0,
		ACTION_MODE = 1,
		SCRIPT_MODE = 2
	};

	enum{
		SCRIPT_RANK = 0,
		SCRIPT_ROBOT = 1,
		SCRIPT_NAME = 2,
		SCRIPT_TIME = 3,
		SCRIPT_MELODY = 4,
		SCRIPT_ACTION = 5
	};
	
	enum {
	MESSAGE_BOX_RETURN_YES = 6,
	MESSAGE_BOX_RETURN_NO = 7
	}returnMsgBox;

#define VIDEO	(path+video_filename + extention)

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
private:
	afx_msg void OnBnClickedMfcbuttonUp();
	afx_msg void OnBnClickedBsend();
	afx_msg void OnBnClickedBon();
	afx_msg void OnBnClickedBoff();
	afx_msg void OnBnClickedMfcbuttonDown();
	afx_msg void OnBnClickedMfcbuttonDelete();
	afx_msg void OnBnClickedMfcbuttonPlay();
	afx_msg void OnBnClickedBclose();
	afx_msg void OnNMDblclkListCommands(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListScript(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListExpression(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBplaymidi();
	afx_msg void OnNMClickListMidicomposer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBspeak();
	afx_msg void OnBnClickedBinsertspeech();
	afx_msg void OnBnClickedBgroup();
	afx_msg void OnNMClickListCommands(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	afx_msg void OnModeCompose();
	afx_msg void OnUpdateModeCompose(CCmdUI *pCmdUI);
	afx_msg void OnModeAction();
	afx_msg void OnUpdateModeAction(CCmdUI *pCmdUI);
	afx_msg void OnModeScript();
	afx_msg void OnUpdateModeScript(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedBclearmidi();
	afx_msg void OnNMThemeChangedSliderMidiscale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderMidiscale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedBaddMidi();
	afx_msg void OnScriptSave();
	afx_msg void OnScriptLoad();
	afx_msg void OnScriptNew();
	afx_msg void OnScriptExit();
	afx_msg void OnUpdateRobotIsobota(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRobotIsobotb(CCmdUI *pCmdUI);
	afx_msg void OnRobotIsobota();
	afx_msg void OnRobotIsobotb();
	afx_msg void OnBnClickedMfcbuttonBota();
	afx_msg void OnBnClickedMfcbuttonBotb();
	afx_msg void OnBnClickedMfcbuttonPause();

	// Controller for List script
	CListCtrl m_ctlListScript;
	// Controller for Expression List
	CListCtrl m_ctlExprList;
	// Controller for List of Commands
	CListCtrl m_ctlListCommands;
	// Controller for Composer List
	CListCtrl m_ctlListComposer;
	
	// Control Variable for Windows Media Player Window
	CWMPWindow m_ctlWMPWindow;
	ComPortSetting m_ctlComPortSetting;

	// Button for inserting speech
	CButton m_ctlBInsertSpeech;
	
	// Serial Port object for ISOBOT
	CSerialPort Serial_Port;
	// Controller for MIDI progress bar
	CProgressCtrl m_ctlProgressBarMidi;
	// MIDI composer object
	CMIDI midi;

	// CSV Reader object
	CSV_Reader csv;

	// Controller for TextTo Speak Editor
	CEdit m_ctlEditTextToSpeak;
	// String value of text to be spoken
	CString m_strTextToSpeak;

	// interger value for MIDI Progress
	int m_iMidiProgress;
	// controller for comobo box of MIDI
	CComboBox m_ctlComboxMidi;
	// Combo Box Values
	int m_iComboxMidi;
	// Controller for Compose Name Editor
	CEdit m_ctlEditComposeName;
	// Controller for adding compose Name Button
	CButton m_ctlBAddComposeName;
	// string value of compose name
	CString m_strEditComposeName;
	// controller for slider to adjust MIDI scale
	CSliderCtrl m_ctlSliderScale;
	// integer value of MIDI scale
	int m_iSliderScale;


	// To select among 3 modes: COMPOSE_MODE, ACTION_MODE, SCRIPT_MODE
	int m_mode;
	// To select among 2 robots: iSobotA, iSobotB (May increase here more)
	int m_robot;
	
	// stores code for ISOBOT commands
	int command_number;
	int m_iCmndNum;
	
	int m_iItemScript;
	LVITEM m_lvitem;

	// Timer Variable for iSobot command time events
	UINT m_uiTimerVal;
	// Timer Variable for Midi events
	UINT m_uiMidiTimer;
	
	
	// Script vector
	vector<int> vScriptRow;
	vector < vector <int> > vScript;
	
	// This has same form as Script vector only except, it is after processing the regular expression
	vector <int> vectorTm ;
	vector < vector <int> > vectorToPlay ;
	
	
	vector <CString> vSpeech;
	vector <CString> ::iterator iterVecSpeech;

	// List box and Script box initialization
	void ScriptInitialize(void);
	void FillScriptRow();
	UINT StartTimer(UINT iTimeDuration);
	void getCommandsForRobot(int Robot);
	void composerInitialize();
	void speechInitialize();
	void musicNamesInitialize();
	void UpdateComposeMatrix();

	typedef struct robotCommandStructure{
		CString command_isobot[140];
		char * Command_code[140];
		int TimeForCommand[140];
	}robotStructure;

	robotStructure m_bot[2];

	/*CString command_isobot[300];
	char * Command_code[300];
	int TimeForCommand[300];*/
	
	CString instruments[128];
	CString getChar(int expressionNum);

	void getPattern();
	int m_iPtrn;

	BOOL matrix[10][20];
	BOOL pattern[10];

	typedef struct composure {
		BOOL m_sMatrix[10][20];
		CString m_sComposeName;
		int m_sScale;
		int m_sInstrument;
	}m_sComposure;

	m_sComposure melody[100];
	int m_melodySelected;
	int m_midiInstrument;
	
	CSaveLoad m_slScript;
	CSaveLoad m_slMelody;

	// Tracking number while playing all items in script
	int m_iPlayItemNumber;
	void CMotionEditorDlg::newMelodyInComposer(int iMelody);

	// To send command to bot 
	void CMotionEditorDlg::SendCommandToBot(int iBot, int iCmd_num);

public:
	int m_iCommandListItem;
	// Converts integer into CString
	CString IntToCstring(int iNumber);
	
	
	
	
	afx_msg void OnSettingsSerialport();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	


};
