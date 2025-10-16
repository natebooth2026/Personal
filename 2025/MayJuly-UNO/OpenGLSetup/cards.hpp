// UNO: Nate's Version (PRE-ALPHA)
// A Nate Booth Production
// May 24th, 2025-July 30th, 2025
// BUG PATCH: August 1st, 2025

#ifndef CARDS_HPP
#define CARDS_HPP

#include <vector>
#include <ctime>

/// CLASSES
enum color { r, y, g, b, wild, noC };
enum type { num, p2, rev, s, w, p4, noT };

class card {
public:
	card() : c(noC), t(noT), n(-1), wX(-0.9f), wY(-0.8f), wW(0.15f), wH(0.225f), visible(true) {}
	card(color x, type y, int z = -1) : c(x), t(y), n(z), wX(-0.9f), wY(-0.8f), wW(0.15f), wH(0.225f), visible(true) {
		if ((x != wild && (y == w || y == p4)) || (x == wild && (y != w && y != p4))) {
			/* THE FOLLOWING IS REMOVED FOR DEBUGGING:
			c = noC;
			t = noT;
			n = -1;
			*/
		}
	}

	color getColor() const { return c; }
	type getType() const { return t; }
	int getNum() const { return n; }
	float getX() const { return wX; }
	float getY() const { return wY; }
	float getW() const { return wW; }
	float getH() const { return wH; }

	void setX(float x) { wX = x; }
	void setY(float y) { wY = y; }
	void setW(float w) { wW = w; }
	void setH(float h) { wH = h; }

	bool operator==(card x) {
		return (c == x.getColor()) && (t == x.getType()) && (n == x.getNum());
	}
	bool operator!=(card x) {
		return (c != x.getColor()) || (t != x.getType()) || (n != x.getNum());
	}

	void wildChangeColor(color x) { c = x; }

	bool visible;
private:
	color c; //contains color
	type t; //contains type
	int n; //contains number
	float wX, wY, wW, wH; //contains position and dimensions
};

class deck; //forwarded for references in hand

class hand {
public:
	hand(int i) : playerID(i), UNO(false) {}

	void sortHand();

	bool isMatch(const card&, const deck&);
	card* findMatch(deck);

	void remove(const card& c) {
		for (size_t i = 0; i < cards.size(); ++i) {
			if (cards[i] == c) {
				cards.erase(cards.begin() + i);
				break;
			}
		}
	}

	void add(const card& c) { cards.push_back(c); sortHand(); }

	bool play(const card&, deck&);

	int getSize() const { return cards.size(); }
	int getID() const { return playerID; }
	bool getUNO() const { return UNO; }
	bool isEmpty() { return cards.empty(); }
	card& operator[](size_t i) { if (i < cards.size() && i >= 0) return cards[i]; }
	card operator[](size_t i) const { if (i < cards.size() && i >= 0) return cards[i]; }

	void toggleUNO() { if (UNO) UNO = false; else UNO = true; }

	bool isCPU() const { return playerID != 0; }
private:
	int playerID;
	std::vector<card> cards;
	bool UNO;
};

class deck {
public:
	void shuffle() {
		srand(time(nullptr));
		std::vector<card> shuffled;
		while (!currentDeck.empty()) {
			int index = rand() % currentDeck.size();
			shuffled.push_back(currentDeck[index]);
			currentDeck.erase(currentDeck.begin() + index);
		}
		currentDeck = shuffled;
	}

	deck(bool shuf = true) {
		//wilds
		for (int i = 0; i < 4; ++i) {
			currentDeck.push_back(card(wild, w));
		}
		for (int i = 0; i < 4; ++i) {
			currentDeck.push_back(card(wild, p4));
		}

		//reds
		currentDeck.push_back(card(r, num, 0));
		for (int i = 1; i < 10; ++i) {
			for (int j = 0; j < 2; ++j) {
				currentDeck.push_back(card(r, num, i));
			}
		}
		for (int i = 0; i < 2; ++i) {
			currentDeck.push_back(card(r, p2));
			currentDeck.push_back(card(r, rev));
			currentDeck.push_back(card(r, s));
		}

		//yellows
		currentDeck.push_back(card(y, num, 0));
		for (int i = 1; i < 10; ++i) {
			for (int j = 0; j < 2; ++j) {
				currentDeck.push_back(card(y, num, i));
			}
		}
		for (int i = 0; i < 2; ++i) {
			currentDeck.push_back(card(y, p2));
			currentDeck.push_back(card(y, rev));
			currentDeck.push_back(card(y, s));
		}

		//greens
		currentDeck.push_back(card(g, num, 0));
		for (int i = 1; i < 10; ++i) {
			for (int j = 0; j < 2; ++j) {
				currentDeck.push_back(card(g, num, i));
			}
		}
		for (int i = 0; i < 2; ++i) {
			currentDeck.push_back(card(g, p2));
			currentDeck.push_back(card(g, rev));
			currentDeck.push_back(card(g, s));
		}

		//blues
		currentDeck.push_back(card(b, num, 0));
		for (int i = 1; i < 10; ++i) {
			for (int j = 0; j < 2; ++j) {
				currentDeck.push_back(card(b, num, i));
			}
		}
		for (int i = 0; i < 2; ++i) {
			currentDeck.push_back(card(b, p2));
			currentDeck.push_back(card(b, rev));
			currentDeck.push_back(card(b, s));
		}

		if (shuf) shuffle();
	}

