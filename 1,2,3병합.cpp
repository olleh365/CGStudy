#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <cmath>
#include <vector>
int settime = 0;
float pacManX3 = -1.0f;        // 팩맨 왼쪽 화면 끝에서 출발 = -1
float pacManY3 = 0.0f;
float pacManSpeed3 = 0.005f;
float pacManAngle3 = 45.0f;
bool mouthOpen3 = true;
int drawStarCount = 0;
float drawStarsArray[1000][2] = {};
float scale = 1.0;
int Cflag = 1;    // 초록색 대륙
double mspeed = 50;    // 입벌리는 속도 느려지게끔
bool start3 = false;
bool start2 = false;

// 담배 관련 변수들
bool t1 = true;
bool t2 = true;
bool t3 = true;
bool tfire = true;
double xfire = 0;
double yfire = 0;
double tfireX, tfireY;
bool firemode = true;
double t2X, t2Y;
double x2, y2;
double t3X, t3Y;
double x3, y3;
double t3glR = 0.8, t3glG = 0.8, t3glB = 0.8;
double t2glR = 0.8, t2glG = 0.8, t2glB = 0.8;
double t1X, t1Y;
double x1, y11;
double tabaX = 0.4;
double tabaY = 1.5; //0.05;
bool emergencytabacco = true;
bool movetabacco = false;
bool smokingtabacco = false;
bool downt3 = false;
bool downt2 = false;
// 문구 확대 변수
double phbx = 1.1;
double phby = 1.1;
double phbz = 1.1;
//준우
float directionAngle;
float growthRate = 0.001;
float pacManColor[3] = {1.0, 1.0, 0.0};

struct Pellet {
    float x;
    float y;
    bool isYellow;
    bool isEaten;
    bool isBlue;
    bool isBrown;
    bool isGreen;
};

struct PacMan_o {
    float x;
    float y;
    float radius;
    float mouthAngle;
    bool isOpening;
    float size;
};



PacMan_o pacMan_o = {-1.3, -0.8, 0.05, 45.0, true, 1.0};

//준우

std::vector<Pellet> pellets = {
    {0.0, -0.8, false, false, true},
    {-0.6, 0.8, true},
    {-0.4, 0.8, true},
    {-0.2, 0.8, true},
    {0.0, 0.8, true},
    {0.0, 0.6, true},
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
    {0.6, 0.0, false, false, false, true},
    {0.4, 0.0, true},

    {0.8, 0.0, true},

    {-0.8, -0.2, true},
    {-0.2, -0.2, true},
    {0.0, -0.2, true},
    {0.2, -0.2, true},
    {0.4, -0.2, true},
    {0.6, -0.2, true},
    {0.8, -0.2, true},

    {-0.8, -0.4, true},
    {0.0, -0.4, true},
    {0.8, -0.4, true},
    {-0.2, -0.4, true},

    {-0.8, -0.8, true}, {-0.9, -0.8, true},
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

    {0.2, -0.8, true},
    {0.4, -0.8, true},
    {0.6, -0.8, true},
    {0.8, -0.8, true},
    {-0.8, 0.8, false, false, false, false, true},
};

