#include "StdAfx.h"
#include "MIDI.h"


#define IDT_TIMER_Midi 1


CMIDI::CMIDI(void)
{
	// Open the MIDI output port
	int midiport = 0;

	m_baseScale = 60; 

	// Open MIDI port for sending short messages
	mmresult = midiOutOpen(&hmo, midiport, 0, 0, CALLBACK_NULL);
  
   if (mmresult != MMSYSERR_NOERROR) {
      TRACE("Error opening MIDI Output.\n");
   }
}



CMIDI::~CMIDI(void)
{
	// turn any MIDI notes currently playing:
   midiOutReset(hmo);

   // Remove any data in MIDI device and close the MIDI Output port
   midiOutClose(hmo);
}


void CMIDI::sendMIDIEvent(BYTE bStatus, BYTE bData1, BYTE bData2)
{
	
	// Construct the MIDI message. 
    u.bData[0] = bStatus;  // MIDI status byte 
    u.bData[1] = bData1;   // first MIDI data byte 
    u.bData[2] = bData2;   // second MIDI data byte 
    u.bData[3] = 0; 
 
	 mmresult = midiOutShortMsg(hmo, u.dwData);
	 if (mmresult != MMSYSERR_NOERROR) 
        TRACE("\n Warning: MIDI Output is not open.\n");
         
}

BYTE CMIDI::getScale(int scale){

	BYTE bData1;
	int baseScale = m_baseScale;

	switch(scale){
		case 0:	bData1 = baseScale + 0;		break;	// C
		case 1:	bData1 = baseScale + 2;		break;	// D
		case 2:	bData1 = baseScale + 4;		break;	// E
		case 3:	bData1 = baseScale + 5;		break;	// F
		case 4:	bData1 = baseScale + 7;		break;	// G
		case 5:	bData1 = baseScale + 9;		break;	// A
		case 6:	bData1 = baseScale + 11;	break;	// B
		case 7:	bData1 = baseScale + 12;	break;	// C+1
		case 8:	bData1 = baseScale + 16;	break;	// E+1
		case 9:	bData1 = baseScale + 20;	break;	// B"+1
		default:bData1 = baseScale;			break;	// C
	}

	//}
	//switch(scale){
	//	case 0:	bData1 = 60;	break;	// C
	//	case 1:	bData1 = 62;	break;	// D
	//	case 2:	bData1 = 64;	break;	// E
	//	case 3:	bData1 = 65;	break;	// F
	//	case 4:	bData1 = 67;	break;	// G
	//	case 5:	bData1 = 69;	break;	// A
	//	case 6:	bData1 = 71;	break;	// B
	//	case 7:	bData1 = 72;	break;	// C+1
	//	case 8:	bData1 = 76;	break;	// E+1
	//	case 9:	bData1 = 80;	break;	// B"+1
	//	default:bData1 = 60;	break;	// C
	//}

return bData1;
}

void CMIDI::playNote(void){

	BYTE bStatus, bData1, bData2;

	static BYTE t = 0;
	/*bStatus = 0x90;
	bData1 = 60 + rand()%10;
	bData2 = 100;*/

	bStatus = 0xC0;
	bData1 = t++;
	bData2 = 10;

	sendMIDIEvent(bStatus, bData1, bData2);
}


void CMIDI::selectInstrument(int scale){

	BYTE bStatus, bData1, bData2;

	
	bStatus = 0xC0;
	bData1 = scale;
	bData2 = 10;

	sendMIDIEvent(bStatus, bData1, bData2);
}


void CMIDI::changeScale(int scaleLevel)
{
	switch(scaleLevel){
	case 0: m_baseScale = 40; break;
	case 1: m_baseScale = 50; break;
	case 2: m_baseScale = 60; break;
	case 3: m_baseScale = 70; break;
	case 4: m_baseScale = 80; break;
	default: m_baseScale = 60; break;
	
	}

}

void CMIDI::playNote(int scale){

	BYTE bStatus, bData1, bData2;

	bStatus = 0X90;
	bData2 = 100;
	bData1 = getScale(scale);
	
	sendMIDIEvent(bStatus, bData1, bData2);
}


void CMIDI::allNotesOff()
{
	BYTE bStatus, bData1, bData2;
		
	bStatus = 0x80;
	//bData1 = scale;
	bData2 = 10;
	
	for(int scale = 40; scale <= 100; scale++)
	{
		bData1 = scale;
		sendMIDIEvent(bStatus, bData1, bData2);
	}
}

//
//void CMIDI::playPattern(BOOL matrix[10][20]){
//	BYTE bStatus, bData1, bData2;
//	bStatus = 0X90;
//	bData2 = 100;
//	bData1 = getScale(0);
//	
//	for(int period = 0; period < 20; period++ )
//	{	
//		TRACE("\n Period %d\t >", period);
//		for(int scale = 0 ; scale < 10; scale++)
//		{
//			TRACE(" %d ", matrix[scale][period]);
//			if( matrix[scale][period])
//				sendMIDIEvent(bStatus, getScale(scale), bData2);
//			
//		}// scale for end	
//		Sleep(400);
//	}// period for end
//
//	
//}

