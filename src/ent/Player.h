// Player.h
#ifndef PLAYER_H_
#define PLAYER_H_


#include "Unit.h"
#include "Npc.h"

class UnitManager;

class Player : public Unit {
public:
	Player(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, TextureData textureData);

	void Render() override;
	void Update(float dt) override;
	void Input(Vector2 deltaMove, bool isRunning, bool isEPressed);

	void setRunningMultiplier(float value) { velocityRunningMultiplier_ = value; }
	void setUnitManager(UnitManager* manager) { units_ = manager; }
	
private:
	UnitManager* units_ = nullptr;
	
	float velocityRunningMultiplier_ = 1.5f;

	bool isRunning_ = false;
	bool isEPressed_ = false;
	//float velocity_diag;
	

	

};

#endif