std::vector<Pellet> mazeWalls = {
// top outside wall
    {0.94,0.99},{0.92,0.99},{0.90,0.99},{0.88,0.99},{0.86,0.99},{0.84,0.99},{0.82,0.99},{0.80,0.99},{0.78,0.99},{0.76,0.99},{0.74,0.99},{0.72,0.99},{0.70,0.99},{0.68,0.99},{0.66,0.99},{0.64,0.99},{0.62,0.99},{0.60,0.99},{0.58,0.99},{0.56,0.99},{0.54,0.99},{0.52,0.99},{0.50,0.99},{0.48,0.99},{0.46,0.99},{0.44,0.99},{0.42,0.99},{0.40,0.99},{0.38,0.99},{0.36,0.99},{0.34,0.99},{0.32,0.99},{0.30,0.99},{0.28,0.99},{0.26,0.99},{0.24,0.99},{0.22,0.99},{0.20,0.99},{0.18,0.99},{0.16,0.99},{0.14,0.99},{0.12,0.99},{0.10,0.99},{0.08,0.99},{0.06,0.99},{0.04,0.99},{0.02,0.99},{0.0,0.99},{-0.02,0.99},{-0.04,0.99},{-0.06,0.99},{-0.08,0.99},{-0.10,0.99},{-0.12,0.99},{-0.14,0.99},{-0.16,0.99},{-0.18,0.99},{-0.20,0.99},{-0.22,0.99},{-0.24,0.99},{-0.26,0.99},{-0.28,0.99},{-0.30,0.99},{-0.32,0.99},{-0.34,0.99},{-0.36,0.99},{-0.38,0.99},{-0.40,0.99},{-0.42,0.99},{-0.44,0.99},{-0.46,0.99},{-0.48,0.99},{-0.50,0.99},{-0.52,0.99},{-0.54,0.99},{-0.56,0.99},{-0.58,0.99},{-0.60,0.99},{-0.62,0.99},{-0.64,0.99},{-0.66,0.99},{-0.68,0.99},{-0.70,0.99},{-0.72,0.99},{-0.74,0.99},{-0.76,0.99},{-0.78,0.99},{-0.80,0.99},{-0.82,0.99},{-0.84,0.99},{-0.86,0.99},{-0.88,0.99},{-0.90,0.99},{-0.92,0.99},{-0.94,0.99},
// bottom outside wall
    {0.94,-0.99},{0.92,-0.99},{0.90,-0.99},{0.88,-0.99},{0.86,-0.99},{0.84,-0.99},{0.82,-0.99},{0.80,-0.99},{0.78,-0.99},{0.76,-0.99},{0.74,-0.99},{0.72,-0.99},{0.70,-0.99},{0.68,-0.99},{0.66,-0.99},{0.64,-0.99},{0.62,-0.99},{0.60,-0.99},{0.58,-0.99},{0.56,-0.99},{0.54,-0.99},{0.52,-0.99},{0.50,-0.99},{0.48,-0.99},{0.46,-0.99},{0.44,-0.99},{0.42,-0.99},{0.40,-0.99},{0.38,-0.99},{0.36,-0.99},{0.34,-0.99},{0.32,-0.99},{0.30,-0.99},{0.28,-0.99},{0.26,-0.99},{0.24,-0.99},{0.22,-0.99},{0.20,-0.99},{0.18,-0.99},{0.16,-0.99},{0.14,-0.99},{0.12,-0.99},{0.10,-0.99},{0.08,-0.99},{0.06,-0.99},{0.04,-0.99},{0.02,-0.99},{0.0,-0.99},{-0.02,-0.99},{-0.04,-0.99},{-0.06,-0.99},{-0.08,-0.99},{-0.10,-0.99},{-0.12,-0.99},{-0.14,-0.99},{-0.16,-0.99},{-0.18,-0.99},{-0.20,-0.99},{-0.22,-0.99},{-0.24,-0.99},{-0.26,-0.99},{-0.28,-0.99},{-0.30,-0.99},{-0.32,-0.99},{-0.34,-0.99},{-0.36,-0.99},{-0.38,-0.99},{-0.40,-0.99},{-0.42,-0.99},{-0.44,-0.99},{-0.46,-0.99},{-0.48,-0.99},{-0.50,-0.99},{-0.52,-0.99},{-0.54,-0.99},{-0.56,-0.99},{-0.58,-0.99},{-0.60,-0.99},{-0.62,-0.99},{-0.64,-0.99},{-0.66,-0.99},{-0.68,-0.99},{-0.70,-0.99},{-0.72,-0.99},{-0.74,-0.99},{-0.76,-0.99},{-0.78,-0.99},{-0.80,-0.99},{-0.82,-0.99},{-0.84,-0.99},{-0.86,-0.99},{-0.88,-0.99},{-0.90,-0.99},{-0.92,-0.99},{-0.94,-0.99},
    // right outside wall
    {0.955, 0.98},{0.97, 0.96},{0.985, 0.94},{1.0, 0.92},{1.0, 0.90},{1.0, 0.88},{1.0, 0.86},{1.0, 0.84},{1.0, 0.82},{1.0, 0.80},{1.0, 0.78},{1.0, 0.76},{1.0, 0.74},{1.0, 0.72},{1.0, 0.70},{1.0, 0.68},{1.0, 0.66},{1.0, 0.64},{1.0, 0.62},{1.0, 0.60},{1.0, 0.58},{1.0, 0.56},{1.0, 0.54},{1.0, 0.52},{1.0, 0.50},{1.0, 0.48},{1.0, 0.46},{1.0, 0.44},{1.0, 0.42},{1.0, 0.40},{1.0, 0.38},{1.0, 0.36},{1.0, 0.34},{1.0, 0.32},{1.0, 0.30},{1.0, 0.28},{1.0, 0.26},{1.0, 0.24},{1.0, 0.22},{1.0, 0.20},{1.0, 0.18},{1.0, 0.16},{1.0, 0.14},{1.0, 0.12},{1.0, 0.10},{1.0, 0.08},{1.0, 0.06},{1.0, 0.04},{1.0, 0.02},{1.0, 0.0},{1.0, -0.02},{1.0, -0.04},{1.0, -0.06},{1.0, -0.08},{1.0, -0.10},{1.0, -0.12},{1.0, -0.14},{1.0, -0.16},{1.0, -0.18},{1.0, -0.20},{1.0, -0.22},{1.0, -0.24},{1.0, -0.26},{1.0, -0.28},{1.0, -0.30},{1.0, -0.32},{1.0, -0.34},{1.0, -0.36},{1.0, -0.38},{1.0, -0.40},{1.0, -0.42},{1.0, -0.44},{1.0, -0.46},{1.0, -0.48},{1.0, -0.50},{1.0, -0.52},{1.0, -0.54},{1.0, -0.56},{1.0, -0.58},{1.0, -0.60},{1.0, -0.62},{1.0, -0.64},{1.0, -0.66},{1.0, -0.68},{1.0, -0.70},{1.0, -0.72},{1.0, -0.74},{1.0, -0.76},{1.0, -0.78},{1.0, -0.80},{1.0, -0.82},{1.0, -0.84},{1.0, -0.86},{1.0, -0.88},{1.0, -0.90},{1.0, -0.92},{0.985, -0.94},{0.97, -0.96},{0.955, -0.98},
   // left outside wall
    {-0.955, 0.98},{-0.97, 0.96},{-0.985, 0.94},{-1.0, 0.92},{-1.0, 0.90},{-1.0, 0.88},{-1.0, 0.86},{-1.0, 0.84},{-1.0, 0.82},{-1.0, 0.80},{-1.0, 0.78},{-1.0, 0.76},{-1.0, 0.74},{-1.0, 0.72},{-1.0, 0.70},{-1.0, 0.68},{-1.0, 0.66},{-1.0, 0.64},{-1.0, 0.62},{-1.0, 0.60},{-1.0, 0.58},{-1.0, 0.56},{-1.0, 0.54},{-1.0, 0.52},{-1.0, 0.50},{-1.0, 0.48},{-1.0, 0.46},{-1.0, 0.44},{-1.0, 0.42},{-1.0, 0.40},{-1.0, 0.38},{-1.0, 0.36},{-1.0, 0.34},{-1.0, 0.32},{-1.0, 0.30},{-1.0, 0.28},{-1.0, 0.26},{-1.0, 0.24},{-1.0, 0.22},{-1.0, 0.20},{-1.0, 0.18},{-1.0, 0.16},{-1.0, 0.14},{-1.0, 0.12},{-1.0, 0.10},{-1.0, 0.08},{-1.0, 0.06},{-1.0, 0.04},{-1.0, 0.02},{-1.0, 0.0},{-1.0, -0.02},{-1.0, -0.04},{-1.0, -0.06},{-1.0, -0.08},{-1.0, -0.10},{-1.0, -0.12},{-1.0, -0.14},{-1.0, -0.16},{-1.0, -0.18},{-1.0, -0.20},{-1.0, -0.22},{-1.0, -0.24},{-1.0, -0.26},{-1.0, -0.28},{-1.0, -0.30},{-1.0, -0.32},{-1.0, -0.34},{-1.0, -0.36},{-1.0, -0.38},{-1.0, -0.40},{-1.0, -0.42},{-1.0, -0.44},{-1.0, -0.46},{-1.0, -0.48},{-1.0, -0.50},{-1.0, -0.52},{-1.0, -0.54},{-1.0, -0.56},{-1.0, -0.58},{-1.0, -0.60},{-1.0, -0.62},{-1.0, -0.64},{-1.0, -0.66},{-1.0, -0.68},{-1.0, -0.70},{-1.12, -0.72},{-1.1, -0.72},{-1.08, -0.72},{-1.06, -0.72},{-1.04, -0.72},{-1.02, -0.72},{-1.0, -0.72},{-1.12, -0.88},{-1.1, -0.88},{-1.08, -0.88},{-1.06, -0.88},{-1.04, -0.88},{-1.02, -0.88},{-1.0, -0.88},{-1.0, -0.90},{-1.0, -0.92},{-0.985, -0.94},{-0.97, -0.96},{-0.955, -0.98},
    
    //center wall
    {-0.2,0.1},{-0.2,0.08},{-0.2,0.06},{-0.2,0.04},{-0.2,0.02},{-0.2,0.0},{-0.2,-0.02},{-0.2,-0.04},{-0.2,-0.06},{-0.2,-0.08},{-0.2,-0.1},{-0.18,-0.1},{-0.16,-0.1},{-0.14,-0.1},{-0.12,-0.1},{-0.1,-0.1},{-0.08,-0.1},{-0.06,-0.1},{-0.04,-0.1},{-0.02,-0.1},{-0.0,-0.1},{0.02,-0.1},
    {0.04,-0.1},{0.06,-0.1},{0.08,-0.1},{0.1,-0.1},{0.12,-0.1},{0.14,-0.1},{0.16,-0.1},{0.18,-0.1},{0.2,-0.1},{0.2,-0.08},{0.2,-0.06},{0.2,-0.04},{0.2,-0.02},{0.2,-0.0},{0.2,0.02},{0.2,0.04},{0.2,0.06},{0.2,0.08},{0.2,0.1},{0.18,0.1},{0.16,0.1},{0.14,0.1},{0.12,0.1},{0.1,0.1},{0.08,0.1},{0.06,0.1},{0.04,0.1},{0.02,0.1},{0.0,0.1},{-0.02,0.1},{-0.04,0.1},{-0.06,0.1},{-0.08,0.1},{-0.1,0.1},{-0.12,0.1},{-0.14,0.1},{-0.16,0.1},{-0.18,0.1},
//left inside wall(1)
    {-0.6, 0.6},{-0.6, 0.58},{-0.6, 0.56},{-0.6, 0.54},{-0.6, 0.52},{-0.6, 0.5},{-0.6, 0.48},{-0.6, 0.46},{-0.6, 0.44},{-0.6, 0.42},
    {-0.58, 0.4},{-0.56, 0.4},{-0.54, 0.4},{-0.52, 0.4},{-0.5, 0.4},{-0.48, 0.4},{-0.46, 0.4},{-0.44, 0.4},{-0.42, 0.4},{-0.4, 0.4},{-0.38, 0.4},{-0.36, 0.4},{-0.34, 0.4},{-0.32, 0.4},{-0.3, 0.4},{-0.28, 0.4},{-0.26, 0.4},{-0.24, 0.4},{-0.22, 0.4},
    {-0.2, 0.42},{-0.2, 0.44},{-0.2, 0.46},{-0.2, 0.48},{-0.48, 0.5},{-0.46, 0.5},{-0.44, 0.5},{-0.42, 0.5},{-0.4, 0.5},{-0.38, 0.5},{-0.36, 0.5},{-0.34, 0.5},{-0.32, 0.5},{-0.3, 0.5},{-0.28, 0.5},{-0.26, 0.5},{-0.24, 0.5},{-0.22, 0.5},{-0.5, 0.52},{-0.5, 0.54},{-0.5, 0.56},{-0.5, 0.58},{-0.5, 0.6},{-0.52, 0.62},{-0.54, 0.62},{-0.56, 0.62},{-0.58, 0.62},
    
//left inside wall(2)
    {-0.58, 0.06},{-0.56, 0.06},{-0.54, 0.06},{-0.52, 0.06},{-0.50, 0.04},{-0.50, 0.02},{-0.50, 0.0},{-0.50, -0.02},{-0.50, -0.04},{-0.50, -0.06},{-0.50, -0.08},{-0.50, -0.1},{-0.50, -0.12},{-0.48, -0.14},{-0.46, -0.14},{-0.44, -0.14},{-0.42, -0.14},{-0.4, -0.14},{-0.38, -0.16},{-0.38, -0.18},{-0.38, -0.2},{-0.38, -0.22},{-0.4, -0.24},{-0.42, -0.24},{-0.44, -0.24},{-0.46, -0.24},{-0.48, -0.24},{-0.5, -0.26},{-0.5, -0.28},{-0.5, -0.3},{-0.5, -0.32},{-0.5, -0.34},{-0.5, -0.36},{-0.5, -0.38},{-0.5, -0.4},{-0.5, -0.42},{-0.5, -0.44},{-0.5, -0.46},{-0.52, -0.48},{-0.54, -0.48},{-0.56, -0.48},{-0.58, -0.48},
    {-0.6, 0.04},{-0.6, 0.02},{-0.6, 0.0},{-0.6, -0.02},{-0.6, -0.04},{-0.6, -0.06},{-0.6, -0.08},{-0.6, -0.1},{-0.6, -0.12},{-0.6, -0.14},{-0.6, -0.16},{-0.6, -0.18},{-0.6, -0.2},{-0.6, -0.22},{-0.6, -0.24},{-0.6, -0.26},{-0.6, -0.28},{-0.6, -0.3},{-0.6, -0.32},{-0.6, -0.34},{-0.6, -0.36},{-0.6, -0.38},{-0.6, -0.4},{-0.6, -0.42},{-0.6, -0.44},{-0.6, -0.46},
//right inside wall(1)
 
    {0.6, 0.6},{0.58, 0.6},{0.56, 0.6},{0.54, 0.6},{0.52, 0.6},{0.50, 0.6},{0.48, 0.6},{0.46, 0.6},{0.44, 0.6},{0.42, 0.6},{0.4, 0.58},{0.4, 0.56},{0.4, 0.54},{0.4, 0.52},{0.38, 0.50},{0.36, 0.50},{0.34, 0.50},{0.32, 0.50},{0.3, 0.50},{0.28, 0.50},{0.26, 0.50},{0.24, 0.50},{0.22, 0.50},{0.2, 0.50},{0.18, 0.48},{0.18, 0.46},{0.18, 0.44},{0.18, 0.42},
    {0.2, 0.4},{0.22, 0.4},{0.24, 0.4},{0.26, 0.4},{0.28, 0.4},{0.3, 0.4},{0.32, 0.4},{0.34, 0.4},{0.36, 0.4},{0.38, 0.4},{0.4, 0.4},{0.38, 0.4},{0.42, 0.4},{0.44, 0.4},{0.46, 0.4},{0.48, 0.4},{0.5, 0.4},{0.52, 0.4},{0.54, 0.4},{0.56, 0.4},{0.58, 0.4},{0.6, 0.4},{0.62, 0.42},{0.62, 0.44},{0.62, 0.46},{0.62, 0.48},{0.62, 0.5},{0.62, 0.52},{0.62, 0.54},{0.62, 0.56},{0.62, 0.58},
//right inside wall(2)
    {0.2, -0.4},{0.22, -0.42},{0.24, -0.44},{0.26, -0.44},{0.28, -0.44},{0.3, -0.44},{0.32, -0.44},{0.34, -0.44},{0.36, -0.44},{0.38, -0.44},{0.4, -0.44},{0.42, -0.44},{0.44, -0.44},{0.46, -0.44},{0.48, -0.44},{0.5, -0.44},{0.52, -0.44},{0.54, -0.44},{0.56, -0.44},{0.58, -0.44},{0.6, -0.42},{0.62, -0.4},{0.6, -0.38},{0.58, -0.36},{0.56, -0.36},{0.54, -0.36},{0.56, -0.36},{0.54, -0.36},{0.52, -0.36},{0.5, -0.36},{0.48, -0.36},{0.46, -0.36},{0.44, -0.36},{0.42, -0.36},{0.4, -0.36},{0.38, -0.36},{0.36, -0.36},{0.34, -0.36},{0.32, -0.36},{0.3, -0.36},{0.28, -0.36},{0.26, -0.36},{0.24, -0.36},{0.22, -0.38},{0.2, -0.4},
    
};






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
                glVertex2f(pellet.x, pellet.y);
                
            } else {
                glColor3f(0.9594, 0.5265, 0.234); // Cigarette ignition part orange
                glVertex2f(pellet.x - 0.06, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.06, pellet.y );
                glColor3f(1.0, 1.0, 1.0);
                glVertex2f(pellet.x - 0.05, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.04, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.03, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.02, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.01, pellet.y + 0.01);
                glVertex2f(pellet.x, pellet.y + 0.01);
                glVertex2f(pellet.x - 0.06, pellet.y + 0.03);
                glVertex2f(pellet.x - 0.05, pellet.y + 0.04);
                glVertex2f(pellet.x - 0.06, pellet.y + 0.05);
                glVertex2f(pellet.x - 0.07, pellet.y + 0.06);
                glVertex2f(pellet.x - 0.06, pellet.y + 0.07);
                
                glColor3f(0.8, 0.8, 0.8);
                glVertex2f(pellet.x - 0.05, pellet.y );
                glVertex2f(pellet.x - 0.04, pellet.y );
                glVertex2f(pellet.x - 0.03, pellet.y );
                glVertex2f(pellet.x - 0.02, pellet.y );
                glVertex2f(pellet.x - 0.01, pellet.y );
                glVertex2f(pellet.x, pellet.y );
                glColor3f(0.8902, 0.7490, 0.4902);
                glVertex2f(pellet.x + 0.01, pellet.y + 0.01);
                glVertex2f(pellet.x + 0.02, pellet.y + 0.01);
                glVertex2f(pellet.x + 0.03, pellet.y + 0.01);
                glColor3f(0.8902, 0.7490, 0.59);
                glVertex2f(pellet.x + 0.01, pellet.y );
                glVertex2f(pellet.x + 0.02, pellet.y );
                glVertex2f(pellet.x + 0.03, pellet.y );
            }
            
        }
    }
    glEnd();
    
    // Draw Pac-Man
    glColor3fv(pacManColor);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(pacMan_o.x, pacMan_o.y);

    for (float angle = pacMan_o.mouthAngle + directionAngle; angle <= 360.0 - pacMan_o.mouthAngle + directionAngle; angle += 5.0) {
        float radianAngle = angle * 3.1415 / 180.0;
        float xPos = pacMan_o.x + pacMan_o.radius * std::cos(radianAngle);
        float yPos = pacMan_o.y + pacMan_o.radius * std::sin(radianAngle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    
    if (settime >= 200) {
        start2 = true;
        
    }
    
}

void updatePacMan_o() {

    if (pacMan_o.isOpening) {
        pacMan_o.mouthAngle += 1.0;
        if (pacMan_o.mouthAngle >= 45.0) {
            pacMan_o.isOpening = false;
        }
    } else {
        pacMan_o.mouthAngle -= 1.0;
        if (pacMan_o.mouthAngle <= 0.0) {
            pacMan_o.isOpening = true;
        }
    }

    // 펠렛을 먹을(충돌)하면 펠렛 베니시
    for (Pellet& pellet : pellets) {
        if (!pellet.isEaten) {
            float distance = std::sqrt((pacMan_o.x - pellet.x) * (pacMan_o.x - pellet.x) +
                                       (pacMan_o.y - pellet.y) * (pacMan_o.y - pellet.y));
            if (distance <  pacMan_o.size * pacMan_o.radius) {
                pellet.isEaten = true;
                
            }
        }
    }
    
    for (Pellet& wallVertex : mazeWalls) {
        if (!wallVertex.isEaten) {
            float distance = std::sqrt((pacMan_o.x - wallVertex.x) * (pacMan_o.x - wallVertex.x) +
                                       (pacMan_o.y - wallVertex.y) * (pacMan_o.y - wallVertex.y));
            if (distance <  pacMan_o.size * pacMan_o.radius && pacMan_o.size>1.0) {
                wallVertex.isEaten = true;
                
            }
        }
    }
}

void growthTimerSmall(int value) {
    if (pacMan_o.size < 1.1) {
        pacMan_o.size += growthRate;
        pacMan_o.radius += growthRate;
        glutTimerFunc(1600, growthTimerSmall, 0);
    }
}
void growthTimerMedium(int value) {
    if (pacMan_o.size < 1.3) {
        pacMan_o.size += growthRate;
        pacMan_o.radius += growthRate;
        glutTimerFunc(1600, growthTimerMedium, 0);
    }
}

void growthTimer(int value) {
    if (pacMan_o.size < 2.0) {
        pacMan_o.size += growthRate;
        pacMan_o.radius += growthRate;
        glutTimerFunc(1600, growthTimer, 0);
    }
}



void eatingPelletSizeup() {
    for (Pellet& pellet : pellets) {
        if (pellet.isEaten && pellet.isBlue) {
            growthTimerSmall(0);
            pacManColor[0] = 0.8;
            pacManColor[1] = 0.8;
            pacManColor[2] = 0.3;
        }

        else if (pellet.isEaten && pellet.isBrown){
            growthTimerMedium(0);
            pacManColor[0] = 0.6;
            pacManColor[1] = 0.6;
            pacManColor[2] = 0.3;
        }
        else if (pellet.isEaten && pellet.isGreen){
            growthTimer(0);
            pacManColor[0] = 0.5;
            pacManColor[1] = 0.5;
            pacManColor[2] = 0.4;
        }
    }
}



void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMaze();
    eatingPelletSizeup();

}



