#include "Game Engine/Render Classes/Render.h"
#include "Game Logic/Entity.h"

//EntityPlayer LOCAL_PLAYER;

Render::Render() : hasGlewInit(false) {
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	this->mainWindow = SDL_CreateWindow("The Exchange", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

	this->mainContext = SDL_GL_CreateContext(this->mainWindow);

	SDL_GL_SetSwapInterval(1);

	glewExperimental = true;
	if (glewInit() == GLEW_OK) {
		this->hasGlewInit = true;

		this->basicShader = new ShaderProgram("basic", new std::string[2]{ "resources/shaders/basic.vert", "resources/shaders/basic.frag" }, new GLuint[2]{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER }, 2);
		this->consoleShader = new ShaderProgram("console", new std::string[2]{ "resources/shaders/console.vert", "resources/shaders/console.frag" }, new GLuint[2]{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER }, 2);
	
		this->cube = RenderModel("resources/models/objects/cube.exm");
		this->cube1ModelMatrix = glm::translate(cube1ModelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
		this->cube2ModelMatrix = glm::translate(cube2ModelMatrix, glm::vec3(-5.0f, -2.5f, -10.0f));
	}
}

Render::~Render() {

}

void Render::update(float deltaTime) {

	SDL_GetWindowSize(this->mainWindow, &this->scrW, &this->scrH);

	this->projectionMatrix = glm::perspective(glm::radians(45.0f), (float)this->scrW / (float)this->scrH, 0.1f, 100.0f);
	this->viewMatrix = glm::lookAt(LOCAL_PLAYER.getPosition(), LOCAL_PLAYER.getPosition() + LOCAL_PLAYER.getForwardLookDirection(), this->UP);

	//std::cout << "Direction - X: " << this->vM_direction.x << " Y: " << this->vM_direction.y << " Z: " << this->vM_direction.z << "\n";

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	cube1ModelMatrix = glm::rotate(cube1ModelMatrix, glm::radians(deltaTime * 10.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	cube2ModelMatrix = glm::rotate(cube2ModelMatrix, glm::radians(-deltaTime * 10.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	glUseProgram(this->basicShader->getShaderProgramID());
	this->basicShader->updateShader(new glm::mat4*[3]{ &this->projectionMatrix, &this->viewMatrix, &cube1ModelMatrix }, new char*[3]{ "projection", "view", "transform" }, 3);
	cube.draw();
	this->basicShader->updateShader(new glm::mat4*[3]{ &this->projectionMatrix, &this->viewMatrix, &cube2ModelMatrix }, new char*[3]{ "projection", "view", "transform" }, 3);
	cube.draw();

	{
		//DRAW UPDATEABLE ENTITIES
		for (unsigned int i = 0; i < ENTITY_UPDATEABLE_REGISTER_EXTRN.size(); i++) {
			ENTITY_UPDATEABLE_REGISTER_EXTRN.at(i)->draw();
		}
	}

	SDL_GL_SwapWindow(this->mainWindow);
}

bool Render::glewInitialised() {
	return hasGlewInit;
}