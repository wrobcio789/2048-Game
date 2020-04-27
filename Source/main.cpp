#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "game.h"
#include "sdl_extension.h"


int main(int argc, char* argv[])
{
	Game game;

	return game.Run();
}