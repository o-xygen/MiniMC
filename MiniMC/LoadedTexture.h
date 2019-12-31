#pragma once
#include <map>
using std::map;
// this map stores loaded texture IDs 
// to avoid loading duplicated textures
map<int, bool> LoadedTextures;