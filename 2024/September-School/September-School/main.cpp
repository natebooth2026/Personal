// The Institution's Records (v1)
// A Nate Booth Production
// 9/21/2024, 9/24/2024, 9/30/2024, 10/1/2024

// Idea URL: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/ (#13)


#include "fileManagement.hpp"

student addStudent(std::string n = "", double h = 0.0, double g = 0.0, int i = 0) { return student(n, h, g, i); }
event addEvent(std::string d = "", std::string n = "", int id = -1) { return event(d, n, id); }
course addCourse(std::string s = "", int i = 0, std::string n = "", double c = 0.0, std::string t = "") { return course(s, i, n, c, t); }

bool editStudent(std::vector<student>&, int = -1);
bool editEvent(std::vector<event>&, int = -1);
bool editCourse(std::vector<course>&, std::string = "", int = -1);

bool deleteStudent(std::vector<student>&, int = -1);
bool deleteEvent(std::vector<event>&, int = -1);
bool deleteCourse(std::vector<course>&, std::string = "", int = -1);

bool ran = false;
std::string buffer; //to avoid bug
const std::string SAVE_FILE = "databaseSave.txt";

int main() {
	if (!ran) {
		std::cout << "The Institution's Records (v1)"
			<< std::endl << "A Nate Booth Production"
			<< std::endl << std::endl;
		ran = true;
	}

	std::vector<student> studentData;
	std::vector<event> eventData;
	std::vector<course> courseData;

	std::ifstream in(SAVE_FILE);
	load(in, studentData, eventData, courseData);

	bool FILES_FUNCTIONING = false;
	std::ofstream out(SAVE_FILE);
	if (!out) {
		std::cerr << "SAVE FILE ERROR" << std::endl;
	}
	else if (out) {
		FILES_FUNCTIONING = true;
	}

	char choice = ' ';
	while (choice != 'q') {
		std::cout << "Select action (p to print, a to add, e to edit, d to delete, q to save & quit): ";
		std::cin >> choice;

		std::string name; //for all (adding)
		std::string date; //for event (adding)
		std::string subject; //for course (adding)
		std::string instr; //for course (adding)
		std::string sub; //for course (editing & deleting)
		bool success = false; //for adding

		switch (choice) {
	//printing
		case 'p':
			if (studentData.size() == 0) {
				std::cout << std::endl << "No student data." << std::endl;
			}
			else {
				std::cout << std::endl << "Student Data:" << std::endl;

				for (size_t i = 0; i < studentData.size(); ++i) {
					studentData[i].operator<<(std::cout);
					std::cout << std::endl;
				}

				std::cout << std::endl;
			}

			if (eventData.size() == 0) {
				std::cout << std::endl << "No event data." << std::endl;
			}
			else {
				std::cout << std::endl << "Event Data:" << std::endl;

				for (size_t i = 0; i < eventData.size(); ++i) {
					eventData[i].operator<<(std::cout);
					std::cout << std::endl;
				}

				std::cout << std::endl;
			}

			if (courseData.size() == 0) {
				std::cout << std::endl << "No course data." << std::endl << std::endl;
			}
			else {
				std::cout << std::endl << "Course Data:" << std::endl;

				for (size_t i = 0; i < courseData.size(); ++i) {
					courseData[i].operator<<(std::cout);
					std::cout << std::endl;
				}

				std::cout << std::endl;
			}
			break;
	//adding
		case 'a':
			std::cout << "What do you want to add? (s for student, e for event, c for course): ";
			char subChoice;
			std::cin >> subChoice;

			switch (subChoice) {
			case 's':
				std::cout << "Provide student name: ";
				getline(std::cin, buffer);
				getline(std::cin, name);

				std::cout << "Provide absent hours: ";
				double hours;
				std::cin >> hours;

				std::cout << "Provide GPA: ";
				double GPA;
				std::cin >> GPA;

				std::cout << "Provide ID (be careful of conflicting IDs): ";
				int ID;
				std::cin >> ID;

				studentData.push_back(addStudent(name, hours, GPA, ID));
				success = true;
				break;
			case 'e':
				std::cout << "Provide event date: ";
				getline(std::cin, buffer);
				getline(std::cin, date);

				std::cout << "Provide event name: ";
				getline(std::cin, name);

				std::cout << "Provide event ID (be careful of conflicting IDs): ";
				int eID;
				std::cin >> eID;

				eventData.push_back(addEvent(date, name, eID));
				success = true;
				break;
			case 'c':
				std::cout << "Provide course subject code: ";
				getline(std::cin, buffer);
				getline(std::cin, subject);

				std::cout << "Provide course ID (be careful of conflicting IDs): ";
				int courseID;
				std::cin >> courseID;

				std::cout << "Provide course name: ";
				getline(std::cin, buffer);
				getline(std::cin, name);

				std::cout << "Provide course awarding credits: ";
				double credits;
				std::cin >> credits;

				std::cout << "Provide instructor name: ";
				getline(std::cin, buffer);
				getline(std::cin, instr);

				courseData.push_back(addCourse(subject, courseID, name, credits, instr));
				success = true;
				break;
			default:
				std::cout << std::endl << "Invalid choice." << std::endl << std::endl;
				break;
			}
			if (success) std::cout << "Successful add!" << std::endl << std::endl;
			else std::cout << "Failed to add." << std::endl << std::endl;
			break;
	//editing
		case 'e':
			std::cout << "Which would you like to edit? (s for student, e for event, c for course): ";
			char eSubChoice;
			std::cin >> eSubChoice;

			switch (eSubChoice) {
			case 's':
				std::cout << "Provide student ID: ";
				int id;
				std::cin >> id;

				if (editStudent(studentData, id)) {
					std::cout << std::endl << "Edit complete!" << std::endl << std::endl;
				}
				else {
					std::cout << "Edit failed." << std::endl << std::endl;
				}
				break;
			case 'e':
				std::cout << "Provide event ID: ";
				int eID;
				std::cin >> eID;

				if (editEvent(eventData, eID)) {
					std::cout << std::endl << "Edit complete!" << std::endl << std::endl;
				}
				else {
					std::cout << "Edit failed." << std::endl << std::endl;
				}
				break;
			case 'c':
				std::cout << "Provide course subject: ";
				getline(std::cin, buffer);
				getline(std::cin, sub);

				std::cout << "Provide course ID: ";
				int cID;
				std::cin >> cID;

				if (editCourse(courseData, sub, cID)) {
					std::cout << std::endl << "Edit complete!" << std::endl << std::endl;
				} 
				else {
					std::cout << "Edit failed." << std::endl << std::endl;
				}
				break;
			default:
				std::cout << std::endl << "Invalid choice." << std::endl << std::endl;
				break;
			}
			break;
	//deleting
		case 'd':
			std::cout << "What do you want to delete? (s for student, e for event, c for course): ";
			char dSubChoice;
			std::cin >> dSubChoice;

			switch (dSubChoice) {
			case 's':
				std::cout << "Provide student ID: ";
				int dSID;
				std::cin >> dSID;

				if (deleteStudent(studentData, dSID)) {
					std::cout << "Deletion complete!" << std::endl;
				}
				else {
					std::cout << "Deletion failed." << std::endl;
				}
				break;
			case 'e':
				std::cout << "Provide event ID: ";
				int dEID;
				std::cin >> dEID;

				if (deleteEvent(eventData, dEID)) {
					std::cout << "Deletion complete!" << std::endl;
				}
				else {
					std::cout << "Deletion failed." << std::endl;
				}
				break;
			case 'c':
				std::cout << "Provide course subject: ";
				std::cin >> sub;

				std::cout << "Provide course ID: ";
				int dCID;
				std::cin >> dCID;

				if (deleteCourse(courseData, sub, dCID)) {
					std::cout << "Deletion complete!" << std::endl;
				}
				else {
					std::cout << "Deletion failed." << std::endl;
				}
				break;
			default:
				std::cout << std::endl << "Invalid choice." << std::endl << std::endl;
				break;
			}
			break;
		case 'q':
			std::cout << std::endl << "To prevent data corruption, ensure there are no (\") characters"
				<< std::endl << "in any text field (other than event name) and that"
				<< std::endl << "there are no (`) characters in the event name field."
				<< std::endl << "Are you sure you want to quit and save? (y for yes, n for no) ";

			char qChoice;
			std::cin >> qChoice;

			if (qChoice == 'y' || qChoice == 'Y') {
				if (FILES_FUNCTIONING) out << save(in, studentData, eventData, courseData);
				break;
			}
			else if (qChoice == 'n' || qChoice == 'N') {
				std::cout << std::endl << "Save cancelled." << std::endl;
				choice = ' ';
				break;
			}
			else {
				std::cout << std::endl << "Invalid response." << std::endl << std::endl;
				choice = ' ';
				break;
			}
		default:
			std::cout << std::endl << "Invalid choice." << std::endl << std::endl;
		}
	}

	return 0;
}

