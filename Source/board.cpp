#include "board.h"

Board::Board(int size)
	:m_Tiles(nullptr), m_PreviousState(nullptr), m_Drawables(nullptr),
     m_Size(size), m_Score(0), m_Time(0), m_DrawablesCount(0), m_IsOver(false)
{
	Reset(size);
}

Board::~Board()
{
	Delete2D(m_PreviousState, m_Size);
	Delete2D(m_Tiles, m_Size);
	Delete1D(m_Drawables);
}

void Board::ToPreviousState()
{
	Copy2D(m_PreviousState, m_Tiles, m_Size);
}

void Board::Reset(int size)
{
	m_DrawablesCount = 0;
	m_Time = 0;
	m_Score = 0;
	m_IsOver = false;

	Delete2D(m_PreviousState, m_Size);
	Delete2D(m_Tiles, m_Size);
	Delete1D(m_Drawables);

	m_Size = size;
	Allocate2D(&m_Tiles, m_Size);
	Allocate2D(&m_PreviousState, m_Size);
	Allocate1D(&m_Drawables, (m_Size + 1) * (m_Size + 1));

	SpawnRandom();
	Copy2D(m_Tiles, m_PreviousState, m_Size);

}

void Board::SpawnRandom()
{
	if (m_IsOver)
		return;

	int empty = 0;
	for (int i = 0; i < m_Size; i++)
		for (int j = 0; j < m_Size; j++)
			if(m_Tiles[i][j].value == Tile::NO_TILE)
				empty++;
	if (empty == 0)
	{
#if _DEBUG
		printf("Cannot spawn random tile. No space left.\n");
#endif
		return;
	}
	int pos = rand() % empty;
	empty = 0;

	for (int i = 0; i < m_Size; i++)
		for (int j = 0; j < m_Size; j++)
			if (m_Tiles[i][j].value == Tile::NO_TILE)
			{
				if (empty == pos)
				{
					m_Tiles[i][j].New();
					AddToDrawables(i, j, i, j, true);
					return;
				}
				empty++;
			}
}

