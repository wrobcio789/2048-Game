#pragma once
#include <cstdio>
#include <cstring>
#include "sdl_extension.h"
#include "constants.h"

class Window
{
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Surface* m_Screen;
	SDL_Texture* m_ScreenTexture;
	SDL_Surface* m_Charset;

	Uint32 m_BackgroundColor;

public:
	Window();
	~Window();

	void Clear();
	void Display();

	void DrawRectangle(int x, int y, int width, int height, int border_width, Uint32 border_color, Uint32 fill_color);
	void DrawString(const char* string, int x, int y, 
		int size = FONT_SIZE, Uint8 red = UINT8_MAX, Uint8 green = UINT8_MAX, Uint8 blue = UINT8_MAX);

	SDL_Surface* GetScreen();
	SDL_Surface* GetCharset();
};