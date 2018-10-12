#include "Map.h"
#include "TextureManager.h"
#include <random>
#include <iostream>

Map::Map()
{
	randomFillPercent = 46;
	smoothingInterations = 5;
	tileSize = 16;

	wall = TextureManager::LoadTexture("res/wall.png");
	floor = TextureManager::LoadTexture("res/floor.png");

	RandomlyFillMap();

	for (int i = 0; i < smoothingInterations; i++)
	{
		SmoothMap();
	}

	PrintMap();

	src.x = src.y = 0;
	src.w = dest.w = tileSize;
	src.h = dest.h = tileSize;

	dest.x = dest.y = 0;
}

Map::~Map()
{

}

void Map::RandomlyFillMap()
{
	std::random_device rd; // Gets random number from a device
	std::mt19937 eng(rd()); // Seed
	std::uniform_int_distribution<> distr(0, 100); // range from 0 to 100%

	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
		{
			// Creates surrounding walls
			if (row == 0 || row == width - 1 || col == 0 || col == height - 1)
			{
				map[row][col] = 1;
			}
			else
			{
				map[row][col] = (distr(eng) < randomFillPercent) ? 1 : 0;
			}
		}
	}
}

void Map::SmoothMap()
{
	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
		{
			int neighborWallTiles = GetSurroundingWallCount(row, col);

			if (neighborWallTiles > 4)
			{
				map[row][col] = 1;
			}
			else if (neighborWallTiles < 4)
			{
				map[row][col] = 0;
			}
		}
	}
}

int Map::GetSurroundingWallCount(int gridX, int gridY)
{
	int wallCount = 0;

	for (int neighborX = gridX - 1; neighborX <= gridX + 1; neighborX++)
	{
		for (int neighborY = gridY - 1; neighborY <= gridY + 1; neighborY++)
		{
			if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height)
			{
				if (neighborX != gridX || neighborY != gridY)
				{
					wallCount += map[neighborX][neighborY];
				}
			}
			else
			{
				wallCount++;
			}
		}
	}

	return wallCount;
}

void Map::DrawMap()
{
	int tileType = 0;

	for (int row = 0; row < width; row++)
	{
		for (int column = 0; column < height; column++)
		{
			tileType = map[row][column];

			dest.x = column * tileSize;
			dest.y = row * tileSize;

			switch (tileType)
			{
				case 0:
					TextureManager::Draw(floor, src, dest);
					break;
				case 1:
					TextureManager::Draw(wall, src, dest);
					break;
			}
		}
	}
}

void Map::PrintMap()
{
	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < height; col++)
		{
			std::cout << map[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
