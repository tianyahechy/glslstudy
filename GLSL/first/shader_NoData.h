#pragma once
#include "GLSLProgram.hpp"

class Shader_NoData : public GLSLProgram
{
public:
	uniform _mvp;
	virtual void initialize()
	{
		const char* vs = "#version 130 \n\
						uniform mat4 _mvp; \n\
						const vec3 _pos[4] =	vec3[] (\n\
												vec3(10, 10, 0), \n\
												vec3(410, 10, 0), \n\
												vec3(10, 410, 0), \n\
												vec3(410, 410, 0)); \n\
						void main()\n\
						{\n\
							gl_Position = _mvp * vec4(_pos[gl_VertexID], 1.0);\n\
						}";
		const char* ps = "void main()\
						{\
							if( gl_FragCoord.x > 100 ) discard; \
							if( gl_FragCoord.y > 400 ) discard; \
							gl_FragColor = gl_FrontFacing ? vec4(1.0, 0.0, 0.0, 1.0) : vec4(0,1,0,1); \
						}";
		createProgram(vs, ps);
		_mvp = glGetUniformLocation(_program, "_mvp");
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