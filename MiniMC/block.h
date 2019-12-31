#pragma once
#include <map>
#include <string>
#include "json.hpp"
#include "LoadedTexture.h"
#include "utils.h"
#include "error.h"
using std::map;
using std::string;
class Blcok;
map<int, Block*> BlockMap;
using json = nlohmann::json;
constexpr auto textureDirPrefix = "resource/textures/";

class Block
{
public:
	Block(json conf);
	~Block();

private:
	int blockID;
	void loadTextures(json textureConf) {
		for (auto iter = textureConf.begin(); iter != textureConf.end(); ++iter) {
			int ID = TextureFromFile(textureDirPrefix + iter.value());
			if (ID == -1) {
				ErrorLog::logError("blockID " + std::to_string(blockID) + "loading texture failed");
				continue;
			}
			// cache
			LoadedTextures.insert({ ID, true });
			// construct name ID map
			textureMap.insert({ iter.key(), ID });
		}
	}


	map<string, int> textureMap;
};

Block::Block(json conf)
{
	blockID = conf.at("blockID");
	loadTextures(conf.at("textures"));
	// generate planes for drawing
}

Block::~Block()
{
}