#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::string;

struct properResponses {
	int one = 5;
	string two = "3/n";
	double three = 3.141592653589;
	bool four = false;
	char five = '#';
};

struct userResponses {
	properResponses userAnswer;
	bool message = false;
};

namespace Nate {
	void doStuff(bool messengeReceived) {
		if (messengeReceived == true) {
			cout << "You found me!" << endl;
		}
		else {
			cout << "Goodbye." << endl;
		}
	}

	int useless = 69;
}
#endif