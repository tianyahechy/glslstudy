#pragma once
#include "GLSLProgram.hpp"

class ShaderLayout_attributeVector : public GLSLProgram
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
								in vec3 _positionAndColor[4];\
								in vec2 _uv;\
							layout(location = 0 )   uniform mat4 _mvp; \
							layout(location = 0 )	out vec3 _outColor;\
							layout(location = 1 )	out vec2 _outUV;\
						void main()\
						{\
							_outColor = _positionAndColor[1] + _positionAndColor[1] +_positionAndColor[3] ;\
							_outUV = _uv; \
							gl_Position = _mvp * vec4(_positionAndColor[0], 1.0);\
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
		_mvp = glGetUniformLocation(_program, "_mvp");
		_tex = glGetUniformLocation(_program, "_tex");
		_color = glGetAttribLocation(_program, "_positionAndColor");
		_uv = glGetAttribLocation(_program, "_uv");
	}

	//ʹ��shader
	virtual void begin()
	{
		glUseProgram(_program);
	}
	//����
	virtual void end()
	{
		glUseProgram(0);
	}
};