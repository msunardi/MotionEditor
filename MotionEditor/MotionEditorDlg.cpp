
// MotionEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MotionEditor.h"
#include "WMPWindow.h"
#include "ComPortSetting.h"
#include "MotionEditorDlg.h"
#include "afxdialogex.h"
#include "listData.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SERIAL_PORT_NUMBER		4
#define COMMAND_SPEECH			1000
#define COMMAND_BRACE_OPEN		995
#define COMMAND_BRACE_CLOSE		996


// CMotionEditorDlg dialog

CMotionEditorDlg::CMotionEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotionEditorDlg::IDD, pParent)
	, m_strTextToSpeak(_T(""))
	, m_iMidiProgress(0)
	, m_iComboxMidi(0)
	, m_strEditComposeName(_T(""))
	, m_iSliderScale(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	command_number = 0;
	m_iCmndNum = 0;
}

void CMotionEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCRIPT, m_ctlListScript);
	DDX_Control(pDX, IDC_LIST_EXPRESSION, m_ctlExprList);
	DDX_Control(pDX, IDC_LIST_COMMANDS, m_ctlListCommands);
	DDX_Control(pDX, IDC_LIST_MIDICOMPOSER, m_ctlListComposer);
	DDX_Control(pDX, IDC_TextToSpeak, m_ctlEditTextToSpeak);
	DDX_Control(pDX, IDC_BInsertSpeech, m_ctlBInsertSpeech);
	DDX_Text(pDX, IDC_TextToSpeak, m_strTextToSpeak);
	DDX_Control(pDX, IDC_PROGRESS_MIDI, m_ctlProgressBarMidi);
	DDX_Control(pDX, IDC_COMBO2, m_ctlComboxMidi);
	DDX_Control(pDX, IDC_EDIT_ComposeName, m_ctlEditComposeName);
	DDX_Control(pDX, IDC_BAdd_MIDI, m_ctlBAddComposeName);
	DDX_Text(pDX, IDC_EDIT_ComposeName, m_strEditComposeName);
	DDX_Control(pDX, IDC_SLIDER_MIDIScale, m_ctlSliderScale);
	DDX_Slider(pDX, IDC_SLIDER_MIDIScale, m_iSliderScale);
}

BEGIN_MESSAGE_MAP(CMotionEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_INITMENUPOPUP()	// For Dialog Menu item check fix
	ON_BN_CLICKED(IDC_MFCBUTTON_UP, &CMotionEditorDlg::OnBnClickedMfcbuttonUp)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMMANDS, &CMotionEditorDlg::OnNMDblclkListCommands)
	ON_BN_CLICKED(IDC_BSEND, &CMotionEditorDlg::OnBnClickedBsend)
	ON_BN_CLICKED(IDC_BON, &CMotionEditorDlg::OnBnClickedBon)
	ON_BN_CLICKED(IDC_BOFF, &CMotionEditorDlg::OnBnClickedBoff)
	ON_BN_CLICKED(IDC_MFCBUTTON_DOWN, &CMotionEditorDlg::OnBnClickedMfcbuttonDown)
	ON_BN_CLICKED(IDC_MFCBUTTON_DELETE, &CMotionEditorDlg::OnBnClickedMfcbuttonDelete)
	ON_BN_CLICKED(IDC_MFCBUTTON_PLAY, &CMotionEditorDlg::OnBnClickedMfcbuttonPlay)
	ON_BN_CLICKED(IDC_BClose, &CMotionEditorDlg::OnBnClickedBclose)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCRIPT, &CMotionEditorDlg::OnNMClickListScript)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EXPRESSION, &CMotionEditorDlg::OnNMClickListExpression)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BPlayMidi, &CMotionEditorDlg::OnBnClickedBplaymidi)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MIDICOMPOSER, &CMotionEditorDlg::OnNMClickListMidicomposer)
	ON_BN_CLICKED(IDC_BSpeak, &CMotionEditorDlg::OnBnClickedBspeak)
	ON_BN_CLICKED(IDC_BInsertSpeech, &CMotionEditorDlg::OnBnClickedBinsertspeech)
	ON_BN_CLICKED(IDC_BGroup, &CMotionEditorDlg::OnBnClickedBgroup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMMANDS, &CMotionEditorDlg::OnNMClickListCommands)
	ON_COMMAND(ID_MODE_COMPOSE, &CMotionEditorDlg::OnModeCompose)
	ON_UPDATE_COMMAND_UI(ID_MODE_COMPOSE, &CMotionEditorDlg::OnUpdateModeCompose)
	ON_COMMAND(ID_MODE_ACTION, &CMotionEditorDlg::OnModeAction)
	ON_UPDATE_COMMAND_UI(ID_MODE_ACTION, &CMotionEditorDlg::OnUpdateModeAction)
	ON_COMMAND(ID_MODE_SCRIPT, &CMotionEditorDlg::OnModeScript)
	ON_UPDATE_COMMAND_UI(ID_MODE_SCRIPT, &CMotionEditorDlg::OnUpdateModeScript)
	ON_BN_CLICKED(IDC_BClear_midi, &CMotionEditorDlg::OnBnClickedBclearmidi)
	ON_BN_CLICKED(IDC_BAdd_MIDI, &CMotionEditorDlg::OnBnClickedBaddMidi)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMotionEditorDlg::OnCbnSelchangeCombo2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MIDIScale, &CMotionEditorDlg::OnNMReleasedcaptureSliderMidiscale)
	ON_COMMAND(ID_SCRIPT_SAVE, &CMotionEditorDlg::OnScriptSave)
	ON_COMMAND(ID_SCRIPT_LOAD, &CMotionEditorDlg::OnScriptLoad)
	ON_COMMAND(ID_SCRIPT_NEW, &CMotionEditorDlg::OnScriptNew)
	ON_COMMAND(ID_SCRIPT_EXIT, &CMotionEditorDlg::OnScriptExit)
	ON_UPDATE_COMMAND_UI(ID_ROBOT_ISOBOTA, &CMotionEditorDlg::OnUpdateRobotIsobota)
	ON_UPDATE_COMMAND_UI(ID_ROBOT_ISOBOTB, &CMotionEditorDlg::OnUpdateRobotIsobotb)
	ON_COMMAND(ID_ROBOT_ISOBOTA, &CMotionEditorDlg::OnRobotIsobota)
	ON_COMMAND(ID_ROBOT_ISOBOTB, &CMotionEditorDlg::OnRobotIsobotb)
	ON_BN_CLICKED(IDC_MFCBUTTON_BOTA, &CMotionEditorDlg::OnBnClickedMfcbuttonBota)
	ON_BN_CLICKED(IDC_MFCBUTTON_BOTB, &CMotionEditorDlg::OnBnClickedMfcbuttonBotb)
	ON_BN_CLICKED(IDC_MFCBUTTON_PAUSE, &CMotionEditorDlg::OnBnClickedMfcbuttonPause)
	ON_COMMAND(ID_SETTINGS_SERIALPORT, &CMotionEditorDlg::OnSettingsSerialport)
