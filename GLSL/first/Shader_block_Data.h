#pragma once
#include "GLSLProgram.hpp"

class Shader_block_Data : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _tex;
	attribute _color;
	attribute _position;
	attribute _uv;
	virtual void initialize()
	{
		const char* vs = "#version 430 \n\
						struct VertAttr \n\
						{ \n\
							vec3 _pos;	\n\
							vec3 _color;	\n\
						};	\n\
						uniform MVP \n\
						{ \n\
							mat4 _mat;	\n\
						}mvp; \n\
						in VertAttr _vert;\
						in vec2 _uv;\
						out block \
						{\
							vec3 _color;\
							vec2 _uv;\
						}Out;\
						void main()\
						{\
							Out._color = _vert._color;\
							Out._uv = _uv; \
							gl_Position = mvp._mat * vec4(_vert._pos, 1.0);\
						}";
		const char* ps = "#version 430 \n\
						in block \
						{\
							vec3 _color;\
							vec2 _uv;\
						}In;\
						layout(location = 1 )	uniform sampler2D _tex; \
						void main()\
						{\
							vec4 color = texture2D(_tex, In._uv); \
							gl_FragColor = color * vec4(In._color, 1.0); \
						}";
		createProgram(vs, ps);
		int len = 0;
		_mvp = glGetUniformBlockIndex(_program, "MVP");		
		_tex = glGetUniformLocation(_program, "_tex");
		_position = glGetAttribLocation(_program, "_vert._pos");
		_color = glGetAttribLocation(_program, "_vert._color");
		_color = glGetAttribLocation(_program, "_vert._test[3]");
		_uv = glGetAttribLocation(_program, "_uv");
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