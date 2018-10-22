#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "glew/glew.h"
#include "OpenGLWindow.h"
#include "shaderNormal.h"
#include "GLFreeImage.hpp"

class sample1 : public OpenGLWindow
{
public:
	shaderNormal _shader;
public:
	struct vertex
	{
		float x, y, z;
		float nx, ny, nz;
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
			{ 10, 10, 0,  1, 1,0 },
			{ 510, 10, 0, 0, 1,1 },
			{ 10, 510, 0, 0, 1,0 },
			{ 510, 510, 0, 1,1,1 },
		};
		//glColor3f(1, 0, 1);
		//绑定纹理
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		_shader.begin();
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		glNormalPointer(GL_FLOAT, sizeof(vertex), &rect[0].nx);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		_shader.end();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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