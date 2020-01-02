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

private:
	int size;
	float stride;
	MapAttr **map;
	// classify all the block, for efficient drawing
	std::map<int, vector<glm::vec3>> blockPosMap;
};