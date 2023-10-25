#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define SLEEP_TIME1 30
#define SLEEP_TIME2 20
#define SLEEP_TIME3 60
#define SLEEP_TIME4 80
#define SLEEP_TIME5 20
#define SLEEP_TIME6 90

#define SLEEP_TIME_Collision 1

const int WWIDTH = 500;
const int WHEIGHT = 500;

// frog
float frog[] = {0,-0.9};
float r = 0.05;

// lives
float life1[] = {-0.9, 0.9};
float life2[] = {-0.7, 0.9};
float life3[] = {-0.5, 0.9};

int count_lives = 0;

// draw original car for road 1
float Road1_TopLeft[] = {-0.125, -0.65};
float Road1_TopRight[] = {0.125, -0.65};
float Road1_BottomRight[] = {0.125, -0.75};
float Road1_BottomLeft[] = {-0.125, -0.75};
float Road1_Seperation = 0.55;

// draw original car for road 2
float Road2_TopLeft[] = {-0.125, -0.45};
float Road2_TopRight[] = {0.125, -0.45};
float Road2_BottomRight[] = {0.125, -0.55};
float Road2_BottomLeft[] = {-0.125, -0.55};
float Road2_Seperation = 0.75;

// draw original car for road 3
float Road3_TopLeft[] = {-0.125, -0.25};
float Road3_TopRight[] = {0.125, -0.25};
float Road3_BottomRight[] = {0.125, -0.35};
float Road3_BottomLeft[] = {-0.125, -0.35};
float Road3_Seperation = 0.55;

// River
float RiverSquareTopLeft[] = {-1.0, 0.8};
float RiverSquareTopRight[] = {1.0, 0.8};
float RiverSquareBottomRight[] = {1.0, 0.0};
float RiverSquareBottomLeft[] = {-1.0, 0.0};

// draw original log for river 1
float River1_TopLeft[] = {-0.225, 0.15};
float River1_TopRight[] = {0.225, 0.15};
float River1_BottomRight[] = {0.225, 0.05};
float River1_BottomLeft[] = {-0.225, 0.05};
float River1_Seperation = 0.7;

// draw original log for river 2
float River2_TopLeft[] = {-0.225, 0.35};
float River2_TopRight[] = {0.225, 0.35};
float River2_BottomRight[] = {0.225, 0.25};
float River2_BottomLeft[] = {-0.225, 0.25};
float River2_Seperation = 0.9;

// draw original log for river 3
float River3_TopLeft[] = {-0.125, 0.55};
float River3_TopRight[] = {0.125, 0.55};
float River3_BottomRight[] = {0.125, 0.45};
float River3_BottomLeft[] = {-0.125, 0.45};
float River3_Seperation = 1.0;

// draw original lilypad
float lilypadX = -0.1;
float lilypadY = 0.7;
float lilypad_sep = 0.4;

bool pad1 = false;
bool pad2 = false;
bool pad3 = false;
bool pad4 = false;
bool pad5 = false;

bool lose = false;
bool win = false;

bool start_menu = true;

