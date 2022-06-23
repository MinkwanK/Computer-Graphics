#include <stdio.h>
#include <vector>
#include "GL/freeglut.h"
#include <math.h>

//#include "CGLab.h"


//Callback: �ٸ� �ڵ��� �μ��μ� �Ѱ��ִ� ���� ������ �ڵ�
struct pt { double x; double y; };
int width = 500, height = 500;
int arrowIdx = 0;
double PI = 3.14159265;
std::vector<pt> pts;
double TopX = 0.0, TopY = 0.0, BottomX = 0.0, BottomY = 0.0;
using namespace std;

/*
void makePolygon()
{
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0;i < arrowIdx;i++)
    {
        glVertex2d(x, y);
    }
    glEnd();
}
*/
void DrawCircle()
{
    double radius = 1.0;
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0;i < arrowIdx;i++)
    {
        double theta = PI * 2.0 * double(i) / double(50);
        double x = radius * cos(theta);
        double y = radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}


void DrawObject() {
    glClear(GL_COLOR_BUFFER_BIT); //�׸��� �׸��� ���� �ʿ��� ���� ���� ����.

    glLineWidth(3.0);

    DrawCircle();
    /*
    glBegin;
    glColor3f(0, 1, 0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < pts.size(); i++)
    {
        glVertex2d(pts[i].x, pts[i].y);
    }
    glEnd();
    */
    glFlush();
}



void KeyDown(unsigned char key, int x, int y)
{
    switch (key) {
    case 'p': case 'P':
        printf("Hello world!\n");
        break;
    case 'r': case 'R':
        pts.erase(pts.begin(), pts.end());
    }
    glutPostRedisplay();
}
void KeySpecial(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: //�ö󰡴� ȭ��ǥ
        arrowIdx++;
        break;
    case GLUT_KEY_DOWN: //�ö󰡴� ȭ��ǥ
        arrowIdx--;
        break;
    }
    glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        TopX = x / 500.0 * 4.0 - 2.0;
        TopY = y / 500.0 * 4.0 - 2.0;

        pts.push_back({ TopX, -TopY });
        printf("Mouse Click (%f %f)\n", TopX, TopY);

    }
    glutPostRedisplay();
}

void Motion(int x, int y)
{
    printf("Mouse motion (%d %d)\n", x, y);

    double xd, yd;          //winodws�� ���� ���콺 ��ǥ�� Opengl ���� ��ǥ�� ��ȯ�Ѵ�.
    xd = x / 500.0 * 4.0 - 2.0;
                                //500 �� ��ǥ�� 1�� ����ȭ [0,1] *4 �ϸ� [0,4] -2�ϸ� [-2,2] �� �ȴ�.
    yd = y / 500.0 * 4.0 - 2.0;
    yd *= -1.0;

    pts.push_back({ xd, yd });
    glutPostRedisplay();
}

void Init()
{
    glViewport(0, 0, width, height);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    //left,right,bottom,top,near,far 
}

int main(int argc, char** argv) {
    int mode = GLUT_RGB | GLUT_SINGLE;
    pts.push_back({ -2.0,0 });


    glutInit(&argc, argv);
    glutInitDisplayMode(mode);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL");
    glutSetWindowTitle("DAU CG");
    Init();
    glutDisplayFunc(DrawObject); //������ â�� ���� �׸����� â�� ���� �ҷ���
    glutKeyboardFunc(KeyDown); //Ű���� Ű(ASCII����)�� ���콺 ��ġ �Բ� ����
    glutMouseFunc(Mouse);      //���콺 ��ư,����(��������,�նô���),xy��ǥ ������ ������ ���� �ι� ȣ��
                                 //3 wheel down 4 wheel up
    glutSpecialFunc(KeySpecial); //GLUT_KEY_* ���(ȭ��ǥ,F1~F12) , ���콺 ��ġ
    glutMotionFunc(Motion); //Ŭ���� �ϸ鼭 �̵��� �ϸ� �̵��� �ϴ� �� �������� ȣ��, passive motion  �� Ŭ�� ��������
    glutIdleFunc(DrawObject);
 
    glutMainLoop();
    return 0;
}