END_MESSAGE_MAP()


// CMotionEditorDlg message handlers


BOOL CMotionEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	m_mode = SCRIPT_MODE;
	m_robot = iSobotA;
	m_ctlComPortSetting.m_iPortNumber = SERIAL_PORT_NUMBER;

	
	
	// Initialize items in List boxes : Command list box & Script report list box
	ScriptInitialize();
	
	// Initialize Composer list box
	composerInitialize();

	speechInitialize();
	
	musicNamesInitialize();
	
	// Update data
	UpdateData(FALSE);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMotionEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
	



}




// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMotionEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMotionEditorDlg::speechInitialize()
{
	// TODO: Add your control notification handler code here

	// Initialize Speech buttons, text edits

	m_ctlEditTextToSpeak.ShowWindow(FALSE);
	m_ctlBInsertSpeech.ShowWindow(FALSE);


}


void CMotionEditorDlg::OnNMDblclkListCommands(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(m_mode == ACTION_MODE)
	{
		m_ctlWMPWindow.m_iVideoNumber = pNMItemActivate->iItem;
		// Display the video of selected command
		m_ctlWMPWindow.DoModal();
	}
	
	if(m_mode == SCRIPT_MODE)
	{
		// Command Number
		m_iCmndNum = pNMItemActivate->iItem;
	
		vScriptRow.at(SCRIPT_RANK) = vScript.size();
		vScriptRow.at(SCRIPT_ROBOT) = m_robot;
		vScriptRow.at(SCRIPT_NAME) = m_iCmndNum;
		vScriptRow.at(SCRIPT_TIME) = m_bot[m_robot].TimeForCommand[m_iCmndNum];
		vScriptRow.at(SCRIPT_MELODY) = 0;
		vScriptRow.at(SCRIPT_ACTION) = 0;
		vScript.push_back(vScriptRow);

		// Insert the item in list box
		m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");
	
		// Fill the rows of Script report with properties associated with command number 
		CMotionEditorDlg::FillScriptRow();
	}
		
	
	UpdateData(FALSE);

	*pResult = 0;
}


