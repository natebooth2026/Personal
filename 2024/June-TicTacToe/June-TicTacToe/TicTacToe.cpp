// Tic-Tac-Toe: C++ Edition
// A Nate Booth Production
// June 28th-29th, 2024

#include <iostream>
#include <string> //for secret only

//the board
const int BOARD_X = 3;
const int BOARD_Y = 3;
char board[BOARD_X][BOARD_Y];

//for intro message
bool run = false;

//template for winCheck()
struct win {
	char winner;
	bool won;
};

//game functions
void computerChoice(char);
void drawBoard();
win winCheck(char);

//program end function
void delayClose();


int main() {
	srand(time(nullptr));

	//intro message
	if (!run) {
		std::cout << "Tic-Tac-Toe: C++ Edition\n";
		std::cout << "A Nate Booth Production\n\n";
		run = true;
	}

	//initalizes board
	for (int i = 0; i < BOARD_X; ++i) {
		for (int j = 0; j < BOARD_Y; ++j) {
			board[i][j] = ' ';
		}
	}

	//choosing player character
	bool validChoice = false;
	char choice;

	while (!validChoice) {
		std::cout << "Choose X or O: ";
		std::cin >> choice;

		if (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o') {
			std::cout << std::endl << "Invalid choice.\n\n";
		} else {
			std::cout << std::endl;
			validChoice = true;
		}

		if (choice == 'x') {
			choice = 'X';
		} else if (choice == 'o') {
			choice = 'O';
		}
	}
	
	int playerFirst = rand() % 2; //determines if computer goes first
	bool winnerChosen = false; //holds if winner has been selected
	char winner = ' '; //holds winner character
	int slotsTaken = 0; //holds number of spots on board taken

	//computer first turn
	if (!playerFirst) {
		std::cout << "Computer goes first.\n";
		computerChoice(choice);
		++slotsTaken;
		playerFirst = true;
	}
	
	//game loop
	while (!winnerChosen || slotsTaken < BOARD_X + BOARD_Y + 1) {
		//draw board
		drawBoard();
		std::cout << std::endl << std::endl;
		
		//player's turn
		int blockNum = -1;
		std::cout << "Your turn.\nChoose a block to place your " << choice << ": ";
		std::cin >> blockNum;

		//determines location on board
		int blockX;
		int blockY;
		if (blockNum >= 1 && blockNum < 4) {
			blockX = 0;
			blockY = blockNum - 1;
		}
		else if (blockNum >= 4 && blockNum < 7) {
			blockX = 1;
			blockY = blockNum - 4;
		}
		else if (blockNum >= 7 && blockNum < 10) {
			blockX = 2;
			blockY = blockNum - 7;
		}
		else {
			std::cout << std::endl << "Invalid choice. \n";
			continue;
		}

		//applies choice
		if (board[blockX][blockY] != ' ') {
			std::cout << std::endl << "Already chosen.\n";
			continue;
		} else {
			board[blockX][blockY] = choice;
			++slotsTaken;
		}

		//check for win and full board with no win
		win checkResult = winCheck(choice);
		winner = checkResult.winner;
		winnerChosen = checkResult.won;
		if (winnerChosen || slotsTaken == BOARD_X * BOARD_Y) {
			drawBoard();
			break;
		} 

		//draw board
		drawBoard();
		std::cout << std::endl << std::endl;

		//computer's turn
		std::cout << "Computer's turn. \n";
		computerChoice(choice);
		++slotsTaken;

		//check for win
		checkResult = winCheck(choice);
		winner = checkResult.winner;
		winnerChosen = checkResult.won;
		if (winnerChosen || slotsTaken == BOARD_X * BOARD_Y) {
			drawBoard();
			break;
		}
	}
	
	//winner statement
	char computerPlayer = choice == 'X' ? 'O' : 'X';
	if (winner == choice) { //player wins
		std::cout << std::endl << std::endl << "Congrats! You win!\n";
	} else if (winner == computerPlayer) { //computer wins
		std::cout << std::endl << std::endl << "The computer won. Better luck next time!\n";
	} else { //tie
		std::cout << std::endl << std::endl << "It's a tie!\n";
	}

	//play again
	std::string playAgainChoice;
	std::cout << "Play again? (y or n) ";
	std::cin >> playAgainChoice;
	if (playAgainChoice == "y") {
		std::cout << std::endl;
		main();
	} else if (playAgainChoice == "n") {
		std::cout << std::endl << "Thanks for playing!";
		delayClose();
	} else if (playAgainChoice == "6292024") { //secret choice
		std::cout << std::endl << "lol you thought you cracked the code" << std::endl << "L bozo";
		delayClose();
	} else {
		std::cout << std::endl << "Invalid choice. Thanks for playing!";
		delayClose();
	}
}

void delayClose() {
	while (true) {
		int useless = 0;
	}
}

void drawBoard() {
	for (int i = 0; i < BOARD_X; ++i) {
		for (int j = 0; j < BOARD_Y; ++j) {
			if (j < BOARD_Y - 1) std::cout << board[i][j] << " | ";
			else std::cout << board[i][j];
		}
		if (i < BOARD_X - 1) std::cout << std::endl << "---------" << std::endl;
	}
}

void computerChoice(char player) {
	char computerPlayer = player == 'X' ? 'O' : 'X'; //finds computer player char

	//finds valid random spot
	bool foundValid = false;
	while (!foundValid) {
		int randBlockX = rand() % BOARD_X;
		int randBlockY = rand() % BOARD_Y;
		if (board[randBlockX][randBlockY] != ' ') {
			continue;
		}
		else {
			board[randBlockX][randBlockY] = computerPlayer;
			foundValid = true;
		}
	}
}

win winCheck(char player) {
	char computerChar = player == 'X' ? 'O' : 'X';
	win result = { ' ', false }; //default, no winner values

	//check for player win pattern, then computer win pattern
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
		(board[0][2] == player && board[1][1] == player && board[2][0] == player) ||
		(board[0][0] == player && board[0][1] == player && board[0][2] == player) ||
		(board[1][0] == player && board[1][1] == player && board[1][2] == player) ||
		(board[2][0] == player && board[2][1] == player && board[2][2] == player) ||
		(board[0][0] == player && board[1][0] == player && board[2][0] == player) ||
		(board[0][1] == player && board[1][1] == player && board[2][1] == player) ||
		(board[0][2] == player && board[1][2] == player && board[2][2] == player)) {
		result = { player, true };
	} else if ((board[0][0] == computerChar && board[1][1] == computerChar && board[2][2] == computerChar) ||
		(board[0][2] == computerChar && board[1][1] == computerChar && board[2][0] == computerChar) ||
		(board[0][0] == computerChar && board[0][1] == computerChar && board[0][2] == computerChar) ||
		(board[1][0] == computerChar && board[1][1] == computerChar && board[1][2] == computerChar) ||
		(board[2][0] == computerChar && board[2][1] == computerChar && board[2][2] == computerChar) ||
		(board[0][0] == computerChar && board[1][0] == computerChar && board[2][0] == computerChar) ||
		(board[0][1] == computerChar && board[1][1] == computerChar && board[2][1] == computerChar) ||
		(board[0][2] == computerChar && board[1][2] == computerChar && board[2][2] == computerChar)) {
		result = { computerChar, true };
	}

	return result;
}