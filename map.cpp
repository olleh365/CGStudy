#include <GL/glut.h>

void MyDisplay()

{

    glClearColor(0.375,0.598,0.992,1.0); //배경색을 흰색으로 지정

    glClear(GL_COLOR_BUFFER_BIT);




    
    //노란 블럭
    glColor3f(1, 1, 0);

    glBegin(GL_QUADS);
    glVertex2f(-0.45, -0.09);
    glVertex2f(-0.45, 0.07);
    glVertex2f(-0.35, 0.07);
    glVertex2f(-0.35, -0.09);

    //벽돌 블럭
    
    glColor3f(0.596, 0.324, 0.244);
    glBegin(GL_QUADS);

    glVertex2f(0, -0.09);
    glVertex2f(0., 0.07);
    glVertex2f(0.1, 0.07);
    glVertex2f(0.1, -0.09);

    //노란 블럭
    glColor3f(1, 1, 0);

    glBegin(GL_QUADS);
    glVertex2f(0.1, -0.09);
    glVertex2f(0.1, 0.07);
    glVertex2f(0.2, 0.07);
    glVertex2f(0.2, -0.09);
    //벽돌 블럭

    glColor3f(0.596, 0.324, 0.244);
    glBegin(GL_QUADS);

    glVertex2f(0.2, -0.09);
    glVertex2f(0.2, 0.07);
    glVertex2f(0.3, 0.07);
    glVertex2f(0.3, -0.09);

    //노란 블럭
    glColor3f(1, 1, 0);

    glBegin(GL_QUADS);
    glVertex2f(0.3, -0.09);
    glVertex2f(0.3, 0.07);
    glVertex2f(0.4, 0.07);
    glVertex2f(0.4, -0.09);

    //벽돌 블럭
    glColor3f(0.596, 0.324, 0.244);
    glBegin(GL_QUADS);

    glVertex2f(0.4, -0.09);
    glVertex2f(0.4, 0.07);
    glVertex2f(0.5, 0.07);
    glVertex2f(0.5, -0.09);

    //벽돌 블럭

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);

    glVertex2f(0.2, 0.35);
    glVertex2f(0.2, 0.51);
    glVertex2f(0.3, 0.51);
    glVertex2f(0.3, 0.35);

    //아랫 토관 

    glColor3f(0.644, 0.78, 0.32);

    glBegin(GL_QUADS);
    glVertex2f(1, -0.09);
    glVertex2f(1, -0.6);
    glVertex2f(0.8, -0.6);
    glVertex2f(0.8, -0.09);

    //윗 토관


    glColor3f(0.644, 0.78, 0.32);
    glBegin(GL_QUADS);
    glVertex2f(1, -0.09);
    glVertex2f(1, -0.29);
    glVertex2f(0.78, -0.29);
    glVertex2f(0.78, -0.09);

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex2f(1, -0.09);
    glVertex2f(1, -0.07);
    glVertex2f(0.78, -0.07);
    glVertex2f(0.78, -0.09);

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex2f(0.8, -0.09);
    glVertex2f(0.8, -0.29);
    glVertex2f(0.78, -0.29);
    glVertex2f(0.78, -0.09);
   
    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex2f(0.8, -0.27);
    glVertex2f(0.8, -0.29);
    glVertex2f(1, -0.29);
    glVertex2f(1, -0.27);

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex2f(0.8, -0.29);
    glVertex2f(0.8, -0.6);
    glVertex2f(0.82, -0.6);
    glVertex2f(0.82, -0.29);

 
    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.86, -0.29);
    glVertex2f(0.86, -0.6);
    glVertex2f(0.88, -0.6);
    glVertex2f(0.88, -0.29);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.84, -0.27);
    glVertex2f(0.84, -0.13);
    glVertex2f(0.86, -0.13);
    glVertex2f(0.86, -0.27);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.84, -0.15);
    glVertex2f(0.84, -0.13);
    glVertex2f(0.8, -0.13);
    glVertex2f(0.8, -0.15);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.9, -0.29);
    glVertex2f(0.9, -0.6);
    glVertex2f(0.92, -0.6);
    glVertex2f(0.92, -0.29);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.88, -0.27);
    glVertex2f(0.88, -0.13);
    glVertex2f(0.9, -0.13);
    glVertex2f(0.9, -0.27);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(0.9, -0.15);
    glVertex2f(0.9, -0.13);
    glVertex2f(1, -0.13);
    glVertex2f(1, -0.15);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(1, -0.27);
    glVertex2f(1, -0.13);
    glVertex2f(0.92, -0.13);
    glVertex2f(0.92, -0.27);

    glColor3f(0.140, 0.64, 0.356);
    glBegin(GL_QUADS);
    glVertex2f(1, -0.29);
    glVertex2f(1, -0.6);
    glVertex2f(0.94, -0.6);
    glVertex2f(0.94, -0.29);


    



    
    // 땅 
    glColor3f(0.832, 0.273, 0.027);

    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(-1, -0.6);
    glVertex2f(1, -0.6);
    glVertex2f(1, -1);


    glEnd();

    glFlush();

}



int main(int argc,char* argv[])

{
    glutInitWindowSize(1600, 900);
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(MyDisplay);

    glutMainLoop();

}