	color getCurrentColor() const { return currentCard.getColor(); }
	type getCurrentType() const { return currentCard.getType(); }
	int getCurrentNum() const { return currentCard.getNum(); }
	card getCurrent() const { return currentCard; }
	card* getCurrentPtr() { return &currentCard; }
	void setCurrentX(float x) { currentCard.setX(x); }
	void setCurrentY(float y) { currentCard.setY(y); }
	void setCurrentW(float w) { currentCard.setW(w); }
	void setCurrentH(float h) { currentCard.setH(h); }

	card draw() {
		if (!currentDeck.empty()) {
			card result = currentDeck.front();
			currentDeck.erase(currentDeck.begin());
			if (currentDeck.empty()) reShuffle();
			return result;
		}

		return card();
	}

	void place(hand& h, const card& c) {
		if (currentCard != card()) discard.push_back(currentCard);
		currentCard = c;
		h.remove(c);
	}

	void placeInit(card debug = card()) { //DEBUG CLAUSES ADDED
		if (currentCard == card()) {
			if (debug == card()) currentCard = draw();
			else currentCard = debug;
		}
	}

	void reShuffle() {
		if (currentDeck.empty()) {
			currentDeck = discard;
			discard.clear();
			shuffle();
		}
	}

	void replaceCurrent(const card& c) {
		if (&currentCard != nullptr) {
			discard.push_back(currentCard);
			currentCard = c;
		}
	}

	size_t getSize(bool d = false) { if (!d) return currentDeck.size(); else return discard.size(); }
	bool isEmpty() { return currentDeck.empty(); }
	card operator[](int i) { if (i < currentDeck.size() && i >= 0) return currentDeck[i]; }
private:
	std::vector<card> currentDeck;
	std::vector<card> discard;
	card currentCard;
};

//sorts the player's hand
void hand::sortHand() {
	//number & type sort
	std::vector<std::vector<card>> sorted;
	for (int i = 0; i < 15; ++i) {
		std::vector<card> temp;
		sorted.push_back(temp);
	}

	for (size_t i = 0; i < cards.size(); ++i) {
		if (cards[i].getType() == num) {
			if (cards[i].getNum() == 0) sorted[0].push_back(cards[i]);
			else if (cards[i].getNum() == 1) sorted[1].push_back(cards[i]);
			else if (cards[i].getNum() == 2) sorted[2].push_back(cards[i]);
			else if (cards[i].getNum() == 3) sorted[3].push_back(cards[i]);
			else if (cards[i].getNum() == 4) sorted[4].push_back(cards[i]);
			else if (cards[i].getNum() == 5) sorted[5].push_back(cards[i]);
			else if (cards[i].getNum() == 6) sorted[6].push_back(cards[i]);
			else if (cards[i].getNum() == 7) sorted[7].push_back(cards[i]);
			else if (cards[i].getNum() == 8) sorted[8].push_back(cards[i]);
			else if (cards[i].getNum() == 9) sorted[9].push_back(cards[i]);
		}
		else if (cards[i].getType() == p2) sorted[10].push_back(cards[i]);
		else if (cards[i].getType() == rev) sorted[11].push_back(cards[i]);
		else if (cards[i].getType() == s) sorted[12].push_back(cards[i]);
		else if (cards[i].getType() == w) sorted[13].push_back(cards[i]);
		else if (cards[i].getType() == p4) sorted[14].push_back(cards[i]);
	}

	//color sort
	std::vector<card> final;
	for (int i = 0; i < 5; ++i) {
		for (size_t j = 0; j < sorted.size(); ++j) {
			if (sorted[j].empty()) continue;
			for (size_t k = 0; k < sorted[j].size(); ++k) {
				if ((i == 0 && sorted[j][k].getColor() == r)
					|| (i == 1 && sorted[j][k].getColor() == y)
					|| (i == 2 && sorted[j][k].getColor() == g)
					|| (i == 3 && sorted[j][k].getColor() == b)
					|| (i == 4 && sorted[j][k].getColor() == wild)) {
					final.push_back(sorted[j][k]);
				}
			}
		}
	}

	cards = final;
}

