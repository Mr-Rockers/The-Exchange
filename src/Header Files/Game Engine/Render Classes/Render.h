#ifndef RENDER_H
#define RENDER_H

#include "Game Engine/Utility Classes/Externals.h"
#include "Game Engine/Render Classes/Shader.h"
#include "Game Engine/Render Classes/RenderModel.h"

class Render {
public:
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
	glm::mat4 viewMatrix, projectionMatrix;
	int scrW, scrH;
};

#endif
