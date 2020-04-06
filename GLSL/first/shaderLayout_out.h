#pragma once
#include "GLSLProgram.hpp"

class ShaderLayout_Out : public GLSLProgram
{
public:
	uniform _mvp;
	attribute _color;
	attribute _position;
	uniform _tex;
	virtual void initialize()
	{
		const char* vs = "#version 430 \n\
							layout(location = 0 )	in vec3 _position;\
							layout(location = 1 )	in vec3 _color;\
							layout(location = 2 )	in vec2 _uv;\
							layout(location = 0 )   uniform mat4 _mvp; \
							layout(location = 0 )	out vec3 _outColor;\
							layout(location = 1 )	out vec2 _outUV;\
						void main()\
						{\
							_outColor = _color;\
							_outUV = _uv; \
							gl_Position = _mvp * vec4(_position, 1.0);\
						}";
		const char* ps = "#version 430 \n\
						layout(location = 0 )	in vec3 _inColor;\
						layout(location = 1 )	in vec2 _inUV;\
						layout(location = 1 )	uniform sampler2D _tex; \
						void main()\
						{\
							vec4 color = texture2D(_tex, _inUV); \
							gl_FragColor = color * vec4(_inColor, 1.0); \
						}";
		createProgram(vs, ps);
		//_mvp = glGetUniformLocation(_program, "_mvp");
		//_tex = glGetUniformLocation(_program, "_tex");
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