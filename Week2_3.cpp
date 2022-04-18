#include <stdio.h>
#include <vector>
#include "GL/freeglut.h"
#include <math.h>

struct pt { double x; double y; };
int width = 500, height = 500;
int arrowIdx = 5;
double PI = 3.14159265;
std::vector<pt> pts;
double mx, my;


void DrawObject() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(0, 1, 0);
	pts.push_back({ 0.0, 0.0 });
	glBegin(GL_POINTS);
	for (int i = 0; i < pts.size(); i++)
	{
		glVertex2d(pts[i].x, pts[i].y);
	}
	glEnd();
	glFlush();
}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p': case 'P':
		printf("Hello world!\n");
		break;
	case 'r' : case 'R':
		pts.erase(pts.begin(), pts.end());
	}

	glutPostRedisplay();
}
void KeySpecial(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		printf("Up");
		arrowIdx++;
		break;
	case GLUT_KEY_DOWN:
		printf("Down");
		arrowIdx--;
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		printf("Mouse Click (%d %d)\n", x, y);
	
	mx = x / 500.0 * 4.0 - 2.0;
	my = y / 500.0 * 4.0 - 2.0;
	pts.push_back({ mx,-my });
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	printf("Mouse motion (%d %d)\n", x, y);

	double xd, yd;
	xd = x / 500.0 * 4.0 - 2.0;
	yd = y / 500.0 * 4.0 - 2.0;
	yd *= -1.0;
	
	pts.push_back({ xd,yd });
	glutPostRedisplay();
}

void Init()
{
	glViewport(0, 0, width, height);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	int mode = GLUT_RGB | GLUT_SINGLE;

	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL");
	glutSetWindowTitle("DAU CG");

	Init();
	glutDisplayFunc(DrawObject);
	glutKeyboardFunc(KeyDown);
	glutMouseFunc(Mouse);
	glutSpecialFunc(KeySpecial);
	glutMotionFunc(Motion);
	glutIdleFunc(DrawObject);
	glutMainLoop();
}