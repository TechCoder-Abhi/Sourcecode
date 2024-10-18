#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // To use time() for randomization
#include <chrono>   // For timers
#include <thread>   // To add a slight delay

using namespace std;

int highestScore = 0;  // To store the best score achieved

// Function that runs the quiz, generates questions, and manages user input
void startQuiz(string operationType, int level, int totalQuestions) {
    int number1, number2, correctAnswer, playerScore = 0;
    char answerChoice;
    srand(static_cast<unsigned>(time(0)));  // Random number seed

    for (int i = 1; i <= totalQuestions; i++) {
        // Generate numbers based on difficulty level
        number1 = rand() % (level * 10) + 1;
        number2 = rand() % (level * 10) + 1;

        if (operationType == "Addition") {
            correctAnswer = number1 + number2;
            cout << "\nQ" << i << ": What is " << number1 << " + " << number2 << "?\n";
        } else if (operationType == "Subtraction") {
            correctAnswer = number1 - number2;
            cout << "\nQ" << i << ": What is " << number1 << " - " << number2 << "?\n";
        } else if (operationType == "Multiplication") {
            correctAnswer = number1 * number2;
            cout << "\nQ" << i << ": What is " << number1 << " * " << number2 << "?\n";
        } else if (operationType == "Division") {
            while (number2 == 0) number2 = rand() % (level * 10) + 1;  // Avoid zero in division
            correctAnswer = number1 / number2;
            cout << "\nQ" << i << ": What is " << number1 << " / " << number2 << "?\n";
        }

        // Provide multiple choices
        int incorrect1 = correctAnswer + (rand() % 5 + 1);
        int incorrect2 = correctAnswer - (rand() % 5 + 1);
        int incorrect3 = correctAnswer + (rand() % 3 + 2);

        // Randomize answer placement
        int correctSpot = rand() % 4;
        int options[4];
        options[correctSpot] = correctAnswer;
        int index = 0;
        for (int j = 0; j < 4; j++) {
            if (j != correctSpot) {
                if (index == 0) options[j] = incorrect1;
                else if (index == 1) options[j] = incorrect2;
                else options[j] = incorrect3;
                index++;
            }
        }

        // Display options
        cout << "A) " << options[0] << "  B) " << options[1] << "  C) " << options[2] << "  D) " << options[3] << "\n";

        // Timer: 10 seconds to answer
        auto start = chrono::steady_clock::now();
        char userAnswer;
        bool timeOut = false;

        // Time checking loop
        while (true) {
            if (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() > 10) {
                timeOut = true;
                cout << "Oops! Time's up!\n";
                break;
            }

            if (cin >> userAnswer) {
                break;
            }
        }

        // If the user answered within the time limit
        if (!timeOut) {
            int chosenAnswerIndex = (userAnswer == 'A' || userAnswer == 'a') ? 0 :
                                    (userAnswer == 'B' || userAnswer == 'b') ? 1 :
                                    (userAnswer == 'C' || userAnswer == 'c') ? 2 : 3;

            if (options[chosenAnswerIndex] == correctAnswer) {
                cout << "Nice! That's correct!\n";
                playerScore++;
            } else {
                cout << "Sorry, that's wrong! The right answer is: " << correctAnswer << "\n";
            }
        } else {
            cout << "Missed it! The correct answer is: " << correctAnswer << "\n";
        }

        // Ask if the user wants a hint for the next question
        cout << "Need a hint for the next one? (Y/N): ";
        cin >> answerChoice;
        if (answerChoice == 'Y' || answerChoice == 'y') {
            cout << "Hint: Sometimes, the first number is key!\n";
        }

        // Pause before moving to the next question
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Final score
    cout << "\nYour score: " << playerScore << "/" << totalQuestions << "\n";

    // Update and display leaderboard
    if (playerScore > highestScore) {
        highestScore = playerScore;
        cout << "New high score: " << highestScore << "!\n";
    } else {
        cout << "Top score remains: " << highestScore << "\n";
    }
}

int main() {
    int quizChoice, difficultyLevel, questionCount;
    string selectedQuiz;
    char exitChoice;

    do {
        cout << "\n### Welcome to the Math Quiz ###\n";
        cout << "Select a quiz category:\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\n";
        cin >> quizChoice;

        // Exit option
        if (quizChoice == 5) {
            cout << "Thanks for playing! Goodbye!\n";
            break;
        }

        // Quiz type selection
        switch(quizChoice) {
            case 1: selectedQuiz = "Addition"; break;
            case 2: selectedQuiz = "Subtraction"; break;
            case 3: selectedQuiz = "Multiplication"; break;
            case 4: selectedQuiz = "Division"; break;
            default: cout << "Invalid option, try again!"; continue;
        }

        // Difficulty selection
        cout << "Pick a difficulty level (1 = Easy, 2 = Medium, 3 = Hard): ";
        cin >> difficultyLevel;

        // User chooses number of questions
        cout << "How many questions would you like to answer? ";
        cin >> questionCount;

        // Start the quiz
        startQuiz(selectedQuiz, difficultyLevel, questionCount);

        // Ask user if they want to exit or play again
        cout << "Would you like to exit? (Y/N): ";
        cin >> exitChoice;

    } while (exitChoice == 'N' || exitChoice == 'n');
    
    return 0;
}
