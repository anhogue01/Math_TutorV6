/**************************************************************************************
Program:     Math Tutor
Section:     4 - 1:00pm
Programmers: Andrew Hogue
Date:        11/25/2024
Version:     5
GitHub URL:  https://github.com/anhogue01/Math_TutorV5
Description:  This program is an easy math tutor that is intended to
            help small children do simple math problems. This program will ask the
            user to enter their name, and then ask them to input numbers
            resulting on an answer, the more questions that the user gets right the
            more that they level up and when they get a question wrong a certain
            number of times they level down.It does all 4 math operations to help kids in all
            math aspects.
**************************************************************************************/

#include <iostream>//This allows the programmer the use of cin's and couts
#include <string> // needed for the user's name
#include <ctime> //Needed for the rand() commands to work
#include <cstdlib> // used for the random number generator
#include <limits> // number validation while loop
#include <vector> // needed for the 2d vector summary report
#include <iomanip> // needed for setw
#include <ranges>

#include "main.h" // math tutor functions to make the game work

using namespace std;

int main() {
    // declaration of the 2d vector at the beginning of main
    vector<vector<int>> allQuestions;
    string userName = "?"; // the user's name
    string userInput = "?";// used for yes/no prompt

    int totalCorrect = 0; // used to level up
    int totalIncorrect = 0; // used to level down
    int mathLvl = 1;      // current level the user is on

    bool isCorrect = false; // did the user answer the current question correctly

    srand(time(0)); // seed the random method with the current time

    DisplayGameIntro();
    userName = GetUserName();

    do {
        // Generate a new question for the current level
        vector<int> currentQuestion = GenerateRandomQuestion(mathLvl);

        // Ask the question and get whether the user answered correctly
        isCorrect = GiveThreeAttempts(userName, currentQuestion);

        // Record the result in the current question vector
        if (isCorrect) {
            totalCorrect++;
        } else {
            totalIncorrect++;
            currentQuestion.push_back(0);
        }

        // Add the current question to the allQuestions summary
        allQuestions.push_back(currentQuestion);

        // Check if the user's level needs to be updated
        CheckForLevelChange(totalCorrect, totalIncorrect, mathLvl);

        // Store the Current question in the 2D vector
        allQuestions.push_back(currentQuestion);

        // Ask the user if they want to play again
        userInput = YesNoQuestion(userName + ", do you want to continue? (y/n)");

    } while (userInput == "yes");

    // Display a summary report
    DisplaySummaryReport(allQuestions);

    // End the program
    cout << "This is the end of the program. Thank You!!" << endl;

    return 0;
}
