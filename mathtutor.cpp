/*************************************************************************************************
 Program: MathTutorV5
 Programmer: Andrew Hogue
 Date: 2024.11.19
 github URL: https://github.com/anhogue01/Math_TutorV5
 Description: This file contains all the functions that the main function calls.
 *************************************************************************************************/
#include "main.h"

#include <cctype>  // for lower casing yes/no input
#include <cstdlib> // for srand and rand
#include <iostream>// for cout and cin
#include <iomanip> // for report column alignment
#include <limits>  // for invalid numeric inputs
#include <string>  // for string data types
#include <vector>  // for storing the questions in a 2D vector

using namespace std;

//max number of attempts per question before displaying the answer
const int MAX_ATTEMPTS = 3;
// how much to increase or decrease the random number range per level
const int LEVEL_RANGE = 10;

// Display the game's intro
void DisplayGameIntro() {


 cout << "***********************************************************************************" << endl;
 cout << "*                __  __       ___  _        _____       __                        *" << endl;
 cout << "*               |  \\/  | __ __|  |_| |__    |_   _|   _|  |_ ___    _ __          *" << endl;
 cout << "*               | |\\/| |/ _`  |  __| '_  \\    | || | | |  __/  _ \\ | '__|         *" << endl; // NOLINT(*-raw-string-literal)
 cout << "*               | |  | | (_|  |  |_| | | |    | || |_| |  || (_) | | |            *" << endl;
 cout << "*               |_|  |_|\\__,_ |\\___|_| |_|    |_| \\__,_|\\__ \\____/ |_|            *" << endl; // NOLINT(*-raw-string-literal)
 cout << "*                                                                                 *" << endl;
 cout << "***********************************************************************************" << endl;
 cout << "*                       Welcome to silly Simple Math Tutor                        *" << endl;
 cout << "***********************************************************************************" << endl;
 // this is the code for the math fun facts
 cout << "Fun Math Facts:" << endl;
 cout << "         * There is no roman numeral for zero " << endl;
 cout << "         * The world forty is the only number spelled alphabetically" << endl;
 cout << "         * The symbol for division is also known as obelus" << endl;
 cout << "         * The word one is the only number that is spelled in decending order" << endl;
 cout << endl;
 cout << "***********************************************************************************" << endl;
 cout << endl;

 cout << "Welcome to the Silly Simple Math Tutor!!!" << endl;

} // end of DisplayGameIntro function

// Get the user's name and welcomes the user
string GetUserName() {
 string userName = "?";

 cout << "What is your name? ";
 getline(cin, userName); // handle for spaced in a person's name
 cout << "Welcome " << userName <<" to the Silly Simply Math Tutor!" << endl;

 return userName;
} // end of GetUserName function

// Gernerate each random question
vector<int> GenerateRandomQuestion(int mathLvl) {
 enum MathType { MT_ADD = 1, MT_SUB = 2, MT_MUL = 3, MT_DIV = 4};
 MathType mathType = static_cast<MathType>(rand() % 4 + 1);

 int leftNum = rand() % (mathLvl * LEVEL_RANGE) + 1;
 int rightNum = rand() % (mathLvl * LEVEL_RANGE) + 1;
 char mathSymbol = '?';
 int correctAns = 0;

 switch (mathType) {
  case MT_ADD:
   mathSymbol = '+';
  correctAns = leftNum + rightNum;
  break;
  case MT_SUB:
   mathSymbol = '-';
  if (rightNum > leftNum) swap(leftNum, rightNum);
  correctAns = leftNum - rightNum;
  break;
  case MT_MUL:
   mathSymbol = '*';
  correctAns = leftNum * rightNum;
  break;
  case MT_DIV:
   mathSymbol = '/';
  rightNum = max(1, rightNum); // avoid division by zero
  leftNum *= rightNum;
  correctAns = leftNum / rightNum;
  break;
  default:
   cout << "Invalid Question Type: " << mathType << endl;
  cout << "Program terminated. Error -1" << endl;
  cout << "Please contact Andrew Hogue at 555-555-5555"<< endl;

 }

 return {mathLvl, leftNum, static_cast<int>(mathSymbol), rightNum, correctAns};
}

