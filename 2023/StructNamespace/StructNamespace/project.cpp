//Weird
//A Nate Booth Production
//10-19-2023

#include <iostream>
#include <string>
#include <cstdlib>
#include "project.h"

using std::cout; using std::cin; using std::endl; using Nate::doStuff;

void invalidResponse();
bool calculate(userResponses, properResponses, int, int);

int main() {
	cout << "Weird - A Nate Booth Production" << endl;
	cout << "October 19th, 2023 - Version 1" << endl << endl;

	userResponses user;
	properResponses correct;

	int convertToBool;

	cout << "Welcome to the most random project you have ever seen!" << endl;
	cout << "To find your missing child, you must answer these specific questions and get all 100% right." << endl;
	cout << "You have one try." << endl << endl;

	cout << "Type in a number 1-10: ";
	cin >> user.userAnswer.one;
	if (user.userAnswer.one < 1 || user.userAnswer.one > 10) {
		invalidResponse();
	}

	cout << endl;

	cout << "What is delta x of the integral from 1 to 4 with an unknown n? ";
	cin >> user.userAnswer.two;

	cout << endl;

	cout << "Type in pi to 12 decimal places. ";
	cin >> user.userAnswer.three;
	if (user.userAnswer.three < 3.0 || user.userAnswer.three > 4.0) {
		invalidResponse();
	}

	cout << endl;

	cout << "True (1) or False (2). ";
	cin >> convertToBool;
	if (convertToBool == 1) {
		user.userAnswer.four = true;
	}
	else if (convertToBool == 2) {
		user.userAnswer.four = false;
	}
	else {
		invalidResponse();
	}

	cout << endl;

	cout << "Type in a character! guess the right one >:) #rekt";
	cin >> user.userAnswer.five;

	cout << endl << endl;
	cout << "Calculating results.... " << endl;

	int originalTime = time(nullptr);

	while (time(nullptr) != originalTime + 3) {
		continue;
	}

	const int correctSize = 5;
	bool isCorrect[correctSize];

	//collects results
	for (int i = 0; i < correctSize; ++i) {
		isCorrect[i] = calculate(user, correct, correctSize, i + 1);
	}
	
	int totalCorrect = 0;

	//displays results
	for (int i = 1; i <= correctSize; ++i) {
		cout << "#" << i << ": ";
		if (isCorrect[i - 1] == true) {
			cout << "100%" << endl;
			++totalCorrect;
		}
		else if (isCorrect[i - 1] == false) {
			cout << "0%" << endl;
		}
		else {
			invalidResponse();
		}
	}

	cout << endl;
	
	if (totalCorrect == correctSize) {
		user.message = true;
		doStuff(user.message);
	}
	else {
		user.message = false;
		doStuff(user.message);
	}
}

void invalidResponse() {
	cout << endl;
	cout << "Invalid response/error detected! You lose!" << endl;
	exit(EXIT_FAILURE);
}

bool calculate(userResponses user, properResponses correct, int correctSize, int question) {
	if (question >= 1 && question <= correctSize) {
		switch (question) {
		case 1:
			if (user.userAnswer.one == correct.one) {
				return true;
			}
			else {
				return false;
			}
			break;
		case 2:
			if (user.userAnswer.two == correct.two) {
				return true;
			}
			else {
				return false;
			}
			break;
		case 3:
			if (user.userAnswer.three == correct.three) {
				return true;
			}
			else {
				return false;
			}
			break;
		case 4:
			if (user.userAnswer.four == correct.four) {
				return true;
			}
			else {
				return false;
			}
			break;
		case 5:
			if (user.userAnswer.five == correct.five) {
				return true;
			}
			else {
				return false;
			}
			break;
		default:
			return false;
			invalidResponse();
		}
	}
	else {
		return false;
		invalidResponse();
	}
}