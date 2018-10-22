#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "glew/glew.h"
#include "OpenGLWindow.h"
#include "ShaderColors.h"
#include "GLFreeImage.hpp"

class sample1 : public OpenGLWindow
{
public:
	shaderColors _shader;
public:
	struct vertex
	{
		float x, y, z;
		unsigned char r0, g0, b0, a0;
		unsigned char r1, g1, b1, a1;
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
			{ 10, 10, 0, 255, 0, 0, 255, 255, 0, 0, 255 },
			{ 510, 10, 0, 0, 255, 0, 255, 255, 0, 0, 255 },
			{ 10, 510, 0, 0, 0, 255, 255, 255, 0, 0, 255 },
			{ 510, 510, 0, 255, 0, 255, 255, 255, 0, 0, 255 },
		};
		//glColor3f(1, 0, 1);
		//绑定纹理
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_SECONDARY_COLOR_ARRAY);
		_shader.begin();
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex), &rect[0].r0);
		glSecondaryColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex), &rect[0].r1);
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