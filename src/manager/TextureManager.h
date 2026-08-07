//TextureManager.h

#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <raylib.h>
#include <unordered_map>
#include <string>

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
	void LoadFont(std::string& path);
	Font* GetFont() { return &font_; }
private:
	std::unordered_map<std::string, Texture2D> textures_;
	Font font_{};
};

#endif