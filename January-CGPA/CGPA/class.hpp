// Basic C++ CGPA Calculator
// A Nate Booth Production
// 1/4/2024 & 1/5/2024

// IDEA FROM: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/

#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>

class Class {
public:
	//accessors
	double getCredits() const { return credits_; }
	int getSelection() const { return gradeSelection_; }

	//mutators
	void setCredits(const double credits) { credits_ = credits; }
	void setSelection(const int selection) { gradeSelection_ = selection; }
private:
	double credits_;
	int gradeSelection_;
};

#endif
