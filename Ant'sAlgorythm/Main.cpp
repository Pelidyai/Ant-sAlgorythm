#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <Windows.h>
#include"Graph.h"
/* начальная ширина и высота окна */
GLint Width = 1000, Height = 800;
Graph* Towns;

int delay = 1000;
/* эта функция управляет всем выводом на экран */
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	Towns->DrawGraph();
	Towns->DrawMin();
	glFinish();
	glutSwapBuffers();
}
/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;
	
	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);
	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int indexxx = 1;
void Timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(delay, Timer, 1);
	//glutPostRedisplay();
}
/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
	if (key == ESCAPE)
		exit(0);
	if (key == '1')
	{
		
	}
	switch (key)
	{
	case '\033':
	{
		exit(0);
	}
	case '1':
	{
		int a = clock();
		std::cout << Towns->LetsGo() << std::endl;
		std::cout << clock() - a << endl;
		glutPostRedisplay();
		break;
	}
	case '2':
	{
		for (int i = 0; i < 100; i++)
		{
			std::cout << Towns->LetsGo() << std::endl;
		}
		glutPostRedisplay();
		break;
	}
	}
}
/* Главный цикл приложения */
int main(int argc, char* argv[])
{
	//srand((int)time(0));
	Towns = new Graph(50, Width, Height, 2, 8);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Ant's Algorythm");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(delay, Timer, 0);
	glutMainLoop();
}