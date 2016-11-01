#pragma once

#include <SDL.h>
#include <glew.h>
#include <string>
#include <iostream>

enum class GameState {PLAY, EXIT};

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

	void Run();
	void DrawGame();

private:
	void InitSystems();
	void GameLoop();
	void ProcessInput();


	SDL_Window *_window;
	int _screenWidth, _screenHeight;
	GameState _gameState;



};