void update() {
    updatePacMan_o();
    glutPostRedisplay();
}



void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move up
            directionAngle = 90.0;
            pacMan_o.y += 0.1;
            break;
        case 's': // Move down
            directionAngle = 270.0;
            pacMan_o.y -= 0.1;
            break;
        case 'a': // Move left
            directionAngle = 180.0;
            pacMan_o.x -= 0.1;
            break;
        case 'd': // Move right
            directionAngle = 0.0;
            pacMan_o.x += 0.1;
            break;
        case 'q' :
            exit(1);
            break;
    }
}

//준우 까지

// 별 출력 함수
void drawStars() {
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);  // 흰색 점
    if (drawStarCount < 1) {
        for (int i = 0; i < 1000; ++i) {
            drawStarsArray[i][0] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1.0부터 1.0 사이의 x 좌표
            drawStarsArray[i][1] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1.0부터 1.0 사이의 y 좌표

        }
    } drawStarCount++;

    for (int i = 0; i < 1000; ++i) {
        glVertex2f(drawStarsArray[i][0], drawStarsArray[i][1]);
    }
    glEnd();
}

// 대륙1
void continent1() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.1, 0.4);
    glVertex2f(-0.095, 0.42);
    glVertex2f(-0.07, 0.47);
    glVertex2f(-0.04, 0.48);
    glVertex2f(-0.01, 0.47);
    glVertex2f(0.02, 0.45);
    glVertex2f(0.05, 0.42);        // (1)
    glVertex2f(0.08, 0.35);
    glVertex2f(0.04, 0.28);
    glVertex2f(0.02, 0.25);
    glVertex2f(0.01, 0.2);
    glVertex2f(0.007, 0.16);
    glVertex2f(0.005, 0.16);
    glVertex2f(0, 0.2);
    glVertex2f(-0.03, 0.2);
    glVertex2f(-0.03, 0.23);
    glVertex2f(-0.03, 0.2);        //(2)
    glVertex2f(-0.02, 0.18);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.02, 0.18);
    glVertex2f(-0.023, 0.14);
    glVertex2f(-0.018, 0.08);
    glVertex2f(-0.024, 0);
    glVertex2f(-0.03, -0.03);
    glVertex2f(-0.038, -0.06);    //(3)
    glVertex2f(-0.05, -0.04);
    glVertex2f(-0.07, -0.02);
    glVertex2f(-0.09, 0.05);
    glVertex2f(-0.06, 0.07);
    glVertex2f(-0.06, 0.08);
    glVertex2f(-0.1, 0.09);
    glVertex2f(-0.1, 0.08);
    glVertex2f(-0.07, 0.1);
    glVertex2f(-0.1, 0.16);
    glVertex2f(-0.15, 0.2);
    glVertex2f(-0.15, 0.24);    //(4)
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.24);
    glVertex2f(-0.12, 0.25);
    glVertex2f(-0.08, 0.24);
    glVertex2f(-0.06, 0.27);
    glVertex2f(-0.07, 0.29);
    glVertex2f(-0.1, 0.32);
    glVertex2f(-0.13, 0.34);
    glVertex2f(-0.11, 0.37);
    glVertex2f(-0.1, 0.4);
    glVertex2f(-0.02, 0.18);
    glEnd();
}
// 대륙2
void continent2() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.45, -0.3);
    glVertex2f(-0.38, -0.35);
    glVertex2f(-0.35, -0.33);
    glVertex2f(-0.32, -0.36);
    glVertex2f(-0.29, -0.38);
    glVertex2f(-0.3, -0.3);
    glVertex2f(-0.27, -0.25);
    glVertex2f(-0.28, -0.21);
    glVertex2f(-0.24, -0.16);
    glVertex2f(-0.17, -0.1);
    glVertex2f(-0.178, -0.06);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.178, -0.06);
    glVertex2f(-0.24, -0.02);
    glVertex2f(-0.24, -0.06);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.24, -0.02);
    glVertex2f(-0.26, 0.04);
    glVertex2f(-0.26, -0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.26, 0.04);
    glVertex2f(-0.22, 0.07);
    glVertex2f(-0.24, 0.08);
    glVertex2f(-0.27, 0.1);
    glVertex2f(-0.29, 0.13);
    glVertex2f(-0.32, 0.12);
    glVertex2f(-0.35, 0.09);
    glVertex2f(-0.394, 0.13);
    glVertex2f(-0.41, 0.09);
    glVertex2f(-0.394, 0.05);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.394, 0.05);
    glVertex2f(-0.41, 0.09);
    glVertex2f(-0.45, 0.06);
    glVertex2f(-0.43, 0.03);
    glVertex2f(-0.44, 0.0);
    glVertex2f(-0.35, 0);
    glVertex2f(-0.35, 0.09);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.44, 0.0);
    glVertex2f(-0.46, -0.05);
    glVertex2f(-0.48, -0.08);
    glVertex2f(-0.48, -0.12);
    glVertex2f(-0.44, -0.14);
    glVertex2f(-0.45, -0.3);
    glVertex2f(-0.35, -0.3);
    glVertex2f(-0.35, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.35, 0.1);
    glVertex2f(-0.26, 0.04);
    glVertex2f(-0.26, -0.16);
    glVertex2f(-0.35, -0.23);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.178, -0.06);
    glVertex2f(-0.24, -0.02);
    glVertex2f(-0.24, -0.13);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.26, -0.02);
    glVertex2f(-0.24, -0.02);
    glVertex2f(-0.24, -0.13);
    glVertex2f(-0.26, -0.14);
    glEnd();
}
// 대륙3
void continent3() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.05, -0.35);
    glVertex2f(-0.05, -0.45);
    glVertex2f(0.23, -0.4);
    glVertex2f(0.23, -0.35);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.05, -0.45);
    glVertex2f(-0.12, -0.32);
    glVertex2f(-0.131, -0.28);
    glVertex2f(-0.05, -0.28);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.131, -0.28);
    glVertex2f(-0.07, -0.24);
    glVertex2f(-0.025, -0.25);
    glVertex2f(-0.005, -0.3);
    glVertex2f(-0.005, -0.45);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.005, -0.45);
    glVertex2f(-0.005, -0.3);
    glVertex2f(-0.052, -0.3);
    glVertex2f(0.05, -0.32);
    glVertex2f(0.052, -0.35);
    glVertex2f(0.07, -0.4);
    glVertex2f(0.08, -0.35);
    glVertex2f(0.084, -0.3);
    glVertex2f(0.087, -0.3);
    glVertex2f(0.088, -0.45);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.087, -0.35);
    glVertex2f(0.13, -0.34);
    glVertex2f(0.15, -0.35);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.15, -0.35);
    glVertex2f(0.16, -0.33);
    glVertex2f(0.17, -0.335);
    glVertex2f(0.18, -0.32);
    glVertex2f(0.23, -0.35);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.23, -0.35);
    glVertex2f(0.25, -0.38);
    glVertex2f(0.23, -0.41);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.18, -0.4);
    glVertex2f(0.15, -0.43);
    glVertex2f(0.12, -0.41);
    glEnd();
    glBegin(GL_POLYGON);

    glEnd();
}

