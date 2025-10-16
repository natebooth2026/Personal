//Hide-N-Seek
//A Nate Booth Production
//11-6-2023 to 11-8-2023

//INSPIRED BY MAZE PROJECT (Labs 8 & 9)

#include "room.hpp"

using std::cout; using std::cin; using std::endl;

Room changeRoom(Room current, char endY, int endX) {
	Room newRoom('*', -1);
	char dir;
	
	while (newRoom.getX() == -1 && newRoom.getY() == '*') {
		cout << "What direction do you want to go? (u, d, l, r) (q to quit) ";

		cin >> dir;
		cout << endl;

		if (dir == 'q') return newRoom;

		switch (dir) {
		case 'u':
			newRoom.changeX(current.getX());
			newRoom.changeY(current.getY());

			if (current.getY() - 1 < 'a') {
				cout << "Ow! Wall!" << endl;
				break;
			}
			else {
				newRoom.changeY(current.getY() - 1);
				break;
			}
		case 'd':
			newRoom.changeX(current.getX());
			newRoom.changeY(current.getY());

			if (current.getY() + 1 > endY) {
				cout << "Ow! Wall!" << endl;
				break;
			}
			else {
				newRoom.changeY(current.getY() + 1);
				break;
			}
		case 'l':
			newRoom.changeX(current.getX());
			newRoom.changeY(current.getY());

			if (current.getX() - 1 < 1) {
				cout << "Ow! Wall!" << endl;
				break;
			}
			else {
				newRoom.changeX(current.getX() - 1);
				break;
			}
		case 'r':
			newRoom.changeX(current.getX());
			newRoom.changeY(current.getY());

			if (current.getX() + 1 > endX) {
				cout << "Ow! Wall!" << endl;
				break;
			}
			else {
				newRoom.changeX(current.getX() + 1);
				break;
			}
		default:
			cout << "Invalid response detected.";
			newRoom.changeY('*' - 1);
			newRoom.changeX(-2);
			break;
		}

		cout << endl;
		return newRoom;
	}
}