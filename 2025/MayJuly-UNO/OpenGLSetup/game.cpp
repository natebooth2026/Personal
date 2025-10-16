// UNO: Nate's Version (PRE-ALPHA)
// A Nate Booth Production
// May 24th, 2025-July 30th, 2025
// BUG PATCH: August 1st, 2025

//NOTE FOR NEXT DEV DAY: FEATURES - Fix CPU drawToMatch rules, add more graphics (Color Wheel, UNO icon, Some background, maybe a title logo?)
#include "cards.hpp"
#include "media.hpp"
#include <iostream> //for pre-boot testing/debugging
#include <cassert> //for pre-boot testing
#include <cmath> //for moving turns

#define WIN_X 100
#define WIN_Y 100
const int WIN_H = 600;
const int WIN_W = 600;

std::vector<hand> players;
int playerCount = 2;
int currentPlayer = 0;

bool controlsShown = false;
bool gameStarted = false;
deck d;
bool initDraw = false; //detects when the inital card draw occurs
bool animationComplete = false; //detects when the card draw is finished
int dealingPlayer = -1; //shows which player is dealing
int cardsAdded = 0; //detects how many cards go out during inital deal

card* selected = nullptr;
color chosenColor = noC;
card* played = nullptr;
hand* temp = new hand(-1);

//actions
bool initPlayerWild = false;
bool reversed = false;
bool forceDraw = false;
int numToDraw = 0;

int winner = -1; //shows which player won the game

bool drawing = false; //detects when player is drawing a card voluntarily

//for player tracking purposes
bool playerDrewPlay = false; //detects when a player draws a card that was forced played
bool playerUNOFail = false; //detects when a player fails to flag UNO before placing 2nd-to-last card
bool CPUDrew = false; //detects when a CPU draws a card
bool CPUPlaySimilar = false; //detects when a CPU plays a similar card

//UNO tracking
bool playerFlaggedUNO = false; //detcts when a player flags to UNO

//extra rules (WILL IMPLEMENT LATER)
bool stacking = false;
bool jumpIn = false;
bool drawToMatch = false;

//functions
void preTest(); //pre-boot testing
void drawHand(hand&); //to draw a player's hand on screen
void drawCard(const card&); //to draw a card on screen
void debugCard(const card&); //prints details of card (TESTING ONLY)
void handleTurn(int = 0); //allows the turn to be performed
void drawingRefresh(int = 0); //allows the display to refresh during drawing
void moveTurns(const card&, bool = false); //moves turn from one player to the next
void initWild(const hand&, card*); //determines wild for CPU if it is the first card
void specWildKey(int, int, int); //forwarded

void init(void) {
	//preTest(); //REMOVED FOR DEBUGGING
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	players.push_back(hand(0));
	players.push_back(hand(1));
}

//draws text (from Super Not Mario Maker)
void textDraw(const std::string& text, int n = -1, float x = 0, float y = 0, float z = 0, float space = 0) {
	glPushMatrix(); //prepares to place text at x,y,z
	glRasterPos3f(x, y, z);
	glColor3f(1.0, 1.0, 1.0);

	for (int i = 0; text[i] != 0; ++i) {
		if (text[i] == '\n') { //newline condition
			y -= space;
			glRasterPos3f(x, y, z);
		}
		else { //regular calculator
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		}
	}

	//number printing
	if (n == 0) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
	}
	else {
		std::vector<char> num;

		while (n > 0) {
			num.push_back(char((n % 10) + int('0')));
			n /= 10;
		}

		for (int i = num.size() - 1; i >= 0; --i) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, num[i]);
		}
	}
	glPopMatrix();
}

