#include <GL/glut.h>
#include <cmath>

int winWidth = 800;
int winHeight = 600;
float pacManAngle = 45.0f;
bool mouthOpen = true;
float pacManX = 0.0f;
float pacManY = 0.0f;
float pacManSpeed = 0.02f;

void drawPacMan() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(pacManX, pacManY, 0.0f); // 팩맨을 현재위치로 변환

    glColor3f(1.0, 1.0, 0.0); // 팩맨 노란색깔

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0); // 팩맨의 센터위치

    // 팩맨모양
    for (float angle = pacManAngle; angle <= 360.0 - pacManAngle; angle += 1.0) {
        float radians = angle * (M_PI / 180.0);
        float x = 0.3 * cos(radians);
        float y = 0.3 * sin(radians);
        glVertex2f(x, y);
    }

    glEnd();

    // 팩맨 입
    if (mouthOpen) {
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        float radians1 = (pacManAngle - 20.0) * (M_PI / 180.0);
        float x1 = 0.3 * cos(radians1);
        float y1 = 0.3 * sin(radians1);
        glVertex2f(x1, y1);
        float radians2 = (360.0 - pacManAngle + 20.0) * (M_PI / 180.0);
        float x2 = 0.3 * cos(radians2);
        float y2 = 0.3 * sin(radians2);
        glVertex2f(x2, y2);
        glEnd();
    }
    glPopMatrix();


    glFlush();
}

//0.5초 단위로 팩맨 입벌렸다가 움츠렸다가 업데이트
void updatePacMan(int value) {
    if (mouthOpen) {
        pacManAngle -= 2.0;
    } else {
        pacManAngle += 2.0;
    }

    if (pacManAngle <= 20.0 || pacManAngle >= 45.0) {
        mouthOpen = !mouthOpen;
    }

    glutPostRedisplay();
    glutTimerFunc(50, updatePacMan, 0);
}
//팩맨 이동키
void specialKeyFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            pacManY += pacManSpeed;
            break;
        case GLUT_KEY_DOWN:
            pacManY -= pacManSpeed;
            break;
        case GLUT_KEY_LEFT:
            pacManX -= pacManSpeed;
            break;
        case GLUT_KEY_RIGHT:
            pacManX += pacManSpeed;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Pac-Man");
    glutDisplayFunc(drawPacMan);

    // 초기상태 팩맨
    pacManAngle = 45.0;
    mouthOpen = true;

    // 팩맨 애니메이션 시작
    glutTimerFunc(50, updatePacMan, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutSpecialFunc(specialKeyFunc);

    glutMainLoop();

    return 0;
}
