#pragma once
#include "GLSLProgram.hpp"

class ShaderLayout_UniformStruct : public GLSLProgram
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
							struct MVP \n\
							{ \n\
								mat4 _mat;	\n\
								float _scaler; \n\
							}; \n\
							in VertAttr _vert;\
							in vec2 _uv;\
							uniform MVP _mvp; \
							layout(location = 0 )	out vec3 _outColor;\
							layout(location = 1 )	out vec2 _outUV;\
						void main()\
						{\
							_outColor = _vert._color * _mvp._scaler;\
							_outUV = _uv; \
							gl_Position = _mvp._mat * vec4(_vert._pos, 1.0);\
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
		int len = 0;
		_mvp = glGetUniformLocation(_program, "_mvp._mat");
		GLuint s = glGetUniformLocation(_program, "_mvp._scaler");
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