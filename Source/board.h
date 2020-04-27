#pragma once
#include <cmath>
#include "window.h"
#include "utils.h"

class Board
{
	struct Tile
	{
		enum { NO_TILE = 0 };
		int value;

		Tile() 
			:value(0) {}

		void New()
		{
			if (rand() % ABNORMAL_TILE_CHANCE == 0)
				value = ABNORMAL_TILE_VALUE;
			else
				value = NORMAL_TILE_VALUE;
		}

		void Delete()
		{
			value = NO_TILE;
		}
	};

	struct DrawableTile : public Tile
	{
		Transformation transformation;
		DrawableTile() { value = NO_TILE; }
		DrawableTile(const Tile& tile, int x, int y, int dest_x, int dest_y, bool wait = false)
			:Tile(tile), transformation(x, y, dest_x, dest_y)
		{
			if (wait)
				transformation.waiting_time = NEW_TILE_WAITING_TIME;
		}
	};


	Tile** m_Tiles;
	Tile** m_PreviousState;
	DrawableTile* m_Drawables;
	int m_DrawablesCount;

	int m_Size;
	int m_Score;
	Uint32 m_Time;
	bool m_AnimationFinished;
	bool m_IsOver;

	void SpawnRandom();

public:
	Board(int size = BOARD_DEFAULT_SIZE);
	~Board();

	void Reset(int size = BOARD_DEFAULT_SIZE);
	void Draw(Window& window);
	void Move(int dx, int dy);
	void ToPreviousState();

	void Update(Uint32 time);

	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;

private:
	void GetTileXY(int* x, int* y, int i, int j) const;
	void AddToDrawables(int i, int j, int dest_i, int dest_j, bool wait = false);
	void CheckIfOver();
};