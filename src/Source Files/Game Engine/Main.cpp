#include "Game Engine/Utility Classes/Externals.h"
#include "Game Engine/Audio Classes/Audio.h"
#include "Game Engine/Render Classes/Render.h"
#include "Game Logic/Entity.h"
#include "Game Logic/Input.h"

int main(int argc, char** argv) {

	Render render;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		std::cout << "SDL Mixer Error - Mix_OpenAudio:\n" << Mix_GetError() << "\n";
		std::cin.get();
		return -1;
	}
	Mix_AllocateChannels(64);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	render.mainWindow = SDL_CreateWindow("The Exchange", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);

	if (render.mainWindow == nullptr) {
		return -1;
	}

	render.mainContext = SDL_GL_CreateContext(render.mainWindow);

	SDL_GL_SetSwapInterval(1);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return -1;
	}

	//BASIC SHADER
	ShaderProgram basicShader = ShaderProgram("basic", new std::string[2]{"resources/shaders/basic.vert", "resources/shaders/basic.frag"}, new GLuint[2]{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, 2);

	//CUBE MODEL
	RenderModel cube = RenderModel("resources/models/cube.exm");
	glm::mat4 cube1ModelMatrix, cube2ModelMatrix, cubeFollowSoundMatrix;
	cube1ModelMatrix = glm::translate(cube1ModelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
	cube2ModelMatrix = glm::translate(cube2ModelMatrix, glm::vec3(-5.0f, -2.5f, -10.0f));

	//AUDIO TESTS
	/*EntityPlayer playerAudioTest = EntityPlayer("Audio Test");
	AudioClip walkingGravelClip = AudioClip("resources/audio/walkingGravel.wav");
	EntityAudioSource testAudioSource = EntityAudioSource(&playerAudioTest, true, true, 10.0f);
	testAudioSource.setPosition(glm::vec3(0.0f, 0.0f, -5.0f));*/

	//PLAYER
	EntityPlayer localPlayer = EntityPlayer("localhost", &render);

	//GL INIT
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//RUN VARIABLES
	float startTime = 0.0f, endTime = 0.0f, deltaTime = 0.0f;
	bool run = true;
	while (run) {
		//CALCULATE DELTATIME
		if (endTime != 0 || startTime != 0) {
			deltaTime = (endTime - startTime) / 1000.0f;
		}
		startTime = (float) SDL_GetTicks();

		//UPDATE UPDATEABLE ENTITIES
		for (unsigned int i = 0; i < ENTITY_UPDATEABLE_REGISTER_EXTRN.size(); i++) {
			ENTITY_UPDATEABLE_REGISTER_EXTRN.at(i)->update(deltaTime);
		}

		//INPUT
		SDL_Event e;
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT) {
				run = false;
			}
			if (e.type == SDL_KEYDOWN) {
				Input::HandleKeyDown(&localPlayer, &e.key);
			}
			if (e.type == SDL_KEYUP) {
				Input::HandleKeyUp(&localPlayer, &e.key);
			}
			if (e.type == SDL_MOUSEMOTION) {
				Input::HandleMouse(&localPlayer, &e.motion);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				Input::HandleMouseButtonDown(&localPlayer, &e.button);
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				Input::HandleMouseButtonUp(&localPlayer, &e.button);
			}
		}
		Input::Update(&localPlayer);

		//PHYSICS

		//LOGIC

		//RENDER
		SDL_GetWindowSize(render.mainWindow, &render.scrW, &render.scrH);

		render.projectionMatrix = glm::perspective(glm::radians(45.0f), (float)render.scrW / (float)render.scrH, 0.1f, 100.0f);
		render.viewMatrix = glm::lookAt(localPlayer.getPosition(), localPlayer.getPosition() + localPlayer.getForwardLookDirection(), render.UP);

		//std::cout << "Direction - X: " << render.vM_direction.x << " Y: " << render.vM_direction.y << " Z: " << render.vM_direction.z << "\n";

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		cube1ModelMatrix = glm::rotate(cube1ModelMatrix, glm::radians(deltaTime * 10.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		cube2ModelMatrix = glm::rotate(cube2ModelMatrix, glm::radians(-deltaTime * 10.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	
		basicShader.updateShader(new glm::mat4*[3]{ &render.projectionMatrix, &render.viewMatrix, &cube1ModelMatrix }, new char*[3]{ "projection", "view", "transform" }, 3);
		cube.draw();
		basicShader.updateShader(new glm::mat4*[3]{ &render.projectionMatrix, &render.viewMatrix, &cube2ModelMatrix }, new char*[3]{ "projection", "view", "transform" }, 3);
		cube.draw();

		SDL_GL_SwapWindow(render.mainWindow);

		//POST UPDATE
		for (unsigned int i = 0; i < ENTITY_UPDATEABLE_REGISTER_EXTRN.size(); i++) {
			ENTITY_UPDATEABLE_REGISTER_EXTRN.at(i)->postUpdate();
		}
		endTime = (float)SDL_GetTicks();
	}

	Mix_Quit();
	SDL_Quit();
	return 0;
}