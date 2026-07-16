//TextureManager.cpp

#include "TextureManager.h"

void TextureManager::load(const std::string& id, const std::string& path) {
	Texture2D texture = LoadTexture(path.c_str());
	SetTextureFilter(texture, TEXTURE_FILTER_POINT);
	textures_[id] = texture;
}

Texture2D& TextureManager::get(std::string id) {
	return textures_.at(id);
}

void TextureManager::unloadAll() {
	for (auto& [id, texture] : textures_) {
		UnloadTexture(texture);
	}
	textures_.clear();
}