void CMotionEditorDlg::FillScriptRow()
{
	// Delete extra items in the list if any
	for(int iItem = vScript.size(); iItem < m_ctlListScript.GetItemCount(); iItem++)
		m_ctlListScript.DeleteItem(iItem);

	vector <int > :: iterator iterVSRow;
	vector < vector <int> > :: iterator iterVScript;

	CString strColumn[6];

	TRACE("\n");

	for(iterVScript = vScript.begin() ; iterVScript != vScript.end(); iterVScript++)
		(*iterVScript)[0] = iterVScript - vScript.begin();



	for(iterVScript = vScript.begin() ; iterVScript != vScript.end(); iterVScript++)
	{
		vScriptRow = (*iterVScript);
		m_iCmndNum = vScriptRow.at(SCRIPT_NAME);
		//(*iterVScript)[0] = iterVScript - vScript.begin();
		
		if (m_iCmndNum >= COMMAND_SPEECH)
		{
			CString strSpeech = vSpeech.at(m_iCmndNum - COMMAND_SPEECH - 1);
			strSpeech = L"****SPEECH > " + strSpeech;
		
			strColumn[SCRIPT_RANK]	= IntToCstring(vScriptRow[SCRIPT_RANK]);		// Column 0: Script Item Number
			strColumn[SCRIPT_ROBOT] = L" --- ";										// Column 1: No Robot selected
			strColumn[SCRIPT_NAME]	= strSpeech;									// Column 2: Command Name	
			strColumn[SCRIPT_TIME]	= IntToCstring(vScriptRow[SCRIPT_TIME]);		// Column 3: Time for command
			strColumn[SCRIPT_MELODY]= L" --- ";										// Column 4: Melody Name
			strColumn[SCRIPT_ACTION]= getChar(vScriptRow[SCRIPT_ACTION]);			// Column 5: Expression for command

		}else
		if (m_iCmndNum == COMMAND_PAUSE)
		{
			CString strMelody = melody[vScriptRow[SCRIPT_MELODY]].m_sComposeName;
			int iRobot = vScriptRow[SCRIPT_ROBOT];

			strColumn[SCRIPT_RANK]	= IntToCstring(vScriptRow[SCRIPT_RANK]);		// Column 0: Script Item Number
			strColumn[SCRIPT_ROBOT] = L" --- ";										// Column 1: No Robot selected
			strColumn[SCRIPT_NAME]	= L"--------PAUSE---------";					// Column 2: Command Name	
			strColumn[SCRIPT_TIME]	= IntToCstring(vScriptRow[SCRIPT_TIME]);		// Column 3: Time for command
			strColumn[SCRIPT_MELODY]= strMelody;									// Column 4: Melody Name
			strColumn[SCRIPT_ACTION]= getChar(vScriptRow[SCRIPT_ACTION]);			// Column 5: Expression for command

		}else
		if (m_iCmndNum == COMMAND_BRACE_OPEN)
		{
			strColumn[SCRIPT_RANK]	= IntToCstring(vScriptRow[SCRIPT_RANK]);		// Column 0: Script Item Number
			strColumn[SCRIPT_ROBOT] = L" --- ";										// Column 1: No Robot selected
			strColumn[SCRIPT_NAME]	= L"  (";										// Column 2: Command Name	
			strColumn[SCRIPT_TIME]	= L" --- ";										// Column 3: Time for command
			strColumn[SCRIPT_MELODY]= L" --- ";										// Column 4: Melody Name
			strColumn[SCRIPT_ACTION]= getChar(vScriptRow[SCRIPT_ACTION]);			// Column 5: Expression for command

		}else
		if (m_iCmndNum == COMMAND_BRACE_CLOSE)
		{
			strColumn[SCRIPT_RANK]	= IntToCstring(vScriptRow[SCRIPT_RANK]);		// Column 0: Script Item Number
			strColumn[SCRIPT_ROBOT] = L" --- ";										// Column 1: No Robot selected
			strColumn[SCRIPT_NAME]	= L"  )";										// Column 2: Command Name	
			strColumn[SCRIPT_TIME]	= L" --- ";										// Column 3: Time for command
			strColumn[SCRIPT_MELODY]= L" --- ";										// Column 4: Melody Name
			strColumn[SCRIPT_ACTION]= getChar(vScriptRow[SCRIPT_ACTION]);			// Column 5: Expression for command
		}
		
		else
		{
			CString strMelody = melody[vScriptRow[SCRIPT_MELODY]].m_sComposeName;
			int iRobot = vScriptRow[SCRIPT_ROBOT];

			strColumn[SCRIPT_RANK]	= IntToCstring(vScriptRow[SCRIPT_RANK]);						// Column 0: Script Item Number
			strColumn[SCRIPT_ROBOT] = ( iRobot == iSobotA) ? L"Bot A" : L"Bot B";					// Column 1: Robot selected
			strColumn[SCRIPT_NAME]	= m_bot[iRobot].command_isobot[m_iCmndNum];						// Column 2: Command Name	
			strColumn[SCRIPT_TIME]	= IntToCstring(m_bot[m_robot].TimeForCommand[m_iCmndNum]);		// Column 3: Time for command
			strColumn[SCRIPT_MELODY]= strMelody;													// Column 4: Melody Name
			strColumn[SCRIPT_ACTION]= getChar(vScriptRow[SCRIPT_ACTION]);							// Column 5: Expression for command
		}

		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_RANK,  strColumn[SCRIPT_RANK]);	// Column 0: Script Item Number
		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_ROBOT, strColumn[SCRIPT_ROBOT]);	// Column 1: Robot selected
		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_NAME,  strColumn[SCRIPT_NAME]);	// Column 2: Command Name	
		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_TIME,  strColumn[SCRIPT_TIME]);	// Column 3: Time for command
		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_MELODY,strColumn[SCRIPT_MELODY]);// Column 4: Melody Name
		m_ctlListScript.SetItemText(vScriptRow[SCRIPT_RANK],SCRIPT_ACTION,strColumn[SCRIPT_ACTION]);// Column 5: Expression for command
		
	} 

	
	printExpression(vScript, vScriptRow);

	m_ctlListScript.UpdateWindow();
	
	UpdateData(FALSE);

}


CString CMotionEditorDlg::getChar(int expressionNum)
{
	CString exprChar = L"";
	switch(expressionNum){
			case 0: exprChar = L"o"; break;
			case 1: exprChar = L"U"; break;
			case 2: exprChar = L"*"; break;
			case 3: exprChar = L"X"; break;
			case 4: exprChar = L"#"; break;
			default:exprChar = L"";  break;
		}

	return exprChar;
}


void CMotionEditorDlg::OnBnClickedBsend()
{
	// TODO: Add your control notification handler code here
	if(Serial_Port.IsOpen())
	{
		command_number=	m_iCommandListItem;
		char *x = m_bot[m_robot].Command_code[command_number];

		// Increment character pointer by 1 to skip the initial redundant character
		x = x + 1;	
		
		// Very Important : All commands have first letter as isobot mode initial. 
		// Hence Fetched command for forward for iSobot A is : "A0DB703" ( A + 6 char)
		// Where as command to be send through port is : "0DB703" (6 char)


		Serial_Port.Write(x,6);
		Serial_Port.TransmitChar('\r');
		Serial_Port.TransmitChar('\n');
	
	}
}