//checks for playable card
bool hand::isMatch(const card& c, const deck& d) {
	if (c.getColor() == d.getCurrentColor()
		|| (c.getType() == d.getCurrentType() && d.getCurrentType() != num)
		|| c.getNum() == d.getCurrentNum()
		|| c.getType() == w || c.getType() == p4) return true;
	return false;
}

//CPU matching and drawToMatch matching
card* hand::findMatch(deck d) {
	//current card properties
	color currentC = d.getCurrentColor();
	type currentT = d.getCurrentType();
	int currentNum = d.getCurrentNum();

	bool colorMatch = false;
	bool typeMatch = false;
	bool numMatch = false;
	bool wildMatch = false;

	card* max = nullptr;

	//color matching
	for (size_t i = 0; i < cards.size(); ++i) {
		if (cards[i].getColor() == currentC) {
			colorMatch = true;
			if (max == nullptr) max = &cards[i];
			else {
				if (cards[i].getType() == p2 ||
					(cards[i].getType() == s && (max->getType() == rev || max->getType() == num)) ||
					(cards[i].getType() == rev && (max->getType() == num)) ||
					(cards[i].getNum() > max->getNum())) {
					max = &cards[i];
				}
			}
		}
	}
	if (colorMatch) return max;

	//type/num matching
	for (size_t i = 0; i < cards.size(); ++i) {
		if (currentNum > -1 && cards[i].getNum() == currentNum) {
			numMatch = true;
			max = &cards[i];
		}
		else if (currentNum == -1 && cards[i].getType() == currentT) {
			typeMatch = true;
			max = &cards[i];
		}
	}

	if (numMatch || typeMatch) return max;

	//wild matching
	for (size_t i = 0; i < cards.size(); ++i) {
		if (cards[i].getColor() == wild) {
			wildMatch = true;
			if (max == nullptr) max = &cards[i];
			else {
				if (cards[i].getType() == p4) max = &cards[i];
			}
		}
	}
	if (wildMatch) {
		int red = 0;
		int yellow = 0;
		int green = 0;
		int blue = 0;

		for (int i = 0; i < cards.size(); ++i) {
			int val = 0;
			if (cards[i].getType() == num && cards[i].getType() != wild) {
				val += cards[i].getNum();
			}
			else if (cards[i].getType() != wild) {
				val += 10;
			}

			if (cards[i].getColor() == r) red += val;
			else if (cards[i].getColor() == y) yellow += val;
			else if (cards[i].getColor() == g) green += val;
			else if (cards[i].getColor() == b) blue += val;
		}

		srand(time(nullptr));
		if (red == yellow && red == green && green == blue) {
			int random = rand() % 4;
			if (random == 0) max->wildChangeColor(r);
			else if (random == 1) max->wildChangeColor(y);
			else if (random == 2) max->wildChangeColor(g);
			else if (random == 3) max->wildChangeColor(b);
		}
		else {
			int random = rand() % 4;

			int maxVal = 0;
			
			if (random == 0) {
				maxVal = red;
				max->wildChangeColor(r);
			}
			else if (random == 1) {
				maxVal = yellow;
				max->wildChangeColor(y);
			}
			else if (random == 2) {
				maxVal = green;
				max->wildChangeColor(g);
			}
			else if (random == 3) {
				maxVal = blue;
				max->wildChangeColor(b);
			}

			if (red > maxVal) {
				maxVal = red; 
				max->wildChangeColor(r);
			}
			else if (yellow > maxVal) {
				maxVal = yellow;
				max->wildChangeColor(y);
			}
			else if (green > maxVal) {
				maxVal = green;
				max->wildChangeColor(g);
			}
			else if (blue > maxVal) {
				maxVal = blue;
				max->wildChangeColor(b);
			}
		}

		return max;
	}

	return nullptr;
}

//plays cards
bool hand::play(const card& c, deck& d) {
	if (isMatch(c, d)) {
		d.replaceCurrent(c);
		remove(c);
		return true;
	}
	return false;
}
///

#endif