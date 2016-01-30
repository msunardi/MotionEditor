#include "stdafx.h"
#include "listData.h"

#include <sstream>

using namespace std;



CString instrumentsT  [] = {
//L"Instrument",
L"Acoustic Grand Piano",
L"Bright Acoustic Piano",
L"Electric Grand Piano",
L"Honky-tonk Piano",
L"Electric Piano 1",
L"Electric Piano 2",
L"Harpsichord",
L"Clavi",
L"Celesta",
L"Glockenspiel",
L"Music Box",
L"Vibraphone",
L"Marimba",
L"Xylophone",
L"Tubular Bells",
L"Dulcimer",
L"Drawbar Organ",
L"Percussive Organ",
L"Rock Organ",
L"Church Organ",
L"Reed Organ",
L"Accordion",
L"Harmonica",
L"Tango Accordion",
L"Acoustic Guitar (nylon)",
L"Acoustic Guitar (steel)",
L"Electric Guitar (jazz)",
L"Electric Guitar (clean)",
L"Electric Guitar (muted)",
L"Overdriven Guitar",
L"Distortion Guitar",
L"Guitar harmonics",
L"Acoustic Bass",
L"Electric Bass (finger)",
L"Electric Bass (pick)",
L"Fretless Bass",
L"Slap Bass 1",
L"Slap Bass 2",
L"Synth Bass 1",
L"Synth Bass 2",
L"Violin",
L"Viola",
L"Cello",
L"Contrabass",
L"Tremolo Strings",
L"Pizzicato Strings",
L"Orchestral Harp",
L"Timpani",
L"String Ensemble 1",
L"String Ensemble 2",
L"SynthStrings 1",
L"SynthStrings 2",
L"Choir Aahs",
L"Voice Oohs",
L"Synth Voice",
L"Orchestra Hit",
L"Trumpet",
L"Trombone",
L"Tuba",
L"Muted Trumpet",
L"French Horn",
L"Brass Section",
L"SynthBrass 1",
L"SynthBrass 2",
L"Soprano Sax",
L"Alto Sax",
L"Tenor Sax",
L"Baritone Sax",
L"Oboe",
L"English Horn",
L"Bassoon",
L"Clarinet",
L"Piccolo",
L"Flute",
L"Recorder",
L"Pan Flute",
L"Blown Bottle",
L"Shakuhachi",
L"Whistle",
L"Ocarina",
L"Lead 1 (square)",
L"Lead 2 (sawtooth)",
L"Lead 3 (calliope)",
L"Lead 4 (chiff)",
L"Lead 5 (charang)",
L"Lead 6 (voice)",
L"Lead 7 (fifths)",
L"Lead 8 (bass + lead)",
L"Pad 1 (new age)",
L"Pad 2 (warm)",
L"Pad 3 (polysynth)",
L"Pad 4 (choir)",
L"Pad 5 (bowed)",
L"Pad 6 (metallic)",
L"Pad 7 (halo)",
L"Pad 8 (sweep)",
L"FX 1 (rain)",
L"FX 2 (soundtrack)",
L"FX 3 (crystal)",
L"FX 4 (atmosphere)",
L"FX 5 (brightness)",
L"FX 6 (goblins)",
L"FX 7 (echoes)",
L"FX 8 (sci-fi)",
L"Sitar",
L"Banjo",
L"Shamisen",
L"Koto",
L"Kalimba",
L"Bag pipe",
L"Fiddle",
L"Shanai",
L"Tinkle Bell",
L"Agogo",
L"Steel Drums",
L"Woodblock",
L"Taiko Drum",
L"Melodic Tom",
L"Synth Drum",
L"Reverse Cymbal",
L"Guitar Fret Noise",
L"Breath Noise",
L"Seashore",
L"Bird Tweet",
L"Telephone Ring",
L"Helicopter",
L"Applause",
L"Gunshot"
};