void CMotionEditorDlg::SendCommandToBot(int iBot, int iCmd_num)
{
	if(Serial_Port.IsOpen())
		{
		//char *x = m_bot[m_robot].Command_code[command_number];
		char *x = m_bot[iBot].Command_code[iCmd_num];


		// Increment character pointer by 1 to skip the initial redundant character
		x = x + 1;	
		
		// Very Important : All commands have first letter as isobot mode initial. 
		// Hence Fetched command for forward for iSobot A is : "A0DB703" ( A + 6 char)
		// Where as command to be send through port is : "0DB703" (6 char)


		Serial_Port.Write(x,6);
		Serial_Port.TransmitChar('\r');
		Serial_Port.TransmitChar('\n');
	}
}

void CMotionEditorDlg::OnBnClickedBon()
{
	// TODO: Add your control notification handler code here
	if(!Serial_Port.IsOpen())
		 Serial_Port.Open(m_ctlComPortSetting.m_iPortNumber);  		
	
	
	GetDlgItem(IDC_BON) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BOFF) -> EnableWindow(TRUE);

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedBoff()
{
	// TODO: Add your control notification handler code here
	if(Serial_Port.IsOpen())
		Serial_Port.Close();
		
	
	GetDlgItem(IDC_BON) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BOFF) -> EnableWindow(FALSE);

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonUp()
{
	// TODO: Add your control notification handler code here
	// First get the item selected by mouse selection
	int iSelection = m_ctlListScript.GetSelectionMark();
	
	if(iSelection > 0)
	{
		vScript[iSelection].swap(vScript[iSelection-1]);
		
		// Set the selection mark to new Item
		m_ctlListScript.SetSelectionMark(iSelection-1);
	}
	
	vector < vector <int> > :: iterator iterVScript;
	for(iterVScript = vScript.begin() ; iterVScript != vScript.end(); iterVScript++)
		(*iterVScript)[0] = iterVScript - vScript.begin();


	FillScriptRow();
	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonDown()
{
	// TODO: Add your control notification handler code here
	// First get the item selected by mouse selection
	int iSelection = m_ctlListScript.GetSelectionMark();
	
	if((iSelection < m_ctlListScript.GetItemCount()-1) && (iSelection >= 0))
	{
		vScript[iSelection].swap(vScript[iSelection+1]);
		
		// Set the selection mark to new Item
		m_ctlListScript.SetSelectionMark(iSelection+1);	
	}

	vector < vector <int> > :: iterator iterVScript;
	for(iterVScript = vScript.begin() ; iterVScript != vScript.end(); iterVScript++)
		(*iterVScript)[0] = iterVScript - vScript.begin();

	FillScriptRow();

	UpdateData(FALSE);	
}


void CMotionEditorDlg::OnBnClickedMfcbuttonDelete()
{
	// TODO: Add your control notification handler code here
	// First get the item selected by mouse selection
	int iSelection = m_ctlListScript.GetSelectionMark();
	TRACE("\n outside iSelection = %d : %d",iSelection, m_ctlListScript.GetItemCount()); 
	if((iSelection < m_ctlListScript.GetItemCount()) && (iSelection >= 0))
	{
		vScript.erase(vScript.begin() + iSelection);
		TRACE("\n iSelection = %d : %d",iSelection, m_ctlListScript.GetItemCount()); 
		// Set the selection mark to new Item
		m_ctlListScript.SetSelectionMark(iSelection);
	}

	vector < vector <int> > :: iterator iterVScript;
	for(iterVScript = vScript.begin() ; iterVScript != vScript.end(); iterVScript++)
		(*iterVScript)[0] = iterVScript - vScript.begin();


	FillScriptRow();

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonPlay()
{
	// TODO: Add your control notification handler code here
	//// Start from the first video in the script
	//int iCmndNum = m_ctlListScript.GetItemData(0);
	//video_filename = IntToCstring(iCmndNum);
	//m_ctlMP.put_URL(VIDEO);
	//

	//// Start the timer
	//UINT TimeDuration = TimeForCommand[iCmndNum] * 1000;
	//m_uiTimerVal = StartTimer(TimeDuration);
	//
	//// Update the script item number to be played
	//m_iItemScript = 1;

	//UpdateData(FALSE);
	////
	
	/*vectorRow.resize(4,0);
	vectorAction.resize( 0, vectorRow);
*/

	srand((UINT) time(NULL));



	//printExpression(vectorAction, vectorRow);
	TRACE("\n ------------------------------------------------- \n");
	printExpression(vScript);

	
	//vectorToPlay = solveExpression(vectorAction);
	vectorToPlay = solveExpression(vScript);
	

	vector<CString> commandNames (0, L"");
	for(int i = 0 ; i <140; i++)
		commandNames.push_back(m_bot[m_robot].command_isobot[i]);

	//CString strExpression =	formatExpression(vectorAction, vectorToPlay,commandNames);
	
	
	CString strExpression =	formatExpression(vScript, vectorToPlay,commandNames);
	

	int returnMsgBox = MessageBox(strExpression,L"Expression Solution", 4);
	TRACE("\n Return Number : %d", returnMsgBox );

	printExpression(vectorToPlay, vectorTm);

	if (returnMsgBox == MESSAGE_BOX_RETURN_YES)
	{
		

		// Start the timer
		m_iPlayItemNumber = 0;

		UINT TimeDuration = vectorToPlay[m_iPlayItemNumber][SCRIPT_TIME] * 1000;
		m_uiTimerVal = StartTimer(TimeDuration);

		m_iPtrn = 0; 
		m_uiMidiTimer = SetTimer(IDT_TIMER_Midi, 200, NULL);
		m_ctlProgressBarMidi.SetPos(0);


		// --- start sending commands -------------
		
		SendCommandToBot(vectorToPlay[m_iPlayItemNumber][SCRIPT_ROBOT], 
							vectorToPlay[m_iPlayItemNumber][SCRIPT_NAME]); 
	
	
		// Update the script item number to be played
		m_iPlayItemNumber = 1;
	}


	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedBclose()
{
	// TODO: Add your control notification handler code here
	Serial_Port.Close();

	// Sound SDK uninitialize
	::CoUninitialize();
    //return;

	// save all melodies -----------
	m_slMelody.vPattern.clear();

	for(int i = 0; i < 100 ; i++)
		for(int j = 0; j < 10; j++)
			for(int k = 0; k < 20; k++)
				m_slMelody.vPattern.push_back(melody[i].m_sMatrix[j][k]);

	m_slMelody.saveMelody();
	//  -----------

	// save all instruments -----------
	m_slMelody.vInstru.clear();

	for(int i = 0; i < 100 ; i++)
		m_slMelody.vInstru.push_back(melody[i].m_sInstrument);

	m_slMelody.saveMelodyInstruments();
	//  -----------

	OnOK();
}


void CMotionEditorDlg::OnNMClickListScript(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int nItem = pNMItemActivate->iItem;
	int count = m_ctlListScript.GetItemCount();


	if((nItem != LB_ERR) && (count > 1))
	{
		m_iItemScript = nItem;
		m_ctlListScript.SetSelectionMark(m_iItemScript) ;
	}

	// Enable / disable the pause button when user clicks withing list script
	// item those are greater than 0
	if((nItem != LB_ERR) && (count > 1) && m_iItemScript > 0)
		GetDlgItem(IDC_MFCBUTTON_PAUSE)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_MFCBUTTON_PAUSE)->ShowWindow(FALSE);

	

	int nSubItem = pNMItemActivate->iSubItem;

	// if 4th column (expression) is clicked then display a ExprList else don't.
	if(nSubItem == SCRIPT_ACTION && nItem != -1){
		if( ! (vScript[nItem][SCRIPT_NAME] == COMMAND_BRACE_OPEN))
			m_ctlExprList.ShowWindow(TRUE);
	}else
		m_ctlExprList.ShowWindow(FALSE);
	

	// if 4th column (MELODY) is clicked then display a Melody dropdown box else don't.
	if(nSubItem == SCRIPT_MELODY && nItem != -1){
		if( ! ((vScript[nItem][SCRIPT_NAME] == COMMAND_BRACE_CLOSE) 
			|| (vScript[nItem][SCRIPT_NAME] == COMMAND_BRACE_OPEN) 
			|| (vScript[nItem][SCRIPT_NAME] >= COMMAND_SPEECH)))
			m_ctlComboxMidi.ShowDropDown(TRUE);
	}else
		m_ctlComboxMidi.ShowDropDown(FALSE);
	
	

	UpdateData(FALSE);

	*pResult = 0;
}


void CMotionEditorDlg::OnNMClickListExpression(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	// get the item number selected from expression list
	int expItem = pNMItemActivate->iItem;

	//vScriptRow.at(5) = expItem;
	vScript[m_iItemScript][SCRIPT_ACTION] = expItem;

	// set the item in the forth column of script list (Expression)
	//m_ctlListScript.SetItemText(m_iItemScript,5,IntToCstring(expItem));	// Column 5: Expression for command
	m_ctlListScript.SetItemText(m_iItemScript,SCRIPT_ACTION,getChar(expItem));	// Column 5: Expression for command
	

	// Disable the expression list window
	m_ctlExprList.ShowWindow(FALSE);


	*pResult = 0;
}


void CMotionEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	// Timer event for MIDI patterns
	if(nIDEvent == m_uiMidiTimer)
	{
		KillTimer(m_uiMidiTimer);
		
		getPattern();

		midi.playPatternOne(pattern);
		
		m_uiMidiTimer = SetTimer(IDT_TIMER_Midi, 200, NULL);

		//Midi Progress bar
		m_ctlProgressBarMidi.StepIt();
	}


	// Timer event for Isobot motion command send
	if(nIDEvent == m_uiTimerVal)
	{
		// First kill the timer
		KillTimer(m_uiTimerVal);

		// Process the event
//		int iCmndNum = m_ctlListScript.GetItemData(m_iItemScript);
////		video_filename = IntToCstring(iCmndNum);
//		//m_ctlMP.put_URL(VIDEO);
//		//m_ctlMP.put_fullScreen(m_ctlMP.get_fullScreen());
//		
//		// Set the new timer if needed
//		if(m_iItemScript < m_ctlListScript.GetItemCount()-1)
//		{
//			m_iItemScript++;
//
//			UINT TimeDuration = m_bot[m_robot].TimeForCommand[iCmndNum] * 1000;
//			m_uiTimerVal = StartTimer(TimeDuration);
//		}
	

		if(m_iPlayItemNumber < vectorToPlay.size())
		{
			// Set the timer and start
			UINT TimeDuration = vectorToPlay[m_iPlayItemNumber][SCRIPT_TIME] * 1000;
			m_uiTimerVal = StartTimer(TimeDuration);

			// Set the robot who will accept command
		//	m_robot = vScript[m_iPlayItemNumber][SCRIPT_ROBOT] ? iSobotB : iSobotA; 
			// Command number to be send to the bot
		//	command_number = vScript[m_iPlayItemNumber][SCRIPT_NAME];

			TRACE("\n %d :> Sending Command number : %d to bot : %d",m_iPlayItemNumber, command_number,m_robot );
			// send ();
			// --- start sending commands -------------
		
			SendCommandToBot(vectorToPlay[m_iPlayItemNumber][SCRIPT_ROBOT], 
							vectorToPlay[m_iPlayItemNumber][SCRIPT_NAME]); 

			// Load new melody in composer matrix and start playing
			newMelodyInComposer(vScript[m_iPlayItemNumber][SCRIPT_MELODY]);
			//OnBnClickedBplaymidi();

			m_iPlayItemNumber++;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


UINT CMotionEditorDlg::StartTimer(UINT iTimeDuration)
{
	UINT TimerVal;
	
	// Set the timer
	TimerVal = 	SetTimer(IDT_TIMER, iTimeDuration, NULL);
	if(TimerVal == 0)
		MessageBox (L"Unable to obtain timer",
					L"IDT_TIMER",
					MB_OK|MB_SYSTEMMODAL);


	return TimerVal;
}


void CMotionEditorDlg::OnNMClickListMidicomposer(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(m_mode == COMPOSE_MODE)
	{
		int nItem = pNMItemActivate->iItem;
		int nSubItem = pNMItemActivate->iSubItem;

		midi.playNote(nItem);

		matrix[nItem][nSubItem] = !matrix[nItem][nSubItem];

		if(matrix[nItem][nSubItem])
			m_ctlListComposer.SetItemText(nItem, nSubItem, L"X");
		else
			m_ctlListComposer.SetItemText(nItem, nSubItem, L" ");

		m_ctlListComposer.Update(nItem);

		UpdateData(FALSE);
	}

	*pResult = 0;
}


void CMotionEditorDlg::OnBnClickedBplaymidi()
{
	// TODO: Add your control notification handler code here
	CString buttonText;
	GetDlgItem(IDC_BPlayMidi)->GetWindowTextW(buttonText);

	if(buttonText == L"Listen")
	{
		GetDlgItem(IDC_BPlayMidi)->SetWindowTextW(L"Stop");
		m_iPtrn = 0; 
		m_uiMidiTimer = SetTimer(IDT_TIMER_Midi, 200, NULL);
		m_ctlProgressBarMidi.SetPos(0);
		//m_ctlProgressBarMidi.SetMarquee(TRUE,40);
	}else
	if(buttonText == L"Stop")
	{
		midi.allNotesOff();
		GetDlgItem(IDC_BPlayMidi)->SetWindowTextW(L"Listen");
		KillTimer(m_uiMidiTimer);
		m_ctlProgressBarMidi.SetPos(0);
	}
}


void CMotionEditorDlg::getPattern(){

	for(int i=0; i<10; i++)
		pattern[i] = matrix[i][m_iPtrn];

	if(m_iPtrn < 20)
		m_iPtrn++;
	else{
		m_iPtrn = 0;
		m_ctlProgressBarMidi.SetPos(0);
	}
}


void CMotionEditorDlg::OnBnClickedBspeak()
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	if(!m_ctlBInsertSpeech.IsWindowVisible())
	{
		m_ctlEditTextToSpeak.ShowWindow(TRUE);
		m_ctlBInsertSpeech.ShowWindow(TRUE);
		GetDlgItem(IDC_BSpeak)->SetWindowTextW(L"Speak");
	}
	else
	{	
		CString TextToSpeak = m_strTextToSpeak;
		ISpVoice * pVoice = NULL;
	
		HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
		if( SUCCEEDED( hr ) )
		{	
			hr = pVoice->Speak(TextToSpeak, 0, NULL);
			pVoice->Release();
			pVoice = NULL;
		}
	}

    UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonPause()
{
	// TODO: Add your control notification handler code here
	// store the current value of m_iItemScript
	// use it to calculate the difference between old value nad new one
	// those number of times, Pause row would be moved up.
	int old_iItemScrip = m_iItemScript;

	m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");
	
		
	vScriptRow.at(SCRIPT_RANK) = old_iItemScrip; // vScript.size();
	vScriptRow.at(SCRIPT_NAME) = COMMAND_PAUSE;
	vScriptRow.at(SCRIPT_TIME) = 5; // COMMAND TIME = 5 
	//vScript.push_back(vScriptRow);

	vector < vector <int> > :: iterator iterVScript;
	iterVScript = vScript.begin() + old_iItemScrip;
	
	iterVScript = vScript.insert( iterVScript, vScriptRow);

	FillScriptRow();
	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedBinsertspeech()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	m_ctlEditTextToSpeak.ShowWindow(FALSE);
	m_ctlBInsertSpeech.ShowWindow(FALSE);
	GetDlgItem(IDC_BSpeak)->SetWindowTextW(L"Speech");
		

	if(0 <= m_iItemScript)
	{
		// Push the new text to string vector vSpeech
		vSpeech.push_back(m_strTextToSpeak);

		

		int old_iItemScrip = m_iItemScript;

		m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");
	
		
		vScriptRow.at(SCRIPT_RANK) = old_iItemScrip; // vScript.size();
		vScriptRow.at(SCRIPT_NAME) = COMMAND_SPEECH + vSpeech.size();
		vScriptRow.at(SCRIPT_TIME) = 3;
		//vScript.push_back(vScriptRow);

		

		vector < vector <int> > :: iterator iterVScript;
		iterVScript = vScript.begin() + old_iItemScrip + 1;
	
		iterVScript = vScript.insert( iterVScript, vScriptRow);

		
		FillScriptRow();
	}

	// Turn the 
	m_strTextToSpeak = _T("");
	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedBgroup()
{
	
	UpdateData(TRUE);
	
	int startIndex = 0;
	int endIndex = 0;

	if( 1 > m_ctlListScript.GetItemCount())
		return;
	

	// Find the first item of group selected : startIndex
	for(int i = 0; i <  m_ctlListScript.GetItemCount() ; i++)
		if (m_ctlListScript.GetItemState(i, LVIS_SELECTED)){
			startIndex = i;
			break;
		}

	// Find the end item of group selected : endIndex
	for(int i = startIndex; i <  m_ctlListScript.GetItemCount() ; i++)
		if (m_ctlListScript.GetItemState(i, LVIS_SELECTED))
			endIndex = i;
					
	

	//TRACE("\n Start : %d  ... End : %d ", startIndex, endIndex);

	// ------------
	// Insert a Pause command with 0 Seconds before the start Index which is starting of group selected
	m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");
		
	vScriptRow.at(SCRIPT_RANK) = startIndex;
	vScriptRow.at(SCRIPT_NAME) = COMMAND_BRACE_OPEN; 
	vScriptRow.at(SCRIPT_TIME) = 0;
	
	vector < vector <int> > :: iterator iterVScript;
	iterVScript = vScript.begin() + startIndex;
	
	iterVScript = vScript.insert( iterVScript, vScriptRow);
	// ------------
		
	// ------------
	// Insert a Pause command with 0 Seconds after the end Index which is end of group selected
	m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");
		
	vScriptRow.at(SCRIPT_RANK) = endIndex;
	vScriptRow.at(SCRIPT_NAME) = COMMAND_BRACE_CLOSE;
	vScriptRow.at(SCRIPT_TIME) = 0;
	
	// to insert closing Curly bracket "AFTER" endIndex, need to add 1
	// Since startIndex already added a row, add another 1, so add in total 2.
	iterVScript = vScript.begin() + endIndex + 2;
	
	iterVScript = vScript.insert( iterVScript, vScriptRow);
	// ------------
	
	
	FillScriptRow();

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnNMClickListCommands(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(m_mode == COMPOSE_MODE)
	{
		m_midiInstrument = pNMItemActivate->iItem;

		midi.allNotesOff();

		midi.selectInstrument(m_midiInstrument);
	}

	if(m_mode == ACTION_MODE)
	{
		m_iCommandListItem = pNMItemActivate->iItem;

		// just for debugging (to check the selected command number)
		GetDlgItem(IDC_txt) ->SetWindowTextW(IntToCstring(m_iCommandListItem));

		UpdateData(FALSE);
	}


	*pResult = 0;
}


void CMotionEditorDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
	// http://support.microsoft.com/default.aspx?scid=kb;en-us;242577
	/*Changing the state (enable/disable, check/uncheck, change text) of a menu item
		from its command user-interface (UI) handler does not work correctly 
		if the menu is attached to a dialog box:
		Solution : The code below is simply copied from the site mentioned */

    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
      state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }
}


void CMotionEditorDlg::OnModeCompose()
{
	// TODO: Add your command handler code here
	m_mode = COMPOSE_MODE;

	m_ctlListCommands.DeleteAllItems();

	// Updates all the command names in the list box
	for(int i=0; i<128; i++)
		m_ctlListCommands.InsertItem(i,instruments[i]);
	
}


void CMotionEditorDlg::OnUpdateModeCompose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_mode == COMPOSE_MODE ? 1 : 0); 
}


void CMotionEditorDlg::OnModeAction()
{
	// TODO: Add your command handler code here
	m_mode = ACTION_MODE;
	m_ctlListCommands.DeleteAllItems();

	 //Updates all the command names in the list box
	for(int i=0; i<140; i++)
		m_ctlListCommands.InsertItem(i,m_bot[m_robot].command_isobot[i]);

}


void CMotionEditorDlg::OnUpdateModeAction(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_mode == ACTION_MODE ? 1 : 0); 
}


void CMotionEditorDlg::OnModeScript()
{
	// TODO: Add your command handler code here
	m_mode = SCRIPT_MODE;

	m_ctlListCommands.DeleteAllItems();

	 //Updates all the command names in the list box
	for(int i=0; i<140; i++)
		m_ctlListCommands.InsertItem(i,m_bot[m_robot].command_isobot[i]);

}


void CMotionEditorDlg::OnUpdateModeScript(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_mode == SCRIPT_MODE ? 1 : 0); 
}


