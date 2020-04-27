#include "game.h"

Game::Game()
	:m_ShouldClose(false)
{
	InitAllSDL();
	srand(time(NULL));
}

Game::~Game()
{
	atexit(SDL_Quit);
}

void Game::Input()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_KEYDOWN)
		{
			switch (Event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				m_Board.Move(1, 0);
				break;
			case SDLK_LEFT:
				m_Board.Move(-1, 0);
				break;

			case SDLK_DOWN:
				m_Board.Move(0, -1);
				break;

			case SDLK_UP:
				m_Board.Move(0, 1);
				break;

			case GAME_END:
				m_ShouldClose = true;
				break;

			case NEW_GAME:
				m_Board.Reset();
				break;

			case SAVE_GAME:

				break;

			case LOAD_GAME:
				
				break;

			case CANCEL_MOVE:
				m_Board.ToPreviousState();
				break;

			case SHOW_RANK:

				break;
			}
		}
		else if (Event.type == SDL_KEYUP)
		{

		}
		else if (Event.type == SDL_QUIT)
			m_ShouldClose = true;
	}
}

int Game::Run()
{
	Uint32 time1, time2;
	time1 = SDL_GetTicks();


	while (!m_ShouldClose)
	{
		time2 = SDL_GetTicks();
		Uint32 delta_time = time2 - time1;
		m_Board.Update(delta_time);
		time1 = time2;

		Input();

		m_Board.Draw(m_Window);
		m_Window.Display();
	}

	return 0;
}


