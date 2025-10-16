// Shape Drawer
// A Nate Booth Prodcuction
// April 28th, 2024

#ifndef SHAPES_HPP
#define SHAPES_HPP

//base
class Shape {
public:
	Shape() : sX(0), sY(0) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				graphic[i][j] = ' ';
			}
		}
	}
	Shape(int x, int y) : sX(x), sY(y) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				graphic[i][j] = ' ';
			}
		}
	}
	virtual ~Shape() {}

	int getX() const { return sX; }
	int getY() const { return sY; }
	char getGraphic(int row, int column) { return graphic[row][column]; }

	virtual void craft() = 0;
protected:
	char graphic[5][5];
	int sX;
	int sY;
};

//derived shapes
class Square : public Shape {
public:
	Square() : Shape() {}
	Square(int x, int y) : Shape(x, y) {}

	void craft() {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (i == 0
					|| i == 4
					|| (i > 0 && i < 4 && (j == 0 || j == 4))) {
					graphic[i][j] = 'S';
				}
				else {
					graphic[i][j] = ' ';
				}
			}
		}
	}
};

class Circle : public Shape {
public:
	Circle() : Shape() {}
	Circle(int x, int y) : Shape(x, y) {}

	void craft() {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (((i == 0 || i == 4) && (j != 0 && j != 4))
					|| ((i > 0 && i < 4) && (j == 0 || j == 4))) {
					graphic[i][j] = 'C';
				}
				else {
					graphic[i][j] = ' ';
				}
			}
		}
	}
};

enum triangleType { topLeft, topRight, bottomLeft, bottomRight, none }; //indicates location of the hypotenuse

class Triangle : public Shape {
public:
	Triangle() : Shape(), type(none) {}
	Triangle(int x, int y, triangleType t) : Shape(x, y), type(t) {}

	void craft() {
		switch (type) {
		case topLeft:
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (j == 4
						|| (i == 1 && j > 2)
						|| (i == 2 && j == 2)
						|| (i == 3 && j == 1)
						|| i == 4) {
						graphic[i][j] = 'T';
					}
					else {
						graphic[i][j] = ' ';
					}
				}
			}
			break;
		case topRight:
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (j == 0
						|| (i == 1 && j < 2)
						|| (i == 2 && j == 2)
						|| (i == 3 && j == 3)
						|| i == 4) {
						graphic[i][j] = 'T';
					}
					else {
						graphic[i][j] = ' ';
					}
				}
			}
			break;
		case bottomLeft:
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (i == 0
						|| (i == 1 && j == 1)
						|| (i == 2 && j == 2)
						|| (i == 3 && j > 2)
						|| j == 4) {
						graphic[i][j] = 'T';
					}
					else {
						graphic[i][j] = ' ';
					}
				}
			}
			break;
		case bottomRight:
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (i == 0
						|| (i == 1 && j == 3)
						|| (i == 2 && j == 2)
						|| (i == 3 && j < 2)
						|| j == 0) {
						graphic[i][j] = 'T';
					}
					else {
						graphic[i][j] = ' ';
					}
				}
			}
			break;
		}
	}
private:
	triangleType type;
};

#endif