//flushes all game and before game graphics
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (gameStarted) {
		for (auto& player : players) {
			if (!initDraw) {
				player.add(d.draw());
				++cardsAdded;
				if (cardsAdded >= 7 * playerCount) {
					initDraw = true;
					selected = &players[0][0];
				}
			}

			if (player.isCPU()) {
				if (playerCount == 2) {
					textDraw("CPU\nCards: ", player.getSize(), -0.075f, 0.75f, 0.0f, 0.075f);
					if (player.getUNO() && player.getSize() != 0) textDraw("**UNO**", -1, 0.2f, 0.675f);
				}
				else {
					if (player.getID() == 1) {
						textDraw("CPU", player.getID(), -0.9f, 0.05f);
						textDraw("Cards: ", player.getSize(), -0.9f, -0.025f);
						if (player.getUNO() && player.getSize() != 0) textDraw("**UNO**", -1, -0.9f, -0.1f);
					}
					else if (player.getID() == 2) {
						textDraw("CPU", player.getID(), -0.075f, 0.75f);
						textDraw("Cards: ", player.getSize(), -0.075f, 0.675f);
						if (player.getUNO() && player.getSize() != 0) textDraw("**UNO**", -1, 0.2f, 0.675f);
					}
					else if (player.getID() == 3) {
						textDraw("CPU", player.getID(), 0.7f, 0.05f);
						textDraw("Cards: ", player.getSize(), 0.7f, -0.025f);
						if (player.getUNO() && player.getSize() != 0) textDraw("**UNO**", -1, 0.7f, -0.1f);
					}
				}
			}
			else {
				drawHand(player);
				if (winner == -1) {
					textDraw("Cards: ", player.getSize(), -0.075f, -0.95f);
					if (player.getUNO() && player.getSize() != 0) textDraw("**UNO**", -1, 0.2f, -0.95f);
				}
				else if (winner == 0) {
					textDraw("You won!", -1, -0.075f, -0.95f);
				}
				else {
					textDraw("You lost.", -1, -0.075f, -0.95f);
				}

			}
		}

		if (initDraw) {
			if (d.getCurrent() == card()) {
				d.placeInit();
				if (d.getCurrent().getColor() == wild) {
					if (players[dealingPlayer].isCPU()) {
						initWild(players[dealingPlayer], d.getCurrentPtr());
						moveTurns(d.getCurrent(), true);
					}
					else {
						played = d.getCurrentPtr();
						initPlayerWild = true;
						glutSpecialFunc(specWildKey);
					}
				}
				else {
					moveTurns(d.getCurrent(), true);
				}
			}
			d.setCurrentX(-0.15f);
			d.setCurrentY(-0.15f);
			d.setCurrentW(0.3f);
			d.setCurrentH(0.45f);
			drawCard(d.getCurrent());
			debugCard(d.getCurrent()); //DEBUG

			std::string currentText = currentPlayer == 0 ? "YOU" : "CPU";
			if (currentText != "YOU") {
				if (currentPlayer == 1) currentText += char(1 + int('0'));
				else if (currentPlayer == 2) currentText += char(2 + int('0'));
				else if (currentPlayer == 3) currentText += char(3 + int('0'));
			}
			if (winner == -1) {
				textDraw("Current Turn: " + currentText, -1, -0.325f, -0.4f);

				if (!forceDraw) {
					if (CPUDrew) {
						textDraw("CPU drew a card.", -1, -0.325f, -0.45f);
					}
					else if (CPUPlaySimilar) {
						textDraw("CPU played a card.", -1, -0.325f, -0.45f);
					}
					else if (playerDrewPlay) {
						textDraw("YOU force-played a card.", -1, -0.325f, -0.45f);
					}
				}
			}
			if (forceDraw) {
				if (!playerUNOFail) textDraw(currentText + " required to draw!", -1, -0.325f, -0.45f);
				else textDraw("YOU failed to UNO properly!", -1, -0.325f, -0.45f);
				
				textDraw("Cards left to draw: ", numToDraw, -0.325f, -0.5f);
			}

			if (playerFlaggedUNO) {
				textDraw("YOU are about to UNO!", -1, 0.3f, -0.95f);
			}
		}

		card deck;
		deck.setX(-0.95f);
		deck.setY(0.65f);
		deck.setW(0.2f);
		deck.setH(0.3f);
		drawCard(deck);

		if (playerCount > 2) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texID[TURN_ARROW]);

			glBegin(GL_POLYGON);

			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.7f, 0.7f);
			glTexCoord2f(reversed ? 1.0 : -1.0, 0.0);
			glVertex2f(0.9f, 0.7f);
			glTexCoord2f(reversed ? 1.0 : -1.0, 1.0);
			glVertex2f(0.9f, 0.9f);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(0.7f, 0.9f);
			

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
	else {
		textDraw("Press Enter to Start!", -1, -0.25f);
		
		std::string currentPlayerCount = "Players: 1 Human & ";
		currentPlayerCount += char((playerCount - 1) + int('0'));
		currentPlayerCount += " CPU(s)";
		textDraw(currentPlayerCount, -1, -0.325f, -0.35f);

		if (!controlsShown) textDraw("Press C for controls.", -1, -0.25f, -0.6f);
		else textDraw("CONTROLS:\nLeft/Right Arrows = Select New Card, Enter = Play Card,\nSpace = Flag UNO, D = Draw, C = Hide Controls, R = Restart\nWild Controls: Up = Green, Down = Red, Left = Blue, Right = Yellow", -1, -0.925f, -0.6f, 0.0f, 0.075f);

		textDraw("Use the up/down arrows to select number of players.", -1, -0.7f, -0.45f);
	}

	glFlush();
}

