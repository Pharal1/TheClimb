// Player.h
#ifndef PLAYER_H_
#define PLAYER_H_


#include "Unit.h"
#include "Npc.h"

class Player : public Unit {
public:
	Player(int posXTile, int posYTile, float velocity, float size, TextureManager& manager, const char* textureID, const char* texturePath);

	void Render() override;
	void Update(float dt) override;
	void Input(Vector2 deltaMove, bool isRunning, bool isEPressed);
	//void Load(TextureManager& textureManager) override;

	void setRunningMultiplier(float value) { velocityRunningMultiplier_ = value; }
	void setNpcList(std::vector<Npc*> list) { npc_ = list; }

	//void setPosTile(int x, int y); // NO ISFREE() CHECK
	
private:

	std::vector<Npc*> npc_ = { nullptr };
	
	float velocityRunningMultiplier_ = 1.5f;

	bool isRunning_ = false;
	bool isEPressed_ = false;
	//float velocity_diag;
	

	

};

#endif