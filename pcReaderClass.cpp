#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "gl/freeglut.h"

float g_fDistance = -1.0f;
float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

struct pt { double x, y, z; };
std::vector<pt> pts;

using namespace std;
ifstream bunny;
pt* bunnydata;
struct aabb { double minx=0, maxx=0, miny=100, maxy=0, minz=100, maxz=0; };
aabb aabbdata;
int amount;

//mix max 두 개의 포인트로 결정 
//AABB를 설정하려면, 해당 물체의 x, y, z축 방향으로의 최대, 최소값만 알면 됩니다. 
//그 값들의 조합으로 나오는 8가지의 점( x값 2개 * y값 2개 * z값 2개 = 8개 )으로 정의된 상자가 그 물체의 AABB입니다

void LoadFile() //min max 두 개의 포인트 구하기 
{
    bunny.open("bunnyData.pts");
    bunny >> amount;
    bunnydata = (pt*)malloc(sizeof(pt) * amount);
    for (int i = 0; i < amount;i++)
    {
        bunny >> bunnydata[i].x;
        if (bunnydata[i].x < aabbdata.minx)
            aabbdata.minx = bunnydata[i].x;
        if (bunnydata[i].x > aabbdata.maxx)
            aabbdata.maxx = bunnydata[i].x;

        bunny >> bunnydata[i].y;
        if (bunnydata[i].y < aabbdata.miny)
            aabbdata.miny = bunnydata[i].y;
        if (bunnydata[i].y > aabbdata.maxy)
            aabbdata.maxy = bunnydata[i].y;

        bunny >> bunnydata[i].z;
        if (bunnydata[i].z < aabbdata.minz)
            aabbdata.minz = bunnydata[i].z;
        if (bunnydata[i].z > aabbdata.maxz)
            aabbdata.maxz = bunnydata[i].z;
    }
}

void DrawModel(void) { //여기서 바운딩 박스 그리기 

    glColor3f(1, 1, 1);
    for(int i=0;i<amount;i++)
    {
       
        glBegin(GL_POINTS);
        glVertex3d(bunnydata[i].x, bunnydata[i].y, bunnydata[i].z);
        glEnd();
    }
    //반시계방향 정면 시계방향 정면 

        glColor3f(0, 0, 1);
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.maxz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.maxz);
        glEnd();
       
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.minz);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.minz);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.maxz);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.maxz);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.maxz);
        glVertex3d(aabbdata.minx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.minz);
        glVertex3d(aabbdata.minx, aabbdata.miny, aabbdata.maxz);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.minz);
        glVertex3d(aabbdata.maxx, aabbdata.maxy, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.maxz);
        glVertex3d(aabbdata.maxx, aabbdata.miny, aabbdata.minz);
        glEnd();
       
       
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, g_fDistance);
    glRotatef(-g_fSpinY, 1.0f, 0.0f, 0.0f);
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);

    DrawModel();

    glutPostRedisplay();
    glutSwapBuffers();
}

void MyInit() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    LoadFile();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MySpecial(int key, int x, int y) {
    if (key == GLUT_KEY_PAGE_UP)
    {
        g_fDistance -= 0.1f;
    }
    else if (key == GLUT_KEY_PAGE_DOWN)
    {
        g_fDistance += 0.1f;
    }

    glutPostRedisplay();
}

void MyMouse(int button, int state, int x, int y) {
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            ptLastMousePosit.x = ptCurrentMousePosit.x = x;
            ptLastMousePosit.y = ptCurrentMousePosit.y = y;
            bMousing = true;
        }
        else
            bMousing = false;
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void MyMotion(int x, int y) {
    ptCurrentMousePosit.x = x;
    ptCurrentMousePosit.y = y;

    if (bMousing)
    {
        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Point Cloud Renderer");
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouse);
    glutMotionFunc(MyMotion);
    glutSpecialFunc(MySpecial);

    MyInit();

    glutMainLoop();
    return 0;
}