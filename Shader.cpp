#include "Shader.h"

std::map<std::string, ShaderProgram*> SHADER_REGISTER_EXTRN = std::map<std::string, ShaderProgram*>();

ShaderProgram::ShaderProgram(std::string customName, std::string* locations, GLenum* shaderTypes, int count) : name(customName) {

	this->programError = false;
	std::string* data = new std::string[count];
	GLuint* shaderIDs = new GLuint[count];

	//Create shader program.
	this->shaderProgramID = glCreateProgram();

	for (int i = 0; i < count; i++) {
		//Create shader.
		shaderIDs[i] = glCreateShader(shaderTypes[i]);

		//Read shader data.
		std::ifstream shaderDataStream = std::ifstream(locations[i]);
		if (shaderDataStream.is_open()) {
			while (!shaderDataStream.eof()) {
				std::string currentLine = "";
				std::getline(shaderDataStream, currentLine);
				data[i].append(currentLine).append("\n");
			}
			shaderDataStream.close();
		}

		//Apply shader data.
		const char *c_str = data[i].c_str();
		glShaderSource(shaderIDs[i], 1, &c_str, NULL);

		//Compile shader.
		glCompileShader(shaderIDs[i]);

		//Get any errors from compilation. If no errors present, attach shader to program.
		GLint hasCompiled;
		glGetShaderiv(shaderIDs[i], GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled) {
			glAttachShader(this->shaderProgramID, shaderIDs[i]);
			std::cout << "Attached shader (" << shaderIDs[i] << ") to program (" << this->shaderProgramID << ").\n";
		}
		else {
			programError = true;
			GLchar* infoLog = new GLchar[512];
			glGetShaderInfoLog(shaderIDs[i], 512, NULL, infoLog);
			std::cout << "SHADER COMPILE ERROR\n" << infoLog << "\n";
		}
	}

	//Link the program and register the shader.
	if (!programError) {
		glLinkProgram(this->shaderProgramID);

		//Get any errors from link.
		GLint hasLinked;
		glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &hasLinked);
		if (hasLinked) {
			std::cout << "Linked program successfully. (" << this->shaderProgramID << ")\n";
		}
		else {
			programError = true;
			GLchar* infoLog = new GLchar[512];
			glGetProgramInfoLog(this->shaderProgramID, 512, NULL, infoLog);
			std::cout << "PROGRAM LINK ERROR\n" << infoLog << "\n";
		}

		//Register.
		SHADER_REGISTER_EXTRN.insert(std::pair<std::string, ShaderProgram*>(this->name, this));
	}

	for (int i = 0; i < count; i++) {
		glDeleteShader(shaderIDs[i]);
	}

	delete[] data;
	delete[] shaderIDs;
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->shaderProgramID);
}

bool ShaderProgram::hasProgramErrored() {
	return this->programError;
}

GLuint ShaderProgram::getShaderProgramID() {
	return this->shaderProgramID;
}

void ShaderProgram::updateShader(glm::mat4* matrix, char* uniform) {
	GLuint uniformLoc = glGetUniformLocation(this->getShaderProgramID(), uniform);
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(*matrix));
}

void ShaderProgram::updateShader(glm::mat4* matrices[], char* uniforms[], unsigned int count) {
	for (int i = 0; i < count; i++) {
		this->updateShader(matrices[i], uniforms[i]);
	}
}
