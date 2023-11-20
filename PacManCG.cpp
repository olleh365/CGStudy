#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>
#include <cmath>
#include <vector>


float directionAngle;
float growthRate = 0.002;
float pacManColor[3] = {1.0, 1.0, 0.0};

struct Pellet {
    float x;
    float y;
    bool isYellow;
    bool isEaten;
    bool isBlue;
    bool isGreen;
};

struct PacMan {
    float x;
    float y;
    float radius;
    float mouthAngle;
    bool isOpening;
    float size;
};

// Define the scenes
enum SceneType {
    PACMAN_SCENE,
    NEXT_SCENE,
    THIRD_SCENE
};


PacMan pacMan = {-0.8, -0.8, 0.05, 45.0, true, 1.0};


std::vector<Pellet> pellets = {
    {-0.8, 0.8, true},
    {-0.6, 0.8, true},
    {-0.4, 0.8, true},
    {-0.2, 0.8, true},
    {0.0, 0.8, false, false, false, true},
    {0.2, 0.8, true},
    {0.4, 0.8, true},
    {0.6, 0.8, true},
    {0.8, 0.8, true},

    {-0.8, 0.6, true},
    {0.8, 0.6, true},

    {-0.8, 0.4, true},
    {0.0, 0.4, true},
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
    {0.0, 0.0, false, false, true},
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
    {0.0, -0.4, true},
    {0.8, -0.4, true},

    {-0.8, -0.6, true},
    {-0.6, -0.6, true},
    {-0.4, -0.6, true},
    {-0.2, -0.6, true},
    {0.0, -0.6, false, false, true},
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

std::vector<Pellet> mazeWalls = {
// top outside wall
    {0.94,0.99},{0.92,0.99},{0.90,0.99},{0.88,0.99},{0.86,0.99},{0.84,0.99},{0.82,0.99},{0.80,0.99},{0.78,0.99},{0.76,0.99},{0.74,0.99},{0.72,0.99},{0.70,0.99},{0.68,0.99},{0.66,0.99},{0.64,0.99},{0.62,0.99},{0.60,0.99},{0.58,0.99},{0.56,0.99},{0.54,0.99},{0.52,0.99},{0.50,0.99},{0.48,0.99},{0.46,0.99},{0.44,0.99},{0.42,0.99},{0.40,0.99},{0.38,0.99},{0.36,0.99},{0.34,0.99},{0.32,0.99},{0.30,0.99},{0.28,0.99},{0.26,0.99},{0.24,0.99},{0.22,0.99},{0.20,0.99},{0.18,0.99},{0.16,0.99},{0.14,0.99},{0.12,0.99},{0.10,0.99},{0.08,0.99},{0.06,0.99},{0.04,0.99},{0.02,0.99},{0.0,0.99},{-0.02,0.99},{-0.04,0.99},{-0.06,0.99},{-0.08,0.99},{-0.10,0.99},{-0.12,0.99},{-0.14,0.99},{-0.16,0.99},{-0.18,0.99},{-0.20,0.99},{-0.22,0.99},{-0.24,0.99},{-0.26,0.99},{-0.28,0.99},{-0.30,0.99},{-0.32,0.99},{-0.34,0.99},{-0.36,0.99},{-0.38,0.99},{-0.40,0.99},{-0.42,0.99},{-0.44,0.99},{-0.46,0.99},{-0.48,0.99},{-0.50,0.99},{-0.52,0.99},{-0.54,0.99},{-0.56,0.99},{-0.58,0.99},{-0.60,0.99},{-0.62,0.99},{-0.64,0.99},{-0.66,0.99},{-0.68,0.99},{-0.70,0.99},{-0.72,0.99},{-0.74,0.99},{-0.76,0.99},{-0.78,0.99},{-0.80,0.99},{-0.82,0.99},{-0.84,0.99},{-0.86,0.99},{-0.88,0.99},{-0.90,0.99},{-0.92,0.99},{-0.94,0.99},
// bottom outside wall
    {0.94,-0.99},{0.92,-0.99},{0.90,-0.99},{0.88,-0.99},{0.86,-0.99},{0.84,-0.99},{0.82,-0.99},{0.80,-0.99},{0.78,-0.99},{0.76,-0.99},{0.74,-0.99},{0.72,-0.99},{0.70,-0.99},{0.68,-0.99},{0.66,-0.99},{0.64,-0.99},{0.62,-0.99},{0.60,-0.99},{0.58,-0.99},{0.56,-0.99},{0.54,-0.99},{0.52,-0.99},{0.50,-0.99},{0.48,-0.99},{0.46,-0.99},{0.44,-0.99},{0.42,-0.99},{0.40,-0.99},{0.38,-0.99},{0.36,-0.99},{0.34,-0.99},{0.32,-0.99},{0.30,-0.99},{0.28,-0.99},{0.26,-0.99},{0.24,-0.99},{0.22,-0.99},{0.20,-0.99},{0.18,-0.99},{0.16,-0.99},{0.14,-0.99},{0.12,-0.99},{0.10,-0.99},{0.08,-0.99},{0.06,-0.99},{0.04,-0.99},{0.02,-0.99},{0.0,-0.99},{-0.02,-0.99},{-0.04,-0.99},{-0.06,-0.99},{-0.08,-0.99},{-0.10,-0.99},{-0.12,-0.99},{-0.14,-0.99},{-0.16,-0.99},{-0.18,-0.99},{-0.20,-0.99},{-0.22,-0.99},{-0.24,-0.99},{-0.26,-0.99},{-0.28,-0.99},{-0.30,-0.99},{-0.32,-0.99},{-0.34,-0.99},{-0.36,-0.99},{-0.38,-0.99},{-0.40,-0.99},{-0.42,-0.99},{-0.44,-0.99},{-0.46,-0.99},{-0.48,-0.99},{-0.50,-0.99},{-0.52,-0.99},{-0.54,-0.99},{-0.56,-0.99},{-0.58,-0.99},{-0.60,-0.99},{-0.62,-0.99},{-0.64,-0.99},{-0.66,-0.99},{-0.68,-0.99},{-0.70,-0.99},{-0.72,-0.99},{-0.74,-0.99},{-0.76,-0.99},{-0.78,-0.99},{-0.80,-0.99},{-0.82,-0.99},{-0.84,-0.99},{-0.86,-0.99},{-0.88,-0.99},{-0.90,-0.99},{-0.92,-0.99},{-0.94,-0.99},
    // right outside wall
    {0.955, 0.98},{0.97, 0.96},{0.985, 0.94},{1.0, 0.92},{1.0, 0.90},{1.0, 0.88},{1.0, 0.86},{1.0, 0.84},{1.0, 0.82},{1.0, 0.80},{1.0, 0.78},{1.0, 0.76},{1.0, 0.74},{1.0, 0.72},{1.0, 0.70},{1.0, 0.68},{1.0, 0.66},{1.0, 0.64},{1.0, 0.62},{1.0, 0.60},{1.0, 0.58},{1.0, 0.56},{1.0, 0.54},{1.0, 0.52},{1.0, 0.50},{1.0, 0.48},{1.0, 0.46},{1.0, 0.44},{1.0, 0.42},{1.0, 0.40},{1.0, 0.38},{1.0, 0.36},{1.0, 0.34},{1.0, 0.32},{1.0, 0.30},{1.0, 0.28},{1.0, 0.26},{1.0, 0.24},{1.0, 0.22},{1.0, 0.20},{1.0, 0.18},{1.0, 0.16},{1.0, 0.14},{1.0, 0.12},{1.0, 0.10},{1.0, 0.08},{1.0, 0.06},{1.0, 0.04},{1.0, 0.02},{1.0, 0.0},{1.0, -0.02},{1.0, -0.04},{1.0, -0.06},{1.0, -0.08},{1.0, -0.10},{1.0, -0.12},{1.0, -0.14},{1.0, -0.16},{1.0, -0.18},{1.0, -0.20},{1.0, -0.22},{1.0, -0.24},{1.0, -0.26},{1.0, -0.28},{1.0, -0.30},{1.0, -0.32},{1.0, -0.34},{1.0, -0.36},{1.0, -0.38},{1.0, -0.40},{1.0, -0.42},{1.0, -0.44},{1.0, -0.46},{1.0, -0.48},{1.0, -0.50},{1.0, -0.52},{1.0, -0.54},{1.0, -0.56},{1.0, -0.58},{1.0, -0.60},{1.0, -0.62},{1.0, -0.64},{1.0, -0.66},{1.0, -0.68},{1.0, -0.70},{1.0, -0.72},{1.0, -0.74},{1.0, -0.76},{1.0, -0.78},{1.0, -0.80},{1.0, -0.82},{1.0, -0.84},{1.0, -0.86},{1.0, -0.88},{1.0, -0.90},{1.0, -0.92},{0.985, -0.94},{0.97, -0.96},{0.955, -0.98},
   // left outside wall
    {-0.955, 0.98},{-0.97, 0.96},{-0.985, 0.94},{-1.0, 0.92},{-1.0, 0.90},{-1.0, 0.88},{-1.0, 0.86},{-1.0, 0.84},{-1.0, 0.82},{-1.0, 0.80},{-1.0, 0.78},{-1.0, 0.76},{-1.0, 0.74},{-1.0, 0.72},{-1.0, 0.70},{-1.0, 0.68},{-1.0, 0.66},{-1.0, 0.64},{-1.0, 0.62},{-1.0, 0.60},{-1.0, 0.58},{-1.0, 0.56},{-1.0, 0.54},{-1.0, 0.52},{-1.0, 0.50},{-1.0, 0.48},{-1.0, 0.46},{-1.0, 0.44},{-1.0, 0.42},{-1.0, 0.40},{-1.0, 0.38},{-1.0, 0.36},{-1.0, 0.34},{-1.0, 0.32},{-1.0, 0.30},{-1.0, 0.28},{-1.0, 0.26},{-1.0, 0.24},{-1.0, 0.22},{-1.0, 0.20},{-1.0, 0.18},{-1.0, 0.16},{-1.0, 0.14},{-1.0, 0.12},{-1.0, 0.10},{-1.0, 0.08},{-1.0, 0.06},{-1.0, 0.04},{-1.0, 0.02},{-1.0, 0.0},{-1.0, -0.02},{-1.0, -0.04},{-1.0, -0.06},{-1.0, -0.08},{-1.0, -0.10},{-1.0, -0.12},{-1.0, -0.14},{-1.0, -0.16},{-1.0, -0.18},{-1.0, -0.20},{-1.0, -0.22},{-1.0, -0.24},{-1.0, -0.26},{-1.0, -0.28},{-1.0, -0.30},{-1.0, -0.32},{-1.0, -0.34},{-1.0, -0.36},{-1.0, -0.38},{-1.0, -0.40},{-1.0, -0.42},{-1.0, -0.44},{-1.0, -0.46},{-1.0, -0.48},{-1.0, -0.50},{-1.0, -0.52},{-1.0, -0.54},{-1.0, -0.56},{-1.0, -0.58},{-1.0, -0.60},{-1.0, -0.62},{-1.0, -0.64},{-1.0, -0.66},{-1.0, -0.68},{-1.0, -0.70},{-1.0, -0.72},{-1.0, -0.74},{-1.0, -0.76},{-1.0, -0.78},{-1.0, -0.80},{-1.0, -0.82},{-1.0, -0.84},{-1.0, -0.86},{-1.0, -0.88},{-1.0, -0.90},{-1.0, -0.92},{-0.985, -0.94},{-0.97, -0.96},{-0.955, -0.98},
    

    {-0.6, 0.6},
    {-0.6, 0.4},
    {-0.2, 0.4},
    {-0.2, 0.6,},

    {0.6, 0.6},
    {0.6, 0.4},
    {0.2, 0.4},
    {0.2, 0.6},
};



SceneType currentScene = PACMAN_SCENE;
float transitionProgress = 0.0; // 0.0은 팩맨 장면을 나타내고, 1.0은 다음 장면을 나타냅니다.


void drawMaze() {
    
    

    for (const Pellet& wallVertex : mazeWalls) {
        if (!wallVertex.isEaten) {
            glColor3f(0.0, 0.2078, 0.8275);
            glBegin(GL_QUADS);
            glVertex2f(wallVertex.x - 0.01, wallVertex.y - 0.01);  // Bottom-left corner
            glVertex2f(wallVertex.x + 0.01, wallVertex.y - 0.01);  // Bottom-right corner
            glVertex2f(wallVertex.x + 0.01, wallVertex.y + 0.01);  // Top-right corner
            glVertex2f(wallVertex.x - 0.01, wallVertex.y + 0.01);  // Top-left corner

            glEnd();
        }
    }
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
    glColor3fv(pacManColor);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(pacMan.x, pacMan.y);

    for (float angle = pacMan.mouthAngle + directionAngle; angle <= 360.0 - pacMan.mouthAngle + directionAngle; angle += 5.0) {
        float radianAngle = angle * 3.1415 / 180.0;
        float xPos = pacMan.x + pacMan.radius * std::cos(radianAngle);
        float yPos = pacMan.y + pacMan.radius * std::sin(radianAngle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    
}

void updatePacMan() {
//    // Update Pac-Man's position and mouth angle
//    if (pacMan.x < 0.0)
//    pacMan.x += 0.002;
//
//
//    // Check if Pac-Man reached the top edge
//    if (pacMan.y > 0.8) {
//        pacMan.y = -0.8; // Reset Pac-Man to the bottom
////        pacMan.size = 1.0;
////        pacMan.radius = 1.0;
//    }
//
//    if (pacMan.x >= 0.0) {
//        pacMan.x += 0.0;
//        pacMan.y +=0.002;
//    }
//    


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

    // 펠렛을 먹을(충돌)하면 펠렛 베니시
    for (Pellet& pellet : pellets) {
        if (!pellet.isEaten) {
            float distance = std::sqrt((pacMan.x - pellet.x) * (pacMan.x - pellet.x) +
                                       (pacMan.y - pellet.y) * (pacMan.y - pellet.y));
            if (distance <  pacMan.size * pacMan.radius) {
                pellet.isEaten = true;
                
            }
        }
    }
    
    for (Pellet& wallVertex : mazeWalls) {
        if (!wallVertex.isEaten) {
            float distance = std::sqrt((pacMan.x - wallVertex.x) * (pacMan.x - wallVertex.x) +
                                       (pacMan.y - wallVertex.y) * (pacMan.y - wallVertex.y));
            if (distance <  pacMan.size * pacMan.radius && pacMan.size>1.5) {
                wallVertex.isEaten = true;
                
            }
        }
    }
}



void growthTimer(int value) {
    if (pacMan.size < 2.0) { // Set the maximum size as needed
        pacMan.size += growthRate;
        pacMan.radius += growthRate;
        glutTimerFunc(1600, growthTimer, 0); // 60 frames per second
    }
}
void growthTimerSmall(int value) {
    if (pacMan.size < 1.2) {
        pacMan.size += growthRate;
        pacMan.radius += growthRate;
        glutTimerFunc(1600, growthTimerSmall, 0);
    }
}


void eatingPelletSizeup() {
    for (Pellet& pellet : pellets) {
        if (pellet.isEaten && pellet.isGreen) {
            growthTimer(0);
        }
        else if (pellet.isEaten && pellet.isBlue){
            growthTimerSmall(0);
            pacManColor[0] = 0.5;
            pacManColor[1] = 0.5;
            pacManColor[2] = 0.5;
        }
    }
}

void drawNextScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);  // Bottom-left
    glVertex2f(0.5, -0.5);   // Bottom-right
    glVertex2f(0.5, 0.5);    // Top-right
    glVertex2f(-0.5, 0.5);   // Top-left
    glEnd();
}

void drawThirdScene() {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.3, -0.3);  // Bottom-left
    glVertex2f(0.3, -0.3);   // Bottom-right
    glVertex2f(0.3, 0.3);    // Top-right
    glVertex2f(-0.3, 0.3);   // Top-left
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == PACMAN_SCENE) {
        drawMaze();
        eatingPelletSizeup();
    } else if (currentScene == NEXT_SCENE) {
        drawNextScene();
    } else if (currentScene == THIRD_SCENE) {
        drawThirdScene();
    }
    glutSwapBuffers();
}

