#pragma once
#include "GLSLProgram.h"

class shaderVaring : public GLSLProgram
{
public:
	uniform _color;
	virtual void initialize()
	{

		const char * vs =	"uniform vec4 _color;\
  							varying vec4 outColor;\
 							void main() \
							{\
								outColor = _color;\
								gl_Position = ftransform();\
							}";
		const char * ps =	"varying vec4 outColor; \
							void main() \
							{\
								gl_FragColor = outColor;\
							}";
	
		createProgram(vs, ps);
		_color = glGetUniformLocation(_program, "_color");
	}

	//ʹ��shader
	virtual void begin()
	{
		glUseProgram(_program);
	}
	//����
	virtual void end()
	{
		glUseProgram(0);
	}
};