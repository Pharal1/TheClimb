// Npc.h

#ifndef NPC_H_
#define NPC_H_

#include "Unit.h"
class Npc : public Unit {
public:
	Npc(
		int posXTile, 
		int posYTile, 
		float velocity, 
		float size, 
		TextureManager& manager, 
		const char* textureID, 
		const char* texturePath,
		bool isInterractalbe
	);
	void Render() override;
	void Update(float dt) override;

	bool isInterractable() const { return isInterractable_; }

	void interract() override;
private:
	bool isInterractable_;
	//bool isTalking_;


};

#endif // !NPC_H_
