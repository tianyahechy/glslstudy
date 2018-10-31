#pragma once
#include "GLSLProgram.h"

class shaderVertex : public GLSLProgram
{
public:
	typedef int attribute;
public:
	uniform _color;
	attribute _position;
	virtual void initialize()
	{

		const char * vs = " attribute vec3 _position;\n\
							void main() \n\
							{\n\
								gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
							}";
		const char * ps = "	uniform vec4 _color;\n\
							void main() \n\
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