#include <iostream>
#include <random>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WIN_SIZE 800
#define BOX_SIZE 50

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLclampf IntToFloat(int i, bool IsX);
void RandomBoxColor();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

GLclampf fBoxRed = 1.0f, fBoxBlue = 1.0f, fBoxGreen = 1.0f;
int iBoxX = 400, iBoxY = 400;
bool LeftButton = false;

void main(int argc, char** argv)					//---윈도우 출력하고 콜백함수 설정
{

	//---윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(WIN_SIZE, WIN_SIZE); // 윈도우의 크기 지정
	glutCreateWindow("Training 3"); // 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse); // 마우스 입력 콜백함수 지정
	glutMotionFunc(Motion);
	glutMainLoop(); // 이벤트 처리 시
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f); // 바탕색 설정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	glColor3f(fBoxRed, fBoxGreen, fBoxBlue);
	glRectf(IntToFloat(iBoxX - BOX_SIZE, true), IntToFloat(iBoxY + BOX_SIZE, false), IntToFloat(iBoxX + BOX_SIZE, true), IntToFloat(iBoxY - BOX_SIZE, false));

	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);
}

GLclampf IntToFloat(int i, bool IsX)
{
	GLclampf fResult;
	float fHalf = (float)WIN_SIZE / 2.0f;
	fResult = ((float)i - fHalf) / fHalf;

	if (IsX)
		return fResult;
	else
		return fResult * -1.0f;
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x >= iBoxX - BOX_SIZE && x <= iBoxX + BOX_SIZE && y >= iBoxY - BOX_SIZE && y <= iBoxY + BOX_SIZE)
		{
			RandomBoxColor();
		}

		else
		{
			RandomBoxColor();
			iBoxX = x;
			iBoxY = y;
		}


		LeftButton = true;
	}

	if (state == GLUT_UP)
	{
		LeftButton = false;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (LeftButton == true)
	{
		iBoxX = x;
		iBoxY = y;
	}
	glutPostRedisplay();
}

void RandomBoxColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 9);

	fBoxRed = (float)(dis(gen)) / 10.0f;
	fBoxBlue = (float)(dis(gen)) / 10.0f;
	fBoxGreen = (float)(dis(gen)) / 10.0f;
}