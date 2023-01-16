#include"ShaderProgram.hpp"
Shader::Shader() {
	programID = glCreateProgram();
}
void Shader::AddShaderFromFile(std::string FileName, Shader::SHADER_TYPE shader_type) {
	GLenum shader;
	if (shader_type==Shader::VERTEX_SHADER)
	{
		shader = GL_VERTEX_SHADER;
	}
	else {
		shader = GL_FRAGMENT_SHADER;
	}
	shaderID[shader_type] = glCreateShader(shader);
	std::string data;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		char chr;
		while ((chr=file.get())!=EOF) {
			data += chr;
		}
	}
	file.close();

	const char* data_ptr = &data[0];
	glShaderSource(shaderID[shader_type], 1, &data_ptr, NULL);
}
void Shader::CompileShader(Shader::SHADER_TYPE shader_type) {
	glCompileShader(shaderID[shader_type]);
}
void Shader::AttachToProgram(Shader::SHADER_TYPE shader_type) {
	glAttachShader(programID, shaderID[shader_type]);
}
void Shader::LinkProgram() {
	glLinkProgram(programID);
}
void Shader::ConnectVariable(std::string var_name) {
	uniform_map[var_name] = glGetUniformLocation(programID, var_name.c_str());
}
void Shader::setVec3(std::string var_name, glm::vec3 position) {
	glUniform3f(uniform_map[var_name], position.x, position.y, position.z);
}
void Shader::setVec4(std::string var_name, glm::vec4 color) {
	glUniform4f(uniform_map[var_name], color.r, color.g, color.b, color.a);
}
unsigned int Shader::getProgramID() {
	return programID;
}