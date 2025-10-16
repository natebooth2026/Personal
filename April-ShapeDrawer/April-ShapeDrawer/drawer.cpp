// Shape Drawer
// A Nate Booth Prodcuction
// April 28th, 2024

#include "shapes.hpp"
#include <iostream>

int runTime = 0; //used to determine intros
const int DIMENSIONS = 75; //holds graph dimensions (>= 25)
void delayEnd(); //for .exe delayed close
class tooSmall {}; //to detect if dimensions is less than 25

int main() {
	srand(time(nullptr));

	//program intro
	if (runTime == 0) {
		std::cout << "Shape Drawer\nA Nate Booth Production\n\n";
		std::cout << "s for Square\nc for Circle\nt for Triangle\n\n";
	}
	
	//initalizes graph (checks if dimensions are too small first)
	try {
		if (DIMENSIONS < 25) throw tooSmall();
	}
	catch (tooSmall) {
		std::cout << "Dimensions error.\n\n";
		delayEnd();
	}

	char graph[DIMENSIONS][DIMENSIONS];
	for (int i = 0; i < DIMENSIONS; ++i) {
		for (int j = 0; j < DIMENSIONS; ++j) {
			graph[i][j] = '!';
		}
	}

	//initalizes shape collection (5 per 25 in dimensions)
	const int COLLECTION_SIZE = 5 * (DIMENSIONS / 25) > 0 ? 5 * (DIMENSIONS / 25) : 1;
	Shape* collection[COLLECTION_SIZE];

	//prints number of shapes to draw
	std::cout << "Number of shapes to draw: " << COLLECTION_SIZE << "\n";

	char choice; //holds shape choice
	int i = 0; //holds number of shapes
	
	//shape generation loop
	while (i < COLLECTION_SIZE) {
		std::cout << "What shape do you want to draw? (Shape " << i + 1 << ") ";
		std::cin >> choice;

		triangleType randType = none; //holds type of triangle
		int randNum = rand() % 4; //holds num to determine randType

		//generates, stores pointer, and crafts shape
		switch (choice) {
		case 's': //square
			collection[i] = new Square(rand() % (DIMENSIONS - 5), rand() % (DIMENSIONS - 5));
			collection[i]->craft();

			++i; //move to next shape
			break;
		case 'c': //circle
			collection[i] = new Circle(rand() % (DIMENSIONS - 5), rand() % (DIMENSIONS - 5));
			collection[i]->craft();

			++i; //move to next shape
			break;
		case 't': //triangle
			//determines type of triangle
			switch (randNum) {
			case 0:
				randType = topLeft;
				break;
			case 1:
				randType = topRight;
				break;
			case 2:
				randType = bottomLeft;
				break;
			case 3:
				randType = bottomRight;
				break;
			}

			//generates, stores, and crafts
			collection[i] = new Triangle(rand() % (DIMENSIONS - 5), rand() % (DIMENSIONS - 5), randType);
			collection[i]->craft();

			++i; //move to next shape
			break;
		default: //error
			std::cout << "Input error.\n\n";
			continue;
		}
	}

	//draws each shape in order onto graph
	std::cout << std::endl;
	for (int i = 0; i < COLLECTION_SIZE; ++i) {
		int x = collection[i]->getX();
		int y = collection[i]->getY();
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				if (graph[y + j][x + k] == '!' || collection[i]->getGraphic(k, j) != ' ') {
					graph[y + j][x + k] = collection[i]->getGraphic(k, j);
				}
			}
		}
	}

	//outputs graph
	for (int i = 0; i < DIMENSIONS; ++i) {
		for (int j = 0; j < DIMENSIONS; ++j) {
			std::cout << graph[i][j];
		}
		std::cout << std::endl;
	}

	//replay section
	std::cout << std::endl << "Go again? (y for yes, n for no) ";
	char exitChoice;
	std::cin >> exitChoice;
	switch (exitChoice) {
	case 'y':
		std::cout << std::endl << std::endl;
		for (int i = 0; i < COLLECTION_SIZE; ++i) {
			delete collection[i];
		}
		++runTime;
		main();
	case 'n':
		std::cout << "Thanks for drawing!\n\n";
		break;
	default:
		std::cout << "Invalid input, thanks for drawing!\n\n";
	}

	delayEnd(); //delays .exe closure
}

//requires user to close program
void delayEnd() {
	std::cout << "It is now safe to close the program.\n";
	while (true) {
		int useless;
	}
}