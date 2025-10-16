// Lottery Simulator
// A Nate Booth Production
// 11-13-2023 & 11-20-2023

#include "ticket.hpp"
#include <iostream>

using std::cout; using std::cin; using std::endl;

int main() {
	srand(time(nullptr));

	cout << "Lottery Simulator" << endl
		<< "A Nate Booth Production" << endl << endl;

	int randSizeChance = 0;

	while (randSizeChance < 10) {
		randSizeChance = rand() % 25 + 1;
	}

	Ticket user(randSizeChance);

	bool sure = false; 
	int num = 0;
	int multiplier = 0;

	cout << "PICK THE RIGHT NUMBER AND MULTIPLIER AND WIN UP TO $1 MILLION!" << endl;
	cout << "YOU HAVE ONE SHOT." << endl;
	cout << endl;

	while (!sure) {
		cout << "Pick a number (1 to " << user.size() << ") and multiplier (1 to 10): ";
		cin >> num >> multiplier;

		char sureChoice = '*';
		while (sureChoice != 'y') {
			cout << "Are you sure? (y or n) ";
			cin >> sureChoice;
			if (sureChoice == 'y') {
				sure = true;
				break;
			}
			else if (sureChoice == 'n') {
				sure = false;
				break;
			}
			else {
				cout << "Invalid response. Try again." << endl;
				continue;
			}
		}

		cout << endl;
	}

	if (user.check(num, multiplier)) {
		user.setWon();
		cout << "YOU WIN!" << endl;
		cout << "Your winnings are: ";
		user.winnings(multiplier);
		cout << "!" << endl;
		million(user);
		cout << endl;
	}
	else {
		cout << "You lost." << endl;
		cout << "Winning combo: ";
		user.winningNums();
		cout << endl;
		cout << "You could've won ";
		user.winnings(user.winningMulti());
		cout << endl << endl;
	}
}