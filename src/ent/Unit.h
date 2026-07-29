//Unit.h

#ifndef UNIT_H_
#define UNIT_H_

#include "raylib.h"
#include "math.h"
#include "../world/Map.h"
#include <iostream>
#include "../manager/TextureManager.h"

class Player;

class Interactable { //убрать в другой файл
public:
	virtual ~Interactable() = default;

	virtual void Interact(Player& player) = 0;
};

class Unit {
public:
	virtual ~Unit() { std::cout << "Unit destroyed\n"; };
	Unit(int posXTile, 
		int posYTile, 
		float velocity, 
		float size, 
		TextureManager& manager, 
		TextureData textureData
	);
	float getPosX() const { return posX_; }
	float getPosY() const { return posY_; }
	float getPosXTile() const { return posXTile_; }
	float getPosYTile() const { return posYTile_; }
	int getDirX() const { return dirX_; }
	int getDirY() const { return dirY_; }
	Vector2 GetPos() const { return Vector2{ posX_, posY_ }; }

	Texture2D getTexture() const { return texture_; }
	Map* getMap() const { return map_; }

	bool isMoving() const { return isMoving_; }
	
	void setPosTile(int x, int y);
	void setMap(Map* map) { map_ = map; }
	void setPosTileX(int x);
	void setPosTileY(int y);

	void setPos(Vector2 pos) { posX_ = pos.x; posY_ = pos.y; }

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	//virtual void Load(TextureManager& textureManager) = 0;

	virtual void interract();

private:
	Map* map_ = nullptr;
protected:
	
	Vector2 dm_{};
	bool isMoving_ = false;
	int posXTile_;
	int posYTile_;
	int targetTileX_;
	int targetTileY_;
	int dirX_ = 0;
	int dirY_ = 0;
	float posX_;
	float posY_;
	float velocity_;
	float targetX_;
	float targetY_;
	
	float size_;
	Texture2D texture_{};
	Rectangle textureSource_{};
	TextureData textureData_;
	Rectangle textureDest_{};
	Vector2 textureOrigin_{};
	int currentFrame_ = 0;

};

#endif // !UNIT_H_
