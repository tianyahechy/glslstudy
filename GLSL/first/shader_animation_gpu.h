#pragma once
#include "GLSLProgram.hpp"

class Shader_Animation_GPU : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _texture;
	uniform	_animInfor;
	attribute _pos;
	attribute _uv;
public:
	virtual void initialize()
	{
		const char* vs = "#version 130 \n\
						uniform mat4 _mvp; \n\
						uniform vec3 _animInfor;\n\
						in vec3 _pos; \n\
						in vec2 _uv; \n\
						out vec2 _outUV; \n\
						void main()\n\
						{\n\
							float uScale = 1.0 / _animInfor.x; \n\
							float vScale = 1.0 / _animInfor.y; \n\
							int col = int(_animInfor.z)% int(_animInfor.x);\n\
							int row = int(_animInfor.z)% int(_animInfor.y);\n\
							_outUV = _uv * vec2(uScale, vScale); \n\
							_outUV.x += float(col) * uScale; \n\
							_outUV.y += float(row) * vScale; \n\
							gl_Position = _mvp * vec4(_pos, 1.0);\n\
						}";
		const char* ps = "uniform sampler2D _texture; \n\
						in vec2 _outUV; \n\
						void main()\
						{\
							gl_FragColor = texture2D(_texture, _outUV); \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_texture = glGetUniformLocation(_program, "_texture");
		_animInfor = glGetUniformLocation(_program, "_animInfor");
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