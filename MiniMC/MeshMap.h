#pragma once
#include "noise.h"
#include "BlockConst.h"
#include "block.h"
#include <vector>
using std::vector;
struct MapAttr {
    vector<int> heights{};
	int blockID = 0;
};

class MeshMap
{
public:
	MeshMap() {
		Perlin perlin;
		stride = 1.f;
		// default 100*100
		size = 100;
		map = new MapAttr* [size];
		for (int x = 0; x < size; x++) {
			map[x] = new MapAttr[size];
			for (int y = 0; y < size; y++) {
				map[x][y].heights.push_back(perlin.PerlinNoise(x, y)*5);
				map[x][y].blockID = GrassBlock;
			}
		}
	}

	void render() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				auto attr = map[i][j];
				Block* block = BlockMap.at(attr.blockID);
				block->setPos({ i, attr.heights[0], j });
				block->draw();
			}
		}
	}

private:
	int size;
	float stride;
	MapAttr **map;
};