// Initialize Report List Script
void CMotionEditorDlg::ScriptInitialize(void)
{
	// Initialie the size of script rows
	vScriptRow.resize(6,0);
	vScript.resize(0, vScriptRow);

	vectorTm.resize (6,0);
	vectorToPlay.resize (0 , vectorTm);
	
	

	getCommandsForRobot(iSobotA);
	
	// Disable Expression List initially
	m_ctlExprList.ShowWindow(FALSE);

	// ------------

	
	// ------------



	// Updates all the command names in the list box
	for(int i=0; i<140; i++)
		m_ctlListCommands.InsertItem(i,m_bot[m_robot].command_isobot[i]);


	m_ctlListCommands.SetHoverTime(2L);

	// Just for debugging, this static text box shows command number
	SetDlgItemText(IDC_txt, L"Command Number");

	// Disable pause button in the beginning
	GetDlgItem(IDC_MFCBUTTON_PAUSE)->ShowWindow(FALSE);

	// Updates all the command names in the Expression list box
	m_ctlExprList.InsertItem(0,L" Concatenate ");	// L"    o     ");
	m_ctlExprList.InsertItem(1,	L" Union ");		//L"    U     ");
	m_ctlExprList.InsertItem(2,	L" Iterate ");		//L"    *     ");
	m_ctlExprList.InsertItem(3,	L" Ignore ");		//L"  Ignore  ");
	m_ctlExprList.InsertItem(4,	L" May Skip ");		//L"  Skip    ");
	
	m_ctlExprList.SetExtendedStyle(LVS_EX_BORDERSELECT
									| LVS_EX_SNAPTOGRID
									| LVS_EX_TRACKSELECT);
	

	// set hower time 
	m_ctlExprList.SetHoverTime(2UL);
	
	m_ctlExprList.SetTextBkColor(RGB(0xF8,0x45,0x20));

	// Initialize Report view
	// (Column Number, Caption, Format, Width, #Subitem)
	m_ctlListScript.InsertColumn(0,L"   #   ",0,50,0);
	m_ctlListScript.InsertColumn(1,L"ROBOT",0,50,0);
	m_ctlListScript.InsertColumn(2,L"NAME",0,150,0);
	m_ctlListScript.InsertColumn(3,L"TIME",0,70,0);
	m_ctlListScript.InsertColumn(4,L"MELODY",0,80,0);	
	m_ctlListScript.InsertColumn(5,L"ACTION",0,100,0);


	m_ctlListScript.SetExtendedStyle(LVS_EX_FULLROWSELECT 
									| LVS_EX_GRIDLINES 
									| LVS_EX_HEADERDRAGDROP 
									| LVS_EX_SUBITEMIMAGES
									| LVS_EX_SNAPTOGRID
									| LVS_EX_DOUBLEBUFFER);
					
	
	
	m_ctlListScript.SetItemCount(150);	// Specifies space for 50 items
	m_lvitem.mask = LVIF_TEXT;			// Text Format
	m_lvitem.state = LVIM_AFTER;		// LVIM_AFTER = TRUE => Insert after item otherwise before.

	m_lvitem.iItem = 0 ;
	m_lvitem.iSubItem = 0;
	m_lvitem.pszText = L"";				// Important to initialize atleast some text
	
	m_ctlListScript.SetItem(&m_lvitem);
	
	m_iItemScript = -1;

	// Delete later .. just dummy method / Modify
	for(int i=0; i<128; i++)
		instruments[i] = instrumentsT[i];
			//m_ctlListCommands.InsertItem(i,instruments[i]);


	UpdateData(FALSE);
}



void CMotionEditorDlg::getCommandsForRobot(int Robot){

	
	for(Robot = iSobotA ; Robot <= iSobotB ; Robot ++)
	{

		int nRetCode = -1;
		CSV_Reader * pCSVReader = new CSV_Reader();
	
		if(Robot == iSobotA)
			nRetCode = pCSVReader->Initialize(_T("CommandsA.csv"));
		else
		if(Robot == iSobotB)
			nRetCode = pCSVReader->Initialize(_T("CommandsB.csv"));

			if(-1 == nRetCode)
				{TRACE("Initialization failed"); 	return; }

		nRetCode = pCSVReader->PopulateCommandData();
			if(-1 == nRetCode)
				{TRACE("PopulateCommandData failed");	return ;}
	
		nRetCode = pCSVReader->DisplayCommandData();

	
		for(int i=0 ; i < 140; i++) {
		
			m_bot[Robot].command_isobot[i] = pCSVReader->command_isobot[i] ;
			m_bot[Robot].Command_code[i] = pCSVReader->Command_code[i];
			m_bot[Robot].TimeForCommand[i] = pCSVReader->TimeForCommand[i];
		}

	}

}


