#include <stdio.h>
#include <vector>
#include "GL/freeglut.h"
#include <math.h>

struct pt { double x; double y; };
int width = 500, height = 500;
int arrowIdx = 0;
double PI = 3.14159265;
std::vector<pt> pts;

void DrawObject() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glEnd();
	glColor3f(0, 1, 0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();

	glLineWidth(1.0);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.2, 20, 20);
	glPushMatrix();
	glRotatef(arrowIdx, 0, 0, 1);
	glTranslatef(0.5, 0, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(0.1, 20, 20);
	glPushMatrix();
	glRotatef(arrowIdx * 5, 0, 0, 1);
	glTranslatef(0.4, 0, 0);
	glColor3f(0, 0, 1);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	
	glRotatef(arrowIdx * 10, 0, 0, 1);
	glTranslatef(0.15, 0, 0);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.01, 20, 20);
	

	glPopMatrix();

	glutSwapBuffers();


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

void Timer(int value)
{
	if (arrowIdx < 100)
		arrowIdx++;
	else
		arrowIdx = 0;
	glutTimerFunc(30, Timer, 1);
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
	int mode = GLUT_RGB | GLUT_DOUBLE;

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
	//glutTimerFunc(1, Timer, 1);
	glutMainLoop();
}
