//Hide-N-Seek
//A Nate Booth Production
//11-6-2023 to 11-8-2023

//INSPIRED BY MAZE PROJECT (Labs 8 & 9)

#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <cstdlib>

using std::cout;

class Room {
public:
	Room(char y, int x) : y_(y), x_(x), scared_(false) {}

	const char getY() const { return y_; }
	const int getX() const { return x_; }

	void changeY(char y) { y_ = y; }
	void changeX(int x) { x_ = x; }

	void output() const { cout << y_ << x_; }

	friend Room changeRoom(Room, char, int);

	const bool getScared() const { return scared_; }

	void setScared(bool scared) { scared_ = scared; }
private:
	char y_;
	int x_;
	bool scared_;
};

#endif // ROOM_HPP