void CMotionEditorDlg::composerInitialize(){

	LVITEM lvitem;
	lvitem.pszText = L" ";

	for(int i= 0; i < 10; i++)
		for(int j= 0; j < 20; j++)
			matrix[i][j] = 0;
	

	for(int i= 0; i <10; i++)
		m_ctlListComposer.InsertItem(i,L" ");
	
	for(int j= 0; j <20; j++)
		m_ctlListComposer.InsertColumn(j,L" ",0,20,0);

	
	/*for(int i= 0; i <10; i++)
		for(int j= 0; j <20; j++)
			m_ctlListComposer.SetItemText(i,j,L" ");
*/
	
	
	UpdateComposeMatrix();

	m_ctlListComposer.SetExtendedStyle(LVS_EX_GRIDLINES
									| LVS_EX_FULLROWSELECT
									| LVS_EX_SNAPTOGRID
									| LVS_EX_TRACKSELECT
									| LVS_EX_SUBITEMIMAGES
									);


	m_ctlListComposer.SetBkColor(0x00D5B7B7);
	
	m_ctlListComposer.SetTextBkColor(0x00D5B7B7);

	
	m_ctlListComposer.SetHoverTime(2L);
	
	// Progress Bar
	m_ctlProgressBarMidi.SetRange(0,200);
	m_ctlProgressBarMidi.SetStep(10);
	m_ctlProgressBarMidi.SetPos(0);
	
	// Edit Compose name box.. make it disabled
	m_ctlEditComposeName.ShowWindow(FALSE);


	// Slider controls
	m_ctlSliderScale.SetRange(0,4);
	TRACE("\n get pos : %d ",m_ctlSliderScale.GetPos());
	
	for(int i = 1; i < 4 ; i++)
		m_ctlSliderScale.SetTic(i);

	m_ctlSliderScale.SetPos(0);
	
	TRACE("\n set pos : %d ",m_ctlSliderScale.GetPos());
	UpdateData(FALSE);
}


void CMotionEditorDlg::UpdateComposeMatrix()
{
	for(int nItem = 0; nItem < 10 ; nItem++){
		for(int nSubItem = 0 ; nSubItem < 20; nSubItem++){

		if(matrix[nItem][nSubItem])
			m_ctlListComposer.SetItemText(nItem, nSubItem, L"X");
		else
			m_ctlListComposer.SetItemText(nItem, nSubItem, L" ");
		}
	}
}


void CMotionEditorDlg:: musicNamesInitialize()
{

	m_ctlComboxMidi.AddString(L""); //First name is purposefully NUll
	for(int i = 1; i < 100; i++)
		m_ctlComboxMidi.AddString(L"Melody " + IntToCstring(i));
		
	CString str;
	for(int i = 0; i < 100; i++)
	{
		m_ctlComboxMidi.GetLBText(i,str);
		melody[i].m_sComposeName = str;	
	}
	
	/*
	// Melody matrix all set to 0
	for(int i = 0; i < 100; i++)
	{
		// Set matrix to all 0;
		for(int nItem = 0; nItem < 10 ; nItem++)
			for(int nSubItem = 0 ; nSubItem < 20; nSubItem++)
				melody[i].m_sMatrix[nItem][nSubItem] = 0;

		// set instrument to 0;
		melody[i].m_sInstrument = 0;
	}
	*/
	
	// Load data in Melody structure ----------		
	int counter = 0;
	m_slMelody.loadMelody();
	m_slMelody.itervPattern = m_slMelody.vPattern.begin();

	for(int i = 0; i < 100 ; i++)
		for(int j = 0; j < 10; j++)
			for(int k = 0; k < 20; k++)
				melody[i].m_sMatrix[j][k] = *m_slMelody.itervPattern++;

	m_slMelody.vPattern.clear();
	// ----------

	

	// Load all instruments -----------
	m_slMelody.vInstru.clear();
	m_slMelody.loadMelodyInstruments();

	for(int i = 0; i < 100 ; i++)
		melody[i].m_sInstrument = m_slMelody.vInstru[i];

	m_slMelody.vInstru.clear();
	//  -----------


	UpdateData(FALSE);
}


// Converts integer into CString
CString CMotionEditorDlg::IntToCstring(int iNumber)
{
	CString strNumber;
	// Convert the int command number in CString format
		std::string s;
		std::stringstream out;
		out << iNumber;
		s = out.str();

		strNumber = s.c_str();
	return strNumber;
}