void CMotionEditorDlg::OnBnClickedBclearmidi()
{
	// TODO: Add your control notification handler code here
	midi.allNotesOff();
	
	for(int i= 0; i < 10; i++)
		for(int j= 0; j < 20; j++)
			matrix[i][j] = 0;

	for(int i= 0; i <10; i++)
		for(int j= 0; j <20; j++)
			m_ctlListComposer.SetItemText(i,j,L" ");


	m_ctlProgressBarMidi.SetPos(0);
	KillTimer(m_uiMidiTimer);

	
	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedBaddMidi()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	
	int iMelody  = m_ctlComboxMidi.GetCurSel();
	TRACE("\n Selection : %d ", iMelody);
	

	if(-1 != iMelody)
	{
		// First copy the matrix to save in the melody structure
		for(int i = 0 ; i < 10; i++)
			for(int j = 0; j < 20; j++)
				melody[iMelody].m_sMatrix[i][j] = matrix[i][j];
		
		// Save the instrument to melody structure
		melody[iMelody].m_sInstrument = m_midiInstrument;
			
		// Save the scale to melody structure
		melody[iMelody].m_sScale = m_ctlSliderScale.GetPos();


		TRACE("\n Saved Melody # %d", iMelody);	
	}
		
	UpdateData(FALSE);
}


void CMotionEditorDlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	int iMelody  = m_ctlComboxMidi.GetCurSel();
	TRACE("\n Selection : %d ", iMelody);
	
	if(m_mode == SCRIPT_MODE && m_iItemScript != -1)
	{
		m_melodySelected = iMelody;
		vScript[m_iItemScript].at(SCRIPT_MELODY) = iMelody;
		FillScriptRow();
	}

	if(m_mode == COMPOSE_MODE)
	{
		newMelodyInComposer(iMelody);
	}


	UpdateData(FALSE);
}


void CMotionEditorDlg::newMelodyInComposer(int iMelody)
{
	// Load the matrix from melody set
	for(int i = 0 ; i < 10; i++)
		for(int j = 0; j < 20; j++)
			matrix[i][j] = melody[iMelody].m_sMatrix[i][j];

	// Load the melody and set the instrument
	m_midiInstrument = melody[iMelody].m_sInstrument;
	midi.allNotesOff();
	midi.selectInstrument(m_midiInstrument);
		
		
	// load the scale from melody structure
	//m_ctlSliderScale.SetPos(melody[iMelody].m_sScale);


	UpdateComposeMatrix();
}


void CMotionEditorDlg::OnNMReleasedcaptureSliderMidiscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int newScale = m_ctlSliderScale.GetPos();
	m_ctlSliderScale.SetPos(newScale);
	if(m_mode == COMPOSE_MODE)
	{
		TRACE("\n New Value : %d ",newScale);
		midi.changeScale(newScale);
	}

	*pResult = 0;
}


