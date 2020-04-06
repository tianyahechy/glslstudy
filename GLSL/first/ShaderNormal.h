#pragma once
#include "GLSLProgram.hpp"

class ShaderNormal : public GLSLProgram
{
public:
	virtual void    initialize()
	{
		const char* vs = "varying vec4 outColor;\
						void main()\
						{\
							outColor = vec4(gl_Normal,1);\
							gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
						}";
		const char* ps = "varying vec4 outColor;\
						void main()\
						{\
							gl_FragColor = outColor ; \
						}";
		createProgram(vs, ps);

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