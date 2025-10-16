// The Institution's Records (v1)
// A Nate Booth Production
// 9/21/2024, 9/24/2024, 9/30/2024

// Idea URL: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/ (#13)

#ifndef DATA
#define DATA

#include <iostream>
#include <string>

//
/* STUDENT */
//
std::string markers[3] = { "FAILING", "CAUTION", "GOOD" }; //for student performance

class student {
public:
	student() : name(""), missedHours(0.0), gpa(0.0), performance(""), id(-1) {}
	student(std::string n, int i) : name(n), missedHours(0.0), gpa(0.0), performance(""), id(i) {}
	student(std::string n, double h, int i) : name(n), missedHours(h), gpa(0.0), performance(""), id(i) {}
	student(std::string n, double h, double g, int i) : name(n), missedHours(h), gpa(g), performance(""), id(i) { calculatePerformance(); }

	void change(int changeID, std::string str = "", double num = 0.0, int numID = 0) {
		switch (changeID) {
		case 0:
			name = str;
			break;
		case 1:
			missedHours = num;
			break;
		case 2:
			gpa = num;
			break;
		case 3:
			performance = str;
			break;
		case 4:
			id = numID;
			break;
		default:
			std::cout << "student.change() Error: Invalid ID Provided" << std::endl;
		}
	}

	void calculatePerformance() {
		if (gpa < 2.0) performance = markers[0];
		if ((missedHours >= 100 && gpa > 2.0) || (gpa < 3.0 && gpa >= 2.0)) performance = markers[1];
		if (missedHours < 100 && gpa >= 3.0) performance = markers[2];
	}

	std::ostream& operator<<(std::ostream& out) {
		out << name << " | "
			<< missedHours << (missedHours == 1 ? " hour missed | GPA: " : " hours missed | GPA: ")
			<< gpa << " | Performance: "
			<< performance << " | ID: " << id;
		return out;
	}

	std::string getName() { return name; }
	double getHours() { return missedHours; }
	double getGPA() { return gpa; }
	std::string getPerformance() { return performance; }
	int getID() { return id; }
private:
	std::string name;
	double missedHours;
	double gpa;
	std::string performance;
	int id;
};

//
/* EVENTS */
//

class event {
public:
	event() : date(""), name(""), id(-1) {}
	event(std::string d, int i = -1) : date(d), name(""), id(i) {}
	event(std::string d, std::string n, int i = -1) : date(d), name(n), id(i) {}

	void change(int changeID, std::string str = "", int newID = -1) {
		switch (changeID) {
		case 0:
			date = str;
			break;
		case 1:
			name = str;
			break;
		case 2:
			id = newID;
			break;
		default:
			std::cout << "event.change() Error: Invalid ID Provided" << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& out) {
		out << date << " | " << name;
		return out;
	}

	std::string getDate() { return date; }
	std::string getName() { return name; }
	int getID() { return id; }
private:
	std::string date;
	std::string name;
	int id;
};

//
/* COURSES */
//
class course {
public:
	course() : subject(""), id(-1), name(""), credit(0) {}
	course(std::string s) : subject(s), id(-1), name(""), credit(0) {}
	course(std::string s, int i) : subject(s), id(i), name(""), credit(0) {}
	course(std::string s, int i, std::string n, double c, std::string instr = "TBD") : subject(s), id(i), name(n), credit(c), instructor(instr) {}

	void change(int changeID, std::string str = "", double num = -1.0) {
		switch (changeID) {
		case 0:
			subject = str;
			break;
		case 1:
			id = num;
			break;
		case 2:
			name = str;
			break;
		case 3:
			credit = num;
			break;
		case 4:
			instructor = str;
			break;
		default:
			std::cout << "course.change() Error: Invalid ID Provided" << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& out) {
		out << subject << " " << id << " | "
			<< name << " | "
			<< credit << (credit == 1.0 ? " credit" : " credits") << " | "
			<< instructor;
		return out;
	}

	std::string getSubject() { return subject; }
	int getID() { return id; }
	std::string getName() { return name; }
	double getCredit() { return credit; }
	std::string getInstructor() { return instructor; }
private:
	std::string subject;
	int id;
	std::string name;
	double credit;
	std::string instructor;
};

#endif