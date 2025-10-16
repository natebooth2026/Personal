// Lottery Simulator
// A Nate Booth Production
// 11-13-2023 & 11-20-2023

#include "ticket.hpp"
#include <iostream>

using std::cout;

Ticket::Ticket(int sizeChance) {
	srand(time(nullptr));

	while (size_ < 5) {
		size_ = rand() % sizeChance + 1;
	}

	nums_ = new int[size_];
	multis_ = new int[size_];

	for (int i = 0; i < size_; ++i) {
		nums_[i] = rand() % size_ + 1;
		multis_[i] = rand() % 10 + 1;
		while (nums_[i] == nums_[i - 1]) {
			nums_[i] = rand() % size_ + 1;
		}
		while (multis_[i] == multis_[i - 1]) {
			multis_[i] = rand() % 10 + 1;
		}
	}

	choiceVar_.num__ = nums_[rand() % size_];
	choiceVar_.multiplier__ = multis_[rand() % size_]; 

	won_ = false;
}

Ticket::Ticket(const Ticket& original) {
	size_ = original.size_;

	nums_ = new int[size_];
	multis_ = new int[size_];
	for (int i = 0; i < size_; ++i) {
		nums_[i] = original.nums_[i];
		multis_[i] = original.multis_[i];
	}

	choiceVar_ = original.choiceVar_;
}

bool Ticket::check(int num, int multi) const {
	return (choiceVar_.num__ == num) && (choiceVar_.multiplier__ == multi);
}

void Ticket::winningNums() const {
	cout << choiceVar_.num__ << " " << choiceVar_.multiplier__;
}

void Ticket::winnings(int multi) const {
	int base = 100000;
	cout << "$" << base * multi;
}

Ticket::~Ticket() {
	delete[] nums_;
	delete[] multis_;
}

void million(Ticket t) {
	if (t.winningMulti() == 10 && t.getWon()) {
		cout << "CONGRATS! YOU GOT THE $1 MILLION JACKPOT!!";
	}
}