// 대륙 기본값은 초록색
double cglR = 0;
double cglG = 1;
double cglB = 0;
// 대륙들 집합 함수
void drawContinent(int flag) {
    if (flag == 0) {
        glColor3f(0.0, 204, 0);
    }
    else {
        glColor3f(cglR, cglG, cglB);
    }
    continent1();
    continent2();
    continent3();

}

// 담배
void drawTabacco() {
    // 담배꽁초 던짐 모션 위해
    if (t1) {
        t1X = tabaX;
        t1Y = tabaY;
        x1 = tabaX;
        y11 = tabaY;
    }
    else {
        t1X = x1;
        t1Y = y11;
    }
    // 담배 꽁초 (갈색)
    glColor3f(0.8f, 0.4f, 0);
    glBegin(GL_POLYGON);
    glVertex2f(t1X, t1Y);
    glVertex2f(t1X + 0.03, t1Y - 0.2);
    glVertex2f(t1X + 0.2, t1Y - 0.1);
    glVertex2f(t1X + 0.17, t1Y + 0.1);
    glEnd();
    // 담배 몸통1 낙하 모션 위함
    if (t2) {
        t2X = tabaX;
        t2Y = tabaY;
        x2 = tabaX;
        y2 = tabaY;
        glColor3f(0.8f, 0.8f, 0.8);
    }
    else {
        t2X = x2;
        t2Y = y2;
        glColor3f(t2glR, t2glG, t2glB);
    }
    // 담배 몸통1(회색)
    glBegin(GL_POLYGON);
    glVertex2f(t2X + 0.17, t2Y + 0.1);
    glVertex2f(t2X + 0.2, t2Y - 0.1);
    glVertex2f(t2X + 0.37, t2Y);        // x+=0.2,y-=0.1
    glVertex2f(t2X + 0.34, t2Y + 0.2);
    glEnd();

    // 담배 몸통2 낙하 모션 위함
    if (t3) {
        t3X = tabaX;
        t3Y = tabaY;
        x3 = tabaX;
        y3 = tabaY;
        glColor3f(0.8f, 0.8f, 0.8);
    }
    else {
        t3X = x3;
        t3Y = y3;
        glColor3f(t3glR, t3glG, t3glB);
    }
    // 담배 몸통2(회색)
    glBegin(GL_POLYGON);
    glVertex2f(t3X + 0.34, t3Y + 0.2);
    glVertex2f(t3X + 0.37, t3Y);
    glVertex2f(t3X + 0.54, t3Y + 0.1);
    glVertex2f(t3X + 0.51, t3Y + 0.3);
    glEnd();

    // 담배피는 모션 위함
    if (firemode) {
        tfireX = tabaX;
        tfireY = tabaY;
        xfire = tabaX;
        yfire = tabaY;
    }    // 담배가 타기 시작
    else {
        tfireX = xfire;
        tfireY = yfire;
    }
    // 담배불
    if (tfire) {
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(tfireX + 0.54, tfireY + 0.1);
        glVertex2f(tfireX + 0.51, tfireY + 0.3);
        glVertex2f(tfireX + 0.48, tfireY + 0.283);
        glVertex2f(tfireX + 0.51, tfireY + 0.08);
        glEnd();
    }
}
bool burning = false;
int firecount = 0;
// 담배몸통1 짙회색 변하 후 낙하
// 담배꽁초 던짐
void downT2(int value) {
    // 짙회색
    if (t2glR >= 0.3) {
        t2glR -= 0.01;
        t2glG -= 0.01;
        t2glB -= 0.01;
    }
    else    // 낙하
        y2 -= 0.01;

    // 담배꽁초 던짐
    if (y2 <= -1.1) {
        t1 = false;
        x1 += 0.005;
        y11 += 0.01;
        xfire += 0.005;
        yfire += 0.01;
    }
    glutPostRedisplay();
    glutTimerFunc(10, downT2, 0);
}
int firecount2 = 0;
// 담배몸통2 짙회색 변화 후 낙하
void downT3(int value) {
    firecount2++;

    // 짙회색
    if (t3glR >= 0.3) {
        t3glR -= 0.01;
        t3glG -= 0.01;
        t3glB -= 0.01;
    }
    else {    // 낙하
        // 몸통1에 다다랐을때 멈추게끔
        if (firecount > 540) {
            y3 -= 0.1;
            firecount++;
            xfire -= 0.00028;
            yfire -= 0.00017;
        }
    }
    // 담배몸통1 이벤트 호출
    if (firecount > 1120) {
        t2 = false;
        downt3 = false;
        downt2 = true;
    }
    glutPostRedisplay();
    if (!downt3 && downt2) {
        glutTimerFunc(10, downT2, 0);
    }
    else {
        glutTimerFunc(1, downT3, 0);
    }
}

// 담배피기
void smokingTabacco(int value) {
    firemode = false;
    firecount++;
    if (firecount > 100)
        burning = true;
    // 몸통2에 다다랐을때
    if (firecount < 550) {
        if (firecount == 549)
            t3 = false;
        xfire -= 0.00028;
        yfire -= 0.00017;
    }

    glutPostRedisplay();
    if (!t3) {
        smokingtabacco = false;
        glutTimerFunc(50, downT3, 0);
    }
    else {
        glutTimerFunc(1, smokingTabacco, 0);
    }
}
bool collapse = false;
int waitcount = 0;
// 팩맨과 충돌했을때 멈춤 + 담배피기 이벤트 호출
void moveTabacco(int value) {
    waitcount++;
    if (tabaX >= 0)
        tabaX -= 0.002;

    if (tabaX <= 0 && collapse && waitcount > 400) {
        movetabacco = false;
        smokingtabacco = true;

    }
    glutPostRedisplay();
    if (!movetabacco && smokingtabacco) {
        glutTimerFunc(1, smokingTabacco, 0);
    }
    else {
        glutTimerFunc(10, moveTabacco, 0);
    }
}
bool downTabacco = true;
bool onebound = true;
bool twobound = true;

// 낙하 후 투바운드까지
void emergencyTabacco(int value) {
    if (downTabacco) {        // 담배 낙하
        if (tabaY > 0.085)
            tabaY -= 0.03;
        else
            downTabacco = false;
    }
    else if (onebound) {    // 담배 첫번째 바운드
        if (tabaX <= 0.45) {
            tabaX += 0.004;
            tabaY += 0.01;
        }
        else if (tabaY >= 0.085) {
            tabaX += 0.004;
            tabaY -= 0.01;
        }
        else
            onebound = false;
    }
    else if (twobound) {    // 담배 두번째 바운드
        if (tabaX <= 0.52) {
            tabaX += 0.002;
            tabaY += 0.006;
        }
        else if (tabaY >= 0.085) {
            tabaX += 0.002;
            tabaY -= 0.006;
        }
        else {
            twobound = false;
            emergencytabacco = false;
            movetabacco = true;
        }
    }
    glutPostRedisplay();
    if (!emergencytabacco && movetabacco) {
        glutTimerFunc(10, moveTabacco, 0);
    }
    else {
        glutTimerFunc(20, emergencyTabacco, 0);
    }
}

// 바다 기본색 = 블루
double pglR = 0;
double pglG = 0;
double pglB = 1;

