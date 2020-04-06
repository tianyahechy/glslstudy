#pragma once
#include "GLSLProgram.hpp"

class Shader_Animation : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _uvOffset;
	uniform _texture;
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
							_outUV = _uv; \n\
							gl_Position = _mvp * vec4(_pos, 1.0);\n\
						}";
		const char* ps = "uniform sampler2D _texture; \n\
						uniform vec2 _uvOffset; \n\
						in vec2 _outUV; \n\
						void main()\
						{\
							gl_FragColor = texture2D(_texture, _outUV + _uvOffset); \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_texture = glGetUniformLocation(_program, "_texture");
		_uvOffset = glGetUniformLocation(_program, "_uvOffset");
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