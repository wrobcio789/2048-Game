#pragma once
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "board.h"
#include "sdl_extension.h"
#include "constants.h"

class Game
{
private:
	
	Window m_Window;
	Board m_Board;
	bool m_ShouldClose;

	void Input();
public:
	Game();
	~Game();

	int Run();
};