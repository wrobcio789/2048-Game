#pragma once
#include <cstdio>
#include <cstdlib>
#include <SDL.h>

// narysowanie napisu txt na powierzchni screen, zaczynaj�c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj�ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset);

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1) 
// b�d� poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

// rysowanie prostok�ta o d�ugo�ci bok�w l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor);

void InitAllSDL();
