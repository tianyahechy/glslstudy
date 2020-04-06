#pragma once
#include "GLSLProgram.hpp"

class Shader_block_std14 : public GLSLProgram
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
						layout(std140) uniform MVP \n\
						{ \n\
							mat4 _prj;	\n\
							mat4 _view;	\n\
							mat4 _model;\n\
							float _iData;\n\
							float _fData; \n\
							float _data[2];\n\
							float _bData;	\n\
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
							gl_Position = mvp._prj * mvp._view * mvp._model * vec4(_vert._pos, 1.0);\
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
		GLint blockSize;
		glGetActiveUniformBlockiv(_program, _mvp, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		char* names[] = { "MVP._prj", "MVP._view", "MVP._model", "MVP._iData", "MVP._fData", "MVP._data","MVP._bData" };
		GLuint indexs[7] = { 0 };
		glGetUniformIndices(_program, 7, names, indexs);
		GLint offset[7];
		glGetActiveUniformsiv(_program, 7, indexs, GL_UNIFORM_OFFSET, offset);
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