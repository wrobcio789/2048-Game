#include "window.h"

Window::Window()
{
	InitAllSDL();
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_Window, &m_Renderer) != 0)
	{
		printf("Could not create window or renderer: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetWindowTitle(m_Window, WINDOW_TITLE);
	SDL_RenderSetLogicalSize(m_Renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_ShowCursor(SDL_DISABLE);

	if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") != SDL_TRUE)
		printf("Linear filtering not set\n");
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);


	m_Screen = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
	if (m_Screen == nullptr)
	{
		printf("Could not create screen surface: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	m_ScreenTexture = SDL_CreateTextureFromSurface(m_Renderer, m_Screen);
	if (m_ScreenTexture == nullptr)
	{
		printf("Could not create screen texture: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	m_Charset = SDL_LoadBMP(CHARSET_FILEPATH);
	if (m_Charset == nullptr) {
		printf("SDL_LoadBMP %s error: %s\n", CHARSET_FILEPATH, SDL_GetError());
		exit(EXIT_FAILURE);
	};
	SDL_SetColorKey(m_Charset, true, 0x00000000);


	m_BackgroundColor = SDL_MapRGB(m_Screen->format, 250, 248, 239);
	Clear();

#if _DEBUG
	printf("SDL initalized properly.\n");
#endif
}

Window::~Window()
{
	SDL_FreeSurface(m_Screen);
	SDL_DestroyTexture(m_ScreenTexture);
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}

void Window::Clear()
{
	SDL_FillRect(m_Screen, nullptr, m_BackgroundColor);
}

void Window::Display()
{
	SDL_UpdateTexture(m_ScreenTexture, NULL, m_Screen->pixels, m_Screen->pitch);
	SDL_RenderCopy(m_Renderer, m_ScreenTexture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);

	Clear();
}

void Window::DrawRectangle(int x, int y, int width, int height, int border_width,
	Uint32 border_color, Uint32 fill_color)
{
	for (int i = 0; i < border_width; i++)
	{
		DrawLine(m_Screen, x + i, y, height + 2*border_width, 0, 1, border_color);
		DrawLine(m_Screen, x, y + i, width + 2*border_width, 1, 0, border_color);
		DrawLine(m_Screen, x + border_width + width + i, y, height + 2*border_width, 0, 1, border_color);
		DrawLine(m_Screen, x, y + border_width + height + i, width + 2*border_width, 1, 0, border_color);
	}

	for (int i = 0; i < width; i++)
		DrawLine(m_Screen, x + border_width + i, y + border_width, height, 0, 1, fill_color);
}


void Window::DrawString(const char* string, int x, int y, int size, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	if (surface == nullptr)
	{
		printf("Could not create surface: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetSurfaceColorMod(m_Charset, red, green, blue);
	::DrawString(surface, x, y, string, GetCharset());

	SDL_Rect src_rect, dst_rect;
	src_rect.x = dst_rect.x = x;
	src_rect.y = dst_rect.y = y;
	src_rect.w = FONT_SIZE * strlen(string);
	src_rect.h = FONT_SIZE;
	dst_rect.w = size * strlen(string);
	dst_rect.h = size;

	SDL_BlitScaled(surface, &src_rect, GetScreen(), &dst_rect);

	SDL_FreeSurface(surface);
}

SDL_Surface* Window::GetScreen()
{
	return m_Screen;
}

SDL_Surface* Window::GetCharset()
{
	return m_Charset;
}