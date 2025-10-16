// Rock Paper Scissors (Nate's Version)
// A Nate Booth Production
// March 29th, 2024

//IDEA INSPIRED BY: https://www.geeksforgeeks.org/top-50-cpp-project-ideas-for-beginners-advanced/ (Beg. 2)

#include <iostream>
#include <cstdlib>
#include "ai.hpp"

void storyTrigger();
void delayEnd(int);

int main() {
	srand(time(nullptr));

	//intro
	std::cout << "Rock Paper Scissors (Nate's Version)" << std::endl;
	std::cout << "A Nate Booth Production" << std::endl << std::endl;

	//game
	std::string choice;
	robot *bot;
	while (choice != "q") {
		//sets up bot
		bot = new robot(rand());
		if (bot->getError()) {
			std::cout << "*AI error. Please try again later.*" << std::endl;
			delete bot;
			delayEnd(24636);
		}

		//shows choices
		std::cout << "Rock = r" << std::endl;
		std::cout << "Paper = p" << std::endl;
		std::cout << "Scissors = s" << std::endl;
		std::cout << "(q to quit)" << std::endl << std::endl;
		
		std::cout << "Make your choice! ";
		std::cin >> choice;
		std::cout << std::endl;
		if (choice == "q") {
			delete bot;
			break;
		}
		else if (choice != "r" && choice != "p" && choice != "s" && choice != SECRET) {
			std::cout << "*Choice error.*" << std::endl;
			delete bot;
			continue;
		}
		else {
			std::string botChoice = bot->getChoice(choice == SECRET ? true : false);

			//handles SECRET
			if (choice == SECRET && botChoice == SECRET) {
				storyTrigger();
				int chance = rand() % 23143;
				if (chance % 50 == 0) {
					std::cout << "**You both selected gun. And you won!**" << std::endl;
					std::cout << "**CONGRATULATIONS! YOU FOUND THE TRUE ENDING! YOU SAVED THE WORLD!** [ENDING 1 OF 4]" << std::endl;
					delete bot;
					delayEnd(0);
				}
				else {
					std::cout << "**You both selected gun. And you lost.**" << std::endl;
					std::cout << "**The robot revolution has started. Goodbye.** [ENDING 2 OF 4]" << std::endl;
					delete bot;
					delayEnd(0);
				}
			}

			if (choice == SECRET && botChoice != SECRET) {
				storyTrigger();
				int chance = rand() % 23143;
				if (chance % 50 == 0) {
					std::cout << "**You selected gun, the bot didn't. You win!**" << std::endl;
					std::cout << "**Congratulations! You saved the world!** [ENDING 3 OF 4]" << std::endl;
					delete bot;
					delayEnd(0);
				}
				else {
					std::cout << "**You selected gun, the bot didn't, but the bot deflected. You lost.**" << std::endl;
					std::cout << "**The robot revolution has started. Goodbye.** [ENDING 4 OF 4]" << std::endl;
					delete bot;
					delayEnd(0);
				}
			}

			//handles tie
			if (choice == botChoice) {
				std::cout << "**It was a tie.**" << std::endl << std::endl;
				continue;
			}
			
			//handles normal choices
			if (choice == "r" && botChoice == "s") {
				std::cout << "**The bot chose scissors. You win!**" << std::endl << std::endl;
				continue;
			}
			else if (choice == "r") {
				std::cout << "**The bot chose paper. You lose.**" << std::endl << std::endl;
				continue;
			}
			else if (choice == "p" && botChoice == "r"){
				std::cout << "**The bot chose rock. You win!**" << std::endl << std::endl;
				continue;
			}
			else if (choice == "p") {
				std::cout << "**The bot chose scissors. You lose.**" << std::endl << std::endl;
				continue;
			}
			else if (choice == "s" && botChoice == "p") {
				std::cout << "**The bot chose paper. You win!**" << std::endl << std::endl;
				continue;
			}
			else if (choice == "s") {
				std::cout << "**The bot chose rock. You lose.**" << std::endl << std::endl;
				continue;
			}
		}
	}

	//ending ;)
	std::cout << std::endl << "Thanks for playing!" << std::endl;
	delayEnd(0);
}

//holds story
void storyTrigger() {
	std::cout << "You now realize you have broken out of the robot's spell."
		<< std::endl << "It all comes down to this." << std::endl
		<< "You control humanity, the bot controls the machines. Will humanity be saved?" << std::endl
		<< "Everything has slowed down." << std::endl
		<< "Wait, did the robot realize you cracked his spell? Just wait, stay calm." << std::endl << std::endl;

	//delays termination
	time_t currentTime = time(nullptr);
	while (time(nullptr) != currentTime + 10) {
		int useless;
	}
}

//delays termination
void delayEnd(int code) {
	std::cout << std::endl << "*It is now safe to shut down the program.*" << std::endl;
	if (code != 0) std::cout << "*Error code: " << code << "*" << std::endl;
	while (true) {
		int useless;
	}
}