void printv(va_list args, const char* str)
{
    size_t buf_size = 8192;
    char buf[buf_size];
    char* ch = buf;
    vsnprintf(buf,buf_size,str,args);
    while(*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

void print(const char* str, ...)
{
    va_list args;
    va_start(args, str);
    printv(args, str);
    va_end(args);
}

void draw_lives()
{
    float x = 0;
    float y = 0;
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
    for (float d=0; d<360; d+=.1)
    {
        x = life1[0] + sin(d)*r;
        y = life1[1] + cos(d)*r;
        glVertex2f(x,y);
    }
    glEnd();

    float x2 = 0;
    float y2 = 0;
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
    for (float d=0; d<360; d+=.1)
    {
        x2 = life2[0] + sin(d)*r;
        y2 = life2[1] + cos(d)*r;
        glVertex2f(x2,y2);
    }
    glEnd();

    float x3 = 0;
    float y3 = 0;
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
    for (float d=0; d<360; d+=.1)
    {
        x3 = life3[0] + sin(d)*r;
        y3 = life3[1] + cos(d)*r;
        glVertex2f(x3,y3);
    }
    glEnd();
}

void draw_lilypad()
{
    float x = 0;
    float y = 0;
    glColor3f (0.12156863, 0.38823529, 0.1372549);
    GLfloat angle, raioX=0.1f, raioY=0.1f;
    GLfloat circle_points = 50.0f;
    glBegin    (GL_TRIANGLE_FAN);
    glVertex2f (lilypadX, lilypadY);
    for (int i = 0; i < circle_points; i++) 
    {
        angle = 1.92*M_PI*i/circle_points;
        x = lilypadX + cos(angle)*raioX;
        y = lilypadY + sin(angle)*raioY;
        glVertex2f(x, y);
    }
    glEnd ();

    float x2 = 0;
    float y2 = 0;
    glColor3f (0.12156863, 0.38823529, 0.1372549);
    GLfloat angle2, raioX2=0.1f, raioY2=0.1f;
    GLfloat circle_points2 = 50.0f;
    glBegin    (GL_TRIANGLE_FAN);
    glVertex2f (lilypadX + lilypad_sep, lilypadY);
    for (int i = 0; i < circle_points2; i++) 
    {
        angle2 = 1.92*M_PI*i/circle_points2;
        x2 = (lilypadX + lilypad_sep) + cos(angle2)*raioX2;
        y2 = lilypadY + sin(angle2)*raioY2;
        glVertex2f(x2, y2);
    }
    glEnd ();

    float x3 = 0;
    float y3 = 0;
    glColor3f (0.12156863, 0.38823529, 0.1372549);
    GLfloat angle3, raioX3=0.1f, raioY3=0.1f;
    GLfloat circle_points3 = 50.0f;
    glBegin    (GL_TRIANGLE_FAN);
    glVertex2f (lilypadX + lilypad_sep*2, lilypadY);
    for (int i = 0; i < circle_points3; i++) 
    {
        angle3 = 1.92*M_PI*i/circle_points3;
        x3 = (lilypadX + lilypad_sep*2) + cos(angle3)*raioX3;
        y3 = lilypadY + sin(angle3)*raioY3;
        glVertex2f(x3, y3);
    }
    glEnd ();

    float x4 = 0;
    float y4 = 0;
    glColor3f (0.12156863, 0.38823529, 0.1372549);
    GLfloat angle4, raioX4=0.1f, raioY4=0.1f;
    GLfloat circle_points4 = 50.0f;
    glBegin    (GL_TRIANGLE_FAN);
    glVertex2f (lilypadX - lilypad_sep, lilypadY);
    for (int i = 0; i < circle_points4; i++) 
    {
        angle4 = 1.92*M_PI*i/circle_points4;
        x4 = (lilypadX - lilypad_sep) + cos(angle4)*raioX4;
        y4 = lilypadY + sin(angle4)*raioY4;
        glVertex2f(x4, y4);
    }
    glEnd ();

    float x5 = 0;
    float y5 = 0;
    glColor3f (0.12156863, 0.38823529, 0.1372549);
    GLfloat angle5, raioX5=0.1f, raioY5=0.1f;
    GLfloat circle_points5 = 50.0f;
    glBegin    (GL_TRIANGLE_FAN);
    glVertex2f (lilypadX - lilypad_sep*2, lilypadY);
    for (int i = 0; i < circle_points5; i++) 
    {
        angle5 = 1.92*M_PI*i/circle_points5;
        x5 = (lilypadX - lilypad_sep*2) + cos(angle5)*raioX5;
        y5 = lilypadY + sin(angle5)*raioY5;
        glVertex2f(x5, y5);
    }
    glEnd ();
}

void draw_river()
{
    glColor3f(0.20392157,0.67058824,0.92156863);
    glBegin(GL_POLYGON);
        glVertex2f (-1.0, 0.0);
        glVertex2f (1.0, 0.0);
        glVertex2f (1.0, 0.8);
        glVertex2f (-1.0, 0.8);
    glEnd();
}

void draw_grass()
{
    glColor3f(0.28235294,0.43529412,0.21960784);
    glBegin(GL_POLYGON);
        glVertex2f (-1.0, 0.0);
        glVertex2f (1.0, 0.0);
        glVertex2f (1.0, -0.2);
        glVertex2f (-1.0, -0.2);
    glEnd();
}

void draw_start()
{
    glColor3f(0.62745098,0.63529412,0.63921569);
    glBegin(GL_POLYGON);
        glVertex2f (-1.0, -0.8);
        glVertex2f (1.0, -0.8);
        glVertex2f (1.0, -1.0);
        glVertex2f (-1.0, -1.0);
    glEnd();
}

void draw_grid()
{
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        //glVertex2f(1.0f, 0.0f); 
        //glVertex2f(-1.0f, 0.0f); 
        //glVertex2f(-1.0f, -0.0f); 
        //glVertex2f(1.0f, -0.0f);

        //glVertex2f(1.0f, 0.2f); 
        //glVertex2f(-1.0f, 0.2f); 
        //glVertex2f(-1.0f, -0.2f); 
        //glVertex2f(1.0f, -0.2f);

        //glVertex2f(1.0f, 0.4f); 
        //glVertex2f(-1.0f, 0.4f); 
        glVertex2f(-1.0f, -0.4f); 
        glVertex2f(1.0f, -0.4f);

        //glVertex2f(1.0f, 0.6f); 
        //glVertex2f(-1.0f, 0.6f); 
        glVertex2f(-1.0f, -0.6f); 
        glVertex2f(1.0f, -0.6f);

        //glVertex2f(1.0f, 0.8f); 
        //glVertex2f(-1.0f, 0.8f); 
        //glVertex2f(-1.0f, -0.8f); 
        //glVertex2f(1.0f, -0.8f);
    glEnd();   
    /*
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 1.0f); 
        glVertex2f(0.0f, -1.0f); 
        glVertex2f(-0.0f, -1.0f); 
        glVertex2f(-0.0f, 1.0f);

        glVertex2f(0.2f, 1.0f); 
        glVertex2f(0.2f, -1.0f); 
        glVertex2f(-0.2f, -1.0f); 
        glVertex2f(-0.2f, 1.0f);
        
        glVertex2f(0.4f, 1.0f); 
        glVertex2f(0.4f, -1.0f); 
        glVertex2f(-0.4f, -1.0f); 
        glVertex2f(-0.4f, 1.0f);

        glVertex2f(0.6f, 1.0f); 
        glVertex2f(0.6f, -1.0f); 
        glVertex2f(-0.6f, -1.0f); 
        glVertex2f(-0.6f, 1.0f);

        glVertex2f(0.8f, 1.0f); 
        glVertex2f(0.8f, -1.0f); 
        glVertex2f(-0.8f, -1.0f); 
        glVertex2f(-0.8f, 1.0f);    
    glEnd(); 
    */
}

void draw_frog()
{
    float x2 = 0;
    float y2 = 0;
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
        for (float d=0; d<360; d+=.1)
        {
            x2 = frog[0] + sin(d)*r;
            y2 = frog[1] + cos(d)*r;
            glVertex2f(x2,y2);
        }
    glEnd();
}

void draw_CompletedFrog(float x) 
{
    float x2 = 0;
    float y2 = 0;
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
        for (float d=0; d<360; d+=.1)
        {
            x2 = x + sin(d)*r;
            y2 = lilypadY + cos(d)*r;
            glVertex2f(x2,y2);
        }
    glEnd();
}

bool CollisionObject(float TopLeft[], float TopRight[], float BottomLeft[], float BottomRight[], float Seperation)
{
    if (BottomLeft[0] <= frog[0] && frog[0] <= BottomRight[0] && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;  
    }

    if (BottomLeft[0] + Seperation <= frog[0] && frog[0] <= BottomRight[0] + Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;   
    }

    if (BottomLeft[0] + Seperation*2 <= frog[0] && frog[0] <= BottomRight[0] + Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;   
    }

    if (BottomLeft[0] + Seperation*3 <= frog[0] && frog[0] <= BottomRight[0] + Seperation*3 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;  
    }
    
    if (BottomLeft[0] + Seperation*4 <= frog[0] && frog[0] <= BottomRight[0] + Seperation*4 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true; 
    }

    if (BottomLeft[0] - Seperation <= frog[0] && frog[0] <= BottomRight[0] - Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;  
    }

    if (BottomLeft[0] - Seperation*2 <= frog[0] && frog[0] <= BottomRight[0] - Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;  
    }

    if (BottomLeft[0] <= frog[0] + r && frog[0] + r <= BottomRight[0] && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true; 
    }

    if (BottomLeft[0] + Seperation <= frog[0] + r && frog[0] + r <= BottomRight[0] + Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;   
    }

    if (BottomLeft[0] + Seperation*2 <= frog[0] + r && frog[0] + r <= BottomRight[0] + Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;  
    }

    if (BottomLeft[0] + Seperation*3 <= frog[0] + r && frog[0] + r<= BottomRight[0] + Seperation*3 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }
    
    if (BottomLeft[0] + Seperation*4 <= frog[0] + r && frog[0] + r <= BottomRight[0] + Seperation*4 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] - Seperation <= frog[0] + r && frog[0] + r <= BottomRight[0] - Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] - Seperation*2 <= frog[0] + r && frog[0] + r <= BottomRight[0] - Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] <= frog[0] - r && frog[0] - r <= BottomRight[0] && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] + Seperation <= frog[0] - r && frog[0] - r <= BottomRight[0] + Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;      
    }

    if (BottomLeft[0] + Seperation*2 <= frog[0] - r && frog[0] - r <= BottomRight[0] + Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true; 
    }

    if (BottomLeft[0] + Seperation*3 <= frog[0] - r && frog[0] - r<= BottomRight[0] + Seperation*3 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }
    
    if (BottomLeft[0] + Seperation*4 <= frog[0] - r && frog[0] - r <= BottomRight[0] + Seperation*4 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] - Seperation <= frog[0] - r && frog[0] - r <= BottomRight[0] - Seperation && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }

    if (BottomLeft[0] - Seperation*2 <= frog[0] - r && frog[0] + r <= BottomRight[0] - Seperation*2 && BottomLeft[1] <= frog[1] && frog[1] <= TopLeft[1]){
        return true;
    }
    return false;
}