void CMIDI::playPatternOne(BOOL pattern[10]){
	BYTE bStatus, bData1, bData2;
	bStatus = 0X90;
	bData2 = 100;
	bData1 = getScale(0);
	
	for(int scale = 0 ; scale < 10; scale++)
	{
		if( pattern[scale])
			sendMIDIEvent(bStatus, getScale(scale), bData2);
	}// scale for end	

}



//
//CMIDI():instrumentsT  [] = {
//	//L"Instrument",
//	L"Acoustic Grand Piano",
//	L"Bright Acoustic Piano",
//	L"Electric Grand Piano",
//	L"Honky-tonk Piano",
//	L"Electric Piano 1",
//	L"Electric Piano 2",
//	L"Harpsichord",
//	L"Clavi",
//	L"Celesta",
//	L"Glockenspiel",
//	L"Music Box",
//	L"Vibraphone",
//	L"Marimba",
//	L"Xylophone",
//	L"Tubular Bells",
//	L"Dulcimer",
//	L"Drawbar Organ",
//	L"Percussive Organ",
//	L"Rock Organ",
//	L"Church Organ",
//	L"Reed Organ",
//	L"Accordion",
//	L"Harmonica",
//	L"Tango Accordion",
//	L"Acoustic Guitar (nylon)",
//	L"Acoustic Guitar (steel)",
//	L"Electric Guitar (jazz)",
//	L"Electric Guitar (clean)",
//	L"Electric Guitar (muted)",
//	L"Overdriven Guitar",
//	L"Distortion Guitar",
//	L"Guitar harmonics",
//	L"Acoustic Bass",
//	L"Electric Bass (finger)",
//	L"Electric Bass (pick)",
//	L"Fretless Bass",
//	L"Slap Bass 1",
//	L"Slap Bass 2",
//	L"Synth Bass 1",
//	L"Synth Bass 2",
//	L"Violin",
//	L"Viola",
//	L"Cello",
//	L"Contrabass",
//	L"Tremolo Strings",
//	L"Pizzicato Strings",
//	L"Orchestral Harp",
//	L"Timpani",
//	L"String Ensemble 1",
//	L"String Ensemble 2",
//	L"SynthStrings 1",
//	L"SynthStrings 2",
//	L"Choir Aahs",
//	L"Voice Oohs",
//	L"Synth Voice",
//	L"Orchestra Hit",
//	L"Trumpet",
//	L"Trombone",
//	L"Tuba",
//	L"Muted Trumpet",
//	L"French Horn",
//	L"Brass Section",
//	L"SynthBrass 1",
//	L"SynthBrass 2",
//	L"Soprano Sax",
//	L"Alto Sax",
//	L"Tenor Sax",
//	L"Baritone Sax",
//	L"Oboe",
//	L"English Horn",
//	L"Bassoon",
//	L"Clarinet",
//	L"Piccolo",
//	L"Flute",
//	L"Recorder",
//	L"Pan Flute",
//	L"Blown Bottle",
//	L"Shakuhachi",
//	L"Whistle",
//	L"Ocarina",
//	L"Lead 1 (square)",
//	L"Lead 2 (sawtooth)",
//	L"Lead 3 (calliope)",
//	L"Lead 4 (chiff)",
//	L"Lead 5 (charang)",
//	L"Lead 6 (voice)",
//	L"Lead 7 (fifths)",
//	L"Lead 8 (bass + lead)",
//	L"Pad 1 (new age)",
//	L"Pad 2 (warm)",
//	L"Pad 3 (polysynth)",
//	L"Pad 4 (choir)",
//	L"Pad 5 (bowed)",
//	L"Pad 6 (metallic)",
//	L"Pad 7 (halo)",
//	L"Pad 8 (sweep)",
//	L"FX 1 (rain)",
//	L"FX 2 (soundtrack)",
//	L"FX 3 (crystal)",
//	L"FX 4 (atmosphere)",
//	L"FX 5 (brightness)",
//	L"FX 6 (goblins)",
//	L"FX 7 (echoes)",
//	L"FX 8 (sci-fi)",
//	L"Sitar",
//	L"Banjo",
//	L"Shamisen",
//	L"Koto",
//	L"Kalimba",
//	L"Bag pipe",
//	L"Fiddle",
//	L"Shanai",
//	L"Tinkle Bell",
//	L"Agogo",
//	L"Steel Drums",
//	L"Woodblock",
//	L"Taiko Drum",
//	L"Melodic Tom",
//	L"Synth Drum",
//	L"Reverse Cymbal",
//	L"Guitar Fret Noise",
//	L"Breath Noise",
//	L"Seashore",
//	L"Bird Tweet",
//	L"Telephone Ring",
//	L"Helicopter",
//	L"Applause",
//	L"Gunshot"
//	};
//