bool phflag = false;
// '노 담' 문구 출력
void drawPhrase(int flag) {
    if (flag) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(phbx, phby, phbz); // x, y, z 축 방향으로 확대
        glColor3f(1, 1, 1);
        // 'ㄴ'
        glBegin(GL_POLYGON);
        glVertex2f(-0.04, 0.05);
        glVertex2f(-0.04, 0.025);
        glVertex2f(-0.035, 0.025);
        glVertex2f(-0.035, 0.05);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-0.035, 0.025);
        glVertex2f(-0.015, 0.025);
        glVertex2f(-0.015, 0.03);
        glVertex2f(-0.035, 0.03);
        glEnd();
        // 'ㅗ'
        glBegin(GL_POLYGON);
        glVertex2f(-0.029, 0.0175);
        glVertex2f(-0.029, 0.01);
        glVertex2f(-0.024, 0.01);
        glVertex2f(-0.024, 0.0175);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-0.045, 0.01);
        glVertex2f(-0.045, 0.005);
        glVertex2f(-0.01, 0.005);
        glVertex2f(-0.01, 0.01);
        glEnd();
        // 'ㄷ'
        glBegin(GL_POLYGON);
        glVertex2f(0.018, 0.055);
        glVertex2f(0.018, 0.03);
        glVertex2f(0.021, 0.03);
        glVertex2f(0.021, 0.055);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.018, 0.055);
        glVertex2f(0.018, 0.051);
        glVertex2f(0.033, 0.051);
        glVertex2f(0.033, 0.055);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.018, 0.034);
        glVertex2f(0.018, 0.03);
        glVertex2f(0.033, 0.03);
        glVertex2f(0.033, 0.034);
        glEnd();
        // 'ㅏ'
        glBegin(GL_POLYGON);
        glVertex2f(0.038, 0.065);
        glVertex2f(0.038, 0.026);
        glVertex2f(0.041, 0.026);
        glVertex2f(0.041, 0.065);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.041, 0.05);
        glVertex2f(0.041, 0.045);
        glVertex2f(0.044, 0.045);
        glVertex2f(0.044, 0.05);
        glEnd();
        // 'ㅁ'
        glBegin(GL_POLYGON);
        glVertex2f(0.022, 0.023);
        glVertex2f(0.022, 0.00);
        glVertex2f(0.025, 0.00);
        glVertex2f(0.025, 0.023);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.022, 0.00);
        glVertex2f(0.04, 0.00);
        glVertex2f(0.04, 0.004);
        glVertex2f(0.022, 0.004);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.037, 0.00);
        glVertex2f(0.04, 0.00);
        glVertex2f(0.04, 0.023);
        glVertex2f(0.037, 0.023);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.022, 0.023);
        glVertex2f(0.022, 0.019);
        glVertex2f(0.04, 0.019);
        glVertex2f(0.04, 0.023);
        glEnd();
    }
}

// 팩맨 + 대륙
void drawPacMan3() {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(pacManX3, pacManY3, 0.0f); // 팩맨을 현재위치로 변환


    glColor3f(pglR, pglG, pglB); // 팩맨 파랑색

    // 팩맨모양
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0); // Center of Pac-Man
    glVertex2f(0.0, 0.0); // 팩맨의 센터위치
    for (float angle = pacManAngle3; angle <= 360.0 - pacManAngle3; angle += 1.0) {
        float radians = angle * (3.14 / 180.0);
        float x = 0.6 * cos(radians);
        float y = 0.6 * sin(radians);
        glVertex2f(x, y);
    }
    glEnd();

    // 팩맨 입
    if (mouthOpen3) {
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        float radians1 = (pacManAngle3 - 20.0) * (3.14 / 180.0);
        float x1 = 0.3 * cos(radians1);
        float y1 = 0.3 * sin(radians1);
        glVertex2f(x1, y1);
        float radians2 = (360.0 - pacManAngle3 + 20.0) * (3.14 / 180.0);
        float x2 = 0.3 * cos(radians2);
        float y2 = 0.3 * sin(radians2);
        glVertex2f(x2, y2);
        glEnd();
    }
    drawContinent(Cflag);
    drawPhrase(phflag);

    glutSwapBuffers();
    glFlush();
}

//0.5초 단위로 팩맨 입벌렸다가 움츠렸다가 업데이트
//갈수록 느리게 움직임
void updatePacMan3(int value) {
    mspeed += 0.4;
    if (mouthOpen3) {
        pacManAngle3 -= 2.0;
    }
    else {
        pacManAngle3 += 2.0;
    }
    if (pacManAngle3 <= 25.0 || pacManAngle3 >= 45.0) {
        mouthOpen3 = !mouthOpen3;
    }
    
    
    glutPostRedisplay();
    glutTimerFunc(mspeed, updatePacMan3, 0);
}

