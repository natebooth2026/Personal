// UNO: Nate's Version
// A Nate Booth Production
// May 24th, 2025-July ????, 2025

#include <cassert>
#include <iostream>
#include "cards.hpp"
#include "globals.hpp"

int main() {
	//creating a card
	{
		card x;
		assert(x.getColor() == noC && x.getType() == noT && x.getNum() == -1);
		std::cout << "Passed default card creation test\n";
	}

	{
		card x(y, p2);
		assert(x.getColor() == y && x.getType() == p2);
		std::cout << "Passed card with properties (non-num) creation test\n";
	}

	{
		card x(g, num, 9);
		assert(x.getColor() == g && x.getType() == num && x.getNum() == 9);
		std::cout << "Passed card with properties (num) creation test\n";
	}

	//erroneous creation
	{
		card x(wild, p2);
		card y(r, w);
		card z(wild, num, 2);

		assert(x.getColor() != wild && y.getColor() != r && z.getColor() != wild
			&& x.getType() != p2 && y.getType() != w && z.getType() != num
			&& z.getNum() != 2);
		std::cout << "Passed erroneous card blank-card creation test\n";
	}

	//wild & +4 color changes
	{
		card x(wild, p4);
		card y(wild, w);

		x.wildChangeColor(r);
		y.wildChangeColor(g);

		assert(x.getColor() == r && x.getType() == p4
			&& y.getColor() == g && y.getType() == w);
		std::cout << "Passed wild & +4 color change checks\n";
	}
	
	//creating the deck
	{
		deck d(false);
		assert(d[0].getColor() == w && d[107].getColor() == b);
		std::cout << "Passed deck creation test\n";
	}

	//drawing all cards
	{
		hand p(0), c1(1), c2(2), c3(3);
		deck d(false);
		for (int i = 0; i < 27; ++i) {
			p.add(d.draw());
			c1.add(d.draw());
			c2.add(d.draw());
			c3.add(d.draw());
		}

		assert(d.isEmpty() && p.getSize() == 27 && c1.getSize() == 27 && c2.getSize() == 27 && c3.getSize() == 27);
		std::cout << "Passed emptying deck test\n";
	}

	//(re)shuffling, placing into the deck
	{
		deck d;
		assert(d.getSize() == 108 && d.getSize(true) == 0);
		std::cout << "Passed shuffiling card amounts test\n";

		d.placeInit();
		assert(d.getSize() == 107 && d.getSize(true) == 0 && d.getCurrentColor() != noC && d.getCurrentType() != noT);
		std::cout << "Passed inital placement test\n";

		hand p(0), c1(1), c2(2), c3(3);
		for (int i = 0; i < 27; ++i) {
			p.add(d.draw());
			d.place(p, p[0]);
			c1.add(d.draw());
			d.place(c1, c1[0]);
			c2.add(d.draw());
			d.place(c2, c2[0]);
		}

		assert(p.isEmpty() && c1.isEmpty() && c2.isEmpty());

		for (int i = 0; i < 25; ++i) {
			c3.add(d.draw());
			d.place(c3, c3[0]);
		}

		assert(d.getSize(true) == 106 && d.getSize() == 1 && c3.isEmpty());
		std::cout << "Passed rapid draw and place tests\n";
	
		c3.add(d.draw());
		assert(d.getSize(true) == 0 && d.getSize() == 106 && c3[0] != card());
		std::cout << "Passed reshuffiling card amounts test\n";

		d.place(c3, c3[0]);
		assert(d.getSize(true) == 1 && d.getSize() == 106 && c3.isEmpty());
		std::cout << "Passed placement after reshuffle test\n";

		c3.add(d.draw());
		assert(d.getSize(true) == 1 && d.getSize() == 105 && c3[0] != card());
		std::cout << "Passed draw after reshuffle test\n";

		d.place(c3, c3[0]);
		assert(d.getSize(true) == 2 && d.getSize() == 105 && d.getCurrent() != card());
		std::cout << "Passed placement of reshuffle card test\n";
	}

	WORKING_GAME = true;
}