int GetNumericValue() {
 int userValue;

 while(!(cin >> userValue)) {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Invalid input. Please enter a number: ";
 }
 return userValue;
}

 bool GiveThreeAttempts(string userName, vector<int> &currentQuestion) {
 int mathLvl = currentQuestion[0];
 int leftNum = currentQuestion[1];
 char mathSymbol = static_cast<char>(currentQuestion[2]);
 int rightNum = currentQuestion[3];
 int correctAns = currentQuestion[4];
 int userAns = 0;

 for (int i = 1; i <= MAX_ATTEMPTS; i++) {
  // prompt the user to answer a random math question and get the userAnswer
  cout << "[Level #" << mathLvl << "] " << userName << ", what does "
       << leftNum << " " << mathSymbol << " " << rightNum << " = ";
  while (!(cin >> userAns)) {
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   cout << "Invalid Input. Please enter a number: ";
  }
  if (userAns == correctAns) {
   cout << "Correct! Well Done!\n";
   currentQuestion.push_back(i);
   return true;
  } else {
   cout << "Incorrect Answer." <<(MAX_ATTEMPTS - i) << " attempts remaining.\n";
  }
 }
 cout << "The Correct answer was: "<< correctAns << endl;
 currentQuestion.push_back(0); // log failed attempts
 return false;
}

void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLvl) {
 const int MAX_CORRECT_TO_LEVEL_UP = 3;
 const int MAX_INCORRECT_TO_LEVEL_DOWN = 3;

 if (totalCorrect >= MAX_CORRECT_TO_LEVEL_UP) {
  mathLvl++;
  totalCorrect = 0;
  totalIncorrect = 0;
  cout << "You've leveled up to level " << mathLvl << "!\n";
 } else if (totalIncorrect >= MAX_INCORRECT_TO_LEVEL_DOWN && mathLvl > 1) {
  mathLvl--;
  totalCorrect = 0;
  totalIncorrect = 0;
  cout << "You've leveled down to level " << mathLvl << "!\n";
 }
}

string YesNoQuestion(string question) {
 string userInput;

 while (true) {
  // Prompt the user to play again
  cout << question;
  cin >> userInput;

  for (char& c : userInput) {
   c = tolower(c); // converts input to lowercase
  }

  if (userInput == "y" || userInput == "yes") {
   return "yes";
  }else if(userInput == "n" || userInput == "no") {
   return "no";
  } else {
   cout << "Invalid Input. Please enter 'y' or 'n'" << endl;
  }
 }
}

void DisplaySummaryReport(const vector<vector<int>> &allQuestions) {
 cout << "========================================================" << endl;
 cout << "                       Summary Report                  " << endl;
 cout << "========================================================" << endl;
 cout << "Level   Question       Correct Answer   Attempts" << endl;
 cout << "--------------------------------------------------------" << endl;

 for (const auto& question : allQuestions) {
  int level = question[0];         // Level
  int num1 = question[1];         // First number
  int num2 = question[2];         // Second number
  int correctAnswer = question[3]; // Correct answer
  int attempts = question[4];     // Attempts
  int userCorrect = question[5];  // Correct or incorrect indicator

  // Print formatted question details
  cout << setw(5) << level << "   "
       << setw(4) << num1 << " "
       << (question[6] == 1 ? "+" : (question[6] == 2 ? "-" : (question[6] == 3 ? "*" : "/")))
       << " " << setw(3) << num2 << "   "
       << setw(13) << correctAnswer << "   "
       << (userCorrect == 1 ? "Correct" : "Incorrect") << endl;
 }

 cout << "========================================================" << endl;
 cout << "This is the end of the program. Thank You!!" << endl;
}