bool CollisionLilypad() 
{
    if ( -0.95 <= frog[0] && frog[0] <= -0.85 && frog[1] == lilypadY){
        //cout << "hit pad1" << endl;
        pad1 = true;
        return true;
    }
    if (-0.55 <= frog[0] && frog[0] <= -0.45 && frog[1] == lilypadY){
        //cout << "hit pad2" << endl;
        pad2 = true;
        return true;
    }
    if (-0.15 <= frog[0] && frog[0] <= -0.05 && frog[1] == lilypadY){
        //cout << "hit pad3" << endl;
        pad3 = true;
        return true;
    }
    if (0.25 <= frog[0] && frog[0] <= 0.35 && frog[1] == lilypadY){
        //cout << "hit pad4" << endl;
        pad4 = true;
        return true;
    }
    if (0.65 <= frog[0] && frog[0] <= 0.75 && frog[1] == lilypadY){
        //cout << "hit pad5" << endl;
        pad5 = true;
        return true;
    }
    if (pad1 && pad2 && pad3 && pad4 &&pad5)
    {
        win = true;
    }
    return false;
}

void draw_cars1()
{
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2fv (Road1_TopLeft);
        glVertex2fv (Road1_TopRight);
        glVertex2fv (Road1_BottomRight);
        glVertex2fv (Road1_BottomLeft);
    glEnd();
    
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] + Road1_Seperation, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] + Road1_Seperation, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] + Road1_Seperation, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] + Road1_Seperation,Road1_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] + Road1_Seperation*2, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] + Road1_Seperation*2, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] + Road1_Seperation*2, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] + Road1_Seperation*2,Road1_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] + Road1_Seperation*3, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] + Road1_Seperation*3, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] + Road1_Seperation*3, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] + Road1_Seperation*3,Road1_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] + Road1_Seperation*4, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] + Road1_Seperation*4, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] + Road1_Seperation*4, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] + Road1_Seperation*4,Road1_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] - Road1_Seperation, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] - Road1_Seperation, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] - Road1_Seperation, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] - Road1_Seperation,Road1_BottomLeft[1]);
    glEnd();
    
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road1_TopLeft[0] - Road1_Seperation*2, Road1_TopLeft[1]);
        glVertex2f (Road1_TopRight[0] - Road1_Seperation*2, Road1_TopRight[1]);
        glVertex2f (Road1_BottomRight[0] - Road1_Seperation*2, Road1_BottomRight[1]);
        glVertex2f (Road1_BottomLeft[0] - Road1_Seperation*2,Road1_BottomLeft[1]);
    glEnd();
    
}

