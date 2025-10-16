// Rock Paper Scissors (Nate's Version)
// A Nate Booth Production
// March 29th, 2024

//IDEA INSPIRED BY: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/ (Beg. 2)

#ifndef AI_HPP_
#define AI_HPP_

#include <string>

const std::string SECRET = "3292024";

class robot {
public:
	robot() : op(false), error(1) {}
	robot(int);

	int getError() { return error; }
	bool getPower() { return op; }
	std::string getChoice(bool);
private:
	const std::string AI[4] = { "r", "p", "s", SECRET };
	bool op;
	int error = 0; //checks for error (default) case
};

#endif