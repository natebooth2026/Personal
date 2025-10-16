// Blackjack (Nate's Version)
// A Nate Booth Production
// December 29th-31st, 2024

#include <iostream>
#include "cards.hpp"

void deal(deck&, contestant&); //universal (dealer & player)
void aceDetect(deck&, contestant&); //universal
void printHands(contestant&, contestant&, bool = false, bool = false); //universal
void printSplitHands(contestant&); //player only

const double INIT_CREDITS = 5;

int main() {
	srand(time(nullptr));

	//Intro
	std::cout << "Blackjack (Nate's Version)\nA Nate Booth Production\n";
	std::cout << "Gambling problem? State of Ohio Gambling Hotline: 1-800-589-9966\n\n";

	double credits = INIT_CREDITS; //inits credits

	//declares player, dealer, and deck of cards
	contestant player;
	contestant house;
	deck cards;

	//GAME LOOP
	while (credits >= 1) {
		//(re)sets player and dealer (house) to empty contestant object
		player = contestant();
		house = contestant();

		cards = deck(); //(re)sets deck of cards to empty deck object

		//prints credit balance
		std::cout << "\nCredit balance: " << credits << std::endl;

		double bet = 0; //holds specific bet
		while (bet == 0) {
			std::cout << "Starting bet (1-credit minimum): ";
			std::cin >> bet;

			if (bet > credits || bet < 1) { //invalid/secret response
				if (bet >= 12292024 && bet == credits) {
					std::cout << "You wasted a lot of time lol\n";
					std::cout << "*It is now safe to close the program.*";
					while (true) {
						int useless;
					}
				} 
				else if (bet == 12292024) {
					std::cout << "10 credits added ;)\n";
					credits += 10;
				}

				if(bet != 12292024) std::cout << "Invalid bet.\n";

				if (bet == 12292024) std::cout << "\nCredit balence: " << credits << std::endl;

				bet = 0; //resets bet for re-input
			}
		}

		//deals first 3 cards (2 to player, 1 to house)
		std::cout << "\nDealing...\n";
		deal(cards, player);
		deal(cards, house);
		deal(cards, player);

		if (player.getV() == 21) { //natural blackjack
			std::cout << "\nPlayer natural blackjack detected!\n";

			//finishes house plays 
			while (house.getV() < 17) {
				deal(cards, house);
			}

			if (player.getV() > house.getV() || house.getV() > 21) { //house short of 21 or bust
				bet *= 1.5; //3 to 2 payout
				credits += bet; //officiates win
				std::cout << "Blackjack win! (1.5x bet reward)\n";
				printHands(house, player); //displays final result of plays
				std::cout << "\n---------\n";
				continue;
			}
			else {
				std::cout << "Blackjack push.\n";
				printHands(house, player); //displays final result of plays
				std::cout << "\n---------\n";
				continue;
			}
		}

		if (house.getV() == 11) { //insurance flag, requires 1/2 bet price for insurance, must support 3/2 bet provided
			if ((3 * bet)/2 > credits) { //not enough credits
				std::cout << "Dealer has ace. Insurance unavailable due to insufficient credits.\n";
				deal(cards, house); //deals second house card
				if (cards.cardValue(house.getCard()) == 10) { //natural blackjack
					std::cout << "Dealer has blackjack. Bet lost.\n";
					printHands(house, player); //displays final result of plays
					credits -= bet; //officiates loss
					std::cout << "\n---------\n";
					continue;
				}
				else { // <= 20
					std::cout << "Dealer doesn't have blackjack.\n";
				}
			} 
			else { //enough credits
				char choice = ' '; //prepares to accept insurance prompt choice
				while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') { //safety guard
					std::cout << "Dealer has ace. Insurance available (1/2 bet price). Do you want insurance? (y for yes, n for no) ";
					std::cin >> choice;
					if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') std::cout << "Invalid choice.\n";
				}

				if (choice == 'y' || choice == 'Y') { //insurance taken
					bet *= 1.5; //adds insurance cost to bet
					std::cout << "\nNew bet: " << bet << std::endl;
					deal(cards, house); //deals second house card
					if (cards.cardValue(house.getCard()) == 10) { //natural blackjack, insurance-granted push
						std::cout << "Dealer has blackjack. Insurance grants a push.\n";
						printHands(house, player); //displays final result of plays
						std::cout << "\n---------\n";
						continue;
					}
					else { // <= 20
						credits -= bet / 3; //officiates loss of insurance cost

						//adjusts bet back to original bet (2/3 of 3/2)
						bet *= 2;
						bet /= 3;

						std::cout << "Dealer doesn't have a blackjack. Insurance bet lost.\n";
						std::cout << "New credit count: " << credits << std::endl;
						std::cout << "Original bet stands: " << bet << std::endl;
					}
				}
				else { //rejected insurance
					deal(cards, house); //deals second house card
					if (cards.cardValue(house.getCard()) == 10) { //natural blackjack
						credits -= bet; //officiates loss of bet
						std::cout << "\nDealer has blackjack. Bet lost.\n";
						printHands(house, player); //displays final result of plays
						std::cout << "\n---------\n";
						continue;
					}
					else { // <= 20
						std::cout << "\nDealer doesn't have a blackjack.\n";
					}
				}
			}
		}
		else { //no insurance flag
			deal(cards, house); //deals second house card
		}

		printHands(house, player, true); //displays current state of cards, hiding the second house card

		char choice = ' '; //prepares to accept play prompt choice
		int standCount = 0; //holds number of times stand/double was issued on a hand (for splits)
		while (choice != 's' && choice != 'S' && (player.getV() < 21 || (player.getSplit() > 0 && (player.getV() < 21 || player.getSV() < 21)))) {
			//requests play choice
			std::cout << "Choose a play (h to hit, s to stand, d to double, p to split, u to surrender): ";
			std::cin >> choice;

			//repeats request if invalid choice
			if (choice != 'h' && choice != 'H' && choice != 's' && choice != 'S' && choice != 'd' && choice != 'D' && choice != 'p' && choice != 'P' && choice != 'u' && choice != 'U') {
				std::cout << "Invalid choice.\n";
				continue;
			}

			if (choice == 'h' || choice == 'H') { //hit
				if (player.getV() == 11 && player.getAmount() == 1 && player.getSplit() > 0 && player.getSplit() % 2 == 1) { //ace split case (hand 1)
					deal(cards, player); //deals new card

					if (standCount == 0) player.setSplit(4); //forces to second hand
					else break; //ends play

					++standCount; //forces next stand/double to end play
					std::cout << std::endl;
					printHands(house, player, true); //displays result of plays
					continue;
				}

				if (player.getSV() == 11 && player.getSecondAmount() == 1 && player.getSplit() > 0 && player.getSplit() % 2 == 0) { //ace split case (hand 2)
					deal(cards, player); //deals new card

					if (standCount == 0) player.setSplit(3); //forces to first hand
					else break; //ends play

					++standCount; //forces next stand/double to end play
					std::cout << std::endl;
					printHands(house, player, true); //displays result of plays
					continue;
				}

				deal(cards, player); //deals new card

				if (player.getSplit() > 0 && standCount == 0) ++player; //split first stand/double case, forces to next hand
				if ((player.getV() >= 21 || player.getSV() >= 21) && standCount != 0) break; //split second stand/double/bust/blackjack case
				else if ((player.getV() >= 21 || player.getSV() >= 21) && player.getSplit() > 0 && standCount == 0) { //split first bust/blackjack case
					++standCount;
					if (player.getV() >= 21) player.setSplit(4); //forces to second hand
					else if (player.getSV() >= 21) player.setSplit(3); //forces to first hand
				}  
				if (player.getV() > 21 && player.getSplit() == 0) break; //regular bust case

				std::cout << std::endl;
				printHands(house, player, true); //displays result of plays
				continue;
			}
			else if ((choice == 's' || choice == 'S') && player.getSplit() > 0 && standCount == 0) { //stand (split first case)
				++standCount; //forces next stand/double to end play

				if (player.getSplit() % 2 == 1) player.setSplit(4); //forces to second hand
				else player.setSplit(3); //forces to first hand

				choice = ' '; //clears for restarting loop
				std::cout << std::endl;
				printHands(house, player, true); //displays result of plays
				continue;
			}
			else if (choice == 'd' || choice == 'D') { //double
				if (player.getSplit() == 0) { //regular case
					if (bet * 2 > credits) { //not enough credits
						std::cout << "Doubiling is unavailable.\n";
						continue;
					}

					bet *= 2; //preforms double
					std::cout << "\nNew bet: " << bet << std::endl;
					deal(cards, player); //deals a final card
					break; //ends play
				}
				else { //split case
					if (bet * 1.5 > credits) { //not enough credits (1.5 * bet since it is doubiling a half of the bet)
						std::cout << "Doubiling is unavaiable.\n";
						continue;
					}

					bet *= 1.5; //performs split double
					std::cout << "\nNew bet: " << bet << std::endl;
					deal(cards, player); //deals a new card

					if (standCount == 0) { //first stand/double
						++standCount; //forces next stand/double to end play

						if (player.getSplit() % 2 == 1) player.setSplit(4); //forces to sec
						else player.setSplit(3); //forces to first hand
			
						printHands(house, player, true); //displays result of plays
						continue;
					}
					else { //second stand/double
						break; //ends play
					}
				}
			}
			else if (choice == 'p' || choice == 'P') { //split
				if (player.checkSplit(cards) && (bet * 2) <= credits && player.getSplit() == 0) { //compatible, enough credits, only successful split
					std::cout << "\nYou chose to split.\n";
					bet *= 2; //spreads original bet over both hands
					std::cout << "New bet: " << bet << " (" << bet / 2 << " per hand)\n";

					player.addToSecond(player[1]); //makes the second hand's first card the second card of the first hand
					player.addToSecVal(player.getV() / 2); //adds half of original hand's value to second hand
					player.addToValue(-(player.getV() / 2)); //subtracts half of original hand's value
					player.eraseCard(); //removes second card from first hand
					++player; //forces to first hand next play

					if (cards.cardValue(player.getCard()) == 1) { //ace split case
						player.setV(11); //sets value of first hand to max ace value
						player.setSV(11); //sets value of second hand to max ace value
					}

					std::cout << std::endl;
					printHands(house, player, true); //displays result of plays
					continue;
				}
				else { //not compatible, not enough credits, or not the first split
					std::cout << "Splitting is unavailable.\n";
					continue;
				}
			}
			else if (choice == 'u' || choice == 'U') { //surrender
				if (player.getAmount() == 2 && player.getSplit() == 0) { //2 cards, un-split
					credits -= (bet / 2); //officiates loss of 1/2 bet
					std::cout << "\nYou have surrendered. 1/2 bet is returned.\n";
					printHands(house, player); //displays result of plays
					std::cout << std::endl;
					break;
				}
				else { //more than 2 cards or split cards
					std::cout << "Surrendering is unavailable.\n";
					continue;
				}
				
			}
		}

		//WIN OR LOSS
		if (choice == 'u' || choice == 'U') { //surrender case (neutral)
			choice = ' '; //clears choice for play again prompt choice
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				std::cout << "Credit balance: " << credits << std::endl;
				std::cout << "Would you like to play again? (y for yes, n for no) ";
				std::cin >> choice;
				if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') std::cout << "Invalid choice.\n";
			}

			std::cout << "\n---------\n";
			if (choice == 'y' || choice == 'Y') continue; //playing again
			else break; //not playing again
		}

		if (player.getSplit() > 0) { //split case
			if (player.getV() > 21 && player.getSV() > 21) { //both bust
				credits -= bet; //officiates loss of bet
				std::cout << "\nBust on both hands. Bet lost.\n";
				printHands(house, player, false, true); //displays result of house plays
				printSplitHands(player); //displays result of player plays
				std::cout << std::endl;
			}
			else { //one or neither bust
				bool bustFlag = false; //indicates if a hand did bust
				int bustNum = 0; //indicates which hand did bust (3 for both--error case)

				if (player.getV() > 21) { //first hand bust
					credits -= (bet / 2); //officiates loss of 1/2 bet
					bet /= 2; //adjusts bet accordingly
					std::cout << "\nBust on first hand. 1/2 bet lost.\n";
					bustFlag = true; //indicates a hand busted
					bustNum += 1; //indicates hand 1 busted
				}

				if (player.getSV() > 21) { //second hand bust
					credits -= (bet / 2); //officiates loss of 1/2 bet
					bet /= 2; //adjusts bet accordingly
					std::cout << "\nBust on second hand. 1/2 bet lost.\n";
					bustFlag = true; //indicates a hand busted
					bustNum += 2; //indicates hand 2 (value of 2) or both (value of 3) busted
				}

				//finishes house plays
				while (house.getV() < 17) {
					deal(cards, house);
				}

				if (player.getV() > house.getV() && house.getV() <= 21 && player.getV() <= 21) { //player wins first hand
					if (!bustFlag) { //no busted hands
						credits += (bet / 2); //officiates win of 1/2 bet
						std::cout << "\nDealer lost on your first hand. 1/2 bet won!\n";
					}
					else { //one hand busted
						credits += bet; //officiates win of 1/2
						std::cout << "Dealer lost on your first hand. 1/2 bet won!\n";
					}
				}
				else if (player.getV() < house.getV() && house.getV() <= 21 && player.getV() <= 21) { //player loses first hand
					if (!bustFlag) { //no busted hands
						credits -= (bet / 2); //officiates loss of 1/2 bet
						std::cout << "\nDealer won on your first hand. 1/2 bet lost.\n";
					}
					else { //one hand busted
						credits -= bet; //officiates loss of 1/2 bet
						std::cout << "Dealer won on your first hand. 1/2 bet lost.\n";
					}
				}
				else if (player.getV() == house.getV() && house.getV() <= 21 && player.getV() <= 21) { //push first hand
					if (!bustFlag) std::cout << '\n'; //styling due to lack of busted hands
					std::cout << "Push on your first hand.";
				}
				else { //house busted
					if (!bustFlag) { //no player hands busted
						credits += (bet / 2); //officiates win of 1/2 bet
						std::cout << "\nDealer bust on your first hand. 1/2 bet won!\n";
					}
					else { //one player hand busted
						if (bustNum != 1 && bustNum != 3) { //not first hand that busted
							credits += bet; //officiates win of 1/2 bet
							std::cout << "Dealer bust on your first hand. 1/2 bet won!\n";
						}
					}
				}

				if (bustFlag && bustNum == 2) { //second hand busted
					printHands(house, player, false, true); //displays result of house plays
					printSplitHands(player); //displays result of player plays
					std::cout << std::endl;
				}

				if (player.getSV() > house.getV() && house.getV() <= 21 && player.getSV() <= 21) { //player wins second hand
					if (!bustFlag) { //no hands busted
						credits += (bet / 2); //officiates win of 1/2 bet
						std::cout << "Dealer lost on your second hand. 1/2 bet won!\n";
						printHands(house, player, false, true); //displays result of house plays
						printSplitHands(player); //displays result of player plays
						std::cout << std::endl;
					}
					else { //one hand busted
						credits += bet; //officiates win of 1/2 bet
						std::cout << "Dealer lost on your second hand. 1/2 bet won!\n";
						printHands(house, player, false, true); //displays result of house plays
						printSplitHands(player); //displays result of house plays
						std::cout << std::endl;
					}
				}
				else if (player.getSV() < house.getV() && house.getV() <= 21 && player.getSV() <= 21) { //players loses second hand
					if (!bustFlag) { //one hand busted
						credits -= (bet / 2); //officiates loss of 1/2 bet
						std::cout << "Dealer won on your second hand. 1/2 bet lost.\n";
						printHands(house, player, false, true); //displays result of house plays
						printSplitHands(player); //displays result of player plays
						std::cout << std::endl;
					}
					else { //one hand busted
						credits -= bet; //officiates loss of 1/2 bet
						std::cout << "Dealer won on your second hand. 1/2 bet lost.\n";
						printHands(house, player, false, true); //displays result of house plays
						printSplitHands(player); //displays result of player plays
						std::cout << std::endl;
					}
				}
				else if (player.getSV() == house.getV() && house.getV() <= 21 && player.getSV() <= 21) { //push second hand
					if (!bustFlag) std::cout << '\n'; //styling due to lack of busted hands
					std::cout << "Push on your second hand.\n";
					printHands(house, player, false, true); //displays result of house plays
					printSplitHands(player); //displays result of player plays
					std::cout << std::endl;
				}
				else { //house busted
					if (!bustFlag) { //no player hands busted
						credits += (bet / 2); //officiates win of 1/2 bet
						std::cout << "Dealer bust on your second hand. 1/2 bet won!\n";
						printHands(house, player, false, true); //displays result of house plays
						printSplitHands(player); //displays result of player plays
						std::cout << std::endl;
					}
					else { //one hand busted
						if (bustNum != 2 && bustNum != 3) { //not second hand that busted
							credits += bet; //officiates win of 1/2 bet
							std::cout << "Dealer bust on your second hand. 1/2 bet won!\n";
							printHands(house, player, false, true); //displays result of house plays
							printSplitHands(player); //displays result of player plays
							std::cout << std::endl;
						}
					}
				}
			}
		}
		else { //regular case
			if (player.getV() > 21) { //player busts
				credits -= bet; //officates loss of bet
				std::cout << "\nBust. Dealer wins. Bet lost.\n";
				printHands(house, player); //displays result of plays
				std::cout << std::endl;
			}
			else { //player didn't bust
				//finishes house plays
				while (house.getV() < 17) {
					deal(cards, house);
				}

				if (player.getV() > house.getV() && house.getV() <= 21) { //player wins
					credits += bet; //officiates win of bet
					std::cout << "\nDealer lost. You won!\n";
					printHands(house, player); //displays result of plays
					std::cout << std::endl;
				}
				else if (player.getV() < house.getV() && house.getV() <= 21) { //player loses
					credits -= bet; //officiates loss of bet
					std::cout << "\nDealer wins. Bet lost.\n";
					printHands(house, player); //displays result of plays
					std::cout << std::endl;
				}
				else if (player.getV() == house.getV() && house.getV() <= 21) { //push
					std::cout << "\nPush.\n";
					printHands(house, player);
					std::cout << std::endl;
				}
				else { //house busted
					credits += bet; //officiates win of bet
					std::cout << "\nDealer bust. You won!\n";
					printHands(house, player); //displays result of plays
					std::cout << std::endl;
				}
			}
		}

		if (credits < 1) break; //ends game loop if there are no longer enough credits

		choice = ' '; //resets choice for play again prompt choice
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			std::cout << "Credit balance: " << credits << std::endl;
			std::cout << "Would you like to play again? (y for yes, n for no) ";
			std::cin >> choice;
			if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') std::cout << "Invalid choice.\n";
		}

		std::cout << "\n---------\n";
		if (choice == 'y' || choice == 'Y') continue; //playing again
		else break; //not playing again, ends game
	}

	//Exit
	if (credits >= 1) { //player quit before being elimnated
		if (credits < INIT_CREDITS) std::cout << "You walk away with " << INIT_CREDITS - credits << " less credits.\n"; //lost credits
		else if (credits > INIT_CREDITS) std::cout << "You walk away with " << credits - INIT_CREDITS << " extra credits!\n"; //gained credits
		else std::cout << "You walk away with the credits you had at the start!\n"; //no gain or loss
		std::cout << "Thanks for playing! Come back again!\n";
		std::cout << "*It is now safe to close the program.*";
		while (true) { //infinite loop for .exe file (waiting for user to close window)
			int useless;
		}
	}
	else { //player eliminated
		std::cout << "Better luck next time.\n";
		std::cout << "*It is now safe to close the program.*";
		while (true) { //infinite loop for .exe file (waiting for user to close window)
			int useless;
		}
	}
}