void timer1(int value)
{
    float X_move = -.01;
    Road1_TopRight[0] += X_move;
    Road1_TopLeft[0] += X_move;
    Road1_BottomLeft[0] += X_move;
    Road1_BottomRight[0] += X_move;
    if (Road1_TopRight[0] < -1)
    {  
        Road1_TopRight[0] = Road1_TopRight[0] + Road1_Seperation*2;
        Road1_TopLeft[0] = Road1_TopLeft[0] + Road1_Seperation*2;
        Road1_BottomLeft[0] = Road1_BottomLeft[0] + Road1_Seperation*2;
        Road1_BottomRight[0] = Road1_BottomRight[0] + Road1_Seperation*2;
    }
    /*
    if (CollisionObject(Road1_TopLeft, Road1_TopRight, Road1_BottomLeft, Road1_BottomRight, Road1_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
    }
    */
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME1, timer1, 0);
}

void draw_cars2()
{
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2fv (Road2_TopLeft);
        glVertex2fv (Road2_TopRight);
        glVertex2fv (Road2_BottomRight);
        glVertex2fv (Road2_BottomLeft);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road2_TopLeft[0] + Road2_Seperation, Road2_TopLeft[1]);
        glVertex2f (Road2_TopRight[0] + Road2_Seperation, Road2_TopRight[1]);
        glVertex2f (Road2_BottomRight[0] + Road2_Seperation, Road2_BottomRight[1]);
        glVertex2f (Road2_BottomLeft[0] + Road2_Seperation, Road2_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road2_TopLeft[0] + Road2_Seperation*2, Road2_TopLeft[1]);
        glVertex2f (Road2_TopRight[0] + Road2_Seperation*2, Road2_TopRight[1]);
        glVertex2f (Road2_BottomRight[0] + Road2_Seperation*2, Road2_BottomRight[1]);
        glVertex2f (Road2_BottomLeft[0] + Road2_Seperation*2, Road2_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road2_TopLeft[0] - Road2_Seperation, Road2_TopLeft[1]);
        glVertex2f (Road2_TopRight[0] - Road2_Seperation, Road2_TopRight[1]);
        glVertex2f (Road2_BottomRight[0] - Road2_Seperation, Road2_BottomRight[1]);
        glVertex2f (Road2_BottomLeft[0] - Road2_Seperation, Road2_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road2_TopLeft[0] - Road2_Seperation*2, Road2_TopLeft[1]);
        glVertex2f (Road2_TopRight[0] - Road2_Seperation*2, Road2_TopRight[1]);
        glVertex2f (Road2_BottomRight[0] - Road2_Seperation*2, Road2_BottomRight[1]);
        glVertex2f (Road2_BottomLeft[0] - Road2_Seperation*2, Road2_BottomLeft[1]);
    glEnd();
}

void timer2(int value)
{
    float X_move = .01;
    Road2_TopRight[0] += X_move;
    Road2_TopLeft[0] += X_move;
    Road2_BottomLeft[0] += X_move;
    Road2_BottomRight[0] += X_move;
    if (Road2_TopRight[0] > 1)
    {  
        Road2_TopRight[0] = Road2_TopRight[0] - Road2_Seperation*2;
        Road2_TopLeft[0] = Road2_TopLeft[0] - Road2_Seperation*2;
        Road2_BottomLeft[0] = Road2_BottomLeft[0] - Road2_Seperation*2;
        Road2_BottomRight[0] = Road2_BottomRight[0] - Road2_Seperation*2;
    }
    /*
    if (CollisionObject(Road2_TopLeft, Road2_TopRight, Road2_BottomLeft, Road2_BottomRight, Road2_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
    }
    */
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME2, timer2, 0);
}

