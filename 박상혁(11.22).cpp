#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>
float pacManX = 0.0f;
float pacManY = 0.0f;
float pacManAngle = 45.0f;
bool mouthOpen = true;
int drawStarCount = 0;
float drawStarsArray[1000][2] = {};
float scale = 1.0;
int Cflag = 1;	// 초록색 대륙
double mspeed = 50;	// 입벌리는 속도 느려지게끔

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
	// 대륙1
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.4);
	glVertex2f(-0.095, 0.42);
	glVertex2f(-0.07, 0.47);
	glVertex2f(-0.04, 0.48);
	glVertex2f(-0.01, 0.47);
	glVertex2f(0.02, 0.45);
	glVertex2f(0.05, 0.42);		// (1)
	glVertex2f(0.08, 0.35);
	glVertex2f(0.04, 0.28);
	glVertex2f(0.02, 0.25);
	glVertex2f(0.01, 0.2);
	glVertex2f(0.007, 0.16);
	glVertex2f(0.005, 0.16);
	glVertex2f(0, 0.2);
	glVertex2f(-0.03, 0.2);
	glVertex2f(-0.03, 0.23);
	glVertex2f(-0.03, 0.2);		//(2)
	glVertex2f(-0.02, 0.18);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.02, 0.18);
	glVertex2f(-0.023, 0.14);
	glVertex2f(-0.018, 0.08);
	glVertex2f(-0.024, 0);
	glVertex2f(-0.03, -0.03);
	glVertex2f(-0.038, -0.06);	//(3)
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
	glVertex2f(-0.15, 0.24);	//(4)
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
	// 대륙 2
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
	glFlush();
}

// 기본값은 초록색
double glR = 0;
double glG = 1;
double glB = 0;

// 대륙들
void drawContinent(int flag) {
	if (flag == 0) {
		glColor3f(0.0, 204, 0);
	}
	else {
		glColor3f(glR, glG, glB);
	}
	continent1();
	continent2();

	// 대륙3
	glBegin(GL_LINE_LOOP);
	glEnd();

	glutSwapBuffers();
}

// 팩맨 + 대륙
void drawPacMan() {

	// 별 출력
	//glScalef(scale, scale, 1.0);

	glColor3f(1, 1.0, 0); // yellow color
	glPushMatrix();
	glTranslatef(pacManX, pacManY, 0.0f); // 팩맨을 현재위치로 변환

	glColor3f(0, 0, 1.0); // 팩맨 노란색깔

	// 팩맨모양
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0, 0.0); // Center of Pac-Man
	glVertex2f(0.0, 0.0); // 팩맨의 센터위치

	for (float angle = pacManAngle; angle <= 360.0 - pacManAngle; angle += 1.0) {
		float radians = angle * (3.14 / 180.0);
		float x = 0.6 * cos(radians);
		float y = 0.6 * sin(radians);
		glVertex2f(x, y);
	}
	glEnd();

	// 팩맨 입
	if (mouthOpen) {
		glBegin(GL_LINES);
		glVertex2f(0.0, 0.0);
		float radians1 = (pacManAngle - 20.0) * (3.14 / 180.0);
		float x1 = 0.3 * cos(radians1);
		float y1 = 0.3 * sin(radians1);
		glVertex2f(x1, y1);
		float radians2 = (360.0 - pacManAngle + 20.0) * (3.14 / 180.0);
		float x2 = 0.3 * cos(radians2);
		float y2 = 0.3 * sin(radians2);
		glVertex2f(x2, y2);
		glEnd();
	}
	glPopMatrix();

	// 표정기능
	/*glColor3f(0.0, 204, 0);
	double rad = 0.1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		double e_angle = i * 3.141592 / 180;
		double e_x = rad * cos(e_angle);
		double e_y = rad * sin(e_angle);
		glVertex2f(e_x+0.08, e_y+0.4);
	}
	glEnd();*/
	/*glColor3f(0.0, 204, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0.06,0.025);
	glVertex2f(0.09, 0.025);
	glVertex2f(0.09, 0.4);
	glVertex2f(0.06, 0.4);
	glEnd();
	glFlush();*/

	// 대륙
	drawContinent(Cflag);

	/*glColor3f(0.0, 204, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.06, 0.025);
	glVertex2f(0.09, 0.025);
	glVertex2f(0.09, 0.4);
	glVertex2f(0.06, 0.4);
	glEnd();*/
	glFlush();
}

// 장면 3 화면 출력 함수
void Scene3() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawStars();
	drawPacMan();

}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	Scene3();

	glFlush();
}

//0.5초 단위로 팩맨 입벌렸다가 움츠렸다가 업데이트
//갈수록 느리게 움직임
void updatePacMan(int value) {
	mspeed += 0.4;
	if (mouthOpen) {
		pacManAngle -= 2.0;
	}
	else {
		pacManAngle += 2.0;
	}
	if (pacManAngle <= 20.0 || pacManAngle >= 45.0) {
		mouthOpen = !mouthOpen;
	}

	// 대륙 = 초록색 -> 붉은색 -> 붉회색
	if (glB <= 0.25) {
		glB += 0.01;
		glG -= 0.015;
		glR += 0.01;
	}
	// 짙녹색 -> 짙회색
	else if (glR <= 0.45){
		glB += 0.01;
		glG -= 0.001;
		glR += 0.01;
	}
	// 붉게
	else if (glR <= 0.53) {
		glR += 0.01;
	}
	else if (glG >= 0.4) {
		glG -= 0.01;
	}
	// 붉회색
	else if (glG >= 0.24) {
		glB -= 0.03;
		glG -= 0.01;
		glR -= 0.01;
	}
		

	glutPostRedisplay();
	glutTimerFunc(mspeed, updatePacMan, 0);
	
	// (별출력 함수) scale += 0.00006;
	
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Space");

	glutTimerFunc(mspeed, updatePacMan, 0);
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}
