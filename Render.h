#ifndef RENDER_H
#define RENDER_H

#include "Externals.h"
#include "Shader.h"
#include "RenderModel.h"

class Render {
public:
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
	glm::mat4 viewMatrix, projectionMatrix;
	int scrW, scrH;
};

#endif
