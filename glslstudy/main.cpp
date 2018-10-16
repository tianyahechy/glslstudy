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