// Lottery Simulator
// A Nate Booth Production
// 11-13-2023 & 11-20-2023

#ifndef TICKET_HPP
#define TICKET_HPP

#include <iostream>

class Ticket {
public:
	Ticket(int);
	Ticket(const Ticket&);
	~Ticket();
	bool check(int, int) const;
	void winnings(int) const;
	int size() const { return size_; }
	void winningNums() const;
	int winningMulti() const { return choiceVar_.multiplier__; }
	void setWon() { won_ = true; }
	bool getWon() const { return won_; }
private:
	int size_;
	int* nums_;
	int* multis_;
	struct choice_ {
		int num__;
		int multiplier__;
	};
	choice_ choiceVar_;
	bool won_;
};

void million(Ticket);

#endif //TICKET_HPP
