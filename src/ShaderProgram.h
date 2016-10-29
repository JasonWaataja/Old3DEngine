#pragma once
#include <string>
#include <GL/glew.h>
#include <map>

using namespace std;

class ShaderProgram
{
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint createShader(const string& path, GLenum type);
	void link();

	map<string, int> uniforms;

public:
	GLuint getProgram();
	void use();
	GLint getUniformLocation(const string& name);
	ShaderProgram(const string& vertexShaderPath, const string& fragmentShaderPath);
	~ShaderProgram();
	static string readTextFile(const string& file);
	int addUniform(const string& name);
	int getUniform(const string& name);
};