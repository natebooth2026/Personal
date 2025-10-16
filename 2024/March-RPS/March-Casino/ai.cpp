// Rock Paper Scissors (Nate's Version)
// A Nate Booth Production
// March 29th, 2024

//IDEA INSPIRED BY: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/ (Beg. 2)

#include "ai.hpp"

robot::robot(int num) {
	error = 0;
	if (!(num % 2)) {
		op = true;
	}
	else {
		op = false;
	}
}

std::string robot::getChoice(bool gun) {
	if (!gun) {
		return AI[rand() % 3];
	}
	else {
		if (op) return AI[3];
		else return AI[rand() % 4];
	}
}