void draw_cars3()
{
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2fv (Road3_TopLeft);
        glVertex2fv (Road3_TopRight);
        glVertex2fv (Road3_BottomRight);
        glVertex2fv (Road3_BottomLeft);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road3_TopLeft[0] + Road3_Seperation, Road3_TopLeft[1]);
        glVertex2f (Road3_TopRight[0] + Road3_Seperation, Road3_TopRight[1]);
        glVertex2f (Road3_BottomRight[0] + Road3_Seperation, Road3_BottomRight[1]);
        glVertex2f (Road3_BottomLeft[0] + Road3_Seperation,Road3_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road3_TopLeft[0] + Road3_Seperation*2, Road3_TopLeft[1]);
        glVertex2f (Road3_TopRight[0] + Road3_Seperation*2, Road3_TopRight[1]);
        glVertex2f (Road3_BottomRight[0] + Road3_Seperation*2, Road3_BottomRight[1]);
        glVertex2f (Road3_BottomLeft[0] + Road3_Seperation*2,Road3_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road3_TopLeft[0] + Road3_Seperation*3, Road3_TopLeft[1]);
        glVertex2f (Road3_TopRight[0] + Road3_Seperation*3, Road3_TopRight[1]);
        glVertex2f (Road3_BottomRight[0] + Road3_Seperation*3, Road3_BottomRight[1]);
        glVertex2f (Road3_BottomLeft[0] + Road3_Seperation*3,Road3_BottomLeft[1]);
    glEnd();

    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road3_TopLeft[0] - Road3_Seperation, Road3_TopLeft[1]);
        glVertex2f (Road3_TopRight[0] - Road3_Seperation, Road3_TopRight[1]);
        glVertex2f (Road3_BottomRight[0] - Road3_Seperation, Road3_BottomRight[1]);
        glVertex2f (Road3_BottomLeft[0] - Road3_Seperation,Road3_BottomLeft[1]);
    glEnd();
    
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (Road3_TopLeft[0] - Road3_Seperation*2, Road3_TopLeft[1]);
        glVertex2f (Road3_TopRight[0] - Road3_Seperation*2, Road3_TopRight[1]);
        glVertex2f (Road3_BottomRight[0] - Road3_Seperation*2, Road3_BottomRight[1]);
        glVertex2f (Road3_BottomLeft[0] - Road3_Seperation*2,Road3_BottomLeft[1]);
    glEnd();
}

void timer3(int value)
{
    float X_move = -.01;
    Road3_TopRight[0] += X_move;
    Road3_TopLeft[0] += X_move;
    Road3_BottomLeft[0] += X_move;
    Road3_BottomRight[0] += X_move;
    if (Road3_TopRight[0] < -1)
    {  
        Road3_TopRight[0] = Road3_TopRight[0] + Road3_Seperation*2;
        Road3_TopLeft[0] = Road3_TopLeft[0] + Road3_Seperation*2;
        Road3_BottomLeft[0] = Road3_BottomLeft[0] + Road3_Seperation*2;
        Road3_BottomRight[0] = Road3_BottomRight[0] + Road3_Seperation*2;
    }
    /*
    if (CollisionObject(Road3_TopLeft, Road3_TopRight, Road3_BottomLeft, Road3_BottomRight, Road3_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
    }
    */
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME3, timer3, 0);
}

void draw_logs1()
{
    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2fv (River1_TopLeft);
        glVertex2fv (River1_TopRight);
        glVertex2fv (River1_BottomRight);
        glVertex2fv (River1_BottomLeft);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River1_TopLeft[0] + River1_Seperation, River1_TopLeft[1]);
        glVertex2f (River1_TopRight[0] + River1_Seperation, River1_TopRight[1]);
        glVertex2f (River1_BottomRight[0] + River1_Seperation, River1_BottomRight[1]);
        glVertex2f (River1_BottomLeft[0] + River1_Seperation, River1_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River1_TopLeft[0] + River1_Seperation*2, River1_TopLeft[1]);
        glVertex2f (River1_TopRight[0] + River1_Seperation*2, River1_TopRight[1]);
        glVertex2f (River1_BottomRight[0] + River1_Seperation*2, River1_BottomRight[1]);
        glVertex2f (River1_BottomLeft[0] + River1_Seperation*2, River1_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River1_TopLeft[0] + River1_Seperation*3, River1_TopLeft[1]);
        glVertex2f (River1_TopRight[0] + River1_Seperation*3, River1_TopRight[1]);
        glVertex2f (River1_BottomRight[0] + River1_Seperation*3, River1_BottomRight[1]);
        glVertex2f (River1_BottomLeft[0] + River1_Seperation*3, River1_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River1_TopLeft[0] - River1_Seperation, River1_TopLeft[1]);
        glVertex2f (River1_TopRight[0] - River1_Seperation, River1_TopRight[1]);
        glVertex2f (River1_BottomRight[0] - River1_Seperation, River1_BottomRight[1]);
        glVertex2f (River1_BottomLeft[0] - River1_Seperation, River1_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River1_TopLeft[0] - River1_Seperation*2, River1_TopLeft[1]);
        glVertex2f (River1_TopRight[0] - River1_Seperation*2, River1_TopRight[1]);
        glVertex2f (River1_BottomRight[0] - River1_Seperation*2, River1_BottomRight[1]);
        glVertex2f (River1_BottomLeft[0] - River1_Seperation*2, River1_BottomLeft[1]);
    glEnd();
}

