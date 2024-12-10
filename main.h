/*****************************************************************************
Program: MathTutorV5
Programmer: Andrew Hogue
Date: 2024.11.12
github URL: https://github.com/anhogue01/Math_TutorV5
Description: This file contains all the prototypes for the functions that the
             main function calls.
*******************************************************************************/

#ifndef MATHTUTOR_H
#define MATHTUTOR_H

#include <string> // for string data types
#include <vector> // for storing the questions in a 2D vector

using namespace std;



void DisplayGameIntro();
string GetUserName();
vector<int> GenerateRandomQuestion(int mathLvl);
int GetNumericValue();
bool GiveThreeAttempts(string userName, vector<int> &currentQuestion);
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect,
                         int &mathLvl);
string YesNoQuestion(string question);
void DisplaySummaryReport(const vector<vector<int>> &allQuestions);

#endif

