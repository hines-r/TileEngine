#pragma once
#include "Game.h"
#include <vector>

class Map
{
public:
	Map();
	~Map();

	void DrawMap();

private:
	SDL_Rect src, dest;

	SDL_Texture* wall;
	SDL_Texture* floor;

	static const int width = 40;
	static const int height = 50;

	int map[width][height];

	int randomFillPercent;
	int smoothingInterations;
	int tileSize;

	void SmoothMap();
	void RandomlyFillMap();
	void PrintMap();

	int GetSurroundingWallCount(int gridX, int gridY);
};