void timer4(int value)
{
    float X_move = .01;
    River1_TopRight[0] += X_move;
    River1_TopLeft[0] += X_move;
    River1_BottomLeft[0] += X_move;
    River1_BottomRight[0] += X_move;
    if (River1_TopRight[0] > 1)
    {  
        River1_TopRight[0] = River1_TopRight[0] - River1_Seperation*2;
        River1_TopLeft[0] = River1_TopLeft[0] - River1_Seperation*2;
        River1_BottomLeft[0] = River1_BottomLeft[0] - River1_Seperation*2;
        River1_BottomRight[0] = River1_BottomRight[0] - River1_Seperation*2;
    }

    if (CollisionObject(River1_TopLeft, River1_TopRight, River1_BottomLeft, River1_BottomRight, River1_Seperation) && 0.05 <= frog[1] && frog[1] <= 0.15){
        frog[0] += 0.01;
    }
    //cout << "frogx: " << frog[0] << " frogy: " << frog[1] << endl;
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME4, timer4, 0);
}

void draw_logs2()
{
    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2fv (River2_TopLeft);
        glVertex2fv (River2_TopRight);
        glVertex2fv (River2_BottomRight);
        glVertex2fv (River2_BottomLeft);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River2_TopLeft[0] + River2_Seperation, River2_TopLeft[1]);
        glVertex2f (River2_TopRight[0] + River2_Seperation, River2_TopRight[1]);
        glVertex2f (River2_BottomRight[0] + River2_Seperation, River2_BottomRight[1]);
        glVertex2f (River2_BottomLeft[0] + River2_Seperation, River2_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River2_TopLeft[0] + River2_Seperation*2, River2_TopLeft[1]);
        glVertex2f (River2_TopRight[0] + River2_Seperation*2, River2_TopRight[1]);
        glVertex2f (River2_BottomRight[0] + River2_Seperation*2, River2_BottomRight[1]);
        glVertex2f (River2_BottomLeft[0] + River2_Seperation*2, River2_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River2_TopLeft[0] + River2_Seperation*3, River2_TopLeft[1]);
        glVertex2f (River2_TopRight[0] + River2_Seperation*3, River2_TopRight[1]);
        glVertex2f (River2_BottomRight[0] + River2_Seperation*3, River2_BottomRight[1]);
        glVertex2f (River2_BottomLeft[0] + River2_Seperation*3, River2_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River2_TopLeft[0] - River2_Seperation, River2_TopLeft[1]);
        glVertex2f (River2_TopRight[0] - River2_Seperation, River2_TopRight[1]);
        glVertex2f (River2_BottomRight[0] - River2_Seperation, River2_BottomRight[1]);
        glVertex2f (River2_BottomLeft[0] - River2_Seperation, River2_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River2_TopLeft[0] - River2_Seperation*2, River2_TopLeft[1]);
        glVertex2f (River2_TopRight[0] - River2_Seperation*2, River2_TopRight[1]);
        glVertex2f (River2_BottomRight[0] - River2_Seperation*2, River2_BottomRight[1]);
        glVertex2f (River2_BottomLeft[0] - River2_Seperation*2, River2_BottomLeft[1]);
    glEnd();
}

void timer5(int value)
{
    float X_move = -.01;
    River2_TopRight[0] += X_move;
    River2_TopLeft[0] += X_move;
    River2_BottomLeft[0] += X_move;
    River2_BottomRight[0] += X_move;
    if (River2_TopRight[0] < -1)
    {  
        River2_TopRight[0] = River2_TopRight[0] + River2_Seperation*2;
        River2_TopLeft[0] = River2_TopLeft[0] + River2_Seperation*2;
        River2_BottomLeft[0] = River2_BottomLeft[0] + River2_Seperation*2;
        River2_BottomRight[0] = River2_BottomRight[0] + River2_Seperation*2;
    }

    if (CollisionObject(River2_TopLeft, River2_TopRight, River2_BottomLeft, River2_BottomRight, River2_Seperation) && 0.25 <= frog[1] && frog[1] <= 0.35){
        frog[0] += -0.01;
    }
    //cout << "frogx: " << frog[0] << " frogy: " << frog[1] << endl;
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME5, timer5, 0);
}

