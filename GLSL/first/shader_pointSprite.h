#pragma once
#include "GLSLProgram.hpp"

class ShaderPointSprite : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _texture0;
	attribute _pos;
	attribute _color;
public:
	virtual void initialize()
	{
		const char* vs = "#version 130 \n\
						uniform mat4 _mvp;\
						in vec3 _pos;\
						in vec4 _color; \
						out vec4 _outColor; \n\
						void main()\
						{\
							gl_PointSize = 64; \n\
							_outColor = _color; \n\
							gl_Position = _mvp * vec4(_pos, 1.0);\
						}";
		const char* ps = "uniform sampler2D _texture0;\
						in vec4	_outColor; \n\
						void main()\
						{\
							vec4 color = _outColor * texture2D(_texture0, gl_PointCoord);\
							gl_FragColor = color; \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_texture0 = glGetUniformLocation(_program, "_texture0");
		_pos = glGetAttribLocation(_program, "_pos");
		_color = glGetAttribLocation(_program, "_color");
	}
	// π”√shader
	virtual void begin()
	{
		glUseProgram(_program);
		glEnableVertexAttribArray(_pos);
		glEnableVertexAttribArray(_color);
	}
	//Ω· ¯
	virtual void end()
	{
		glDisableVertexAttribArray(_pos);
		glDisableVertexAttribArray(_color);
		glUseProgram(0);
	}
};