#ifndef RENDER_H
#define RENDER_H

#include "Externals.h"
#include "Shader.h"
#include "RenderModel.h"

class Render {
public:
	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
	glm::mat4 viewMatrix, projectionMatrix;
	int scrW, scrH;
};

#endif
