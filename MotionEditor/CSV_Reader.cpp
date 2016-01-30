// CSV_Reader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSV_Reader.h"
//#include "MotionEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

//CWinApp theApp;

using namespace std;

CSV_Reader::CSV_Reader()
{
	m_pcfileFileObject = NULL;
}

CSV_Reader::~CSV_Reader()
{
	if(NULL != m_pcfileFileObject)
	{
		delete m_pcfileFileObject;
		m_pcfileFileObject = NULL;
	}
}

int CSV_Reader::Initialize(CString strFilePath)
{
	m_pcfileFileObject = new CStdioFile();
	if(NULL == m_pcfileFileObject)
	{
		return -1;
	}

	if (FALSE == m_pcfileFileObject->Open(strFilePath,CFile::modeRead))
	{
		DWORD dw = GetLastError();
		TRACE("Couldn't open source file: %d",dw);
		return -1;
	}
	return 0;
}

int CSV_Reader::PopulateCommandData(void)
{
	
	if(NULL == m_pcfileFileObject)
	{
		return -1;
	}

	CString strLine;
	BOOL bSkipFirstLine = TRUE;
	int nIndex = 0;
	while( FALSE != m_pcfileFileObject->ReadString(strLine))
	{
		if(bSkipFirstLine)
		{
			bSkipFirstLine = FALSE;
		}
		else
		{
			T_CommandData* ptCommandData = new T_CommandData();
			//while(-1 != nIndex)
			//{
				CString strRank, strCommand, strCode, strTime;

				nIndex = 0;
				strRank = strLine.Tokenize(_T(","),nIndex);
				strRank.Trim();

				// --------- Command Rank -------------
				ptCommandData->unRank = StrToInt(strRank);

				// --------- Command Name -------------
				ptCommandData->strCommand = strLine.Tokenize(_T(","),nIndex);
				ptCommandData->strCommand.Trim();

				// --------- Command Code -------------
				strCode = strLine.Tokenize(_T(","),nIndex);
				strCode.Trim();
				TCHAR* pszStrCode = new TCHAR[7];
				_tcscpy(pszStrCode,strCode);
				ptCommandData->pszHexCode = new char[7];
				strcpy(ptCommandData->pszHexCode,CW2A(pszStrCode)); 

				// --------- Command Time -------------
				strTime = strLine.Tokenize(_T("\0"),nIndex);
				strTime.Trim();
				ptCommandData->unTime = StrToInt(strTime);

				m_vectCommandData.push_back(ptCommandData);

			//};
		}
	};

	return 0;
}

int CSV_Reader::DisplayCommandData()
{
	vector<T_CommandData*>::iterator itr;
	UINT unIndex = 0;
	for(itr = m_vectCommandData.begin(); itr != m_vectCommandData.end(); itr++,unIndex++)
	{
		command_isobot[unIndex] = (*itr)->strCommand;
		Command_code[unIndex] = (*itr)->pszHexCode;
		TimeForCommand[unIndex] = (*itr)->unTime;

//		((CMediaProjectApp*)AfxGetApp())->TimeForCommand[unIndex] 7= (*itr)->unTime;
//		CString strMessage;
	//	strMessage.Format(_T("%d "),(*itr)->unRank);
//		strMessage += (*itr)->strCommand;
		//CString str((*itr)->pszHexCode);
//		strMessage += str;
//		strMessage.AppendFormat(_T("%u"),(*itr)->unTime);
	}
	return 0;
}

int CSV_Reader::Uninitialize(void)
{
	
	m_vectCommandData.clear();

	m_pcfileFileObject->Close();

	return 0;
}



