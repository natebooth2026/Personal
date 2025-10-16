// Basic C++ CGPA Calculator
// A Nate Booth Production
// 1/4/2024 & 1/5/2024

// IDEA FROM: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/

#include <iostream>
#include <vector>
#include <cstdlib>
#include "class.hpp"

//intro stuff
int runTime = 0;
void intro(int&);

//grade selections and corresponding GPAs
const std::string availableGrades[] = { "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F" };
const double gpas[] = { 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1.3, 1.0, 0.0 };

//custom exception
class divisionByZero {};

int main() {
	intro(runTime);

	//defines information storages
	std::vector<Class> classes(1);
	std::vector<std::vector<Class>> semesters;

	//holds if a new class is being added or if the game is going to be restarted
	//initalized to * as a holder
	char nextSemesterOperation = '*';
	char nextClassOperation = '*';

	//holds information to be held in the classes
	double credits;
	int gradeNum;

	//loops until all classes are added
	while (nextSemesterOperation != 'n' && nextSemesterOperation != 'r') {
		std::cout << "SEMESTER " << semesters.size() + 1 << ": "
			<< std::endl << std::endl;
		while (nextClassOperation != 'n' && nextClassOperation != 'r') {
			//allows loop for grade selection 
			gradeNum = 0;

			std::cout << "Enter the number of credits: ";
			std::cin >> credits;

			while (gradeNum >= 12 || gradeNum <= 0) {
				//prints grades and corresponding numbers
				std::cout << "Here's the list of all available grades to choose from: "
					<< std::endl << "1- " << availableGrades[0] << std::endl <<
					"2- " << availableGrades[1] << std::endl <<
					"3- " << availableGrades[2] << std::endl <<
					"4- " << availableGrades[3] << std::endl <<
					"5- " << availableGrades[4] << std::endl <<
					"6- " << availableGrades[5] << std::endl <<
					"7- " << availableGrades[6] << std::endl <<
					"8- " << availableGrades[7] << std::endl <<
					"9- " << availableGrades[8] << std::endl <<
					"10- " << availableGrades[9] << std::endl <<
					"11- " << availableGrades[10] << std::endl <<
					"Select the appropriate grade with the corresponding number: ";

				//collects the grade selection
				std::cin >> gradeNum;
				std::cout << std::endl;

				//screens choice for correct selection
				if (gradeNum >= 12 || gradeNum <= 0) {
					std::cout << std::endl;
					std::cout << "Invalid choice." << std::endl << std::endl;
				}
			}

			//adds class details to the last element of the vecotr
			classes.back().setCredits(credits);
			classes.back().setSelection(gradeNum);

			//asks for next operation
			std::cout << std::endl << "Class recorded! Got another one for this semester? (y or n, r to restart) ";
			std::cin >> nextClassOperation;
			std::cout << std::endl << std::endl;

			if (nextClassOperation == 'y') {
				classes.resize(classes.size() + 1);
				continue;
			}
		}

		if (nextClassOperation == 'r') break;

		//records the semester
		semesters.push_back(classes);
		
		//asks for next semester operation
		std::cout << "Semester recorded! Got another one? (y or n, r to restart) ";
		std::cin >> nextSemesterOperation;
		std::cout << std::endl << std::endl;
		
		if (nextSemesterOperation == 'y') {			
			//resets classes vector for use in another semester
			classes.clear();
			classes.resize(1);

			//resets nextClassOperation
			nextClassOperation = '*';

			continue;
		}
	}
	
	//restarts program
	if (nextClassOperation == 'r' || nextSemesterOperation == 'r') {
		main();
		exit(EXIT_SUCCESS);
	}

	//prints all course details
	std::cout << "Thank you for using! Here are all the details!" << std::endl;

	//prints out each semester's details
	for (size_t i = 0; i < semesters.size(); ++i) {
		std::cout << "Semester " << i + 1 << ": " << std::endl;

		int classMarker = 0; //holds class number

		for (std::vector<Class>::iterator j = semesters[i].begin(); 
			j != semesters[i].end();
			++j) {
			++classMarker;
			std::cout << "Course " << classMarker << " credits: " 
				<< j->getCredits() << std::endl;
			std::cout << "Course grade & GPA: " << availableGrades[j->getSelection() - 1]
				<< " (" << gpas[j->getSelection() - 1] << ")" << std::endl << std::endl;
		}
	}

	//
	// calculates GPA
	//

	//holds credit and GPA sums
	double semesterCreditSum = 0;
	double semesterGPASum = 0;
	double creditSum = 0;
	double GPASum = 0;

	//gets credit and GPA sums per semester
	for (size_t i = 0; i < semesters.size(); ++i) {
		for (std::vector<Class>::iterator j = semesters[i].begin();
			j != semesters[i].end(); 
			++j) {
			semesterCreditSum += j->getCredits();
			semesterGPASum += gpas[j->getSelection() - 1] * j->getCredits();
			creditSum += j->getCredits();
			GPASum += gpas[j->getSelection() - 1] * j->getCredits();
		}

		//checks for division by zero
		try {
			if (semesterCreditSum == 0) throw divisionByZero();
		}
		catch (divisionByZero) {
			std::cout << "ERROR #0: DIVISION BY ZERO" << std::endl;
			exit(EXIT_FAILURE);
		}

		//prints semester details
		std::cout << "Semester " << i + 1 << " GPA: " << semesterGPASum / semesterCreditSum << std::endl << std::endl;

		//resets semester trackers if it is not the final semester counted
		if (i != semesters.size() - 1) {
			semesterCreditSum = 0;
			semesterGPASum = 0;
		}
	}

	std::cout << "Cumulative GPA: " << GPASum / creditSum << std::endl << std::endl;
}

//intro function
void intro(int& run) {
	if (run == 0) {
		std::cout << "Basic C++ CGPA Calculator" << std::endl;
		std::cout << "A Nate Booth Production" << std::endl << std::endl;
		++run;
	}
}