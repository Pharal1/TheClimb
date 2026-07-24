//TextureManager.h

#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <unordered_map>
#include <string>
#include "raylib.h"

struct TextureData {
	std::string textureID;
	std::string texturePath;
	int frames = 1;
};

class TextureManager {
public:
	void load(const std::string& id, const std::string& path);
	Texture2D& get(const std::string id);
	void unloadAll();
private:
	std::unordered_map<std::string, Texture2D> textures_;
};

#endif