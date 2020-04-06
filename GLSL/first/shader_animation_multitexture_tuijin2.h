#pragma once
#include "GLSLProgram.hpp"

class Shader_Animation_MultiTexture_Tuijin2 : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _texture0;
	uniform _texture1;
	uniform _offset;
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
						uniform float _offset;\n\
						in vec2 _outUV; \n\
						void main()\
						{\
							vec4 color0 = texture2D(_texture0, vec2(_outUV.x+1 - _offset, _outUV.y)); \n\
							if( _outUV.x > _offset )	\n\
							{							\n\
								color0 = texture2D(_texture1, vec2(_outUV.x - _offset, _outUV.y));	\n\
							}							\n\
							gl_FragColor = color0; \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_texture0 = glGetUniformLocation(_program, "_texture0");
		_texture1 = glGetUniformLocation(_program, "_texture1");
		_offset = glGetUniformLocation(_program, "_offset");
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