#include "ShaderProgram.h"
#include <GL/glew.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int ShaderProgram::addUniform(const string& name)
{
	int location = glGetUniformLocation(program, name.c_str());
	if (location < 0)
	{
		cout << "Error finding uniform " << name << endl;
	}
	else
	{
		uniforms[name] = location;
	}
	return location;
}

int ShaderProgram::getUniform(const string& name)
{
	try
	{
		int location = uniforms.at(name);
		return location;
	}
	catch (out_of_range e)
	{
		cout << "Error finding uniform " << name << endl;
		cout << e.what() << endl;
	}
	return -1;
}

GLuint ShaderProgram::getProgram()
{
	return program;
}

string ShaderProgram::readTextFile(const string& file)
{
	string contents;
	ifstream reader;
	reader.open(file);
	if (reader.is_open())
	{
		string line;
		while (getline(reader, line))
		{
			contents.append(line);
			contents.append("\n");
		}
		cout << "Read file " << file << endl;
	}
	else
	{
		cout << "Error opening file " << file << endl;
		int input;
		cin >> input;
	}
	return contents;
}

void ShaderProgram::use()
{
	glUseProgram(program);
}

GLint ShaderProgram::getUniformLocation(const string& name)
{
	return glGetUniformLocation(program, name.c_str());
}

GLuint ShaderProgram::createShader(const string& path, GLenum type)
{
	GLuint shader;
	string contents = readTextFile(path);
	shader = glCreateShader(type);
	const GLchar* asCString = contents.c_str();
	cout << asCString << endl;
	glShaderSource(shader, 1, &asCString, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		cout << "Error compiling shader." << endl;
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar* log = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, log);
		cout << log << endl;
		delete[] log;
		int input;
		cin >> input;
	}
	else
	{
		cout << "Compiled Shader" << endl;
	}
	return shader;
}

void ShaderProgram::link()
{
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		cout << "Error linking program." << endl;
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar* log = new GLchar[length + 1];
		glGetProgramInfoLog(program, length, NULL, log);
		cout << log << endl;
		delete[] log;
		int input;
		cin >> input;
	}
}

ShaderProgram::ShaderProgram(const string& vertexShaderPath, const string& fragmentShaderPath)
{
	program = glCreateProgram();
	vertexShader = createShader(vertexShaderPath, GL_VERTEX_SHADER);
	fragmentShader = createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
}
