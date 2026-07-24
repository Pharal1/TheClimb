// Npc.h

#ifndef NPC_H_
#define NPC_H_

#include "Unit.h"
#include "../manager/dialogue/Dialogue.h"

class Npc : public Unit, public Interactable {
public:
	Npc(
		int posXTile, 
		int posYTile, 
		float velocity, 
		float size, 
		TextureManager& manager, 
		TextureData textureData,
		bool isInterractalbe
	);
	void Render() override;
	void Update(float dt) override;

	bool isInterractable() const { return isInterractable_; }

	Dialogue* getDialogue() { return &dialogue_; }
	void setDialogue(Dialogue dialogue) { dialogue_ = dialogue; }

	void Interact(Player& player) override;
private:
	bool isInterractable_;

	Dialogue dialogue_{};
	//bool isTalking_;


};

#endif // !NPC_H_
