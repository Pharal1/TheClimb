// Npc.cpp

#include "Npc.h"

Npc::Npc(
	int posXTile,
	int posYTile,
	float velocity,
	TextureManager& manager,
	DialogueManager& dialogueManager,
	TextureData textureData
	//std::string dialogue
) : Unit(
		posXTile, 
		posYTile, 
		velocity, 
		manager, 
		textureData
	), dialogueManager_(dialogueManager) {

}

void Npc::Render() {
	float posX = posX_;
	float posY = posY_;

	textureDest_ = { posX, posY - (float)texture_.width / 2, (float)texture_.width, (float)texture_.height };
	DrawTexturePro(texture_, textureSource_, textureDest_, textureOrigin_, 0.0f, WHITE);
}

void Npc::Update(float dt) {
	
}

void Npc::Interact(Player& player) {
	std::cout << "Pong!" << std::endl;

	dialogueManager_.startDialogue(dialogue_, player, *this);
}