void updateNextScene() {
    // Add code to update elements of the next scene
}

void update() {
    if (currentScene == PACMAN_SCENE) {
        updatePacMan();
    } else if (currentScene == NEXT_SCENE) {
        updateNextScene();
    }

    glutPostRedisplay();
}

void transitionToNextScene() {
    
    if (currentScene == PACMAN_SCENE) {
        currentScene = NEXT_SCENE;
    } else if (currentScene == NEXT_SCENE) {
        currentScene = THIRD_SCENE;
    }

    transitionProgress = 0.0;
    glutTimerFunc(16, [](int) {
        transitionProgress += 0.02; // Adjust the transition speed as needed
        if (transitionProgress >= 1.0) {
            transitionProgress = 1.0;
        }
        glutPostRedisplay();
    }, 0);
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move up
            directionAngle = 90.0;
            pacMan.y += 0.1;
            break;
        case 's': // Move down
            directionAngle = 270.0;
            pacMan.y -= 0.1;
            break;
        case 'a': // Move left
            directionAngle = 180.0;
            pacMan.x -= 0.1;
            break;
        case 'd': // Move right
            directionAngle = 0.0;
            pacMan.x += 0.1;
            break;
        case 'n': // Press 'n' to transition to the next scene
            transitionToNextScene();
            break;
        case 'q' :
            exit(1);
            break;
    }
}



void display() {

    drawScene();

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
    update();
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
    
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();

    return 0;
}