void Board::Move(int dx, int dy)
{
#if _DEBUG
	if (dx && dy)
		printf("Two moves at once.\n");
#endif

	if (m_IsOver)
		return;

	bool** WasConnected;
	Allocate2D(&WasConnected, m_Size);
	Memset2D(WasConnected, m_Size, false);
	m_DrawablesCount = 0;

	Tile** Buffor;
	Allocate2D(&Buffor, m_Size);
	Copy2D(m_Tiles, Buffor, m_Size);

	bool change_occured = false;

	if (dx)	//Horizontal move
	{
		int start_j =	(dx > 0 ?	m_Size - 1	:	 0);
		int d_j =		(dx > 0 ?	-1			:	 1);
		int limit_j =	(dx > 0 ?	-1			:	 m_Size);
		int start_k =	(dx > 0 ?	 1			:	-1);
		int limit_k =	(dx > 0 ?	 m_Size		:	-1);
		int d_k =		(dx > 0 ?	 1			:	-1);

		for (int i = 0; i < m_Size; i++)
		{
			for (int j = start_j; j != limit_j; j += d_j)
			{
				bool no_tile_found = true;
				if (m_Tiles[i][j].value == Tile::NO_TILE)
					continue;

				bool added_to_drawables = false;

				for (int k = j + start_k; k != limit_k; k += d_k)
				{
					if (m_Tiles[i][k].value != Tile::NO_TILE)
					{
						if (m_Tiles[i][k].value == m_Tiles[i][j].value && WasConnected[i][k] == false)
						{

							AddToDrawables(i, j, i, k);
							added_to_drawables = true;

							m_Tiles[i][k].value *= 2;
							m_Tiles[i][j].Delete();
							m_Score += m_Tiles[i][k].value;


							WasConnected[i][k] = true;
							change_occured = true;
						}
						else
							if (k != j + start_k)
							{
								AddToDrawables(i, j, i, k - d_k);
								added_to_drawables = true;

								m_Tiles[i][k - d_k] = m_Tiles[i][j];
								m_Tiles[i][j].Delete();
								change_occured = true;
							}
						no_tile_found = false;
						break;
					}
				}

				if (no_tile_found && j != start_j)
				{
					AddToDrawables(i, j, i, start_j);
					added_to_drawables = true;

					m_Tiles[i][start_j] = m_Tiles[i][j];
					m_Tiles[i][j].Delete();
					change_occured = true;
				}

				if (!added_to_drawables)
					AddToDrawables(i, j, i, j);
			}
		}
	}
	else if (dy)
	{
		int start_j =	(dy < 0 ?	m_Size - 1	:	 0);
		int d_j =		(dy < 0 ?	-1			:	 1);
		int limit_j =	(dy < 0 ?	-1			:	 m_Size);
		int start_k =	(dy < 0 ?	1			:	-1);
		int limit_k =	(dy < 0 ?	m_Size		:	-1);
		int d_k =		(dy < 0 ?	 1			:	-1);

		for (int i = 0; i < m_Size; i++)
		{
			for (int j = start_j; j != limit_j; j += d_j)
			{
				bool no_tile_found = true;
				if (m_Tiles[j][i].value == Tile::NO_TILE)
					continue;

				bool added_to_drawables = false;

				for (int k = j + start_k; k != limit_k; k += d_k)
				{
					if (m_Tiles[k][i].value != Tile::NO_TILE)
					{
						if (m_Tiles[k][i].value == m_Tiles[j][i].value && WasConnected[k][i] == false)
						{
							AddToDrawables(j, i, k, i);
							added_to_drawables = true;

							m_Tiles[k][i].value *= 2;
							m_Tiles[j][i].Delete();
							m_Score += m_Tiles[k][i].value;

							WasConnected[k][i] = true;
							change_occured = true;
						}
						else
							if (k != j + start_k)
							{
								AddToDrawables(j, i, k - d_k, i);
								added_to_drawables = true;

								m_Tiles[k - d_k][i] = m_Tiles[j][i];
								m_Tiles[j][i].Delete();
								change_occured = true;
							}
						no_tile_found = false;
						break;
					}
				}

				if (no_tile_found && j != start_j)
				{
					AddToDrawables(j, i, start_j, i);
					added_to_drawables = true;

					m_Tiles[start_j][i] = m_Tiles[j][i];
					m_Tiles[j][i].Delete();
					change_occured = true;
				}

				if (!added_to_drawables)
					AddToDrawables(j, i, j, i);
			}
		}
	}


	if (change_occured)
	{
		SpawnRandom();
		Copy2D(Buffor, m_PreviousState, m_Size);
	}

	Delete2D(WasConnected, m_Size);
	Delete2D(Buffor, m_Size);


	CheckIfOver();
}

void Board::Update(Uint32 time)
{
	if(!m_IsOver)
		m_Time += time;

	m_AnimationFinished = true;
	for (int i = 0; i < m_DrawablesCount; i++)
	{
		DrawableTile& tile = m_Drawables[i];

		int dx = (tile.transformation.dest_x - tile.transformation.x);
		int movement = min<int>(abs(dx), static_cast<float>(TILE_SPEED*time) / 1000.f);
		if (dx < 0)
			tile.transformation.x -= movement;
		else
			tile.transformation.x += movement;

		int dy = (tile.transformation.dest_y - tile.transformation.y);
		movement = min<int>(abs(dy), static_cast<float>(TILE_SPEED*time) / 1000.f);
		if (dy < 0)
			tile.transformation.y -= movement;
		else
			tile.transformation.y += movement;
		
		if (tile.transformation.waiting_time)
			tile.transformation.waiting_time = max<int>(0, abs(tile.transformation.waiting_time - time));

		if (tile.transformation.x != tile.transformation.dest_x ||
			tile.transformation.y != tile.transformation.dest_y || tile.transformation.waiting_time!=0)
			m_AnimationFinished = false;
	}

	if (m_AnimationFinished)
	{
		m_DrawablesCount = 0;
		for (int i = 0; i < m_Size; i++)
			for (int j = 0; j < m_Size; j++)
				if(m_Tiles[i][j].value != Tile::NO_TILE)
				AddToDrawables(i, j, i, j);
	}
}

