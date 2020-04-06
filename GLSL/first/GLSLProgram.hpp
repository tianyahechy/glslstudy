#pragma once
#include <assert.h>
#include "glew\glew.h"

class GLSLProgram
{
public:
	typedef GLint	attribute;
	typedef GLint	uniform;
public:
	GLint			_vHandle;
	GLint			_pHandle;
	GLint			_program;
public:
	GLSLProgram()
	{
		_vHandle = -1;
		_pHandle = -1;
		_program = -1;
	}
	virtual ~GLSLProgram()
	{

	}
	virtual void initialize()
	{
		const char * vs = "";
		const char * ps = "";
		createProgram(vs, ps);
	}
	//使用shader
	virtual void begin()
	{
		glUseProgram(_program);
	}
	//结束
	virtual void end()
	{
		glUseProgram(0);
	}
	//根据输入的源代码编译shader
	bool createProgram(const char * vs, const char * ps)
	{
		bool result = false;
		do
		{
			//创建shader
			_vHandle = glCreateShader(GL_VERTEX_SHADER);
			_pHandle = glCreateShader(GL_FRAGMENT_SHADER);
			//指定shader的源代码
			glShaderSource(_vHandle, 1, (const GLchar**)& vs, 0);
			glShaderSource(_pHandle, 1, (const GLchar**)& ps, 0);

			//编译shader
			glCompileShader(_vHandle);
			GLint status = 0;
			char compileLog[1024] = { 0 };
			glGetShaderiv(_vHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(_vHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			glCompileShader(_pHandle);
			glGetShaderiv(_pHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(_pHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			//创建程序
			_program = glCreateProgram();
			glAttachShader(_program, _vHandle);
			glAttachShader(_program, _pHandle);
			//链接程序
			glLinkProgram(_program);
			glGetProgramiv(_program, GL_LINK_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetProgramInfoLog(_program, sizeof(compileLog), 0, compileLog);
				break;
			}
			result = true;
		} while (false);

		if (!result)
		{
			if ( -1 != _vHandle )
			{
				glDeleteShader(_vHandle);
			}
			if (-1 != _pHandle)
			{
				glDeleteShader(_pHandle);
			}
			if (-1 != _program)
			{
				glDeleteProgram(_program);
			}
			_vHandle = -1;
			_pHandle = -1;
			_program = -1;
		}
		return result;
	}
};

class HelloShader : public GLSLProgram
{
public:
	GLint			_color;
public:
	virtual void initialize()
	{
		const char* vs = "void main()\
						{\
							gl_Position = ftransform();\
						}";
		const char* ps = "uniform vec4 _color;\
						void main()\
						{\
							gl_FragColor = _color; \
						}";
		createProgram(vs, ps);
		_color = glGetUniformLocation(_program, "_color");
	}
};