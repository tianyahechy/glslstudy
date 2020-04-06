#pragma once
#include "GLSLProgram.hpp"

class ShaderLayout_attribute : public GLSLProgram
{
public:
	uniform _mvp;
	attribute _color;
	attribute _position;
	virtual void initialize()
	{
		const char* vs = "#version 330 \n\
							layout(location = 0 )	in vec3 _position;\
							layout(location = 1 )	in vec3 _color;\
							uniform mat4 _mvp; \
							out vec3 _outColor;\
						void main()\
						{\
							_outColor = _color;\
							gl_Position = _mvp * vec4(_position, 1.0);\
						}";
		const char* ps = "in vec3 _outColor;\
						void main()\
						{\
							gl_FragColor = vec4(_outColor, 1.0); \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		//_color = glGetAttribLocation(_program, "_color");
		//_position = glGetAttribLocation(_program, "_position");
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