#include "StdAfx.h"
#include "SaveLoad.h"

using namespace std;

CSaveLoad::CSaveLoad(void)
{
	vector <int > vRow(5);
	vector < vector <int> > vSL(0, vRow);

	vector <BOOL> vPattern(0);
}


CSaveLoad::~CSaveLoad(void)
{
}


void CSaveLoad::saveScript()
{
	CFileDialog ldFile(FALSE); // TRUE for FileOpen, FALSE for FileSaveAs

	if(ldFile.DoModal() == IDOK)
	{
		CString saveToFile = ldFile.GetPathName(); // + ldFile.GetFileName();

		

		CT2A ascii(saveToFile);
		TRACE(" Saving data to File  : %s ", ascii.m_psz);

		ofstream vectorFile(saveToFile, ios::binary);
		

		for(itervSL = vSL.begin(); itervSL != vSL.end(); itervSL++)
			for(itervRow = (*itervSL).begin(); itervRow != (*itervSL).end(); itervRow++)
				//vectorFile <<  *itervRow;
				vectorFile.write((char*) &(*itervRow), sizeof(int));

		int endOfFile = 12500;
		//*itervRow = 12500;
		vectorFile.write((char*)&endOfFile, sizeof(int));
		//vectorFile << (int) 12500;

		vectorFile.close();
	}

}


void CSaveLoad::loadScript()
{
	CFileDialog ldFile(TRUE); // TRUE for FileOpen, FALSE for FileSaveAs

	if(ldFile.DoModal() == IDOK)
	{
		CString loadFromFile = ldFile.GetPathName(); //ldFile.GetFileName();
		vSL.clear();
		TRACE(" Loading data from File : %s \n",((CT2A)loadFromFile).m_psz);

		ifstream vectorFile(loadFromFile, ios::binary);
		//streamsize(sizeof(int));
		

		int countSix = 0;
		int iRead = 0;
		
		int countbreak = 500;
		while(countbreak--)
		{
			//vectorFile.read((char*)&iRead, sizeof(int));
			vectorFile.read((char*)&iRead, sizeof(int));
			
			TRACE(" %d ", iRead);
			if(iRead == 12500)	break;

			else{
				vRow.push_back((int)iRead);
				countSix++;
				if(countSix == 6)
				{
					vSL.push_back(vRow);
					vRow.clear();
					countSix = 0;
				}//if end
			}//else end
		}// while 1 end

		vectorFile.close();

	}

}


void CSaveLoad::saveMelody()
{
	
	CString saveToFile = L"Melodies.bin";
		

	CT2A ascii(saveToFile);
	TRACE(" Saving Melodies to File  : %s ", ascii.m_psz);

	ofstream vectorFile(saveToFile, ios::binary);
		

	for(itervPattern = vPattern.begin(); itervPattern != vPattern.end(); itervPattern++)
		vectorFile.write((char*) &(*itervPattern), sizeof(BOOL));

	//char endOfFile = 12500;
	//*itervRow = 12500;
	//vectorFile.write((char*)&endOfFile, sizeof(BOOL));
	//vectorFile << (int) 12500;

	vectorFile.close();
}


void CSaveLoad::loadMelody()
{
	
	CString loadFromFile = L"Melodies.bin";
		

	CT2A ascii(loadFromFile);
	TRACE(" Loading Melodies From File  : %s ", ascii.m_psz);

	ifstream vectorFile(loadFromFile, ios::binary);
		
	vPattern.clear();

	BOOL bRead = 0;

	int countBreak = 20000;	// 10 rows x 20 columns x 100 matrices
	while(countBreak--)
	{
		vectorFile.read((char*) &(bRead), sizeof(BOOL));
		vPattern.push_back(bRead);
	}
	
	vectorFile.close();
}


void CSaveLoad::saveMelodyInstruments()
{
	
	CString saveToFile = L"MelodiesInstruments.bin";
		

	CT2A ascii(saveToFile);
	TRACE(" Saving instruments to File  : %s ", ascii.m_psz);

	ofstream vectorFile(saveToFile, ios::binary);
		

	for(itervInstru = vInstru.begin(); itervInstru != vInstru.end(); itervInstru++)
		vectorFile.write((char*) &(*itervInstru), sizeof(int));

	//char endOfFile = 12500;
	//*itervRow = 12500;
	//vectorFile.write((char*)&endOfFile, sizeof(BOOL));
	//vectorFile << (int) 12500;

	vectorFile.close();
}


void CSaveLoad::loadMelodyInstruments()
{
	
	CString loadFromFile = L"MelodiesInstruments.bin";
		

	CT2A ascii(loadFromFile);
	TRACE(" Loading instruments From File  : %s ", ascii.m_psz);

	ifstream vectorFile(loadFromFile, ios::binary);
		
	vPattern.clear();

	int iRead = 0;

	int countBreak = 100;	// 10 rows x 20 columns x 100 matrices
	while(countBreak--)
	{
		vectorFile.read((char*) &(iRead), sizeof(int));
		vInstru.push_back(iRead);
	}
	
	vectorFile.close();
}


