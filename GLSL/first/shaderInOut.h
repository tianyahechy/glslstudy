#pragma once
#include "GLSLProgram.hpp"

class ShaderInOut : public GLSLProgram
{
public:

	attribute _color;
	attribute _position;
	virtual void initialize()
	{
		const char* vs = "#version 130 \n\
							in vec3 _color;\
							in vec3 _position;\
							out vec3 _outColor;\
						void main()\
						{\
							_outColor = _color;\
							gl_Position = gl_ModelViewProjectionMatrix * vec4(_position, 1.0);\
						}";
		const char* ps = "in vec3 _outColor;\
						void main()\
						{\
							gl_FragColor = vec4(_outColor, 1.0); \
						}";
		createProgram(vs, ps);
		_color = glGetAttribLocation(_program, "_color");
		_position = glGetAttribLocation(_program, "_position");
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