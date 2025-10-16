//Hide-N-Seek
//A Nate Booth Production
//11-6-2023 to 11-8-2023

//INSPIRED BY MAZE PROJECT (Labs 8 & 9)

#include "room.hpp"

using std::cin; using std::cout; using std::endl;

int runTime = 0;
void intro(int&);

int main() {
	srand(time(nullptr));

	const int MAXIMUM_SIZE = 26;

	int randEndX = rand() % MAXIMUM_SIZE + 1;
	char randEndY = 'a' + rand() % MAXIMUM_SIZE; //FIXED 12/12/2023
												 //Coordinate {1 spotted


	while (randEndX < 5 || randEndY < 'a' + 5 || randEndY > 'a' + MAXIMUM_SIZE) {
		randEndX = rand() % MAXIMUM_SIZE + 1;
		randEndY = 'a' + rand() % MAXIMUM_SIZE; //FIXED 12/12/2023
												//Coordinate {1 spotted
	}

	int randX = rand() % randEndX + 1;
	char randY = 'a' + rand() % (randEndY - 'a') + 1;

	intro(runTime);

	cout << "I'm hiding. Come find me!" << endl << endl;

	Room start('a', 1);
	Room friendHide(randY, randX);
	Room end(randEndY, randEndX);
	Room current = start;

	while (!(current.getX() == friendHide.getX() && current.getY() == friendHide.getY())) {
		Room ref = current;
		Room* cp = &current; //ADDED 12/12/2023
							 //cp = current pointer
		
		//on 12/12/2023,
		//all below code showing "cp->" was changed from "current." 
		//and all below code showing "*cp" was changed from "current"
		while (cp->getX() == ref.getX() && cp->getY() == ref.getY()) {
			cout << "Current location: ";
			cp->output();
			cout << endl;

			*cp = changeRoom(*cp, end.getY(), end.getX());
		}
		
		if (cp->getY() == '*' && cp->getX() == -1) {
			cout << "Geez, debby downer." << endl;
			cout << "I was in room " << friendHide.getY() << friendHide.getX() << endl;
			exit(EXIT_SUCCESS);
		}

		if (cp->getY() == '*' - 1 && cp->getX() == -2) {
			exit(EXIT_FAILURE);
		}

		int chance = rand() % 2;

		if (chance == 0 && (cp->getX() != friendHide.getX() || cp->getY() != friendHide.getY())) {
			cout << "*You don't hear anything*" << endl;
		}
		else if (chance == 1 && (cp->getX() != friendHide.getX() || cp->getY() != friendHide.getY())) {
			cout << "*You hear quiet movement*" << endl;
		}
	}

	cout << "*You hear loud movement*" << endl;
	cout << "Did you find him? (y or n) ";
	char found;
	cin >> found;
	if (found == 'y') {
		cout << endl;
	}
	else if (found == 'n') {
		friendHide.setScared(true);
		cout << endl << "BOOO!!! Got ya!" << endl;
	}
	else {
		cout << endl << "Invalid response detected." << endl << endl;
		exit(EXIT_FAILURE);
	}

	if (!friendHide.getScared()) {
		cout << "Ah! You found me!" << endl;
	}

	cout << "Want to go again? (y or n) ";
	
	char again;
	cin >> again;

	if (again == 'y') {
		cout << endl << "Okay!" << endl;
		main();
	}
	else if (again == 'n') {
		cout << endl << "Okay then! I got to go! Bye!" << endl;
	}
	else {
		cout << endl << "wut?" << endl;
	}
}

void intro(int& runs) {
	if (runs == 0) {
		cout << "Hide-N-Seek" << endl << "A Nate Booth Production" << endl << "INSPIRED BY MAZE PROJECT (CS IB Labs 8 & 9)" << endl << "---------" << endl << endl;
		++runs;
	}
}