void Board::Draw(Window& window)
{
	//Drawing actual board:
	Uint32 border_color = SDL_MapRGB(window.GetScreen()->format, 187, 173, 160);
	Uint32 fill_color = SDL_MapRGB(window.GetScreen()->format, 205, 193, 180);
	int width = (BOARD_WIDTH - (m_Size - 1) * BOARD_BORDER[m_Size]) / m_Size;
	int height = (BOARD_HEIGHT - (m_Size - 1) * BOARD_BORDER[m_Size]) / m_Size;

	for (int i = 0; i < m_Size; i++)
		for (int j = 0; j < m_Size; j++)
		{
			int x = BOARD_X[m_Size] + j * (width + BOARD_BORDER[m_Size]) + BOARD_BORDER[m_Size];
			int y = BOARD_Y + i * (height + BOARD_BORDER[m_Size]) + BOARD_BORDER[m_Size];
			window.DrawRectangle(x, y, width, height, BOARD_BORDER[m_Size], border_color, fill_color);
		}


	for (int i = 0; i < m_DrawablesCount; i++)
	{
		DrawableTile& tile = m_Drawables[i];

		if (tile.transformation.waiting_time != 0)
			continue;

		int power_of_two = static_cast<int>(log2f(tile.value));
		Uint32 tile_color = SDL_MapRGB(window.GetScreen()->format, TILE_SCORE_RED[power_of_two], TILE_SCORE_GREEN[power_of_two], TILE_SCORE_BLUE[power_of_two]);

		char* value_string = to_cstring(tile.value);


		int font_size = min<int>(TILE_FONT_SIZE, (width - 2 * TILE_PADDING) / strlen(value_string));
		window.DrawRectangle(tile.transformation.x + BOARD_BORDER[m_Size], tile.transformation.y + BOARD_BORDER[m_Size], width, height,0, border_color, tile_color);
		window.DrawString(value_string, tile.transformation.x + (width - static_cast<int>(strlen(value_string))*font_size) / 2 + BOARD_BORDER[m_Size], 
			tile.transformation.y + (height - font_size) / 2 + BOARD_BORDER[m_Size], font_size,
			TILE_LABEL_COLOR_RED, TILE_LABEL_COLOR_GREEN, TILE_LABEL_COLOR_BLUE);

		delete[] value_string;

	}

	//Drawing labels:
	window.DrawString(LOGO_STRING, LOGO_X, LOGO_Y, LOGO_FONT_SIZE, LABEL_COLOR_RED, LABEL_COLOR_GREEN, LABEL_COLOR_BLUE);
	window.DrawString(LABEL_STRING, LABEL_X, LABEL_Y, LABEL_FONT_SIZE, LABEL_COLOR_RED, LABEL_COLOR_GREEN, LABEL_COLOR_GREEN);
	if(m_IsOver)
		window.DrawString(GAMEOVER_STRING, GAMEOVER_X, GAMEOVER_Y, GAMEOVER_FONT_SIZE, LABEL_COLOR_RED, LABEL_COLOR_GREEN, LABEL_COLOR_BLUE);

	//Drawing score:
	window.DrawRectangle(SCORE_X, SCORE_Y, SCORE_WIDTH, SCORE_HEIGHT, 0, border_color, fill_color);
	window.DrawString(SCORE_STRING, SCORE_X + ((SCORE_WIDTH - strlen(SCORE_STRING)*SCORE_FONT_SIZE) / 2),
		SCORE_Y + SCORE_PADDING, SCORE_FONT_SIZE, SCORE_COLOR_RED, SCORE_COLOR_GREEN, SCORE_COLOR_BLUE);
	char* score_value_string = to_cstring(m_Score);
	int score_value_font = min<int>(SCORE_VALUE_FONT_SIZE, (SCORE_WIDTH-2*SCORE_PADDING) / strlen(score_value_string));
	window.DrawString(score_value_string, SCORE_X + ((SCORE_WIDTH - static_cast<int>(strlen(score_value_string))*score_value_font) / 2),
		SCORE_Y + SCORE_FONT_SIZE + SCORE_PADDING * 2, score_value_font, SCORE_VALUE_COLOR_RED, SCORE_VALUE_COLOR_GREEN, SCORE_VALUE_COLOR_BLUE);
	delete[] score_value_string;

	//Drawing time:
	window.DrawRectangle(TIME_X, TIME_Y, TIME_WIDTH, TIME_HEIGHT, 0, border_color, fill_color);
	window.DrawString(TIME_STRING, TIME_X + ((TIME_WIDTH - strlen(TIME_STRING)*TIME_FONT_SIZE) / 2),
		TIME_Y + TIME_PADDING, TIME_FONT_SIZE, TIME_COLOR_RED, TIME_COLOR_GREEN, TIME_COLOR_BLUE);
	char* time_value_string = to_time(m_Time/1000, false);
	int time_value_font = min<int>(TIME_VALUE_FONT_SIZE, (TIME_WIDTH - 2 * TIME_PADDING) / strlen(time_value_string));
	window.DrawString(time_value_string, TIME_X + ((TIME_WIDTH - static_cast<int>(strlen(time_value_string))*time_value_font) / 2),
		TIME_Y + TIME_FONT_SIZE + TIME_PADDING * 2, time_value_font, TIME_VALUE_COLOR_RED, TIME_VALUE_COLOR_GREEN, TIME_VALUE_COLOR_BLUE);
	delete[] time_value_string;


}

