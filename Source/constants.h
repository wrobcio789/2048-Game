#pragma once
#include <cstdint>

typedef unsigned int uint;

const int WINDOW_WIDTH = 420;
const int WINDOW_HEIGHT = 560;
constexpr const char* WINDOW_TITLE = "2048 GAME";


//LOGO DIMENSIONS:
const int LOGO_X = 20;
const int LOGO_Y = 20;
const int LOGO_FONT_SIZE = 42;
constexpr const char* LOGO_STRING = "2048";

//Label constants:
const int LABEL_X = LOGO_X;
const int LABEL_Y = LOGO_Y + LOGO_FONT_SIZE + 20;
const int LABEL_FONT_SIZE = 16;
constexpr const char* LABEL_STRING = "Maciej Wroblewski";

//Game over:
const int GAMEOVER_X = LOGO_X;
const int GAMEOVER_Y = LABEL_Y + LABEL_FONT_SIZE + 20;
const int GAMEOVER_FONT_SIZE = 16;
constexpr const char* GAMEOVER_STRING = "Game over. Press N.";

//Score:
const int SCORE_X = LOGO_X + 4 * LOGO_FONT_SIZE + 10;
const int SCORE_Y = LOGO_Y;
const int SCORE_WIDTH = 119;
const int SCORE_HEIGHT = LOGO_FONT_SIZE;
const int SCORE_FONT_SIZE = 8;
const int SCORE_PADDING = 5;
const int SCORE_VALUE_FONT_SIZE = 16;
constexpr const char* SCORE_STRING = "SCORE";

//Time:
const int TIME_X = SCORE_X + SCORE_WIDTH + 10;
const int TIME_Y = SCORE_Y;
const int TIME_WIDTH = 190 - SCORE_WIDTH;
const int TIME_HEIGHT = LOGO_FONT_SIZE;
const int TIME_FONT_SIZE = 8;
const int TIME_PADDING = 5;
const int TIME_VALUE_FONT_SIZE = 16;
constexpr const char* TIME_STRING = "TIME";


//BOARD DIMENSIONS:
const int BOARD_DEFAULT_SIZE = 4;

const int BOARD_WIDTH = 360;
const int BOARD_HEIGHT = BOARD_WIDTH;
const int BOARD_BORDER[] = {10, 10, 10, 10, 10, /*5*/10, 9, 8, 7, 6, /*10*/ 5, 5, 4, 4, 4, /*15*/ 3, 3};
const int BOARD_X[] =	   {10, 10, 10, 10, 10, /*5*/10, 12, 13, 16, 16, /*10*/ 16, 16, 18, 16, 16, /*15*/ 18, 21 };
const int BOARD_Y = LABEL_Y + LABEL_FONT_SIZE + 60;

const int NORMAL_TILE_VALUE = 2;
const int ABNORMAL_TILE_VALUE = 4;
const int ABNORMAL_TILE_CHANCE = 10;

const int TILE_FONT_SIZE = 32;
const int TILE_PADDING = 3;

//Tile speed:
const int TILE_SPEED = 1800;
const int NEW_TILE_WAITING_TIME = 170;

//Colors:
const Uint8 LABEL_COLOR_RED = 119;
const Uint8 LABEL_COLOR_GREEN = 110;
const Uint8 LABEL_COLOR_BLUE = 101;

const Uint8 SCORE_COLOR_RED = 238;
const Uint8 SCORE_COLOR_GREEN = 228;
const Uint8 SCORE_COLOR_BLUE = 218;

const Uint8 SCORE_VALUE_COLOR_RED = 255;
const Uint8 SCORE_VALUE_COLOR_GREEN = 255;
const Uint8 SCORE_VALUE_COLOR_BLUE = 255;

const Uint8 TIME_COLOR_RED = 238;
const Uint8 TIME_COLOR_GREEN = 228;
const Uint8 TIME_COLOR_BLUE = 218;

const Uint8 TIME_VALUE_COLOR_RED = 255;
const Uint8 TIME_VALUE_COLOR_GREEN = 255;
const Uint8 TIME_VALUE_COLOR_BLUE = 255;

const Uint8 TILE_LABEL_COLOR_RED = 119;
const Uint8 TILE_LABEL_COLOR_GREEN = 110;
const Uint8 TILE_LABEL_COLOR_BLUE = 101;

//Tile colors:
const Uint8 TILE_SCORE_RED[18] =		{0, 241, 241, 252, 255, 255, 255, 242, 244, 244, 243, 246, 252, 252, 241, 108, 90,  0};
const Uint8 TILE_SCORE_GREEN[18] =		{ 0, 227, 221, 179, 153, 133, 106, 202, 200, 194, 190, 188, 114, 92,  81,  174, 155, 115 };
const Uint8 TILE_SCORE_BLUE[18] =		{ 0, 220, 199, 119, 98,  95,  59,  112, 95,  80,  60,  43,  108, 89,  55,  217, 230, 195 };

//Font:
const int FONT_SIZE = 8;
constexpr const char* CHARSET_FILEPATH = "cs8x8.bmp";

#define GAME_END		SDLK_ESCAPE
#define NEW_GAME		SDLK_n
#define SAVE_GAME		SDLK_s
#define LOAD_GAME		SDLK_l
#define CANCEL_MOVE		SDLK_u
#define SHOW_RANK		SDLK_r
#define SORT_BY_TIME	SDLK_t
#define SORT_BY_SCORE	SDLK_p

