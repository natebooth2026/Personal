#include <GL/glut.h>
#include <iostream>

#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600
#define WIN_W 600

GLfloat scale = 0.5;
bool reversed = false;
bool polyToggle = false;

void init(void) {

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void oper(double& x, double& y, double m) {
	if (reversed) x -= m;
	else x += m;

	y = std::sin((x >= 1 && !reversed) ? std::acos(1) : std::acos(x));
	if (reversed) y *= -1;
	

	if (x >= 1 && !reversed) reversed = true;
	if (x <= -1 && reversed) reversed = false;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	double x = -1;
	double y = std::sin(std::acos(x));
	glBegin(polyToggle ? GL_POLYGON : GL_LINE_LOOP);
	glVertex3f(x * scale, y * scale, 0);
	for (int i = 0; i < 400000; ++i) {
		oper(x, y, 0.00001);
	
		if (i % 3 == 0) glColor3f(1, 0, 0);
		if (i % 3 == 1) glColor3f(0, 1, 0);
		if (i % 3 == 2) glColor3f(0, 0, 1);
		if (i == 0 || i == 399999) glColor3f(0.5, 0.5, 0.5);

		glVertex3f(x * scale, y * scale, 0);
	}
	glEnd();
	glFlush();
}

void key(unsigned char k, int x, int y) {
	if (k == 32) {
		if (polyToggle) {
			polyToggle = false;
		}
		else {
			polyToggle = true;
		}

		display();
	}

	if (k == 'r') {
		polyToggle = false;
		scale = 0.5;
		display();
	}
}

void specKey(int k, int x, int y) {
	if (k == GLUT_KEY_UP) {
		if ((scale < 1.415 && !polyToggle) || polyToggle) {
			scale += 0.005;
		}
	}

	if (k == GLUT_KEY_DOWN) {
		if (scale > 0.005) scale -= 0.005;
	}

	display();
}

int main(int argc, char** argv) {
	srand(time(nullptr));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WIN_W, WIN_H);
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("hey epic circle");

	init();

	glutKeyboardFunc(key);
	glutSpecialFunc(specKey);

	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}