#pragma once
#include <assert.h>
#include "glew/glew.h"

class GLSLProgram
{
public:
	typedef GLint attribute;
	typedef GLint uniform;

public:
	GLint	_vHandle;
	GLint	_pHandle;
	GLint	_program;
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
		const char* vs = "";
		const char* ps = "";
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
protected:
	//���������Դ�������shader
	bool createProgram(const char* vs, const char* ps)
	{
		bool result = false;
		do
		{
			//����shader
			_vHandle = glCreateShader(GL_VERTEX_SHADER);
			_pHandle = glCreateShader(GL_FRAGMENT_SHADER);
			//ָ��shader��Դ����
			glShaderSource(_vHandle, 1, (const GLchar**)& vs, 0);
			glShaderSource(_pHandle, 1, (const GLchar**)& ps, 0);
			//����shader
			glCompileShader(_vHandle);
			GLint status = 0;
			char compileLog[1024] = { 0 };
			glGetShaderiv(_vHandle, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				glGetShaderInfoLog(_vHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			glCompileShader(_pHandle);
			glGetShaderiv(_pHandle, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				glGetShaderInfoLog(_pHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			//��������
			_program = glCreateProgram();
			glAttachShader(_program, _vHandle);
			glAttachShader(_program, _pHandle);
			//���ӳ���
			glLinkProgram(_program);
			glGetProgramiv(_program, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				glGetProgramInfoLog(_program, sizeof(compileLog), 0, compileLog);
				break;
			}
			result = true;
		} while (false);

		if (!result)
		{
			if (_vHandle != -1)
			{
				glDeleteShader(_vHandle);
			}
			if (_pHandle != -1)
			{
				glDeleteShader(_pHandle);
			}
			if (_program != -1)
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
	uniform _color;
public:
	virtual void initialize()
	{
		const char * vs = "void main() \
						   {\
							  gl_Position = ftransform();\
							}";
		const char * ps = 
						"void main() \
						{\
							gl_FragColor = vec4(1,0,0,1);\
						}";
		createProgram(vs,ps);
		_color = glGetUniformLocation(_program, "_color");
	}

};

class ShaderUniform : public GLSLProgram
{
public:
	uniform _ucolor;
	attribute _position;
	attribute _color;
public:
	virtual void initialize()
	{
		const char * vs = "	attribute vec3 _position; \n\
						  	attribute vec3 _color;\n\
							varying vec3 _outColor;\n\
							void main() \n\
							{\n\
								_outColor = _color;\n\
								gl_Position = gl_ModelViewProjectionMatrix * vec4(_position,1.0);\n\
							}";
		const char * ps = "	uniform vec4 _color; \n\
							varying vec3 _outColor;\n\
							void main() \n\
							{\n\
								gl_FragColor = vec4(_outColor,1);\n\
							}";
		createProgram(vs, ps);
		_ucolor = glGetUniformLocation(_program, "_color");
		_position = glGetAttribLocation(_program, "_position");
		_color = glGetAttribLocation(_program, "_color");
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
private:

};

class ShareVertex : public GLSLProgram
{
public:
	typedef int attribute;
	attribute _position;
	attribute _color;
public:
	virtual void initialize()
	{
		const char * vs = "	#version 130\n\
							in vec3 _position; \n\
						  	in vec3 _color;\n\
							out vec3 _outColor;\n\
							void main() \n\
							{\n\
								_outColor = _color;\n\
								gl_Position = gl_ModelViewProjectionMatrix * vec4(_position,1.0);\n\
							}";
		const char * ps = "	in vec3 _outColor;\n\
							void main() \n\
							{\n\
								gl_FragColor = vec4(_outColor,1);\n\
							}";
		createProgram(vs, ps);
		_position = glGetAttribLocation(_program, "_position");
		_color = glGetAttribLocation(_program, "_color");
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
private:

};