//Detects ace and adjusts values of hands as needed
void aceDetect(deck &d, contestant &c) {
	if (d.cardValue(c.getCard()) == 1 && c.getV() <= 11) { //ace to 11 regular/first hand case
		c.addToValue(10); //officiates ace to 11 change
		c.setAce(true);
	}
	else if (d.cardValue(c.getCard()) == 1) { //ace stays 1 regular/first hand case
		if(!c.getAce()) c.setAceLimit(); //prohibits deductions to hand value if first ace
		c.setAce(true);
	}
	else if (c.getSplit() > 0 && c.getSplit() % 2 == 0){ //split case
		if (d.cardValue(c.getSecond()) == 1 && c.getSV() <= 11) { //ace to 11 second hand case
			c.addToSecVal(10); //officiates ace to 11 change
			c.setAce2(true);
		}
		else if (d.cardValue(c.getSecond()) == 1) { //ace stays 1 second hand case
			if (!c.getAce2()) c.setAce2Limit(); //prohibits deductions to hand value if first ace
			c.setAce2(true);
		}
	}
}

//Deals one new card to specified contestant
void deal(deck &d, contestant &c) {
	if (c.getSplit() % 2 == 1 || c.getSplit() == 0) { //regular/first hand case
		c.addCard(d.grabCard()); //adds a random card from deck into (first) hand
		c.addToValue(d.cardValue(c.getCard())); //adds value of new card to hand value
		aceDetect(d, c); //detects ace and performs any necessary ace changes
		if (c.getAce() && c.getAceRepeat() && c.getV() > 21) { //multiple aces/bust with 11-ace case
			c.addToValue(-10); //reverses ace to 11 change
			c.setAce(false);
			c.setAceLimit(); //prohibits future deductions to hand value
		}
	}
	else { //second hand case
		c.addToSecond(d.grabCard()); //adds a random card from deck into second hand
		c.addToSecVal(d.cardValue(c.getSecond())); //adds value of new card to hand value
		aceDetect(d, c); //detects ace performs any necessary ace changes
		if (c.getAce2() && c.getAce2Repeat() && c.getSV() > 21) { //multiple aces/bust with 11-ace case
			c.addToSecVal(-10); //reverses ace to 11 change
			c.setAce2(false);
			c.setAce2Limit(); //prohibits future deductions to hand value
		}

	}
}

