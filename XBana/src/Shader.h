#pragma once
#include <string>
#include <GL/glew.h>
#include <iostream>
class Shader
{
public:
	Shader(const std::string VertexShader,const std::string fragmentshader);
	~Shader();
	void Compile();
	void Use();
	unsigned int program;
	unsigned int getuniformlocation(std::string name);
private:
	// Compiling a shader from source and type
	static unsigned int cmpshdr(const std::string& source, unsigned int type);
	std::string VertexShader, fragmentshader;
};

