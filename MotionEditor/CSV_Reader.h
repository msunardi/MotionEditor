#pragma once
#include "stdafx.h"
#include "resource.h"


struct T_CommandData
{
	UINT unRank;
	CString strCommand;
	char * pszHexCode;
	UINT unTime;

	T_CommandData()
	{
		unRank = 0;
		pszHexCode = NULL;
		unTime = 0;
	}

	T_CommandData(UINT Rank, char* pHexCode, UINT Time)
	{
		unRank = Rank;
		pszHexCode = pHexCode;
		unTime = Time;
	}

	~T_CommandData()
	{
		unRank = 0;
		if(NULL != pszHexCode)
		{
			delete [] pszHexCode;
			pszHexCode = NULL;
		}
		unTime = 0;
	}
};

class CSV_Reader
{
public:
	CString command_isobot[300];
	char * Command_code[300];
	int TimeForCommand[300];

public:
	CStdioFile* m_pcfileFileObject;
	CString m_strFilePath;
	std::vector <T_CommandData*> m_vectCommandData;

	CSV_Reader();
	~CSV_Reader();

	int Initialize(CString strFilePath);
	int PopulateCommandData();
	int DisplayCommandData();
	int Uninitialize();
};