//REQUIRES: h.cards.size() > 0
//Displays house hand and player hand (non-split case only)
//dealHide is when player isn't done playing to hide second card
//skipPlayer is for split cases at end of play, set to false by default
void printHands(contestant& h, contestant& p, bool dealHide, bool skipPlayer) {
	//HOUSE
	std::cout << "Dealer hand: ";

	if (dealHide) { //hide second card case
		std::cout << h[0] << " [HIDDEN]\n";
	}
	else { //play is over
		for (size_t i = 0; i < h.getAmount(); ++i) {
			std::cout << h[i] << " "; //displays each individual card
		}

		std::cout << "(" << h.getV() << ")\n"; //displays hand value
	}


	//PLAYER
	if (skipPlayer) return; //ends function if split player hands at end of play

	if (p.getSplit() == 0) { //regular case
		std::cout << "Your hand: ";

		for (size_t i = 0; i < p.getAmount(); ++i) {
			std::cout << p[i] << " "; //displays each individual card
		}

		std::cout << "(" << p.getV() << ")\n"; //displays hand value
	}
	else { //split, during-play case
		std::cout << "Your current hand: ";

		if (p.getSplit() % 2 == 1) { //first hand case
			for (size_t i = 0; i < p.getAmount(); ++i) {
				std::cout << p[i] << " "; //displays each individual card
			}
		}
		else { //second hand case
			for (size_t i = 0; i < p.getSecondAmount(); ++i) {
				std::cout << p(i) << " "; //displays each individual card
			}
		}
		
		//displays current hand value
		std::cout << "(";
		if (p.getSplit() % 2 == 1) std::cout << p.getV() << ")\n"; //first hand case
		else std::cout << p.getSV() << ")\n"; //second hand case
	}
}

//Displays player hands at end of play in a split case
void printSplitHands(contestant &p) {
	//FIRST HAND
	std::cout << "Your first hand: ";

	for (size_t i = 0; i < p.getAmount(); ++i) {
		std::cout << p[i] << " "; //displays each individual card
	}

	std::cout << "(" << p.getV() << ")\n"; //displays first hand value


	//SECOND HAND
	std::cout << "Your second hand: ";

	for (size_t i = 0; i < p.getSecondAmount(); ++i) {
		std::cout << p(i) << " "; //displays each individual card
	}

	std::cout << "(" << p.getSV() << ")\n"; //displays second hand value
}