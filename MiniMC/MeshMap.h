#pragma once
#include "noise.h"
#include "BlockConst.h"
struct MapAttr {
	int height;
	int blockID;
};

class MeshMap
{
public:
	MeshMap() {
		Perlin perlin;
		stride = 1.f;
		// default 100*100
		const auto size = 100;
		map = new MapAttr* [size];
		for (int x = 0; x < size; x++) {
			map[x] = new MapAttr[size];
			for (int y = 0; y < size; y++) {
				map[x][y].height = perlin.PerlinNoise(x, y);
				map[x][y].blockID = GrassBlock;
			}
		}
	}
	~MeshMap();

private:
	float stride;
	MapAttr **map;
};

MeshMap::~MeshMap()
{
}