void CMotionEditorDlg::OnScriptSave()
{
	// TODO: Add your command handler code here

	// copy the current script vector in to the vSL vector from saveLoad file
	m_slScript.vSL = vScript;
	
	// Call the function to make file write
	m_slScript.saveScript();

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnScriptLoad()
{
	// TODO: Add your command handler code here
	
	// Call the load file function which loads the previously saved vector into vector vSL from saveLoad class
	m_slScript.loadScript();

	// Append the new vector at the end of current vScript
	vScript.insert(vScript.end(), m_slScript.vSL.begin(), m_slScript.vSL.end());

	// Count the new size of vector in order to add the same number of lines in script list view
	int noOfLines = vScript.size();

	// Delete all rows in the column and again add the number of lines enough to contain new vector size.
	m_ctlListScript.DeleteAllItems();
	for(int i = 0; i < noOfLines;i++)
		m_iItemScript = m_ctlListScript.InsertItem(LVM_GETITEMCOUNT,L"");

	// Update the new script list
	TRACE("\n Data has been loaded ");
 	FillScriptRow();
}


void CMotionEditorDlg::OnScriptNew()
{
	// TODO: Add your command handler code here
	UpdateData(TRUE);
	// clear the script and then delete all items in current script list view
	vScript.clear();
	m_ctlListScript.DeleteAllItems();

	// don't forget to update the script list view, although deleting all contents.
	FillScriptRow();

	
}


void CMotionEditorDlg::OnScriptExit()
{
	// TODO: Add your command handler code here
	
	OnBnClickedBclose();
}


void CMotionEditorDlg::OnUpdateRobotIsobota(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_robot == iSobotA ? 1 : 0); 
}


void CMotionEditorDlg::OnUpdateRobotIsobotb(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_robot == iSobotB ? 1 : 0); 
}


void CMotionEditorDlg::OnRobotIsobota()
{
	// TODO: Add your command handler code here
	m_robot = iSobotA;

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnRobotIsobotb()
{
	// TODO: Add your command handler code here
	m_robot = iSobotB;

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonBota()
{
	// TODO: Add your control notification handler code here
	m_robot = iSobotA;

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnBnClickedMfcbuttonBotb()
{
	// TODO: Add your control notification handler code here
	m_robot = iSobotB;
	GetDlgItem(IDC_MFCBUTTON_BOTA)->ShowOwnedPopups(TRUE);

	UpdateData(FALSE);
}


void CMotionEditorDlg::OnSettingsSerialport()
{
	// TODO: Add your command handler code here
	if(TRUE == m_ctlComPortSetting.DoModal())
		TRACE("\n Port selected is : %d ", m_ctlComPortSetting.m_iPortNumber);
	else
		TRACE("\n Port number isn't modified. It's still # %d",  m_ctlComPortSetting.m_iPortNumber);
	
}