// 팩맨 이동
void movePacMan3(int value) {
    if (pacManX3 <= -0.3)
        pacManX3 += 0.003;
    if (pacManX3 > -0.3)
        collapse = true;
    glutPostRedisplay();
    glutTimerFunc(18, movePacMan3, 0);
}
bool burningq = false;
int deathcount = 0;
// 대륙 색상 마무리
void updateContinent2(int value) {
    deathcount++;
    if (cglR > 0.25) {
        cglB -= 0.01;
        cglG -= 0.01;
        cglR -= 0.03;
        if (pacManY3 >= -0.02) {
            pacManY3 -= 0.07;
        }
        else if (pacManY3 <= 0.02) {
            pacManY3 += 0.07;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, updateContinent2, 0);
}
// 대륙들 색상변화
void updateContinent(int value) {
    if (burning) {
        // 대륙 = 초록색 -> 붉은색 -> 붉회색
        if (cglB <= 0.25) {
            cglB += 0.01;
            cglG -= 0.015;
            cglR += 0.01;
        }
        // 짙녹색 -> 짙회색
        else if (cglR <= 0.45) {
            cglB += 0.01;
            cglG -= 0.001;
            cglR += 0.01;
        }
        // 붉게
        else if (cglR <= 0.53) {
            cglR += 0.01;
            if (pacManY3 >= -0.02) {
                pacManY3 -= 0.07;
            }
            else if (pacManY3 <= 0.02) {
                pacManY3 += 0.07;
            }
        }
        else if (cglG >= 0.4) {
            cglG -= 0.01;
        }
        // 붉회색
        else if (cglG >= 0.24) {
            cglB -= 0.03;
            cglG -= 0.01;
            cglR -= 0.01;
        }
        else {
            burningq = true;
        }

        glutPostRedisplay();
        if (burningq) {
            glutTimerFunc(50, updateContinent2, 0);
        }
        else {
            glutTimerFunc(50, updateContinent, 0);
        }
    }
    else {
        glutTimerFunc(50, updateContinent, 0);
    }

}
int rgbcount = 0;
// 바다 색상변화
void updateOcean(int value) {
    if (burning) {
        // 짙은 보라
        if (rgbcount == 0) {
            if (pglR <= 0.15) {
                pglR += 0.002;
                pglG += 0.002;
                pglB -= 0.01;
            }
            else
                rgbcount++;
        }
        if (rgbcount == 1) {
            if (pglR >= 0.08) {
                pglR -= 0.01;
                pglG -= 0.01;
                pglB -= 0.01;
            }
            else
                rgbcount++;
        }
        if (rgbcount == 2) {
            if (pglB >= 0.15) {
                pglR -= 0.001;
                pglG -= 0.003;
                pglB -= 0.01;
            }
            rgbcount++;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(50, updateOcean, 0);
}

// '노 담' 문구 출력
void emergencyPhrase(int value) {
    if (phbx <= 10) {
        phbx += 0.02;
        phby += 0.015;
        phbz += 0.01;
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glutPostRedisplay();
    glutTimerFunc(1, emergencyPhrase, 0);
}
// 팩맨 사망
void deathPacMan3(int value) {
    if (deathcount > 37) {
        pacManY3 -= 0.01;
        pacManX3 += 0.002;
    }
    if (deathcount > 85) {
        phflag = true;
    }
    glutPostRedisplay();
    if (phflag) {
        glutTimerFunc(50, emergencyPhrase, 0);
    }
    else {
        glutTimerFunc(20, deathPacMan3, 0);
    }
}

// 장면 3 화면 출력 함수
void Scene3() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    drawStars();
    drawTabacco();
    glPushMatrix();
    drawPacMan3();
    glPopMatrix();
    
    
}



float b = 0.6;
float move = 0;
float ciga_move = 0;
float ciga_d_move = 0;
float randbox_y = 0;
float ciga_move2 = 0;
float ciga_u_move2 = 0;
bool firebool = true;
bool move_randbox = true;
bool cigamoveRight = true;
bool cigamoveDown = false;
bool cigamove_turn = false;
bool moveRight = true;
bool pacMan_move = true;
bool monstermove_turn = false;

//팩맨 설정값
struct PacMan {
    float x;
    float y;
    float radius;
    float mouthAngle;
    bool isOpening;
};

PacMan pacMan = { -1.0, -0.61, 0.075, 45.0 };


void Draw_m_Randbox() {

    //원점
    //좌측 노란 블럭
    glColor3f(0.9828, 0.5928, 0.2184);

    glBegin(GL_QUADS);
    glVertex2f(0.112 * 4 - 0.407, -0.09 + randbox_y);
    glVertex2f(0.112 * 4 - 0.407, +0.106 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +0.106 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +-0.09 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.407, +0.106 + randbox_y);
    glVertex2f(0.112 * 4 - 0.407, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +0.106 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.512, +-0.07775 + randbox_y);
    glVertex2f(0.112 * 4 - 0.512, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.505, +-0.07775 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4, +-0.09 + randbox_y);
    glVertex2f(0.112 * 4 - 0.4, +-0.07775 + randbox_y);
    glVertex2f(0.112 * 4 - 0.512, +-0.07775 + randbox_y);
    glVertex2f(0.112 * 4 - 0.512, +-0.09 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4, +-0.07775 + randbox_y);
    glVertex2f(0.112 * 4 - 0.4, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.407, +0.09375 + randbox_y);
    glVertex2f(0.112 * 4 - 0.407, +-0.07775 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.414, +0.06925 + randbox_y);
    glVertex2f(0.112 * 4 - 0.414, +0.0815 + randbox_y);
    glVertex2f(0.112 * 4 - 0.421, +0.0815 + randbox_y);
    glVertex2f(0.112 * 4 - 0.421, +0.06925 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.498, +-0.0655 + randbox_y);
    glVertex2f(0.112 * 4 - 0.498, +-0.05325 + randbox_y);
    glVertex2f(0.112 * 4 - 0.491, +-0.05325 + randbox_y);
    glVertex2f(0.112 * 4 - 0.491, +-0.0655 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.414, +-0.0655 + randbox_y);
    glVertex2f(0.112 * 4 - 0.414, +-0.05325 + randbox_y);
    glVertex2f(0.112 * 4 - 0.421, +-0.05325 + randbox_y);
    glVertex2f(0.112 * 4 - 0.421, +-0.0655 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.498, +0.06925 + randbox_y);
    glVertex2f(0.112 * 4 - 0.498, +0.0815 + randbox_y);
    glVertex2f(0.112 * 4 - 0.491, +0.0815 + randbox_y);
    glVertex2f(0.112 * 4 - 0.491, +0.06925 + randbox_y);

    //상자 안 물음표 그림자
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.456, +-0.0655 + randbox_y);
    glVertex2f(0.112 * 4 - 0.456, +-0.041 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +-0.041 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +-0.0655 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.456, +-0.00425 + randbox_y);
    glVertex2f(0.112 * 4 - 0.456, +-0.02875 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +-0.02875 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +-0.00425 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.449, +-0.00425 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +-0.00425 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.442, +-0.00425 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +0.04475 + randbox_y);
    glVertex2f(0.112 * 4 - 0.428, +0.04475 + randbox_y);
    glVertex2f(0.112 * 4 - 0.428, +-0.00425 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.435, +0.04475 + randbox_y);
    glVertex2f(0.112 * 4 - 0.435, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.47, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.47, +0.04475 + randbox_y);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.463, +0.04475 + randbox_y);
    glVertex2f(0.112 * 4 - 0.463, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.477, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.477, +0.04475 + randbox_y);

    //상자 안 물음표 (x좌표를 -0.007, y좌표를 0.01225 더함)

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.463, +-0.05325 + randbox_y);
    glVertex2f(0.112 * 4 - 0.463, +-0.02875 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +-0.02875 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +-0.05325 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.463, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.463, +-0.0165 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +-0.0165 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +0.008 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.456, +0.007 + randbox_y);
    glVertex2f(0.112 * 4 - 0.456, +0.02025 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +0.02025 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +0.007 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.449, +0.008 + randbox_y);
    glVertex2f(0.112 * 4 - 0.449, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.435, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.435, +0.008 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.442, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.442, +0.06925 + randbox_y);
    glVertex2f(0.112 * 4 - 0.477, +0.06925 + randbox_y);
    glVertex2f(0.112 * 4 - 0.477, +0.057 + randbox_y);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * 4 - 0.470, +0.057 + randbox_y);
    glVertex2f(0.112 * 4 - 0.470, +0.02025 + randbox_y);
    glVertex2f(0.112 * 4 - 0.484, +0.02025 + randbox_y);
    glVertex2f(0.112 * 4 - 0.484, +0.057 + randbox_y);
}
void DrawRandbox(float x, float y) {

    //원점
    //좌측 노란 블럭
    glColor3f(0.9828, 0.5928, 0.2184);

    glBegin(GL_QUADS);
    glVertex2f(0.112 * x - 0.407, y * 0.196 - 0.09);
    glVertex2f(0.112 * x - 0.407, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + -0.09);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.407, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.407, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + 0.106);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.505, y * 0.196 + -0.07775);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.09);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.407, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.407, y * 0.196 + -0.07775);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.414, y * 0.196 + 0.06925);
    glVertex2f(0.112 * x - 0.414, y * 0.196 + 0.0815);
    glVertex2f(0.112 * x - 0.421, y * 0.196 + 0.0815);
    glVertex2f(0.112 * x - 0.421, y * 0.196 + 0.06925);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.498, y * 0.196 + -0.0655);
    glVertex2f(0.112 * x - 0.498, y * 0.196 + -0.05325);
    glVertex2f(0.112 * x - 0.491, y * 0.196 + -0.05325);
    glVertex2f(0.112 * x - 0.491, y * 0.196 + -0.0655);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.414, y * 0.196 + -0.0655);
    glVertex2f(0.112 * x - 0.414, y * 0.196 + -0.05325);
    glVertex2f(0.112 * x - 0.421, y * 0.196 + -0.05325);
    glVertex2f(0.112 * x - 0.421, y * 0.196 + -0.0655);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.498, y * 0.196 + 0.06925);
    glVertex2f(0.112 * x - 0.498, y * 0.196 + 0.0815);
    glVertex2f(0.112 * x - 0.491, y * 0.196 + 0.0815);
    glVertex2f(0.112 * x - 0.491, y * 0.196 + 0.06925);

    //상자 안 물음표 그림자
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + -0.0655);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + -0.041);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.041);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.0655);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + -0.00425);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + -0.02875);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.02875);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.00425);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + -0.00425);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.00425);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + -0.00425);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + 0.04475);
    glVertex2f(0.112 * x - 0.428, y * 0.196 + 0.04475);
    glVertex2f(0.112 * x - 0.428, y * 0.196 + -0.00425);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.435, y * 0.196 + 0.04475);
    glVertex2f(0.112 * x - 0.435, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.47, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.47, y * 0.196 + 0.04475);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + 0.04475);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.477, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.477, y * 0.196 + 0.04475);

    //상자 안 물음표 (x좌표를 -0.007, y좌표를 0.01225 더함)

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + -0.05325);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + -0.02875);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + -0.02875);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + -0.05325);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.463, y * 0.196 + -0.0165);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + -0.0165);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.008);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + 0.007);
    glVertex2f(0.112 * x - 0.456, y * 0.196 + 0.02025);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.02025);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.007);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.008);
    glVertex2f(0.112 * x - 0.449, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.435, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.435, y * 0.196 + 0.008);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.442, y * 0.196 + 0.06925);
    glVertex2f(0.112 * x - 0.477, y * 0.196 + 0.06925);
    glVertex2f(0.112 * x - 0.477, y * 0.196 + 0.057);

    glColor3f(0.78, 0.2964, 0.0468);
    glVertex2f(0.112 * x - 0.470, y * 0.196 + 0.057);
    glVertex2f(0.112 * x - 0.470, y * 0.196 + 0.02025);
    glVertex2f(0.112 * x - 0.484, y * 0.196 + 0.02025);
    glVertex2f(0.112 * x - 0.484, y * 0.196 + 0.057);
}
void DrawBrickbox(float x, float y) {
    glColor3f(0.78, 0.2964, 0.0468);
    glBegin(GL_QUADS);
    glVertex2f(0.112 * x - 0.4, y * 0.196 - 0.09);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09);

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + 0.09375);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + 0.09375);


    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.09);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.07775);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09 + (0.01225 * 4));


    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4, y * 0.196 + -0.106 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.106 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.106 + (0.01225 * 16));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.106 + (0.01225 * 16));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.106 + (0.01225 * 16));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.106 + (0.01225 * 16));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.106 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.106 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.106 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.106 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.106 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0, 0, 0);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.106 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 12));











}
void DrawTile(float x, float y) {
    glColor3f(0.78, 0.2964, 0.0468);

    glBegin(GL_QUADS);
    glVertex2f(0.112 * x - 0.4, y * 0.196 - 0.09);
    glVertex2f(0.112 * x - 0.4, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + 0.106);
    glVertex2f(0.112 * x - 0.512, y * 0.196 + -0.09);

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -1));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 6));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -11));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 1));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -10));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 5));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -11));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 4));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -12));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 3));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -12));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 1));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -10));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 4));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * 0));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 6));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -4));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 10));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -5));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 10));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -1));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 11));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -6));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 1));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -14));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 0));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -15));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 0));//플러스로   아래서 밑에




    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -15));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 0));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -12));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 0));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -12));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 3));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -11));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 4));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -13));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 2));//플러스로   아래서 밑에



    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -10));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -10));//왼쪽에서 거리 첫째 오른쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 4));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -6));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -6));//오른쪽에서 거리 첫째 왼쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 6));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -6));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -6));//오른쪽에서 거리 첫째 왼쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 9));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -1));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -1));//오른쪽에서 거리 첫째 왼쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 11));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * 0));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * 0));//오른쪽에서 거리 첫째 왼쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 15));//플러스로   아래서 밑에

    glColor3f(982.8, 0.7332, 0.6864);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * 0));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * 0));//오른쪽에서 거리 첫째 왼쪽에서 거리 두째
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 15));//플러스로   아래서 밑에
}
void DrawPipe_part_1(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * 0));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 0));//플러스로   아래서 밑에

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0., 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 0));
}
void DrawPipe_part_2(float x, float y) {
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 1));


    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 1));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 15));

    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 2));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 14));
}
void DrawPipe_part_3(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -14));//마이너스 위에서 아래
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 1));//플러스로   아래서 밑에

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 2));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 15));

    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 2));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 2));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 2));
}
void DrawPipe_part_4(float x, float y) {
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0.4992, 0.8112, 0.624);//연한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0.6552, 0);//진한 배관색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 0));
}
void DrawBush_m(float x, float y) {

    glBegin(GL_QUADS);
    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 3));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0, 0.6552, 0); //덤불 진한 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0.6552, 0); //덤불 진한 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0.6552, 0); //덤불 진한 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 9));

    glColor3f(0, 0.6552, 0); //덤불 진한 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 10));


    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 9));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 10));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 14));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 15));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 14));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 8));
    glEnd();
}
void DrawBush_l(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 1));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 1));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 3));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 7));
    glEnd();

}
void DrawBush_r(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.4992, 0.8112, 0.0624); //덤불 색
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 3));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 4));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 4));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 1));
    glEnd();
}
void DrawCloud_D_r(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 10));

    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 10));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 9));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 10));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 14));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 15));
    glEnd();
}
void DrawCloud_D_m(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 10));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 10));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 10));


    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 15));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 11));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 12));
    glEnd();
}
void DrawCloud_D_l(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 15));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 11));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 15));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 15));
    glEnd();
}
void DrawCloud_U_r(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 6));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 6));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 5));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 6));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 7));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 4));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 3));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 4));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 1));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 0));
    glEnd();
}
void DrawCloud_U_m(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 10));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -15), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 10));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 13));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 14));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 15));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 11));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 11));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 12));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 15), y * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 9));
    glColor3f(0.234, 0.7332, 0.9828);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 10));
    glEnd();
}
void DrawCloud_U_l(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 3));
    glColor3f(1, 1, 1);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -7), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 1));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 3));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 5));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 6));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 7));
    glEnd();
}
void DrawMountain_l(float x, float y) {
    glBegin(GL_QUADS);
    for (int i = 15; i >= 0; i--) {
        glColor3f(0, 0, 0);
        glVertex2f(0.112 * x - 0.4 + (0.007 * -i), y * 0.196 + -0.09 + (0.01225 * 0));
        glVertex2f(0.112 * x - 0.4 + (0.007 * -i), y * 0.196 + 0.106 + (0.01225 * -i));
        glVertex2f(0.112 * x - 0.512 + (0.007 * (15 - i)), y * 0.196 + 0.106 + (0.01225 * -i));
        glVertex2f(0.112 * x - 0.512 + (0.007 * (15 - i)), y * 0.196 + -0.09 + (0.01225 * 0));
    }
    for (int i = 1; i <= 15; i++) {
        glColor3f(0, 0.6552, 0);
        glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
        glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * (-16 + i)));
        glVertex2f(0.112 * x - 0.512 + (0.007 * i), y * 0.196 + 0.106 + (0.01225 * (-16 + i)));
        glVertex2f(0.112 * x - 0.512 + (0.007 * i), y * 0.196 + -0.09 + (0.01225 * 0));
    }
    glEnd();
}
void DrawMountain_r(float x, float y) {
    glBegin(GL_QUADS);
    for (int i = 15; i >= 0; i--) {
        glColor3f(0, 0, 0);
        glVertex2f(0.112 * x - 0.4 + (0.007 * -(15 - i)), y * 0.196 + -0.09 + (0.01225 * 0));
        glVertex2f(0.112 * x - 0.4 + (0.007 * -(15 - i)), y * 0.196 + 0.106 + (0.01225 * -i));
        glVertex2f(0.112 * x - 0.512 + (0.007 * i), y * 0.196 + 0.106 + (0.01225 * -i));
        glVertex2f(0.112 * x - 0.512 + (0.007 * i), y * 0.196 + -0.09 + (0.01225 * 0));

    }
    for (int i = 1; i <= 15; i++) {
        glColor3f(0, 0.6552, 0);
        glVertex2f(0.112 * x - 0.4 + (0.007 * -i), y * 0.196 + -0.09 + (0.01225 * 0));
        glVertex2f(0.112 * x - 0.4 + (0.007 * -i), y * 0.196 + 0.106 + (0.01225 * (-16 + i)));
        glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * (-16 + i)));
        glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    }
    glEnd();
}
void DrawMountain_m(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0, 0.6552, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -16), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -16), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 16), y * 0.196 + 0.106 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 16), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 8));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 11));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 10));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 15));
    glEnd();
}
void DrawMountain_t(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0, 0.6552, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 0), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -0), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 0));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 1));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 1));
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 2));
    glEnd();
}
void DrawCloud_zip(float a, float b) {
    DrawCloud_D_r(a + 1, b);
    DrawCloud_D_m(a, b);
    DrawCloud_D_l(a - 1, b);
    DrawCloud_U_r(a + 1, b + 1);
    DrawCloud_U_m(a, b + 1);
    DrawCloud_U_l(a - 1, b + 1);
}
void DrawCloud_zip2(float a, float b) {
    DrawCloud_D_r(a + 3, b);
    DrawCloud_U_r(a + 3, b + 1);
    DrawCloud_D_m(a, b);
    DrawCloud_U_m(a, b + 1);
    DrawCloud_D_m(a + 1, b);
    DrawCloud_U_m(a + 1, b + 1);
    DrawCloud_D_m(a + 2, b);
    DrawCloud_U_m(a + 2, b + 1);
    DrawCloud_D_l(a - 1, b);
    DrawCloud_U_l(a - 1, b + 1);
}
void DrawBush_zip(float a) {
    DrawBush_l(a - 1, -3);
    DrawBush_m(a, -3);
    DrawBush_r(a + 1, -3);

}
void DrawBush_zip2(float a) {
    DrawBush_l(a - 1, -3);
    DrawBush_m(a, -3);
    DrawBush_m(a + 1, -3);
    DrawBush_r(a + 2, -3);
}
void DrawPipe_part_zip(float a) {
    DrawPipe_part_1(a, -3);
    DrawPipe_part_2(a, -2);
    DrawPipe_part_3(a + 1, -2);
    DrawPipe_part_4(a + 1, -3);
}
void DrawMountain_zip(float a) {
    DrawMountain_l(a - 1, -3);
    DrawMountain_m(a, -3);
    DrawMountain_r(a + 1, -3);
    DrawMountain_t(a, -2);
}
void DrawMonster() {
    glBegin(GL_QUADS);
    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -0) + move, -3 * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -0) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 0) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 0) + move, -3 * 0.196 + -0.09 + (0.01225 * 6));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + move, -3 * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + move, -3 * 0.196 + -0.09 + (0.01225 * 5));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + move, -3 * 0.196 + -0.09 + (0.01225 * 9));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + move, -3 * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + move, -3 * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + -0.09 + (0.01225 * 12));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + -0.09 + (0.01225 * 13));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + move, -3 * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + move, -3 * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + move, -3 * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + move, -3 * 0.196 + -0.09 + (0.01225 * 14));

    glColor3f(0.5967, 0.2925, 0.0351);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + -0.09 + (0.01225 * 15));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + 0.106 + (0.01225 * -0));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + -0.09 + (0.01225 * 15));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + move, -3 * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + -0.09 + (0.01225 * 1));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + move, -3 * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + move, -3 * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + move, -3 * 0.196 + -0.09 + (0.01225 * 2));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + move, -3 * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + move, -3 * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + move, -3 * 0.196 + -0.09 + (0.01225 * 3));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + move, -3 * 0.196 + -0.09 + (0.01225 * 7));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0.9945, 0.780, 0.7176);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + move, -3 * 0.196 + -0.09 + (0.01225 * 11));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + move, -3 * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + move, -3 * 0.196 + -0.09 + (0.01225 * 8));

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + move, -3 * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + move, -3 * 0.196 + -0.09 + (0.01225 * 9));
}
void Fire1(int x, int y)
{
    glBegin(GL_QUADS);



    glColor3f(0.9906, 0.5031, 0.0741);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.9867, 0.3471, 0.0819);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 1));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 2));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 3));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 4));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -8));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 5));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 8));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 9));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -12), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 10));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 6), y * 0.196 + -0.09 + (0.01225 * 10));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 14));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 7));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 6));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 8));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 13));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 13));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 5));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 10));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 4));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 1));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(1, 1, 1);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 2));


    glEnd();
}
void Fire2(int x, int y)
{
    glBegin(GL_QUADS);



    glColor3f(0.9906, 0.5031, 0.0741);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(0.9867, 0.3471, 0.0819);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 3), y * 0.196 + -0.09 + (0.01225 * 1));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -11), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 3));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 4));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -14), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + 0.106 + (0.01225 * -11));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 1), y * 0.196 + -0.09 + (0.01225 * 5));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 9));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -6));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 9));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -13), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 2), y * 0.196 + -0.09 + (0.01225 * 11));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 4), y * 0.196 + -0.09 + (0.01225 * 8));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -9), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -4));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 11));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + -0.09 + (0.01225 * 12));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -10), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 5), y * 0.196 + -0.09 + (0.01225 * 12));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 10));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 10));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 6));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -9));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 6));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 7));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -2));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 7));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 8));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 8));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 9), y * 0.196 + -0.09 + (0.01225 * 14));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + -0.09 + (0.01225 * 5));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -4), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -7));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 5));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 4));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + 0.106 + (0.01225 * -5));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 11), y * 0.196 + -0.09 + (0.01225 * 4));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 11));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -3));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 11));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 14));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -1));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 14));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + -0.09 + (0.01225 * 3));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -1), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + 0.106 + (0.01225 * -10));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 14), y * 0.196 + -0.09 + (0.01225 * 3));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + -0.09 + (0.01225 * 1));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -2), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 13), y * 0.196 + -0.09 + (0.01225 * 1));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -3), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 12), y * 0.196 + -0.09 + (0.01225 * 0));

    glColor3f(1, 1, 1);

    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -6), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + 0.106 + (0.01225 * -12));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 8), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -8), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + 0.106 + (0.01225 * -14));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 7), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 0));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -15));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 0));

    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + -0.09 + (0.01225 * 2));
    glVertex2f(0.112 * x - 0.4 + (0.007 * -5), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + 0.106 + (0.01225 * -13));
    glVertex2f(0.112 * x - 0.512 + (0.007 * 10), y * 0.196 + -0.09 + (0.01225 * 2));


    glEnd();
}
void Drawcigarette() {
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 0) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -15) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -15) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 0) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -14) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -14) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -14) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -14) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 1) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 14) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 14) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 13) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -0) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -0) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 15) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 15) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 14) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -1) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -1) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 14) + ciga_d_move);

    glColor3f(0.9594, 0.5265, 0.234);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -14) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -14) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 1) + ciga_d_move);

    glColor3f(0.9945, 0.9594, 0.1911);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);

    glColor3f(0.9945, 0.9594, 0.1911);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 9) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);


    glColor3f(0.4095, 0.4407, 0.4407);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -11) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 4) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 10) + ciga_d_move);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -2) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 13) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 11) + ciga_d_move);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -1) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 14) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 14) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 12) + ciga_d_move);

    glColor3f(0.4095, 0.4407, 0.4407);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0.2964, 0.3666, 0.3666);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -12) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -13) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 3) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 2) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -12) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 3) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -11) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 4) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -10) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 5) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -7) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -9) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 8) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 6) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -6) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 9) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 7) + ciga_d_move);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.4 + (0.007 * -5) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + 0.106 + (0.01225 * -7) + ciga_d_move);
    glVertex2f(0.112 * 4 - 0.512 + (0.007 * 10) + ciga_move, 1 * 0.196 + -0.09 + (0.01225 * 8) + ciga_d_move);
    glEnd();
}
void Drawcigarette2() {
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 0) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -15) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -15) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 0) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -14) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -14) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -14) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -14) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 1) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 1) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 14) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 14) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 13) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -0) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -0) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 15) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 15) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);

    glColor3f(0, 0, 0);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 14) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -1) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -1) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 14) + ciga_u_move2);

    glColor3f(0.9594, 0.5265, 0.234);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -14) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -14) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 1) + ciga_u_move2);

    glColor3f(0.9945, 0.9594, 0.1911);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);

    glColor3f(0.9945, 0.9594, 0.1911);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 9) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);

    glColor3f(0.7605, 0.8385, 0.8853);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);


    glColor3f(0.4095, 0.4407, 0.4407);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -11) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 4) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);

    glColor3f(0.9594, 0.4446, 0.2028);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 10) + ciga_u_move2);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -2) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 13) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 11) + ciga_u_move2);

    glColor3f(0.5577, 0.3354, 0.2301);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -1) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 14) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 14) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 12) + ciga_u_move2);

    glColor3f(0.4095, 0.4407, 0.4407);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0.2964, 0.3666, 0.3666);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -12) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -13) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 3) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 2) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -12) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 3) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -11) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 4) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -10) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 5) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -7) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -9) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 8) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 6) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -6) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 9) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 7) + ciga_u_move2);

    glColor3f(0.6045, 0.6747, 0.7137);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.4 + (0.007 * -5) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + 0.106 + (0.01225 * -7) + ciga_u_move2);
    glVertex2f(0.112 * 7 - 0.512 + (0.007 * 10) + ciga_move2, -3 * 0.196 + -0.09 + (0.01225 * 8) + ciga_u_move2);
    glEnd();
}

