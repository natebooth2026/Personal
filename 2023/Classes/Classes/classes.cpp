//Celcius Challenge
//A Nate Booth Production
//10-27-2023 & 10-29/30-2023

#include "def.hpp"
#include <iostream>
#include <cstdlib>

using std::cout; using std::cin; using std::endl;

int runTime = 0;
void intro(int&); 

int main() {
	intro(runTime);

	srand(time(nullptr)); //FIXED 12/12/2023

	cout << "Welcome to the Celcius Challenge!" << endl;
	cout << "Can you put in the right fareinheit temp to convert to the right celcius measurement?" << endl;
	cout << "don't cheat lol, no calculator" << endl;

	City randCity(rand() % 5, rand() % 5 + 1);
	TempsByMonth records;

	cout << "City name: " << cities[randCity.getCityNum()] << endl;
	cout << "Month: " << months[randCity.getMonthNum()] << endl;

	int tempFar = 0;
	cout << "Temperature in Farienheit: ";
	cin >> tempFar;

	randCity.convert(tempFar);
	int tempCel = randCity.getTemp();
	cout << endl << "You answered: " << tempCel << " degrees Celcius" << endl;

	if (randCity.checkAnswer(tempCel, records, randCity.getCityNum(), randCity.getMonthNum() + 1)) {
		cout << endl << "Congrats! You got it! Thanks for playing!" << endl;
		exit(EXIT_SUCCESS);
	}
	else {
		cout << endl << "Oops. Not it! Correct answer: ";
		switch (randCity.getMonthNum() + 1) {
		case 1:
			cout << records.January[randCity.getCityNum()];
			break;
		case 2:
			cout << records.February[randCity.getCityNum()];
			break;
		case 3:
			cout << records.March[randCity.getCityNum()];
			break;
		case 4:
			cout << records.April[randCity.getCityNum()];
			break;
		case 5:
			cout << records.May[randCity.getCityNum()];
			break;
		case 6:
			cout << records.June[randCity.getCityNum()];
			break;
		case 7:
			cout << records.July[randCity.getCityNum()];
			break;
		case 8:
			cout << records.August[randCity.getCityNum()];
			break;
		case 9:
			cout << records.September[randCity.getCityNum()];
			break;
		case 10:
			cout << records.October[randCity.getCityNum()];
			break;
		case 11:
			cout << records.November[randCity.getCityNum()];
			break;
		case 12:
			cout << records.December[randCity.getCityNum()];
			break;
		}
		cout << " degrees Celcius. Better luck next time." << endl;
		exit(EXIT_FAILURE);
	}

}

bool City::checkAnswer(int userTemp, TempsByMonth collection, int cityNum, int monthNum) {
	switch (monthNum) {
	case 1:
		if (userTemp != collection.January[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 2:
		if (userTemp != collection.February[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 3:
		if (userTemp != collection.March[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 4:
		if (userTemp != collection.April[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 5:
		if (userTemp != collection.May[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 6:
		if (userTemp != collection.June[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 7:
		if (userTemp != collection.July[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 8:
		if (userTemp != collection.August[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 9:
		if (userTemp != collection.September[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 10:
		if (userTemp != collection.October[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 11:
		if (userTemp != collection.November[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	case 12:
		if (userTemp != collection.December[cityNum]) {
			return false;
			break;
		}
		else {
			break;
		}
	}

	return true;
}

void City::convert(int temp) {
	temp_ = temp - 32;
	temp_ *= 5;
	temp_ /= 9;
}

void intro(int& run) {
	if (run == 0) {
		cout << "Celcius Challenge" << endl;
		cout << "A Nate Booth Production" << endl << endl << endl;
		++run;
	}
}