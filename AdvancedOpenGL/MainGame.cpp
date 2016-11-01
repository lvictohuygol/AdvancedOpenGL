#include "MainGame.h"

#include <iostream>

void fatalError(std::string error)
{
	std::cout << error << std::endl;
	std::cout << "Enter any key to quit...";
	std::cin.get();

	SDL_Quit();
	exit(1);
}

CMainGame::CMainGame()
{
	_window = nullptr;
	_screenWidth = 800;
	_screenHeight = 600;
	_gameState = GameState::PLAY;
}


CMainGame::~CMainGame()
{
}

void CMainGame::Run()
{
	InitSystems();
	GameLoop();
}

void CMainGame::InitSystems()
{
	// Khoi tao SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Tao window
	_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		fatalError("SDL window could not be create!");
	}

	// Bat context cho _window
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be create!");
	}

	// Khoi tao glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew!");
	}

	// Bat double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0, 0, 1.0, 1.0);
}

void CMainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		ProcessInput();
		DrawGame();
	}
}


void CMainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}

void CMainGame::DrawGame()
{
	// Clear buffer ???
	glClearDepth(1.0); // Set do sau clear buffer depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 0, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 500);
	glVertex2f(500, 500);

	glEnd();


	// render _window
	SDL_GL_SwapWindow(_window);
}