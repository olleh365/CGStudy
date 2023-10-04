#include <GL/glut.h>
#include <cmath>

int winWidth = 800;
int winHeight = 600;
float pacManAngle = 45.0f;
bool mouthOpen = true;

void drawPacMan() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0); // Yellow color

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0); // Center of Pac-Man

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

    glFlush();
}

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

    glutMainLoop();

    return 0;
}
