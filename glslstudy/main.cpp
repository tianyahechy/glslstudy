#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "glew/glew.h"
#include "OpenGLWindow.h"
#include "GLSLProgram.h"
#include "GLFreeImage.hpp"

class sample1 : public OpenGLWindow
{
public:
	ShaderUniform _shader;
public:
	struct vertex
	{
		float x, y, z;
		unsigned char r, g, b;
	};
	char * _pixel;
	sample1()
	{

	}
	virtual void onInitGL()
	{
		glewInit();
		_shader.initialize();
	}
	virtual void render()
	{
		//指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//将投影矩阵清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);
		//glColor3f(1, 0, 1);
		vertex rect[] =
		{
			{ 10, 10, 0,  1, 0,0 },
			{ 510, 10, 0, 0, 1,0 },
			{ 10, 510, 0, 0, 0,1 },
			{ 510, 510, 0, 1,0,1 },
		};
		_shader.begin();
		glColor3f(1, 0, 1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect[0].r);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		_shader.end();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
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
