#include "Shader.h"



Shader::Shader(const std::string VertexShader, const std::string fragmentshader)
{
	this->VertexShader = VertexShader;
	this->fragmentshader = fragmentshader;
}


Shader::~Shader()
{
	std::cout << "[*] I am a shader and i am dying :(" << std::endl;
	glDeleteProgram(program);
}

void Shader::Compile()
{
	unsigned int program = glCreateProgram();
	unsigned int vs = cmpshdr(VertexShader, GL_VERTEX_SHADER);
	unsigned int fs = cmpshdr(fragmentshader, GL_FRAGMENT_SHADER);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	this->program = program;
	std::cout << "My Current Program : " << program << std::endl;
}
 unsigned int Shader::cmpshdr(const std::string& source, unsigned int type) {
	 unsigned int id = glCreateShader(type);
	 const char* src = source.c_str();
	 glShaderSource(id, 1, &src, nullptr);
	 glCompileShader(id);
	 int  success;
	 char infoLog[512];
	 glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	 if (!success)
	 {
		 glGetShaderInfoLog(id, 512, NULL, infoLog);
		 std::cout <<  ( type == GL_VERTEX_SHADER ?  "ERROR::SHADER::VERTEX:: COMPILATION_FAILED\n" : "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"  )<< infoLog << std::endl;
	 }
	 return id;
}
 void Shader::Use() {
	 glUseProgram(program);
 }

 unsigned int Shader::getuniformlocation(std::string name)
 {
	 return glGetUniformLocation(program, name.c_str());
 }