bool editStudent(std::vector<student> &vect, int id) {
	bool found = false;
	for (size_t i = 0; i < vect.size(); ++i) {
		if (vect[i].getID() == id) {
			std::cout << "Found student!" << std::endl << std::endl;
			found = true;

			char choice = ' ';
			while (choice == ' ') {
				std::cout << "What do you want to edit?" << std::endl;
				std::cout << "(n for name, h for absence, g for GPA, p for performance marker, i for ID) ";
				std::cin >> choice;

				std::string name;
				double hours;
				double GPA;
				std::string perf;
				int newID;

				switch (choice) {
				case 'n':
					std::cout << "Enter a new name: ";
					getline(std::cin, buffer);
					getline(std::cin, name);
					vect[i].change(0, name);
					std::cout << std::endl << "Change complete!";
					break;
				case 'h':
					std::cout << "Enter a new amount of absent hours: ";
					std::cin >> hours;
					vect[i].change(1, "", hours);
					std::cout << std::endl << "Change complete!";
					break;
				case 'g':
					std::cout << "Enter a new GPA: ";
					std::cin >> GPA;
					vect[i].change(2, "", GPA);
					std::cout << std::endl << "Change complete!";
					break;
				case 'p':
					std::cout << "Enter a new performance marker: ";
					getline(std::cin, buffer);
					getline(std::cin, perf);
					vect[i].change(3, perf);
					std::cout << std::endl << "Change complete!";
					break;
				case 'i':
					std::cout << "Enter a new ID (be careful of conflicting IDs): ";
					std::cin >> newID;
					vect[i].change(4, "", 0.0, newID);
					std::cout << std::endl << "Change complete!";
					break;
				default:
					choice = ' ';
					continue;
				}
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool editEvent(std::vector<event>& vect, int id) {
	bool found = false;
	for (size_t i = 0; i < vect.size(); ++i) {
		if (vect[i].getID() == id) {
			std::cout << "Found event!" << std::endl << std::endl;
			found = true;

			char choice = ' ';
			while (choice == ' ') {
				std::cout << "What do you want to edit?" << std::endl;
				std::cout << "(d for date, n for name, i for ID) ";
				std::cin >> choice;

				std::string date;
				std::string name;
				int newID;

				switch (choice) {
				case 'd':
					std::cout << "Enter a new date: ";
					getline(std::cin, buffer);
					getline(std::cin, date);
					vect[i].change(0, date);
					std::cout << std::endl << "Change complete!";
					break;
				case 'n':
					std::cout << "Enter a new name: ";
					getline(std::cin, buffer);
					getline(std::cin, name);
					vect[i].change(1, name);
					std::cout << std::endl << "Change complete!";
					break;
				case 'i':
					std::cout << "Enter a new event ID (be careful of conflicting IDs): ";
					std::cin >> newID;
					vect[i].change(2, "", newID);
					std::cout << std::endl << "Change complete!";
					break;
				default:
					choice = ' ';
					continue;
				}
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
		return false;
	}
	else {
		return true;
	}
}
bool editCourse(std::vector<course>& vect, std::string sub, int id) {
	bool found = false;
	for (size_t i = 0; i < vect.size(); ++i) {
		if (vect[i].getSubject() == sub && vect[i].getID() == id) {
			std::cout << "Found course!" << std::endl << std::endl;
			found = true;

			char choice = ' ';
			while (choice == ' ') {
				std::cout << "What do you want to edit?" << std::endl;
				std::cout << "(s for subject, i for ID, n for name, c for rewarding credits, t for teacher) ";
				std::cin >> choice;

				std::string newSub;
				int newID;
				std::string name;
				double cred;
				std::string instr;

				switch (choice) {
				case 's':
					std::cout << "Enter a new subject code: ";
					getline(std::cin, buffer);
					getline(std::cin, newSub);
					vect[i].change(0, newSub);
					std::cout << std::endl << "Change complete!";
					break;
				case 'i':
					std::cout << "Enter a new course ID (be careful of conflicting IDs): ";
					std::cin >> newID;
					vect[i].change(1, "", newID);
					std::cout << std::endl << "Change complete!";
					break;
				case 'n':
					std::cout << "Enter a new name: ";
					getline(std::cin, buffer);
					getline(std::cin, name);
					vect[i].change(2, name);
					std::cout << std::endl << "Change complete!";
					break;
				case 'c':
					std::cout << "Enter the rewarding credits: ";
					std::cin >> cred;
					vect[i].change(3, "", cred);
					std::cout << std::endl << "Change complete!";
					break;
				case 't':
					std::cout << "Enter a new instructor: ";
					getline(std::cin, buffer);
					getline(std::cin, instr);
					vect[i].change(4, instr);
					std::cout << std::endl << "Change complete!";
					break;
				default:
					choice = ' ';
					continue;
				}
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool deleteStudent(std::vector<student>& sVect, int id) {
	bool found = false;
	for (size_t i = 0; i < sVect.size(); ++i) {
		if (sVect[i].getID() == id) {
			std::cout << "Found student!" << std::endl << std::endl;
			found = true;

			sVect[i].operator<<(std::cout);
			std::cout << std::endl << "Are you sure you want to delete student " << id << "? (y for yes, n for no) ";
			char choice;
			std::cin >> choice;
			std::cout << std::endl;

			if (choice == 'y' || choice == 'Y') {
				sVect.erase(sVect.begin() + i);
				std::cout << "Student deleted." << std::endl;
				break;
			}
			else if (choice == 'n' || choice == 'N') {
				std::cout << "Deletion cancelled." << std::endl;
				found = false;
				break;
			}
			else {
				std::cout << "Invalid response. Deletion not preformed." << std::endl;
				found = false;
				break;
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
	}
	return found;
}

bool deleteEvent(std::vector<event>& eVect, int id) {
	bool found = false;
	for (size_t i = 0; i < eVect.size(); ++i) {
		if (eVect[i].getID() == id) {
			std::cout << "Found event!" << std::endl << std::endl;
			found = true;

			eVect[i].operator<<(std::cout);
			std::cout << std::endl << "Are you sure you want to delete event " << id << "? (y for yes, n for no) ";
			char choice;
			std::cin >> choice;
			std::cout << std::endl;

			if (choice == 'y' || choice == 'Y') {
				eVect.erase(eVect.begin() + i);
				std::cout << "Event deleted." << std::endl;
				break;
			}
			else if (choice == 'n' || choice == 'N') {
				std::cout << "Deletion cancelled." << std::endl;
				found = false;
				break;
			}
			else {
				std::cout << "Invalid response. Deletion not preformed." << std::endl;
				found = false;
				break;
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
	}
	return found;
}

bool deleteCourse(std::vector<course>& cVect, std::string sub, int id) {
	bool found = false;
	for (size_t i = 0; i < cVect.size(); ++i) {
		if (cVect[i].getSubject() == sub && cVect[i].getID() == id) {
			std::cout << "Found course!" << std::endl << std::endl;
			found = true;

			cVect[i].operator<<(std::cout);
			std::cout << std::endl << "Are you sure you want to delete course " << sub << " " << id << "? (y for yes, n for no) ";
			char choice;
			std::cin >> choice;
			std::cout << std::endl;

			if (choice == 'y' || choice == 'Y') {
				cVect.erase(cVect.begin() + i);
				std::cout << "Course deleted." << std::endl;
				break;
			}
			else if (choice == 'n' || choice == 'N') {
				std::cout << "Deletion cancelled." << std::endl;
				found = false;
				break;
			}
			else {
				std::cout << "Invalid response. Deletion not preformed." << std::endl;
				found = false;
				break;
			}
		}
	}
	if (!found) {
		std::cout << "Item not found." << std::endl;
	}
	return found;
}