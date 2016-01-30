#pragma once

#include <Windows.h>
#include <MMSystem.h>
#include <vector>

#pragma comment (lib, "winmm")


class CMIDI 
{

private:
	// Handle to MIDI Output device
	HMIDIOUT hmo;
	
	HWND hWnd;

	// Error Value : MM Result
	MMRESULT mmresult;

	union { 
        DWORD dwData; 
        BYTE bData[4]; 
    } u; 

	void sendMIDIEvent(BYTE bStatus, BYTE bData1, BYTE bData2); 
	BYTE getScale(int scale);
	int m_baseScale;

public:
	CMIDI(void);
	~CMIDI(void);

	
	void playNote();
	void playNote(int scale);
	
	const CString instrumentsT[128];
	
	void CMIDI::playPattern(BOOL matrix[10][20]);
	void CMIDI::playPatternOne(BOOL pattern[10]);
	void CMIDI::selectInstrument(int scale);
	void CMIDI::allNotesOff();
	void CMIDI::changeScale(int scaleLevel);
};

