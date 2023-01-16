#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include<iostream>
#include<fstream>
#include<map>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Shader {
public:
	enum SHADER_TYPE
	{
		VERTEX_SHADER=0,
		FRAGMENT_SHADER=1
	};


	Shader();
	void AddShaderFromFile(std::string FileName,Shader::SHADER_TYPE shader_type);
	void CompileShader(Shader::SHADER_TYPE shader_type);
	void AttachToProgram(Shader::SHADER_TYPE shader_type);
	void LinkProgram();
	unsigned int getProgramID();



	void ConnectVariable(std::string var_name);
	void setVec3(std::string var_name,glm::vec3 position);
	void setVec4(std::string var_name,glm::vec4 color);
private:
	unsigned int programID;
	unsigned int shaderID[2];
	std::map<std::string, int> uniform_map;

};
#endif // !SHADERPROGRAM_HPP
