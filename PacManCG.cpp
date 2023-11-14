#include <GL/freeglut.h>
#include <cmath>
#include <vector>

struct Pellet {
    float x;
    float y;
    bool isYellow;
    bool isEaten;
};

struct PacMan {
    float x;
    float y;
    float radius;
    float mouthAngle;
    bool isOpening;
};

PacMan pacMan = {-0.8, -0.8, 0.05, 45.0, true};

std::vector<Pellet> pellets = {
    {-0.8, 0.8, true},
    {-0.6, 0.8, true},
    {-0.4, 0.8, true},
    {-0.2, 0.8, true},
    {0.0, 0.8, true},
    {0.2, 0.8, true},
    {0.4, 0.8, true},
    {0.6, 0.8, true},
    {0.8, 0.8, true},

    {-0.8, 0.6, true},
    {0.8, 0.6, true},

    {-0.8, 0.4, true},
    {0.0, 0.4, false},
    {0.8, 0.4, true},

    {-0.8, 0.2, true},
    {-0.6, 0.2, true},
    {-0.4, 0.2, true},
    {-0.2, 0.2, true},
    {0.0, 0.2, true},
    {0.2, 0.2, true},
    {0.4, 0.2, true},
    {0.6, 0.2, true},
    {0.8, 0.2, true},

    {-0.8, 0.0, true},
    {0.0, 0.0, false},
    {0.8, 0.0, true},

    {-0.8, -0.2, true},
    {-0.6, -0.2, true},
    {-0.4, -0.2, true},
    {-0.2, -0.2, true},
    {0.0, -0.2, true},
    {0.2, -0.2, true},
    {0.4, -0.2, true},
    {0.6, -0.2, true},
    {0.8, -0.2, true},

    {-0.8, -0.4, true},
    {0.0, -0.4, false},
    {0.8, -0.4, true},

    {-0.8, -0.6, true},
    {-0.6, -0.6, true},
    {-0.4, -0.6, true},
    {-0.2, -0.6, true},
    {0.0, -0.6, true},
    {0.2, -0.6, true},
    {0.4, -0.6, true},
    {0.6, -0.6, true},
    {0.8, -0.6, true},

    {-0.6, -0.8, true},
    {-0.4, -0.8, true},
    {-0.2, -0.8, true},
    {0.0, -0.8, true},
    {0.2, -0.8, true},
    {0.4, -0.8, true},
    {0.6, -0.8, true},
    {0.8, -0.8, true},
};

void drawMaze() {
    glColor3f(0.0, 0.2078, 0.8275); 
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.97, -0.97);
    glVertex2f(0.97, -0.97);
    glVertex2f(0.97, 0.97);
    glVertex2f(-0.97, 0.97);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6, 0.6);
    glVertex2f(-0.6, 0.4);
    glVertex2f(-0.2, 0.4);
    glVertex2f(-0.2, 0.6);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.6, 0.4);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.2, 0.6);
    glEnd();

    // Draw pellets
    glPointSize(5.0);
    glBegin(GL_POINTS);

    for (const Pellet& pellet : pellets) {
        if (!pellet.isEaten) {
            if (pellet.isYellow) {
                glColor3f(1.0, 1.0, 0.0);
            } else {
                glColor3f(0.0, 0.0, 1.0);
            }
            glVertex2f(pellet.x, pellet.y);
        }
    }
    glEnd();
    
    // Draw Pac-Man
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(pacMan.x, pacMan.y);
    float directionAngle = (pacMan.y > -0.78) ? 90.0 : 0.0;

    for (float angle = pacMan.mouthAngle + directionAngle; angle <= 360.0 - pacMan.mouthAngle + directionAngle; angle += 5.0) {
        float radianAngle = angle * 3.14159265358979323846 / 180.0;
        float xPos = pacMan.x + pacMan.radius * std::cos(radianAngle);
        float yPos = pacMan.y + pacMan.radius * std::sin(radianAngle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    
}

void updatePacMan() {
    // Update Pac-Man's position and mouth angle
    if (pacMan.x < 0.0)
    pacMan.x += 0.002;


    // Check if Pac-Man reached the top edge
    if (pacMan.y > 0.8) {
        pacMan.y = -0.8; // Reset Pac-Man to the bottom
    }

    // Check if Pac-Man reached 0.0 on the x-axis
    if (pacMan.x >= 0.0) {
        pacMan.x += 0.0;
        pacMan.y +=0.002;
    }


    // Update mouth angle based on opening or closing direction
    if (pacMan.isOpening) {
        pacMan.mouthAngle += 1.0;
        if (pacMan.mouthAngle >= 45.0) {
            pacMan.isOpening = false;
        }
    } else {
        pacMan.mouthAngle -= 1.0;
        if (pacMan.mouthAngle <= 0.0) {
            pacMan.isOpening = true;
        }
    }

    // Check for pellet collisions
    for (Pellet& pellet : pellets) {
        if (!pellet.isEaten) {  // Skip eaten pellets
            float distance = std::sqrt((pacMan.x - pellet.x) * (pacMan.x - pellet.x) +
                                       (pacMan.y - pellet.y) * (pacMan.y - pellet.y));
            if (distance < pacMan.radius) {
                // Pac-Man collided with the pellet, mark it as eaten
                pellet.isEaten = true;

            }
        }
    }
}





void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    updatePacMan();
    // Draw the maze
    drawMaze();

    glutSwapBuffers();
}

void MyReshape(int NewWidth, int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat aspectRatio = (GLfloat)NewWidth / (GLfloat)NewHeight;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspectRatio > 1.0) {
        glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0, 1.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 frames per second
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("Pac-Man Maze");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    glutReshapeFunc(MyReshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
