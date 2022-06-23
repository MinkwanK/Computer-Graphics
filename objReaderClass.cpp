#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "gl/freeglut.h"



float g_fDistance = -200.0f;
float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

struct pt { double x, y, z; };

struct face { int i[3]; int n[3]; };
std::vector<pt> pts;
std::vector<pt> normals;
std::vector<face> faces;


void parse(const std::string& str, std::vector<std::string>& values, std::string& delimiter)
{
    std::string::size_type Fpos = str.find_first_not_of(delimiter, 0); 
    std::string::size_type Lpos = str.find_first_of(delimiter, Fpos);
    while(std::string::npos != Fpos || std::string::npos != Lpos)
    {
        values.push_back(str.substr(Fpos, Lpos - Fpos));
        Fpos = str.find_first_not_of(delimiter, Lpos);
        Lpos = str.find_first_of(delimiter, Fpos);
    }
}

void LoadFile() //파스를 통해 데이터를 분리하고 이를 오브젝트 데이터 형식에 맞춰 걸러서 정보를 받아오면 된다.
{
    std::string fileName = "bunny.obj";
    std::ifstream ifs(fileName);
    if(ifs.fail())
    std::cerr << "File read error!" << std::endl;
    char line[100];
    std::string delimiter = " ";
    std::string slash = "/";
    int cnt = 0;
	while(!ifs.eof())
    {
        ifs.getline(line, 100);
        std::string s = line;
        std::vector<std::string>values; //정보를 받기위한 vector 변수
     



        //Use this code below or make your nice code!
        if(s[0] == '#')
            printf("Comment : %s\n", s.c_str()); //이건 주석
        else if(s[0] == 'v' && s[1] != 't' && s[1] != 'n')
        {
            parse(line, values, delimiter); //values vector 변수에 line 을 " " 를 구분으로 받는다.
            pt temp;
            temp.x = std::stod(values[1]);
            temp.y = std::stod(values[2]);
            temp.z = std::stod(values[3]);
            pts.push_back(temp);
            
        }
        else if(s[0] == 'v' && s[1] == 'n')
        {
            parse(line, values, delimiter); //values vector 변수에 line 을 " " 를 구분으로 받는다.
            pt temp;
            temp.x = std::stod(values[1]);
            temp.y = std::stod(values[2]);
            temp.z = std::stod(values[3]);
            normals.push_back(temp);
        }
        else if(s[0] == 'f')
		{
            std::string line1;
            std::string line2;
            std::string line3;
            parse(line, values, delimiter); //values vector 변수에 line 을 "/" 를 구분으로 받는다.
            line1 = values[1];
            line2 = values[2];
            line3 = values[3];
            parse(line1, values, slash);
            parse(line2, values, slash);
            parse(line3, values, slash);
            face temp;
     
            temp.i[0] = std::stoi(values[4])-1;
            temp.n[0] = std::stoi(values[5])-1;
            temp.i[1] = std::stoi(values[6])-1;
            temp.n[1] = std::stoi(values[7])-1;
            temp.i[2] = std::stoi(values[8])-1;
            temp.n[2] = std::stoi(values[9])-1;
            
            faces.push_back(temp);
        
           
		}
		else
		{
            printf("Not processed : %s\n", s.c_str());
        }
    }

    std::cout << "dsd" << std::endl;
}

void DrawModel(void) {

   
    for(auto f : faces)
    {
        glBegin(GL_POLYGON);
        for(int i=0;i<3;i++)
        {
            int idx = f.i[i];
            int nIdx = f.n[i];
            auto v = pts[idx];
            auto n = normals[nIdx];
            glNormal3d(n.x, n.y, n.z);
            glVertex3d(v.x, v.y, v.z);
        }
        glEnd();
    }
  
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, g_fDistance);
    glRotatef(-g_fSpinY, 1.0f, 0.0f, 0.0f);
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);

    //	glRotatef(-90.0, 1.0, 0.0, 0.0);
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

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
    if(key == GLUT_KEY_PAGE_UP)
    {
        g_fDistance -= 5.0f;
    }
    else if(key == GLUT_KEY_PAGE_DOWN)
    {
        g_fDistance += 5.0f;
    }

    glutPostRedisplay();
}

void MyMouse(int button, int state, int x, int y) {
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
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

    if(bMousing)
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
    glutCreateWindow("OBJ Loader");
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouse);
    glutMotionFunc(MyMotion);
    glutSpecialFunc(MySpecial);

    MyInit();

    glutMainLoop();
    return 0;
}