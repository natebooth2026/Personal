// Lottery Simulator 2
// A Nate Booth Production
// 11/28/2023 & 11/29/2023

// CODE FROM LOTTERY SIMULATOR REUSED
// INSPIRED BY CS IB LAB 12

#include "print.hpp"
#include <iostream>

using std::cout; using std::endl;

//prints tickets for user viewage based on what the coordinates flag
void printTicket(vector<vectBool> ticket) {
	for (size_t i = 0; i < ticket.size(); ++i) { //nums, rows
		for (size_t j = 0; j < ticket[i].size(); ++j) { //multipliers, columns
			if (ticket[i][j] == false) {
				cout << "X  ";
			}
			else {
				cout << "!  "; //as checkmark is incompatible
			}
		}
		cout << endl;
	}
}