void draw_logs3()
{
    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2fv (River3_TopLeft);
        glVertex2fv (River3_TopRight);
        glVertex2fv (River3_BottomRight);
        glVertex2fv (River3_BottomLeft);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River3_TopLeft[0] + River3_Seperation, River3_TopLeft[1]);
        glVertex2f (River3_TopRight[0] + River3_Seperation, River3_TopRight[1]);
        glVertex2f (River3_BottomRight[0] + River3_Seperation, River3_BottomRight[1]);
        glVertex2f (River3_BottomLeft[0] + River3_Seperation, River3_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River3_TopLeft[0] + River3_Seperation*2, River3_TopLeft[1]);
        glVertex2f (River3_TopRight[0] + River3_Seperation*2, River3_TopRight[1]);
        glVertex2f (River3_BottomRight[0] + River3_Seperation*2, River3_BottomRight[1]);
        glVertex2f (River3_BottomLeft[0] + River3_Seperation*2, River3_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River3_TopLeft[0] - River3_Seperation, River3_TopLeft[1]);
        glVertex2f (River3_TopRight[0] - River3_Seperation, River3_TopRight[1]);
        glVertex2f (River3_BottomRight[0] - River3_Seperation, River3_BottomRight[1]);
        glVertex2f (River3_BottomLeft[0] - River3_Seperation, River3_BottomLeft[1]);
    glEnd();

    glColor3f (0.36078431, 0.25098039, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f (River3_TopLeft[0] - River3_Seperation*2, River3_TopLeft[1]);
        glVertex2f (River3_TopRight[0] - River3_Seperation*2, River3_TopRight[1]);
        glVertex2f (River3_BottomRight[0] - River3_Seperation*2, River3_BottomRight[1]);
        glVertex2f (River3_BottomLeft[0] - River3_Seperation*2, River3_BottomLeft[1]);
    glEnd();
}

void timer6(int value)
{
    float X_move = -.01;
    River3_TopRight[0] += X_move;
    River3_TopLeft[0] += X_move;
    River3_BottomLeft[0] += X_move;
    River3_BottomRight[0] += X_move;
    if (River3_TopRight[0] < -1)
    {  
        River3_TopRight[0] = River3_TopRight[0] + River3_Seperation*2;
        River3_TopLeft[0] = River3_TopLeft[0] + River3_Seperation*2;
        River3_BottomLeft[0] = River3_BottomLeft[0] + River3_Seperation*2;
        River3_BottomRight[0] = River3_BottomRight[0] + River3_Seperation*2;
    }

    if (CollisionObject(River3_TopLeft, River3_TopRight, River3_BottomLeft, River3_BottomRight, River3_Seperation) && 0.45 <= frog[1] && frog[1] <= 0.55){
        frog[0] += -0.01;
    }
    //cout << "frogx: " << frog[0] << " frogy: " << frog[1] << endl;
    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME6, timer6, 0);
}

void lifeupdate()
{
    count_lives++;
    if (count_lives > 3)
    {
        lose = true;
        pad1 = false;
        pad2 = false;
        pad3 = false;
        pad4 = false;
        pad5 = false;
    }
}

