// Constant Divide
// A Nate Booth Production
// 12/6/23

//OUTRO SEQUENCE INSPIRED BY ISAAC SYNDER

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

using std::cout; using std::cin; using std::endl;
using std::string;

//intro-related
bool run = false;
void intro(bool&);

//named exceptions
class dividingZero {};
class divisionByZero {};
class zeroTimes {};
class notEven {};
class notInt {};
class rethrow {};

//computes all division and prints; using recursion to keep dividing
void divide(double, double, int);

int main() {
	//program intro
	intro(run); 

	//solution intro
	cout << "Enter three numbers (last one must be even): " << endl;

	//holds all parts needed
	double dividend;
	double divisor;
	double times;

	//outer ends with a throw rethrow()
	try {
		//inner ends with specified throw
		try {
			cin >> dividend >> divisor >> times;

			if (divisor == 0) throw divisionByZero();
			if (dividend == 0) throw dividingZero();
			if (times == 0) throw zeroTimes();
			//static casting is used to round down times
			if (times / static_cast<int>(times) != 1) throw notInt();
			if (static_cast<int>(times) % 2 != 0) throw notEven();

			cout << endl;
		}

		//non-std exception handlers
		catch (dividingZero) {
			cout << endl << "The answer is zero. Plain and simple you simpilton." << endl;
			throw rethrow();
		}
		catch (divisionByZero) {
			cout << endl << "You can't divide by zero moron." << endl;
			throw rethrow();
		}
		catch (zeroTimes) {
			cout << endl << "Soooooooo, you wanted to divide stuff "
				<< "how many times? " << endl
				<< "None? That's a shame. " << endl
				<< "Get out of my face idiot." << endl;
			throw rethrow();
		}
		catch (notEven) {
			cout << endl << "Hey dimwit, " << times << " is not even even! Try again loser. "
				<< endl;
			throw rethrow();
		}
		catch (notInt) {
			cout << endl << "Hey flatbrain, how the hell do you divide "
				<< times << " times?!" << endl;
			throw rethrow();
		}
		
		//non retry ending; std exception error
		catch (...) {
			cout << endl << "Oops! An error occurred! Error code: #69ewJACKA$$"
				<< endl << "(this time the insult goes to the developer)" << endl;
			exit(EXIT_FAILURE);
		}
	}

	//retry sequence
	catch (rethrow) {
		cout << endl << "Try again? (y or n) ";

		//collects user response
		char choice;
		cin >> choice;

		if (choice == 'y') { //yes
			cout << endl << endl;
			main(); //recurses main
		}
		else if (choice == 'n') { //no
			cout << "wimp" << endl << endl;
			exit(EXIT_FAILURE);
		}
		else { //invalid
			cout << endl
				<< "BRO COULDN'T EVEN CHOOSE BETWEEN y OR n, GET YOUR BRAIN CHECKED!!"
				<< endl << endl;
			exit(EXIT_FAILURE);
		}
	}

	//non retry ending
	catch (...) {
		cout << endl << "Oops! An error occurred! Error code: #69ewJACKA$$"
			<< endl << "(this time the insult goes to the developer)" << endl;
		exit(EXIT_FAILURE);
	}

	//if all succeeds
	divide(dividend, divisor, static_cast<int>(times));
	
	cout << endl << endl;

	//solution outro
	cout << "In the year 2023, the US political climate is a toxic environment," << endl 
		//" in " was added below on 12/12/2023, was grammar mistake
		<< "just having opinions can result in cancellation. We are in this" << endl 
		<< "constant divide in this country. Does this piece show just how" << endl
		<< "divided we are in society? So much so that we are regressing as humans?" << endl
		<< "Take it as you will but this piece just divides numbers :/" << endl;

	//program outro
	exit(EXIT_SUCCESS);
}

//computes divisions
void divide(double n, double d, int times) {
	//so one line is not packed with numbers
	//casted d so it can be used to judge how many numbers end up in a line
	//(people know what they are in for by choosing large number)
	if (times > 0 && times % static_cast<int>(d) == 0) { 
		if (n / d != 0 && times != 1) { //last condition prevents an
										//extra space at the solution outro
			cout << n / d << endl;
			divide(n / d, d, times - 1); //keeps dividing the number by d
		}
		else if (n / d != 0) {
			cout << n / d << " ";
			divide(n / d, d, times - 1);
		}
	}
	else if (times > 0) {
		if (n / d != 0) {
			cout << n / d << " ";
			divide(n / d, d, times - 1);
		}
	}
}

//program intro; run passed by reference to prevent 2nd run through if main()
//is being recursed through
void intro(bool &run) {
	if (!run) {
		cout << "Constant Divide" << endl;
		cout << "A Nate Booth Production" << endl << endl;
		cout << "Outro sequence inspired by Isaac Synder" << endl << endl;
		run = true;
	}
}