void Board::GetTileXY(int* x, int* y, int i, int j) const
{
	int width = (BOARD_WIDTH - (m_Size - 1) * BOARD_BORDER[m_Size]) / m_Size;
	int height = (BOARD_HEIGHT - (m_Size - 1) * BOARD_BORDER[m_Size]) / m_Size;
	*x = BOARD_X[m_Size] + j * (width + BOARD_BORDER[m_Size]) + BOARD_BORDER[m_Size];
	*y = BOARD_Y + i * (height + BOARD_BORDER[m_Size]) + BOARD_BORDER[m_Size];
}

void Board::AddToDrawables(int i, int j, int dest_i, int dest_j, bool wait)
{
	int x, y;
	GetTileXY(&x, &y, i, j);
	int dstx, dsty;
	GetTileXY(&dstx, &dsty, dest_i, dest_j);
	m_Drawables[m_DrawablesCount++] = DrawableTile(m_Tiles[i][j], x, y, dstx, dsty, wait);
}

void Board::CheckIfOver()
{
	for(int i = 0; i < m_Size; i++)
		for(int j = 0; j<m_Size; j++)
			if (m_Tiles[i][j].value == Tile::NO_TILE)
			{
				m_IsOver = false;
				return;
			}

	for (int i = 0; i < m_Size; i++)
		for (int j = 0; j < m_Size; j++)
		{
			if (j != m_Size - 1 && m_Tiles[i][j].value == m_Tiles[i][j + 1].value)
			{
				m_IsOver = false;
				return;
			}

			if (i != m_Size - 1 && m_Tiles[i][j].value == m_Tiles[i + 1][j].value)
			{
				m_IsOver = false;
				return;
			}
		}

	m_IsOver = true;
}