void CollisionTimer(int value)
{
    if (CollisionObject(Road1_TopLeft, Road1_TopRight, Road1_BottomLeft, Road1_BottomRight, Road1_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (CollisionObject(Road2_TopLeft, Road2_TopRight, Road2_BottomLeft, Road2_BottomRight, Road2_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }
    
    if (CollisionObject(Road3_TopLeft, Road3_TopRight, Road3_BottomLeft, Road3_BottomRight, Road3_Seperation) && -0.8 <= frog[1] && frog[1] <= -0.2){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (!(CollisionObject(River1_TopLeft, River1_TopRight, River1_BottomLeft, River1_BottomRight, River1_Seperation)) && 0.05 <= frog[1] && frog[1] <= 0.15){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (CollisionObject(River1_TopLeft, River1_TopRight, River1_BottomLeft, River1_BottomRight, River1_Seperation) && 0.05 <= frog[1] && frog[1] <= 0.15 && frog[0] >= 0.9){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (!(CollisionObject(River2_TopLeft, River2_TopRight, River2_BottomLeft, River2_BottomRight, River2_Seperation)) && 0.25 <= frog[1] && frog[1] <= 0.35){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (CollisionObject(River2_TopLeft, River2_TopRight, River2_BottomLeft, River2_BottomRight, River2_Seperation) && 0.25 <= frog[1] && frog[1] <= 0.35 && frog[0] <= -0.9){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (!(CollisionObject(River3_TopLeft, River3_TopRight, River3_BottomLeft, River3_BottomRight, River3_Seperation)) && 0.45 <= frog[1] && frog[1] <= 0.55){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }

    if (CollisionObject(River3_TopLeft, River3_TopRight, River3_BottomLeft, River3_BottomRight, River3_Seperation) && 0.45 <= frog[1] && frog[1] <= 0.55 && frog[0] <= -0.9){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    } 

    if (!CollisionLilypad() && 0.65 <= frog[1] && frog[1] <= 0.75){
        frog[0] = 0;
        frog[1] = -0.9;
        lifeupdate();
    }
    
    if (CollisionLilypad())
    {
        frog[0] = 0;
        frog[1] = -0.9;
        //lifeupdate();
    }

    glutPostRedisplay();
    glutTimerFunc(SLEEP_TIME_Collision, CollisionTimer, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_river();
    draw_lives();
    draw_lilypad();
    
    if (pad1){
        draw_CompletedFrog(-0.9);
    }
    if (pad2){
        draw_CompletedFrog(-0.5);
    }
    if (pad3){
        draw_CompletedFrog(-0.1);
    }
    if (pad4){
        draw_CompletedFrog(0.3);
    }
    if (pad5){
        draw_CompletedFrog(0.7);
    }
    
    draw_grass();
    draw_start();
    draw_grid();
    draw_cars1();
    draw_cars2();
    draw_cars3();
    draw_logs1();
    draw_logs2();
    draw_logs3();
    //glFlush();
    //glutPosRoad1_TopRightedisplay(); 
    draw_frog();

    if (count_lives >= 1)
    {
        float x3 = 0;
        float y3 = 0;
        glColor3f(0,0,0);
        glBegin(GL_TRIANGLE_FAN);
        for (float d=0; d<360; d+=.1)
        {
            x3 = life3[0] + sin(d)*r;
            y3 = life3[1] + cos(d)*r;
            glVertex2f(x3,y3);
        }
        glEnd();
    }
    if (count_lives >= 2)
    {
        float x2 = 0;
        float y2 = 0;
        glColor3f(0,0,0);
        glBegin(GL_TRIANGLE_FAN);
        for (float d=0; d<360; d+=.1)
        {
            x2 = life2[0] + sin(d)*r;
            y2 = life2[1] + cos(d)*r;
            glVertex2f(x2,y2);
        }
        glEnd();
    }
    if (count_lives >= 3) 
    {
        float x = 0;
        float y = 0;
        glColor3f(0,0,0);
        glBegin(GL_TRIANGLE_FAN);
        for (float d=0; d<360; d+=.1)
        {
            x = life1[0] + sin(d)*r;
            y = life1[1] + cos(d)*r;
            glVertex2f(x,y);
        }
        glEnd();
    }
    if (lose){
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);
            glVertex2f(-1.0, 1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(-1.0, -1.0);
        glEnd();

        glColor3f(1,1,1);
        glRasterPos2d(-0.25,0.5);
        print("You Lose! :(");
        glRasterPos2d(-0.25,0);
        print("Game Over");
        glRasterPos2d(-0.25,-0.1); 
        print("Press 'R' to play again");
        glRasterPos2d(-0.25,-0.2);
        print("Press 'Q' to quit");
    }
    if (win){
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);
            glVertex2f(-1.0, 1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(-1.0, -1.0);
        glEnd();
        
        glColor3f(1,1,1);
        glRasterPos2d(-0.25,0.5);
        print("You Win! :)");
        glRasterPos2d(-0.25,0);
        print("Game Over");
        glRasterPos2d(-0.25,-0.1); 
        print("Press 'R' to play again");
        glRasterPos2d(-0.25,-0.2);
        print("Press 'Q' to quit");
    }

    if (start_menu)
    {
        glColor3f(0,1,0);
        glRasterPos2d(-0.15,0.87);
        print("TOADER");
        glColor3f(1,1,1);
        glRasterPos2d(-0.25,-0.13);
        print("Press S to start");
    }
    glutSwapBuffers();
}

void movement(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT && frog[0] < .9) {
        frog[0] += .1;
    }
    else if (key == GLUT_KEY_LEFT && frog[0] > -.9) {
        frog[0] -= .1;
    }
    else if (key == GLUT_KEY_UP && frog[1] < .6) {
        frog[1] += .2;
    }
    else if (key == GLUT_KEY_DOWN && frog[1] > -.9) {
        frog[1] -= .2;
    }
}

void keyboard_handler(unsigned char key, int x, int y)
{
    if (key == 's')
    {
        start_menu = false;
        glutSpecialFunc(movement);
    }
    if (key == 'r')
    {
        frog[0] = 0;
        frog[1] = -0.9;
        lose = false;
        win = false;
        pad1 = false;
        pad2 = false;
        pad3 = false;
        pad4 = false;
        pad5 = false;
        count_lives = 0;
    }
    if (key == 'q')
    {
        exit(0);
    }
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WWIDTH,WHEIGHT);
    glutCreateWindow("Toader");

    glutDisplayFunc(display);
    //glutSpecialFunc(movement);
    glutKeyboardFunc(keyboard_handler);
    glutTimerFunc(SLEEP_TIME1, timer1, 0);
    glutTimerFunc(SLEEP_TIME2, timer2, 0);
    glutTimerFunc(SLEEP_TIME3, timer3, 0);
    glutTimerFunc(SLEEP_TIME4, timer4, 0);
    glutTimerFunc(SLEEP_TIME5, timer5, 0);
    glutTimerFunc(SLEEP_TIME6, timer6, 0);
    glutTimerFunc(SLEEP_TIME_Collision, CollisionTimer, 0);
    glutMainLoop();
    return 0;
}
