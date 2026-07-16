// Player.h
#ifndef PLAYER_H_
#define PLAYER_H_


#include "Unit.h"

class Player : public Unit {
public:
	Player(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath);

	void Render() override;
	void Update(float dt, Vector2 dm, bool isRunning) override;
	//void Load(TextureManager& textureManager) override;

	void setRunningMultiplier(float value) { velocityRunningMultiplier = value; }
	//void setPosTile(int x, int y); // NO ISFREE() CHECK
	void setPosTileX(int x);
	void setPosTileY(int y);
private:

	
	
	float velocityRunningMultiplier = 1.5f;
	//float velocity_diag;
	

	

};

#endif