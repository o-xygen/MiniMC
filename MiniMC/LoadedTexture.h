#pragma once
#include <map>
using std::map;
// this map stores loaded texture IDs 
// to avoid loading duplicated textures
extern map<int, bool> LoadedTextures;