#pragma once
#include "GLSLProgram.hpp"

class ShaderVertex : public GLSLProgram
{
public:
	uniform _color;
	virtual void initialize()
	{
		const char* vs = "varying vec4 _color;\
						varying vec4 outColor;\
						void main()\
						{\
							outColor = _color;\
							gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
							//gl_Position = ftransform();\
						}";
		const char* ps = "varying vec4 outColor;\
						void main()\
						{\
							gl_FragColor = outColor; \
						}";
		createProgram(vs, ps);
		_color = glGetUniformLocation(_program, "_color");
	}


};