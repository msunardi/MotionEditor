// Expression.cpp : implementation file
//

#include "stdafx.h"
#include "MotionEditorDlg.h"
#include "Expression.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;


#define COMMAND_SPEECH		1000
#define COMMAND_BRACE_OPEN	995
#define COMMAND_BRACE_CLOSE	996




void printExpression(vector < vector <int> > vectorAction,  vector <int> vectorRow)
{
	vector <int> :: iterator iterRow  ;
	vector < vector<int> > :: iterator iterAction ;

	
	TRACE("\n vectorRow size : %d", vectorRow.size());
	TRACE("\n vectorColumn size : %d", vectorAction.size());
	TRACE("\n");
	
	int obj = 0;

	TRACE("\n");
	for(iterAction = vectorAction.begin() ; iterAction != vectorAction.end(); iterAction++, obj++)
	{
		try {TRACE ("Object %d : ", obj);}
		catch(exception&) { TRACE("BAM");}

		for(iterRow = (*iterAction).begin(); iterRow != (*iterAction).end(); iterRow++)
		{
			TRACE(" %d ", *iterRow);
		}TRACE("\n");

	} 
	TRACE("\n");
}



void printExpression(vector < vector <int> > vectorAction)
{
	vector <int> vectorRow (4);
	
	printExpression( vectorAction,  vectorRow);
	
}



// Return Solution Vector[Num][2]
vector< vector<int> > solveExpression(vector < vector <int> > vectorAction)
{
	// Input Vector
	vector <int> vectorRow (6);
	vector <int> :: iterator iterRow  ;
	vector < vector<int> > :: iterator iterAction ;

	// Solution Vector
	vector <int> vecSolutionRow (6,0);
	vector < vector <int> > vecSolution (0 , vecSolutionRow); 
	vector <int> :: iterator iterSolRow;
	vector < vector <int> > :: iterator iterSol;

	
	vecSolution.clear();
	
	for(iterAction = vectorAction.begin(); iterAction != vectorAction.end(); iterAction++)
	{
		vectorRow = (*iterAction);
		vecSolutionRow = vectorRow;

		//int rank =  (*iterAction).at(0);  //vectorAction[iterAction][0];
		//int cmnd =  (*iterAction).at(1);  //vectorAction[*iterAction][1];
		//int tme =  (*iterAction).at(2);  //vectorAction[*iterAction][2];
		// Regular expression
		int expr = (*iterAction).at(5);  //vectorAction[*iterAction][4];

		int probability = 0;

		switch(expr){
		case 0: // Concatenate
			vecSolution.push_back(vecSolutionRow);
			break;

		case 1: // Union
			// first push the row in solution vector
			vecSolution.push_back(vecSolutionRow);
			
			// Skip the test if it is first element
			if(vecSolution.begin() != vecSolution.end() -1)
			{

				// get a random number
				probability = rand()%2; 
				TRACE("\n Union Operation, argumuent chosen (0 / 1) : %d ", probability);


				if(probability)
					vecSolution.erase(vecSolution.end()-1);
				else
					vecSolution.erase(vecSolution.end()-2);

			}
			break;

		case 2: // iterate
			// get a random number
			probability = rand()%5; 
			TRACE("Iteration Probability2 : %d ",probability);

			for(int tempi = 0; tempi < probability; tempi ++)
				vecSolution.push_back(vecSolutionRow);
			
			break;

		case 3: // Ignore the action .. Skip it
			break;

		case 4: // May skip this action
			// get a random number
			probability = rand()%2; 
			TRACE("Probability4: %d ", probability);

			if(probability)
				vecSolution.push_back(vecSolutionRow);

			break;

		default:
			vecSolution.push_back(vecSolutionRow);
			break;
		}//switch end

	}// for end



	//// Erase the un-necessary columns in Solution vector and keep only 2 :
	//// 1. ActionCommand , 2. actionTime
	//for(iterSol = vecSolution.begin(); iterSol != vecSolution.end(); iterSol++)
	//{
	//	//for(iterSolRow = (*iterSol).begin(); iterSolRow != (*iterSol).end()
	//	(*iterSol).erase((*iterSol).begin() );
	//	(*iterSol).erase((*iterSol).end()- 1);
	//}

	return vecSolution;
}




CString formatExpression(vector < vector <int> > vectorAction, vector< vector<int> > vecSolution, vector<CString> commandNames)
{
	CString strExpression = L"";
	CString str;
		
	// Input Vector
	vector < vector<int> > :: iterator iterAction ;
	vector < vector<int> > :: iterator iterSolution ;


	for(iterAction = vectorAction.begin(); iterAction != vectorAction.end(); iterAction++)
	{
		// Command Name -------------------
		int commandNumber = (*iterAction).at(2);
		//str.Format(L"%d",(*iterAction).at(1));
		if( commandNumber == COMMAND_BRACE_OPEN )
			str = L"(";
		else if(commandNumber == COMMAND_BRACE_CLOSE)
			str = L")";
		else if(commandNumber == COMMAND_PAUSE)
			str = L"...";
		else if(commandNumber >= COMMAND_SPEECH)
			str = L"..SPEECH..";
		else
			str = commandNames.at(commandNumber);
			
	
		strExpression += str;
		strExpression += L" ";
		// -----------------------------------


		// Expression Character ------------------- 
		int ExpressionNumber = (*iterAction).at(4);
		
		switch(ExpressionNumber){
			case 0: str = L"o";	break;
			case 1: str = L"U"; break;
			case 2: str = L"*";	break;
			case 3: str = L"X"; break;
			case 4: str = L"#"; break;
			default:str = L""; break;
		}

		strExpression += str;
		strExpression += L" ";
		// -----------------------------------
	}

	// is equal to ---------------------
	str = L" \n\n    =     \n\n ";
	strExpression += str;
	strExpression += L" ";
	// -----------------------------------

	for(iterSolution = vecSolution.begin(); iterSolution != vecSolution.end(); iterSolution++)
	{
		// Command Name -------------------
		int commandNumber = (*iterSolution).at(2);
		//str.Format(L"%d",(*iterAction).at(1));
		if( commandNumber == COMMAND_BRACE_OPEN )
			str = L" ";
		else if(commandNumber == COMMAND_BRACE_CLOSE)
			str = L" ";
		else if(commandNumber == COMMAND_PAUSE)
			str = L"...";
		else if(commandNumber >= COMMAND_SPEECH)
			str = L"..SPEECH..";
		else
			str = commandNames.at(commandNumber);
			
	
		strExpression += str;
		strExpression += L" > ";
		// -----------------------------------
	}

	CString msgHeader = L"\n The User given Script,  after calculation of Regular Expression \n -------------------------------------------------------------- \n\n";
	CString msgFooter = L"\n -------------------------------------------------------------- \n\n Do you want to play the Script now? \n";
	

	return (msgHeader + strExpression + msgFooter);
}

