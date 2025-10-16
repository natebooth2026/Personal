// The Institution's Records (v1)
// A Nate Booth Production
// 9/24/2024, 9/30/2024, 10/1/2024

#ifndef FILE_MANAGAMENT
#define FILE_MANAGEMENT

#include "data.hpp"
#include <vector>
#include <fstream>

std::string save(std::ifstream& in,
	std::vector<student>& sVect,
	std::vector<event>& eVect,
	std::vector<course>& cVect) {
	in.clear();

	std::string result;

	for (size_t i = 0; i < sVect.size(); ++i) {
		result += '\"';
		result += sVect[i].getName();
		result += "\" ";
		result += std::to_string(sVect[i].getHours());
		result += ' ';
		result += std::to_string(sVect[i].getGPA());
		result += " \"";
		result += sVect[i].getPerformance();
		result += "\" ";
		result += std::to_string(sVect[i].getID());
		result += '\n';
	}

	result += "\n";

	for (size_t i = 0; i < eVect.size(); ++i) {
		result += "\"";
		result += eVect[i].getDate();
		result += "\" `";
		result += eVect[i].getName();
		result += "` ";
		result += std::to_string(eVect[i].getID());
		result += '\n';
	}

	result += '\n\n';

	for (size_t i = 0; i < cVect.size(); ++i) {
		result += "\"";
		result += cVect[i].getSubject();
		result += "\" ";
		result += std::to_string(cVect[i].getID());
		result += " \"";
		result += cVect[i].getName();
		result += "\" ";
		result += std::to_string(cVect[i].getCredit());
		result += " \"";
		result += cVect[i].getInstructor();
		result += "\"";
		if (i != cVect.size() - 1) result += "\n";
	}

	return result;
}

void load(std::ifstream& in,
	std::vector<student>& sVect,
	std::vector<event>& eVect,
	std::vector<course>& cVect) {
	if (!in) {
		std::cerr << std::endl << "Load error. To prevent data loss, DO NOT QUIT NORMALLY." << std::endl << "Close the program immediately." << std::endl;
		return;
	}

	bool students = true;
	bool events = true;
	bool courses = true;
	int done = 0;
	while (!in.eof()) {
		std::string line = "";
		getline(in, line);

		if (line == "") {
			if (done == 0) { students = false; ++done; }
			else if (done == 1) { events = false; ++done; }
			else if (done == 2) { break; }
			continue;
		}

		if (students) {
			line.erase(line.begin());

			std::string name;
			int hours;
			double GPA;
			int ID;
			std::string perf;

			name = line.substr(0, line.find("\""));
			line.erase(line.begin(), line.begin() + (line.find("\"") + 2));

			hours = stoi(line.substr(0, line.find(" ")));
			line.erase(line.begin(), line.begin() + (line.find(" ") + 1));

			GPA = std::stod(line.substr(0, line.find(" ")));
			line.erase(line.begin(), line.begin() + (line.find(" ") + 1));

			line.erase(line.begin());
			perf = line.substr(0, line.find("\""));
			line.erase(line.begin(), line.begin() + (line.find("\"") + 2));

			ID = stoi(line);
			line = "";

			sVect.push_back(student(name, hours, GPA, ID));
			sVect.back().change(3, perf);
			continue;
		}
		else if (events) {
			line.erase(line.begin());

			std::string date;
			std::string name;
			int ID;

			date = line.substr(0, line.find("\""));
			line.erase(line.begin(), line.begin() + line.find("\"") + 2);

			line.erase(line.begin());
			name = line.substr(0, line.find("`"));
			line.erase(line.begin(), line.begin() + line.find("`") + 2);

			ID = stoi(line);
			line = "";

			eVect.push_back(event(date, name, ID));
			continue;
		}
		else if (courses) {
			line.erase(line.begin());

			std::string sub;
			int ID;
			std::string name;
			double cred;
			std::string instr;

			sub = line.substr(0, line.find("\""));
			line.erase(line.begin(), line.begin() + line.find("\"") + 2);

			ID = stoi(line.substr(0, line.find(" ")));
			line.erase(line.begin(), line.begin() + line.find(" ") + 1);

			line.erase(line.begin());
			name = line.substr(0, line.find("\""));
			line.erase(line.begin(), line.begin() + line.find("\"") + 2);

			cred = std::stod(line.substr(0, line.find(" ")));
			line.erase(line.begin(), line.begin() + line.find(" ") + 1);

			line.erase(line.begin());
			instr = line.substr(0, line.find("\""));
			line = "";

			cVect.push_back(course(sub, ID, name, cred, instr));
			continue;
		}
		else {
			std::cerr << std::endl << "Load error. To prevent data loss, DO NOT QUIT NORMALLY." << std::endl << "Close the program immediately." << std::endl;
		}
	}
}

#endif