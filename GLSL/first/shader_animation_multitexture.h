#pragma once
#include "GLSLProgram.hpp"

class Shader_Animation_MultiTexture : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _texture0;
	uniform _texture1;
	uniform _mix;
	attribute _pos;
	attribute _uv;
public:
	virtual void initialize()
	{
		const char* vs = "#version 130 \n\
						uniform mat4 _mvp; \n\
						in vec3 _pos; \n\
						in vec2 _uv; \n\
						out vec2 _outUV; \n\
						void main()\n\
						{\n\
							_outUV = _uv;\n\
							gl_Position = _mvp * vec4(_pos, 1.0);\n\
						}";
		const char* ps = "uniform sampler2D _texture0; \n\
						uniform sampler2D _texture1; \n\
						uniform float _mix;\n\
						in vec2 _outUV; \n\
						void main()\
						{\
							vec4 color0 = texture2D(_texture0, _outUV); \
							vec4 color1 = texture2D(_texture1, _outUV); \
							vec4 dstColor = color0 * ( 1- _mix) + color1 * _mix;\n\
							gl_FragColor = dstColor; \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_texture0 = glGetUniformLocation(_program, "_texture0");
		_texture1 = glGetUniformLocation(_program, "_texture1");
		_mix = glGetUniformLocation(_program, "_mix");
		_pos = glGetAttribLocation(_program, "_pos");
		_uv = glGetAttribLocation(_program, "_uv");
		
	}

	// π”√shader
	virtual void begin()
	{
		glUseProgram(_program);
		glEnableVertexAttribArray(_pos);
		glEnableVertexAttribArray(_uv);
	}
	//Ω· ¯
	virtual void end()
	{
		glDisableVertexAttribArray(_pos);
		glDisableVertexAttribArray(_uv);
		glUseProgram(0);
	}
};