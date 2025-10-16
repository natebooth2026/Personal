# ifndef CARDS_HPP
# define CARDS_HPP

#include <string>
#include <vector>

const int NUM_CARDS = 52;

//deck of cards structure
class deck {
public: 
	deck() {}

	std::string operator[](int i) { if(i >= 0 && i < 52) return cards[i]; } //returns a card from deck (comparisons only)

	//determines card value by name of card
	int cardValue(std::string current) {
		for (int i = 0; i < NUM_CARDS; ++i) {
			if (cards[i] == current && i < 40) { //before Jacks
				return i / 4 + 1;
			}
			else if (cards[i] == current) { //Jacks and after
				return 10;
			}
		}

		return -1; //error -> no match
	}

	//retrieves a random card
	std::string grabCard() {
		int randIndex = rand() % NUM_CARDS; //random index

		//analyzes taken cards and places in strings
		std::string takenReport = "";
		for (int i = 0; i < taken.size(); ++i) {
			takenReport += taken[i];
		}

		//if randIndex == an element in taken
		while (takenReport.find(randIndex) != std::string::npos) {
			randIndex = rand() % NUM_CARDS; //new random index
		}

		taken.push_back(randIndex); //adds new card's index into taken
		return cards[randIndex]; //returns card name
	}
private:
	std::string cards[NUM_CARDS] = { "A-S", "A-C", "A-H", "A-D",
							"2-S", "2-C", "2-H", "2-D",
							"3-S", "3-C", "3-H", "3-D",
							"4-S", "4-C", "4-H", "4-D",
							"5-S", "5-C", "5-H", "5-D",
							"6-S", "6-C", "6-H", "6-D",
							"7-S", "7-C", "7-H", "7-D",
							"8-S", "8-C", "8-H", "8-D",
							"9-S", "9-C", "9-H", "9-D",
							"10-S", "10-C", "10-H", "10-D",
							"J-S", "J-C", "J-H", "J-D",
							"Q-S", "Q-C", "Q-H", "Q-D",
							"K-S", "K-C", "K-H", "K-D" }; //format -> FACE VALUE-SUITE

	std::vector<int> taken; //holds indicies of cards already drawn
};

//player & dealer data structure
class contestant {
public:
	contestant() : value(0), secondValue(0), hasAce(false), hasAce2(false), canOne(true), canOne2(true), splitIter(0) {}

	//MUTATORS
	void addCard(std::string c) { cards.push_back(c); }
	void eraseCard() { cards.erase(cards.end() - 1); }
	void addToSecond(std::string c) { secondHand.push_back(c); }
	void addToValue(int n) { value += n; }
	void addToSecVal(int n) { secondValue += n; }
	void setAce(bool b) { hasAce = b; }
	void setAce2(bool b) { hasAce2 = b; }
	void setAceLimit() { canOne = false; }
	void setAce2Limit() { canOne = false; }
	void setSplit(int i) { splitIter = i; }
	void setV(int i) { value = i; }
	void setSV(int i) { secondValue = i; }
	void operator++() { ++splitIter; }
	void operator++(int) { ++splitIter; }

	//ACCESSORS
	std::string getCard() { return cards.back(); }
	std::string getSecond() { return secondHand.back(); }
	std::string operator[](size_t i) { return cards[i]; }
	std::string operator()(size_t i) { return secondHand[i]; } //same functionality as operator[]
	size_t getAmount() { return cards.size(); }
	size_t getSecondAmount() { return secondHand.size(); }
	int getV() { return value; }
	int getSV() { return secondValue; }
	bool getAce() { return hasAce; }
	bool getAce2() { return hasAce2; }
	bool getAceRepeat() { return canOne; }
	bool getAce2Repeat() { return canOne2; }
	int getSplit() { return splitIter; }


	//computes if split is possible
	bool checkSplit(deck &d) {
		if (d.cardValue(cards[0]) == d.cardValue(cards[1]) && getAmount() == 2) return true; //equal card value and 2 cards
		return false;
	}
private:
	std::vector<std::string> cards; //holds cards in (first) hand
	std::vector<std::string> secondHand; //holds cards in second hand (split)
	int value; //holds card value of cards
	int secondValue; //holds card value of secondHand
	bool hasAce; //indicates if an ace was detected in cards
	bool hasAce2; //indicates if an ace was detected in secondHand
	bool canOne; //indicates if an ace of value 11 can exist in cards such that the value can be moved down to 1 if needed
	bool canOne2; //indicates if an ace of value 11 can exist in secondHand such that the value can be moved to 1 if needed
	int splitIter; //holds number of iteration in the split sequence
				   //odd == first hand
				   //even == second hand
				   //0 == ignore, no split
};
# endif