//up, down, left, right operations during and before games
void specKey(int k, int x, int y) {
	if (k == GLUT_KEY_UP && !gameStarted && playerCount < 4) {
		++playerCount;
		glutPostRedisplay();
	}

	if (k == GLUT_KEY_DOWN && !gameStarted && playerCount > 2) {
		--playerCount;
		glutPostRedisplay();
	}

	if (k == GLUT_KEY_LEFT && gameStarted
		&& players[0][0].getX() <= -0.91
		&& players[0][0].getX() + 0.2 <= -0.89
		&& animationComplete && !forceDraw && currentPlayer == 0 && winner == -1) {
		int selectedIndex = -1;

		for (size_t i = 0; i < players[0].getSize(); ++i) {
			players[0][i].setX(players[0][i].getX() + 0.2);
			if (players[0][i].getX() > -0.91) players[0][i].visible = true;
			if (&players[0][i] == selected) selectedIndex = i;
		}

		if (selectedIndex > 0) selected = &players[0][selectedIndex - 1];

		glutPostRedisplay();
	}

	if (k == GLUT_KEY_RIGHT && gameStarted
		&& players[0][players[0].getSize() - 1].getX() > -0.8
		&& animationComplete && !forceDraw && currentPlayer == 0 && winner == -1) {
		int selectedIndex = -1;

		for (size_t i = 0; i < players[0].getSize(); ++i) {
			players[0][i].setX(players[0][i].getX() - 0.2);
			if (players[0][i].getX() < -0.91) players[0][i].visible = false;
			if (&players[0][i] == selected) selectedIndex = i;
		}

		if (selectedIndex != players[0].getSize() - 1) selected = &players[0][selectedIndex + 1];

		glutPostRedisplay();
	}
}

//up, down, left, right operations during a player's wild card color choice
void specWildKey(int k, int x, int z) {
	if (k == GLUT_KEY_UP) {
		chosenColor = g;
	}

	if (k == GLUT_KEY_DOWN) {
		chosenColor = r;
	}

	if (k == GLUT_KEY_LEFT) {
		chosenColor = b;
	}

	if (k == GLUT_KEY_RIGHT) {
		chosenColor = y;
	}

	d.getCurrentPtr()->wildChangeColor(chosenColor);
	if (!initPlayerWild) moveTurns(d.getCurrent());
	else {
		moveTurns(*played, true);
		initPlayerWild = false;
	}
	chosenColor = noC;
	glutPostRedisplay();
	glutSpecialFunc(specKey);
}

