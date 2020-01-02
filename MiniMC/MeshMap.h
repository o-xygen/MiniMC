#pragma once
#include "noise.h"
#include "BlockConst.h"
#include "block.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>
using std::vector;
struct MapAttr {
    vector<int> heights{};
	int blockID = 0;
};

class MeshMap
{
public:
	MeshMap();
	void render();
	int size;
	MapAttr **map;
	std::map<int, vector<glm::vec3>> blockPosMap;

private:
	float stride;
	// classify all the block, for efficient drawing
};