// Npc.h

#ifndef NPC_H_
#define NPC_H_

#include "Unit.h"
#include "../manager/dialogue/Dialogue.h"
#include "../manager/dialogue/DialogueManager.h"
#include <string>

class Npc : public Unit, public Interactable {
public:
	Npc(
		int posXTile, 
		int posYTile, 
		float velocity, 
		TextureManager& manager,
		DialogueManager& dialogueManager,
		TextureData textureData
	);
	void Render() override;
	void Update(float dt) override;

	bool isInterractable() const { return isInterractable_; }

	//Dialogue* getDialogue() { return &dialogue_; }
	std::string& GetDialogue() { return dialogue_; }
	void SetDialogue(std::string dialogue) { dialogue_ = dialogue; }

	void Interact(Player& player) override;
private:
	bool isInterractable_ = false;
	bool hasDialogue = false;
	std::string dialogue_{};
	DialogueManager& dialogueManager_;
	//bool isTalking_;


};

#endif // !NPC_H_