//enter, space, c, d, r
void key(unsigned char k, int x, int y) {
	if (k == 13 && !gameStarted) { //enter
		gameStarted = true;

		if (playerCount >= 3) players.push_back(hand(2));
		if (playerCount == 4) players.push_back(hand(3));

		srand(time(nullptr));
		dealingPlayer = rand() % playerCount;
		currentPlayer = dealingPlayer; 

		glutTimerFunc(0, drawingRefresh, 0);
	}
	else if (k == 13 && animationComplete && currentPlayer == 0 && winner == -1) {
		int selectedIndex = -1;

		if (players[0].isMatch(*selected, d)) {
			CPUDrew = false;
			CPUPlaySimilar = false;
			playerDrewPlay = false;

			for (size_t i = 0; i < players[0].getSize(); ++i) {
				if (&players[0][i] == selected) {
					selectedIndex = i;
					break;
				}
			}

			played = new card(*selected);

			if (players[0].play(*selected, d)) {
				if (players[0].getSize() == 1 && playerFlaggedUNO && !players[0].getUNO()) {
					playerFlaggedUNO = false;
					players[currentPlayer].toggleUNO();
				}
				if (players[0].getSize() > 0) {
					if (selectedIndex == 0 || selectedIndex == players[0].getSize()) {
						players[0][0].setX(-0.9f);
						for (size_t i = 0; i < players[0].getSize(); ++i) {
							players[0][i].visible = true;
						}
					}
					drawHand(players[0]);
					if (selectedIndex < players[0].getSize()) selected = &players[0][selectedIndex];
					else selected = &players[0][0];

					if (played->getColor() == wild) {
						glutSpecialFunc(specWildKey);
					}
				}
			}

			glutPostRedisplay();
			if (played->getColor() != wild || players[0].getSize() == 0) {
				moveTurns(*played);
			}
		}
	}
	
	if (k == 32 && animationComplete && currentPlayer == 0 && winner == -1 && gameStarted) { //space
		if (players[currentPlayer].getSize() > 2) {
			forceDraw = true;
			playerUNOFail = true;
			numToDraw = 2;
			glutTimerFunc(500, handleTurn, 0);
			glutPostRedisplay();
		}
		else if (!players[currentPlayer].getUNO()){
			playerFlaggedUNO = true;
			glutPostRedisplay();
		}
	}

	if (k == 'c' && !gameStarted) {
		if (controlsShown) controlsShown = false;
		else controlsShown = true;
		glutPostRedisplay();
	}

	if (k == 'd' && currentPlayer == 0 && !drawing && winner == -1 && gameStarted) {
		CPUDrew = false;
		CPUPlaySimilar = false;

		drawing = true;
		if (drawToMatch) {
			forceDraw = true;
			glutTimerFunc(500, handleTurn, 0);
		}
		else {
			hand temp(-1);
			card newCard = d.draw();
			temp.add(newCard);
			players[0].add(newCard);
			if (temp.findMatch(d) != nullptr) {
				players[0].play(newCard, d);

				playerDrewPlay = true;

				if (newCard.getColor() != wild) moveTurns(newCard);
				else {
					played = &newCard;
					glutSpecialFunc(specWildKey);
				}
			}
			else {
				moveTurns(card());
				playerFlaggedUNO = false;
				if (players[0].getUNO()) players[0].toggleUNO();
			}
			glutTimerFunc(500, drawingRefresh, 0);
			drawing = false;
			if (!playerDrewPlay) {
				selected = &players[0][0];
				players[0][0].setX(-0.9f);
				for (size_t i = 0; i < players[0].getSize(); ++i) {
					players[0][i].visible = true;
				}
			}
		}
	}

	if (k == 'r' && gameStarted && winner != -1) {
		gameStarted = false;

		d = deck();
		
		initDraw = false;
		animationComplete = false;
		cardsAdded = 0;

		selected = nullptr;
		chosenColor = noC;
		played = nullptr;

		initPlayerWild = false;
		reversed = false;
		forceDraw = false;
		numToDraw = 0;
		winner = -1;
		drawing = false;

		delete temp;
		temp = new hand(-1);

		players[0] = hand(0);
		players[1] = hand(1);
		if (playerCount >= 3) players.erase(players.end() - 1);
		if (playerCount == 4) players.erase(players.end() - 1);
		playerCount = 2;

		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	srand(time(nullptr));

	init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("UNO: Nate's Version (PRE-ALPHA)");

	loadTex();

	glutKeyboardFunc(key);
	glutSpecialFunc(specKey);

	glutDisplayFunc(display);

	glutMainLoop();
	
	return 0;
}

//PRE-BOOT TESTING
void preTest() {
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
}

//displays a card
void drawCard(const card& c) {
	int index = -1;

	if (c.getColor() == wild) {
		if (c.getType() == w) index = START_OF_WILD;
		else index = START_OF_P4;
	}
	else if (c.getColor() == r) {
		if (c.getType() == num) index = START_OF_RED + c.getNum();
		else if (c.getType() == p2) index = START_OF_RED + 10;
		else if (c.getType() == rev) index = START_OF_RED + 11;
		else if (c.getType() == s) index = START_OF_RED + 12;
		else if (c.getType() == w) index = START_OF_WILD + 1;
		else if (c.getType() == p4) index = START_OF_P4 + 1;
	}
	else if (c.getColor() == y) {
		if (c.getType() == num) index = START_OF_YELLOW + c.getNum();
		else if (c.getType() == p2) index = START_OF_YELLOW + 10;
		else if (c.getType() == rev) index = START_OF_YELLOW + 11;
		else if (c.getType() == s) index = START_OF_YELLOW + 12;
		else if (c.getType() == w) index = START_OF_WILD + 2;
		else if (c.getType() == p4) index = START_OF_P4 + 2;
	}
	else if (c.getColor() == g) {
		if (c.getType() == num) index = START_OF_GREEN + c.getNum();
		else if (c.getType() == p2) index = START_OF_GREEN + 10;
		else if (c.getType() == rev) index = START_OF_GREEN + 11;
		else if (c.getType() == s) index = START_OF_GREEN + 12;
		else if (c.getType() == w) index = START_OF_WILD + 3;
		else if (c.getType() == p4) index = START_OF_P4 + 3;
	}
	else if (c.getColor() == b) {
		if (c.getType() == num) index = START_OF_BLUE + c.getNum();
		else if (c.getType() == p2) index = START_OF_BLUE + 10;
		else if (c.getType() == rev) index = START_OF_BLUE + 11;
		else if (c.getType() == s) index = START_OF_BLUE + 12;
		else if (c.getType() == w) index = START_OF_WILD + 4;
		else if (c.getType() == p4) index = START_OF_P4 + 4;
	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, index != -1 ? texID[index] : texID[0]);

	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(c.getX(), c.getY());
	glTexCoord2f(1.0, 0.0);
	glVertex2f(c.getX() + c.getW(), c.getY());
	glTexCoord2f(1.0, 1.0);
	glVertex2f(c.getX() + c.getW(), c.getY() + c.getH());
	glTexCoord2f(0.0, 1.0);
	glVertex2f(c.getX(), c.getY() + c.getH());

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//prints details of card (TESTING ONLY)
void debugCard(const card& c) {
	switch (c.getColor()) {
	case r:
		std::cout << "Red ";
		break;
	case y:
		std::cout << "Yellow ";
		break;
	case g:
		std::cout << "Green ";
		break;
	case b:
		std::cout << "Blue ";
		break;
	default:
		std::cout << "<COLOR ERROR> ";
		break;
	}

	switch (c.getType()) {
	case num:
		std::cout << c.getNum() << std::endl;
		break;
	case rev:
		std::cout << "Reverse\n";
		break;
	case s:
		std::cout << "Skip\n";
		break;
	case w:
		std::cout << "Wild\n";
		break;
	case p2:
		std::cout << "+2\n";
		break;
	case p4:
		std::cout << "+4\n";
		break;
	default:
		std::cout << "<TYPE ERROR>\n";
		break;

	}
}

//displays the player's hand
void drawHand(hand& h) {
	for (size_t i = 0; i < h.getSize(); ++i) {
		int index = -1;

		if (h[i].getColor() == wild) {
			if (h[i].getType() == w) index = START_OF_WILD;
			else index = START_OF_P4;
		}
		else if (h[i].getColor() == r) {
			if (h[i].getType() == num) index = START_OF_RED + h[i].getNum();
			else if (h[i].getType() == p2) index = START_OF_RED + 10;
			else if (h[i].getType() == rev) index = START_OF_RED + 11;
			else if (h[i].getType() == s) index = START_OF_RED + 12;
			else if (h[i].getType() == w) index = START_OF_WILD + 1;
			else if (h[i].getType() == p4) index = START_OF_P4 + 1;
		}
		else if (h[i].getColor() == y) {
			if (h[i].getType() == num) index = START_OF_YELLOW + h[i].getNum();
			else if (h[i].getType() == p2) index = START_OF_YELLOW + 10;
			else if (h[i].getType() == rev) index = START_OF_YELLOW + 11;
			else if (h[i].getType() == s) index = START_OF_YELLOW + 12;
			else if (h[i].getType() == w) index = START_OF_WILD + 2;
			else if (h[i].getType() == p4) index = START_OF_P4 + 2;
		}
		else if (h[i].getColor() == g) {
			if (h[i].getType() == num) index = START_OF_GREEN + h[i].getNum();
			else if (h[i].getType() == p2) index = START_OF_GREEN + 10;
			else if (h[i].getType() == rev) index = START_OF_GREEN + 11;
			else if (h[i].getType() == s) index = START_OF_GREEN + 12;
			else if (h[i].getType() == w) index = START_OF_WILD + 3;
			else if (h[i].getType() == p4) index = START_OF_P4 + 3;
		}
		else if (h[i].getColor() == b) {
			if (h[i].getType() == num) index = START_OF_BLUE + h[i].getNum();
			else if (h[i].getType() == p2) index = START_OF_BLUE + 10;
			else if (h[i].getType() == rev) index = START_OF_BLUE + 11;
			else if (h[i].getType() == s) index = START_OF_BLUE + 12;
			else if (h[i].getType() == w) index = START_OF_WILD + 4;
			else if (h[i].getType() == p4) index = START_OF_P4 + 4;
		}

		if (i > 0) h[i].setX(h[i - 1].getX() + 0.2);

		if (&h[i] == selected) {
			glBegin(GL_POLYGON);

			glColor3f(0, 1, 0);
			glVertex2f(h[i].getX() - 0.035, h[i].getY() + h[i].getH() + 0.035);
			glVertex2f(h[i].getX() + h[i].getW() + 0.035, h[i].getY() + h[i].getH() + 0.035);
			glVertex2f(h[i].getX() + h[i].getW() + 0.035, h[i].getY() - 0.035);
			glVertex2f(h[i].getX() - 0.035, h[i].getY() - 0.035);

			glEnd();
		}

		if (h[i].visible) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, index != -1 ? texID[index] : texID[0]);

			glBegin(GL_POLYGON);

			glTexCoord2f(0.0, 0.0);
			glVertex2f(h[i].getX(), h[i].getY());
			glTexCoord2f(1.0, 0.0);
			glVertex2f(h[i].getX() + h[i].getW(), h[i].getY());
			glTexCoord2f(1.0, 1.0);
			glVertex2f(h[i].getX() + h[i].getW(), h[i].getY() + h[i].getH());
			glTexCoord2f(0.0, 1.0);
			glVertex2f(h[i].getX(), h[i].getY() + h[i].getH());

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
}

//inital wild choice if CPU is given first card wild
void initWild(const hand& p, card* c) {
	int red = 0;
	int yellow = 0;
	int green = 0;
	int blue = 0;

	for (int i = 0; i < p.getSize(); ++i) {
		int val = 0;
		if (p[i].getType() == num && p[i].getType() != wild) {
			val += p[i].getNum();
		}
		else if (p[i].getType() != wild) {
			val += 10;
		}

		if (p[i].getColor() == r) red += val;
		else if (p[i].getColor() == y) yellow += val;
		else if (p[i].getColor() == g) green += val;
		else if (p[i].getColor() == b) blue += val;
	}

	srand(time(nullptr));
	if (red == yellow == green == blue) {
		int random = rand() % 4;
		if (random == 0) c->wildChangeColor(r);
		else if (random == 1) c->wildChangeColor(y);
		else if (random == 2) c->wildChangeColor(g);
		else if (random == 3) c->wildChangeColor(b);
	}
	else {
		int random = rand() % 4;

		int maxVal = 0;

		if (random == 0) {
			maxVal = red;
			c->wildChangeColor(r);
		}
		else if (random == 1) {
			maxVal = yellow;
			c->wildChangeColor(y);
		}
		else if (random == 2) {
			maxVal = green;
			c->wildChangeColor(g);
		}
		else if (random == 3) {
			maxVal = blue;
			c->wildChangeColor(b);
		}

		if (red > maxVal) {
			maxVal = red;
			c->wildChangeColor(r);
		}
		else if (yellow > maxVal) {
			maxVal = yellow;
			c->wildChangeColor(y);
		}
		else if (green > maxVal) {
			maxVal = green;
			c->wildChangeColor(g);
		}
		else if (blue > maxVal) {
			maxVal = blue;
			c->wildChangeColor(b);
		}
	}
}

//moves turns after a card is played
void moveTurns(const card& c, bool forceRev) {
	if (players[currentPlayer].getSize() == 0) {
		winner = currentPlayer; selected = nullptr;
	}

	if (players[currentPlayer].getSize() == 1 &&
		!players[currentPlayer].isCPU() &&
		!players[currentPlayer].getUNO()) {
		forceDraw = true;
		playerUNOFail = true;
		numToDraw = 2;
		std::cout << "Player " << currentPlayer << " is required to draw 2 cards for failing to UNO!\n"; //DEBUG
		glutTimerFunc(1000, handleTurn, 0);
		glutPostRedisplay();
		return;
	}

	if (playerCount == 2) {
		if (c.getType() != rev && c.getType() != s) currentPlayer = (currentPlayer + 1) % 2;

		if (c.getType() == p2 || c.getType() == p4) {
			forceDraw = true;
			if (c.getType() == p2) numToDraw = 2;
			else numToDraw = 4;
			std::cout << "Player " << currentPlayer << " is required to draw " << numToDraw << " cards!\n"; //DEBUG
		}
	}
	else {
		if (c.getType() == rev) {
			if (reversed) reversed = false;
			else reversed = true;
		}
		if (reversed) {
			if (c.getType() == s) {
				if (currentPlayer == 0) currentPlayer = 2;
				else if (currentPlayer == 1 && playerCount == 3) currentPlayer = 0;
				else if (currentPlayer == 1 && playerCount == 4) currentPlayer = 3;
				else if (currentPlayer == 2) currentPlayer = 0;
				else if (currentPlayer == 3) currentPlayer = 1;
			}
			else {
				if (currentPlayer == 0 && playerCount == 4) currentPlayer = 3;
				else if (currentPlayer == 0 && playerCount == 3) currentPlayer = 2;
				else if (currentPlayer == 1) currentPlayer = 0;
				else if (currentPlayer == 2) currentPlayer = 1;
				else if (currentPlayer == 3) currentPlayer = 2;
			}

			if (c.getType() == p2 || c.getType() == p4) {
				forceDraw = true;
				if (c.getType() == p2) numToDraw = 2;
				else numToDraw = 4;
			}
		}
		else {
			if (c.getType() == s) currentPlayer = (currentPlayer + 2) % playerCount;
			else if (!forceRev) currentPlayer = (currentPlayer + 1) % playerCount;
			else currentPlayer = (std::abs(currentPlayer - 1)) % playerCount;
			

			if (c.getType() == p2 || c.getType() == p4) {
				forceDraw = true;
				if (c.getType() == p2) numToDraw = 2;
				else numToDraw = 4;
			}
		}
	}
	if (players[currentPlayer].isCPU() || forceDraw) glutTimerFunc(1000, handleTurn, 0);
	glutPostRedisplay();
}

//refreshes the screen during the initial draw
void drawingRefresh(int) {
	if (cardsAdded < 7 * playerCount) {
		glutPostRedisplay();
		glutTimerFunc(500, drawingRefresh, 0);
	}
	else if (cardsAdded == 7 * playerCount) {
		glutPostRedisplay();
		animationComplete = true;
	}
}

//preforms card drawing operations and plays CPU cards
void handleTurn(int) {
	if (currentPlayer != 0) { //CPU
		CPUDrew = false;
		CPUPlaySimilar = false;

		if (forceDraw) {
			if (players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO();

			players[currentPlayer].add(d.draw());
			--numToDraw;
			if (numToDraw == 0) {
				forceDraw = false;
				moveTurns(card());
			}
			else {
				glutPostRedisplay();
				glutTimerFunc(750, handleTurn, 0);
			}
		}
		else if (winner == -1) {
			card* c = players[currentPlayer].findMatch(d);
			card played;
			if (c) {
				while (c->getColor() == wild) { c = players[currentPlayer].findMatch(d); }
				played = *c;
				if (played == d.getCurrent() &&
					played.getType() != p2 &&
					played.getType() != p4) CPUPlaySimilar = true;
				else CPUPlaySimilar = false;
				std::cout << "CPU match with: "; //DEBUG
				debugCard(played); //DEBUG
			}
			if (c && players[currentPlayer].play(*c, d)) {
				std::cout << "CPU officially plays: "; //DEBUG
				debugCard(played); //DEBUG

				if (players[currentPlayer].getSize() == 1) {
					//int chance = rand() % 3;
					//if (chance == 0 && !players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO();
					if (!players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO(); //FOR ALPHA ONLY
				}

				moveTurns(played);
			}
			else {
				if (drawToMatch) { //NEEDS LOOKED AT (check out player drawToMatch rules (else if (forceDraw)), need to add UNO rules)
					card newCard = d.draw();
					players[currentPlayer].add(newCard);
					temp->add(newCard);
					if (temp->findMatch(d) != nullptr) {
						if (newCard == d.getCurrent()) CPUPlaySimilar = true;
						players[currentPlayer].play(newCard, d);
						forceDraw = false;
						moveTurns(newCard);

						delete temp;
						temp = new hand(-1);
					}
				}
				else {
					players[currentPlayer].add(d.draw());
					c = players[currentPlayer].findMatch(d);
					if (c) {
						played = *c;
						if (played == d.getCurrent() &&
							played.getType() != p2 &&
							played.getType() != p4) CPUPlaySimilar = true;
						else CPUPlaySimilar = false;
						std::cout << "CPU drew and matched with: "; //DEBUG
						debugCard(played); //DEBUG
					}
					else {
						std::cout << "CPU no match.\n";
						CPUDrew = true;
						if (players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO();
					}

					if (c && players[currentPlayer].play(*c, d)) {
						std::cout << "CPU officially plays: "; //DEBUG
						debugCard(played); //DEBUG

						if (players[currentPlayer].getSize() == 1) {
							//int chance = rand() % 3;
							//if (chance == 0 && !players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO();
							if (!players[currentPlayer].getUNO()) players[currentPlayer].toggleUNO(); //FOR ALPHA ONLY
						}

						moveTurns(played);
					}
					else moveTurns(card());
				}
			}
			playerDrewPlay = false;
			glutPostRedisplay();
		}
	}
	else { //actual player (drawing cards only)
		if (forceDraw && numToDraw > 0) {
			players[0][0].setX(-0.9f);
			for (size_t i = 0; i < players[0].getSize(); ++i) {
				players[0][i].visible = true;
			}
			drawHand(players[0]);
			selected = &players[0][0];

			if (players[0].getUNO()) players[0].toggleUNO();

			players[0].add(d.draw());
			--numToDraw;
			if (numToDraw == 0) {
				forceDraw = false;
				playerUNOFail = false;
				if (!playerUNOFail) moveTurns(card());
				else moveTurns(d.getCurrent());
				selected = &players[0][0];
			}
			else {
				glutPostRedisplay();
				glutTimerFunc(750, handleTurn, 0);
			}
		}
		else if (forceDraw) {
			players[0][0].setX(-0.9f);
			for (size_t i = 0; i < players[0].getSize(); ++i) {
				players[0][i].visible = true;
			}
			drawHand(players[0]);
			selected = &players[0][0];

			if (players[0].getUNO()) players[0].toggleUNO();

			card newCard = d.draw();
			players[0].add(newCard);
			temp->add(newCard);
			if (temp->findMatch(d) != nullptr) {
				players[0].play(newCard, d);
				forceDraw = false;
				playerDrewPlay = true;
				moveTurns(newCard);

				delete temp;
				temp = new hand(-1);
			}

			drawing = false;

			glutPostRedisplay();
			glutTimerFunc(750, handleTurn, 0);
		}
	}
}