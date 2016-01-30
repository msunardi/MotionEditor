#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <vector>


using namespace std;


void printExpression(vector < vector <int> > vectorAction,  vector <int> vectorRow);
void printExpression(vector < vector <int> > vectorAction);


CString formatExpression(vector < vector <int> > vectorAction, vector< vector<int> > vecSolution, vector<CString> commandNames);

vector< vector<int> > solveExpression(vector < vector <int> > vectorAction);

