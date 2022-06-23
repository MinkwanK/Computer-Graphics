#include <stdio.h>
#include <vector>
#include "GL/freeglut.h"
#include <math.h>

//#include "CGLab.h"


//Callback: 다른 코드의 인수로서 넘겨주는 실행 가능한 코드
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
    glClear(GL_COLOR_BUFFER_BIT); //그림을 그리기 위해 필요한 색깔 버퍼 비운다.

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
    case GLUT_KEY_UP: //올라가는 화살표
        arrowIdx++;
        break;
    case GLUT_KEY_DOWN: //올라가는 화살표
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

    double xd, yd;          //winodws상에 찍힌 마우스 좌표를 Opengl 상의 좌표로 변환한다.
    xd = x / 500.0 * 4.0 - 2.0;
                                //500 은 좌표를 1로 정규화 [0,1] *4 하면 [0,4] -2하면 [-2,2] 가 된다.
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
    glutDisplayFunc(DrawObject); //윈도우 창을 열때 그릴려고 창을 열때 불러옴
    glutKeyboardFunc(KeyDown); //키보드 키(ASCII문자)랑 마우스 위치 함께 전달
    glutMouseFunc(Mouse);      //마우스 버튼,상태(눌렀는지,손뗐는지),xy좌표 보내줌 눌렀다 떼면 두번 호출
                                 //3 wheel down 4 wheel up
    glutSpecialFunc(KeySpecial); //GLUT_KEY_* 상수(화살표,F1~F12) , 마우스 위치
    glutMotionFunc(Motion); //클릭을 하면서 이동을 하면 이동을 하는 매 순간마다 호출, passive motion  은 클릭 안했을때
    glutIdleFunc(DrawObject);
 
    glutMainLoop();
    return 0;
}