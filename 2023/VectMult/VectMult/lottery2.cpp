// Lottery Simulator 2
// A Nate Booth Production
// 11/28/2023 & 11/29/2023

// CODE FROM LOTTERY SIMULATOR REUSED
// INSPIRED BY CS IB LAB 12

#include "print.hpp"
#include <iostream>

using std::cout; using std::cin; using std::endl;

const int rows = 10;

int main() {
	srand(time(nullptr));

	//program intro
	cout << "Lottery Simulator 2" << endl
		<< "A Nate Booth Production" << endl
		<< "Inspired by CS IB Lab 6 (CS I Lab 12)" << endl
		<< "For the best experience, play in full screen!" << endl << endl;

	//sets randomized size
	int randSizeChance = 0;
	while (randSizeChance < 10) {
		randSizeChance = rand() % 25 + 1;
	}

	int size = 0;
	while (size < 5) {
		size = rand() % randSizeChance + 1;
	}

	//defines the rows of the tickets
	vectBool userBase(rows);
	vectBool winningBase(rows);

	//holds the tickets by defining the columns then adding the rows
	//nums is the first dimension
	vector<vectBool> user;
	vector<vectBool> winner;

	for (size_t i = 0; i < size; ++i) {
		user.push_back(userBase);
		winner.push_back(winningBase);
	}

	//determines winning numbers with a random amount of chances
	//creates random chance of winning with rows/shots due to random size
	//determining the amount of winners
	int shots = rand() % 5 + 1;

	vector<int> winningNums(rows/shots);
	vector<int> winningMultipliers(rows/shots);

	for (int i = 0; i < rows / shots; ++i) {
		if (i == 0) { //inital
			winningNums[i] = rand() % size;
			winningMultipliers[i] = rand() % rows;
		}
		//else cases add new numbers and make sure that they do not match
		//the previous selection
		else if (winningNums[i] != winningNums[i - 1] && winningMultipliers[i] != winningMultipliers[i - 1]) { 
			winningNums[i] = rand() % size;
			winningMultipliers[i] = rand() % rows;
			while (winningNums[i] == winningNums[i - 1]
				|| winningMultipliers[i] == winningMultipliers[i - 1]) {
				winningNums[i] = rand() % size;
				winningMultipliers[i] = rand() % rows;
			}
		}
		else {
			winningNums[i] = rand() % size;
			winningMultipliers[i] = rand() % rows;
			while (winningNums[i] == winningNums[i - 1]
				|| winningMultipliers[i] == winningMultipliers[i - 1]) {
				winningNums[i] = rand() % size;
				winningMultipliers[i] = rand() % rows;
			}
		}
		//flags which part of the ticket needs to be lit up on the winner ticket
		winner[winningNums[i]][winningMultipliers[i]] = true;
	}

	//defines vars to hold user choices
	int num = 0;
	int multiplier = 0;

	//game intro
	cout << "PICK ONE OF THE RIGHT NUMBERS AND MULTIPLIERS AND WIN UP TO $1 MILLION!" << endl;
	cout << "YOU HAVE " << shots << " SHOTS. " << shots << " ATTEMPT(S)." 
		<< " ~" << rows / shots << " WINNERS." << endl;
	cout << endl;

	//holds amount of attempts
	int attempts = 0;

	//holds all previous, valid choices
	vector<int> originalNums(attempts);
	vector<int> originalMults(attempts);

	//holds case if the num and multiplier can be assigned to the previous vectors
	bool validAssign = false;

	//lottery choice loop, ends when the # of attempts equals the allotted shots
	while (attempts < shots) {
		if (attempts != 0 && validAssign) {
			originalNums[attempts-1] = num;
			originalMults[attempts-1] = multiplier;
		}
		
		//asks user
		cout << "Pick a number (1 to " << size << ") and multiplier (1 to " << rows << "): ";
		cin >> num >> multiplier;

		//checks for invalid response, restarts loop if so
		if (num > size || multiplier > rows || num < 1 || multiplier < 1) {
			validAssign = false;
			num = originalNums[attempts - 1];
			multiplier = originalMults[attempts - 1];
			cout << "Invalid response." << endl << endl;
			continue;
		}

		//checks to see if it already selected, restarts loop if so
		bool alreadySelected = false;
		if (attempts != 0) {
			for (size_t i = 0; i < originalNums.size(); ++i) {
				if (!alreadySelected && num == originalNums[i] && multiplier == originalMults[i]) {
					alreadySelected = true;
				}
			}
		}

		if (alreadySelected) {
			validAssign = false;
			num = originalNums[attempts - 1];
			multiplier = originalMults[attempts - 1];
			cout << "You already selected this spot!" << endl << endl;
			continue;
		}

		//verifies user choice, if so: flags choice on ticket,
		//resizes original choices vector, takes up one attempt,
		//allows assignment to original choice vector and restarts loop
		//if not or invalid, reboots loop with no additional changes
		char sureChoice = '*';
		while (sureChoice != 'y') {
			cout << "Are you sure? (y or n) ";
			cin >> sureChoice;
			if (sureChoice == 'y') {
				user[num-1][multiplier-1] = true;
				++attempts;
				originalNums.resize(attempts);
				originalMults.resize(attempts);
				validAssign = true;
				break;
			}
			else if (sureChoice == 'n') {
				validAssign = false;
				num = originalNums[attempts - 1];
				multiplier = originalMults[attempts - 1];
				break;
			}
			else {
				validAssign = false;
				num = originalNums[attempts - 1];
				multiplier = originalMults[attempts - 1];
				cout << "Invalid response. Try again." << endl;
				continue;
			}
		}

		cout << endl;
	}

	//adds final choice to vector
	if (attempts != 0 && validAssign) {
		originalNums[attempts - 1] = num;
		originalMults[attempts - 1] = multiplier;
	}

	//resizes winner vectors so they can be compared with previous choices
	winningNums.resize(shots);
	winningMultipliers.resize(shots);

	//checks for a winner
	bool wonNum = false;
	bool wonMult = false;
	for (int i = 0; i < shots; ++i) { 
		//flags boolean for a winner by checking if the appropriate coordinate
		//on winner ticket is true, and then ups the multiplier to winner
		if (winner[originalNums[i] - 1][originalMults[i] - 1] 
			&& wonNum == false && wonMult == false) {
			wonNum = true;
			wonMult = true;
			multiplier = originalMults[i];
		}
		//if multiple choices are winners and the boolean has already been flagged
		//ups the multiplier if the user won more than the last multiplier
		//allows
		if (winner[originalNums[i] - 1][originalMults[i] - 1] 
			&& multiplier < originalMults[i]) { //runs even if winner has already been found
			multiplier = originalMults[i];
		}
	}

	//checks if the user won, prints tickets, and prints results
	if (wonNum && wonMult) {
		cout << "YOU WON!" << endl << endl;

		cout << "Your ticket: " << endl;
		printTicket(user);
		cout << "Winning ticket: " << endl;
		printTicket(winner);
		cout << endl;

		//program and game outro
		cout << "Your winnings are: "
			<< "$" << 100000 * multiplier << "!";
		if (multiplier == 10) {
			cout << endl << "CONGRATS! YOU GOT THE $1 MILLION JACKPOT!!";
		}
		cout << endl;
	}
	else {
		cout << "You lost." << endl << endl;

		cout << "Your ticket: " << endl;
		printTicket(user);
		cout << "Winning ticket: " << endl;
		printTicket(winner);
		cout << endl;

		//program and game outro
		cout << "You could've won "
			<< "up to $1 million!"
			<< endl << "Better luck next time!"
			<< endl;
	}
}