void DrawPacMan() {
    // Draw Pac-Man
    glColor3f(b, 0.6, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(pacMan.x, pacMan.y);

    for (float angle = pacMan.mouthAngle; angle <= 360.0 - pacMan.mouthAngle; angle += 5.0) {
        float radianAngle = angle * 3.14159265358979323846 / 180.0;
        float xPos = pacMan.x + pacMan.radius * std::cos(radianAngle);
        float yPos = pacMan.y + pacMan.radius * std::sin(radianAngle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
}
void MyReshape(int NewWidth, int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)1600;
    GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)900;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}
void Fire_f() {
    if (firebool)
    {
        Fire1(1, -3);
        Fire1(3, -3);
    }
    else
    {
        Fire2(1, -3);
        Fire2(3, -3);
    }
    if (settime >= 1100 && settime < 1160) {
        firebool = true;
    }
    if (settime >= 1160 && settime < 1220) {
        firebool = false;
    }
    if (settime >= 1220 && settime < 1280) {
        firebool = true;
    }
    if (settime >= 1280 && settime < 1340) {
        firebool = false;
    }
    if (settime >= 1340 && settime < 1400) {
        firebool = true;
    }
    if (settime >= 1400 && settime < 1460) {
        firebool = true;
    }
    if (settime >= 1460 && settime < 1520) {
        firebool = false;
    }
    if (settime >= 1520 && settime < 1580) {
        firebool = true;
    }
    if (settime >= 1580 && settime < 1640) {
        firebool = false;
    }
    if (settime >= 1640 && settime < 1700) {
        firebool = true;
    }
    if (settime >= 1700 && settime < 1760) {
        firebool = false;
    }
    if (settime >= 1760 && settime < 1820) {
        firebool = true;
    }
    if (settime >= 1820 && settime < 1880) {
        firebool = false;
    }
    if (settime >= 1880 && settime < 1940) {
        firebool = true;
    }
    if (settime >= 1940 && settime < 2000) {
        firebool = false;
    }
   
}
void Fire_s() {
    if (firebool)
    {
        Fire1(-3, -3);
        Fire1(-2, -3);
    }
    else
    {
        Fire2(-3, -3);
        Fire2(-2, -3);
    }
}
void Fire_t()
{
    if (firebool) {
        Fire1(9, -3);
    }
    else {
        Fire2(9, -3);
    }
}

void Drawboxs() {

    DrawRandbox(0, 0);
    DrawRandbox(6, 0);
    DrawRandbox(5, 3);
    DrawBrickbox(3, 0);
    DrawBrickbox(5, 0);
    DrawBrickbox(7, 0);
    DrawPipe_part_zip(11);
    DrawBush_zip(9);
    DrawBush_zip2(-3);
    Draw_m_Randbox();
    DrawMountain_zip(2);

    DrawPacMan();
    DrawCloud_zip(-2, 3);
    DrawCloud_zip2(9, 3);

    if (settime < 2500 && settime >= 1100) {
        Fire_f();
    }
    if (settime < 2500 && settime>1400) {
        Fire_s();
    }
    if (settime < 2500 && settime>1700) {
        Fire_t();
    }
    DrawMonster();
    if (settime >= 550 && settime <= 950) {
        Drawcigarette();
    }
    if (settime < 1100 && settime >= 1000) {
        Drawcigarette2();
    }


    for (int i = -10; i <= -4; i++) {
        for (int j = -9; j <= 17; j++) {
            DrawTile(j, i);
        }
    }
    if (settime >= 2000) {
        start3 = true;

    }
}


// 장면3 변환 타이머
int Wait3 = 0;
void secneStartTimer(int value) {
    Wait3++;
    if (Wait3 > 20) {
        glutTimerFunc(mspeed, updatePacMan3, 0);
        glutTimerFunc(10, movePacMan3, 0);
        if (emergencytabacco)
            glutTimerFunc(20, emergencyTabacco, 0);
        glutTimerFunc(100, updateContinent, 0);
        glutTimerFunc(100, updateOcean, 0);
        glutTimerFunc(100, deathPacMan3, 0);
    }
    else {
        glutTimerFunc(20, secneStartTimer, 0);
    }
}

void updatePacMan() {
    if (pacMan_move) {
        pacMan.x += 0.002;
    }


    if (pacMan.isOpening) {
        pacMan.mouthAngle += 1.0;
        if (pacMan.mouthAngle >= 45.0) {
            pacMan.isOpening = false;
        }
    }
    else {
        pacMan.mouthAngle -= 1.0;
        if (pacMan.mouthAngle <= 0.0) {
            pacMan.isOpening = true;
        }
    }
    if (settime >= 445 && settime < 495) {
        pacMan.y += 0.008;
    }
    if (settime >= 495 && settime < 545) {
        pacMan.y -= 0.008;
    }
    if (settime == 420) {
        move += 5000000;
        pacMan.y += 0.025;
        pacMan.radius += 0.02;
        b -= 0.1;
    }
    if (settime >= 650 && settime < 1150) {
        pacMan_move = false;
    }
    else {
        pacMan_move = true;
    }
}
void update_ciga() {
    if (settime >= 550) {
        if (cigamoveRight)
        {
            ciga_move += 0.0025;
            if (ciga_move >= 0.44) //0.44가 블럭 모서리
            {
                ciga_d_move -= 0.0125;   //속도는 0.025
                if (ciga_d_move <= -0.7875)     //바닥은 0.7875
                    ciga_d_move = -0.7875;

            }
            if (ciga_move >= 0.6875)
            {
                ciga_move = 0.6875;
                cigamoveRight = false;
            }
        }
        else {
            ciga_move -= 0.0025;
            if (ciga_move <= -5000000) {
                moveRight = true;
            }
        }
    }
}
void update_ciga2()
{
    if (settime < 1050 && settime >= 1000)
    {
        ciga_u_move2 += 0.005;
        ciga_move2 -= 0.005;
    }
    if (settime < 1100 && settime >= 1050)
    {
        ciga_u_move2 -= 0.005;
        ciga_move2 -= 0.005;
    }
}
void update_mob() {
    if (moveRight) {
        move += 0.0035;
        if (move >= 0.68) {
            move = 0.68;
            moveRight = false;
        }
    }
    else {
        move -= 0.0035;
        if (move <= -5000000) {
            moveRight = true;
        }
    }
}
void update_box() {
    if (settime >= 500 && settime < 525) {
        randbox_y += 0.002;
    }
    if (settime >= 525 && settime < 550) {
        randbox_y -= 0.004;
    }
    if (settime >= 550 && settime < 575) {
        randbox_y += 0.002;
    }
}
void update_file()
{

}
void Scene2(){
    glClear(GL_COLOR_BUFFER_BIT);
    updatePacMan();
    update_mob();
    update_ciga();
    update_ciga2();
    update_box();

    Drawboxs();
    glColor3f(0.832, 0.273, 0.027);
    glBegin(GL_QUADS);
    glFlush();
    glEnd();
}
//우진
void timer(int value)
{
    settime++;
    update();
    glutPostRedisplay();
    if (!start3) {
        glutTimerFunc(16, timer, 0); // 60 frames per second
    }
    else {
        glutTimerFunc(50, secneStartTimer, 0);
    }

}

void MyDisplay()
{
    drawScene();
    if (start2) {
        glClearColor(0.375, 0.598, 0.992, 1.0);
    }else if(start3) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
    }else {
        glClearColor(0.0, 0.0, 0.0, 0.0);
    }
    
    if (start2) {
        Scene2();
    }else if (start3) {
        Scene3();
    }
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1600, 900);
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL");
    
    glutReshapeFunc(MyReshape);
    // 우진
    glutTimerFunc(1, timer, 0);

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
