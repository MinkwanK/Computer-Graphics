#include <stdio.h>
#include <vector>
#include "GL/freeglut.h"
#include <math.h>
//#include "CGLab.h"

struct pt { double x; double y; };
int width = 500, height = 500;
int arrowIdx = 0;
double PI = 3.14159265;
std::vector<pt> pts;

void DrawObject() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 10.0);
	//사물의 위치, 사람의 시점을 책임지는 공간이 GL_MODEVIEW이다. 앞으로 나오는 식이 이 공간에 영향을 미친다는 뜻
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, width / 2, height / 2);
	glLoadIdentity();
	//gluLookAt(0, 5, 0, 0, 0, 0, 0, 1, 0);
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, 1); 
	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);


	glViewport(width / 2, 0, width / 2, height / 2);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	glViewport(0, height/2, width / 2, height / 2);
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	glViewport(width/2, height / 2, width / 2, height / 2);
	glLoadIdentity();
	gluLookAt(5, 0, 0, 0, 0, 0, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	glFlush();
}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p': case 'P':
		printf("Hello world!\n");
		break;
	}
	glutPostRedisplay();
}
void KeySpecial(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		arrowIdx++;
		break;
	case GLUT_KEY_DOWN:
		arrowIdx--;
		break;
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		printf("Mouse Click (%d %d)\n", x, y);

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	printf("Mouse motion (%d %d)\n", x, y);

	double xd, yd;
	xd = x / 500.0 * 4.0 - 2.0;
	yd = y / 500.0 * 4.0 - 2.0;
	yd *= -1.0;

	glutPostRedisplay();
}

void Init()
{
	glViewport(0, 0, width, height);
	glClearColor(1.0, 1.0, 1.0, 1.0);

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