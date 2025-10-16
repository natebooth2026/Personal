#ifndef DEF_HPP
#define DEF_HPP

#include <string>

using std::string;

//random cities collected from https://randomcity.net/
//temperature information collected from https://weatherspark.com/

string cities[5] = {"Hallstadt, Germany", "Dublin, Ireland", "Sevilla, Spain", "Phnom Penh, Cambodia", "Muscat, Oman"};
string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

struct TempsByMonth {
	int January[5] = {0, 6, 10, 27, 21};
	int February[5] = {1, 6, 12, 28, 22};
	int March[5] = {5, 7, 15, 30, 25};
	int April[5] = {9, 9, 17, 31, 29};
	int May[5] = {14, 11, 20, 30, 34};
	int June[5] = {17, 14, 25, 29, 34};
	int July[5] = {19, 16, 27, 29, 33};
	int August[5] = {19, 15, 27, 28, 31};
	int September[5] = {14, 14, 24, 28, 31};
	int October[5] = {10, 11, 20, 28, 29};
	int November[5] = {5, 8, 15, 27, 26};
	int December[5] = {1, 6, 12, 27, 23};
};

class City {
public:
	City(int city, int month) : cityNum_(city), monthNum_(month) {}
	void convert(int);
	bool checkAnswer(int, TempsByMonth, int, int);
	int getCityNum() const { return cityNum_; }
	int getMonthNum() const { return monthNum_; }
	int getTemp() const { return temp_; }
private:
	int cityNum_;
	int monthNum_;
	int temp_;
	TempsByMonth temps_;
};

#endif //DEF_HPP
