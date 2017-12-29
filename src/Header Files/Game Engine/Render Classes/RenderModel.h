#ifndef RENDERMODEL_H
#define RENDERMODEL_H

#include "Game Engine/Utility Classes/Externals.h"

class RenderModel {
	GLuint VAO, elementOrderCount;
	std::vector<float> data;

	std::string preferredShaderTag;

	//Speed optimisation. Stops class from performing check for shader every frame.
	GLuint preferredShaderID;
	bool shaderRetrievalSuccessful;

public:
	static void Load(std::string& location, std::string& preferredShader, int& elementCount, std::vector<int>& elementOrder, std::vector<float>& elementColours, std::vector<float>& elementCoordPoints, std::vector<float>& elementUVs);
	
	RenderModel(std::string location);
	virtual ~RenderModel();

	GLuint getElementOrderCount();
	GLuint getModelVAO();
	GLuint getPreferredShader();

	//This simply does a check for the model's preferred shader tag and
	//does not perform a check to see if the preferred shader exists.
	bool hasPreferredShader();

	//Only use this function if a shader is defined in the model file.
	void draw();
	void draw(GLuint shaderID);
};

#endif
