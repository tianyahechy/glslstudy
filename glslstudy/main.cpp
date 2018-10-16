#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "glew/glew.h"
#include "OpenGLWindow.h"

class sample1 : public OpenGLWindow
{
public:
	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};
	char * _pixel;
	sample1()
	{

	}
	virtual void onInitGL()
	{
		glewInit();
	}
	virtual void render()
	{
		char * ext = (char *)glGetString(GL_EXTENSIONS);
#define M_PI	(3.1415926535)
		//ָ�����µĲ������ͶӰ����
		glMatrixMode(GL_PROJECTION);
		//��ͶӰ������ճɵ�λ����
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);
		//glColor3f(1, 0, 1);
		vertex rect[] =
		{
			{ 10, 10, 0, 1, 0, 0 },
			{ 110, 10, 0, 0, 1, 0 },
			{ 10, 110, 0, 0, 0, 1 },
			{ 110, 110, 0, 1, 0, 1 },
		};
		//glColor3f(1, 0, 1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect[0].r);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		vertex rect1[] =
		{
			{ 10, 10, 0, 1, 0, 0 },
			{ 110, 10, 0, 0, 1, 0 },
			{ 10, 110, 0, 1, 0, 1 },
			{ 110, 110, 0, 1, 0, 1 },
		};
		for (int i = 0; i < 4; i++)
		{
			rect1[i].x += 100;
		}
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect1);
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect1[0].r);
		//glColor3f(0, 0, 1);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
	)
{
	sample1 instance;
	instance.main(800, 600);
	return 0;
}