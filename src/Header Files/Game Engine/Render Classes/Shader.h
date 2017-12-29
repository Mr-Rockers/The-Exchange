#ifndef SHADER_H
#define SHADER_H

#include "Game Engine/Utility Classes/Externals.h"

class ShaderProgram {
	GLuint shaderProgramID;
	bool programError;
	std::string name;
public:
	ShaderProgram(std::string customName, std::string* locations, GLenum* shaderTypes, int count);
	virtual ~ShaderProgram();

	bool hasProgramErrored();
	GLuint getShaderProgramID();

	void updateShader(glm::mat4* matrix, char* uniform);
	void updateShader(glm::mat4* matrices[], char* uniforms[], unsigned int count);
};
extern std::map<std::string, ShaderProgram*> SHADER_REGISTER_EXTRN;

#endif