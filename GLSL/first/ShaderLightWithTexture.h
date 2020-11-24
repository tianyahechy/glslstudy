#pragma once
#include "GLSLProgram.hpp"

class ShaderLightWithTexture : public GLSLProgram
{
public:
	uniform _mvp;
	uniform _lightDir;
	uniform _lightColor;
	uniform _lightAmbient;
	uniform _texture;

	attribute _position;
	attribute _normal;
	attribute _uv;

public:
	virtual void    initialize()
	{
		const char* vs = "#version 330 \n\
						uniform mat4 _mvp; \n\
						uniform vec3 _lightDir; \n\
						uniform vec3 _lightColor; \n\
						uniform vec3 _lightAmbient; \n\
						in vec3 _position; \n\
						in vec3 _normal; \n\
						in vec2 _uv; \n\
						out vec4 _outColor;\n\
						out vec2 _outUV;	\n\
						void main()\
						{\
							_outUV = _uv;	\n\
							float NDotL = max(dot(_normal, _lightDir), 0.1 ); \
							_outColor = vec4(_lightColor * NDotL + _lightAmbient, 1.0);\
							gl_Position = _mvp * vec4(_position, 1.0 );\
						}";
		const char* ps = "#version 330 \n\
						in vec4 _outColor;\
						out vec2 _outUV; \n\
						uniform sampler2D _texture;\n\
						void main()\
						{\
							vec4 color = texture2D(_texture, _outUV); \n\
							gl_FragColor = color * _outColor ; \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
		_lightDir = glGetUniformLocation(_program, "_lightDir");
		_lightColor = glGetUniformLocation(_program, "_lightColor");
		_lightAmbient = glGetUniformLocation(_program, "_lightAmbient");
		_texture = glGetUniformLocation(_program, "_texture");

		_position = glGetAttribLocation(_program, "_position");
		_normal = glGetAttribLocation(_program, "_normal");
		_uv = glGetAttribLocation(_program, "_uv");

	}

	// π”√shader
	virtual void begin()
	{
		glEnableVertexAttribArray(_position);
		glEnableVertexAttribArray(_normal);
		glEnableVertexAttribArray(_uv);
		glUseProgram(_program);
	}
	//Ω· ¯
	virtual void end()
	{
		glDisableVertexAttribArray(_position);
		glDisableVertexAttribArray(_normal);
		glDisableVertexAttribArray(_uv);
		glUseProgram(0);
	}
};