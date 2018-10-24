#pragma once
#include "GLSLProgram.h"

class shaderVertex : public GLSLProgram
{
public:
	uniform _color;
	virtual void initialize()
	{

		const char * vs = "	uniform vec4 _color;\
							varying vec4 outColor;\
							void main() \
							{\
								outColor = _color;\
								gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
							}";
		const char * ps = "	varying vec4 outColor; \
							void main() \
							{\
								gl_FragColor = outColor;\
							}";

		createProgram(vs, ps);
		_color = glGetUniformLocation(_program, "_color");
	}

	// π”√shader
	virtual void begin()
	{
		glUseProgram(_program);
	}
	//Ω· ¯
	virtual void end()
	{
		glUseProgram(0);
	}
};