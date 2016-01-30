#pragma once

#include <fstream>
#include <iostream>

using namespace std;

class CSaveLoad
{
public:
	CSaveLoad(void);
	~CSaveLoad(void);

public:
	// ----------------------------------
	vector <int> vRow;
	vector < vector <int> > vSL;

	vector <int> ::iterator itervRow;
	vector < vector <int> > ::iterator itervSL;

	void loadScript();
	void saveScript();
	// ----------------------------------


	// ----------------------------------
	vector <BOOL> vPattern;
	vector <BOOL>::iterator itervPattern;
	
	void saveMelody();
	void loadMelody();
	// ----------------------------------


	// ----------------------------------
	vector <int> vInstru;
	vector <int>::iterator itervInstru;
	
	void saveMelodyInstruments();
	void loadMelodyInstruments();
	// ----------------------------------
};

