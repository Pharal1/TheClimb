// Npc.cpp

#include "Npc.h"

Npc::Npc(
	int posXTile,
	int posYTile,
	float velocity,
	float size,
	TextureManager& manager,
	DialogueManager& dialogueManager,
	TextureData textureData
	//std::string dialogue
) : Unit(
		posXTile, 
		posYTile, 
		velocity, 
		size, 
		manager, 
		textureData
	), dialogueManager_(dialogueManager) {

}

void Npc::Render() {
	float posX = posX_;
	float posY = posY_;
	float size = size_;

	textureDest_ = { posX, posY - (float)texture_.width / 2, (float)texture_.width, (float)texture_.height };
	DrawTexturePro(texture_, textureSource_, textureDest_, textureOrigin_, 0.0f, WHITE);
}

void Npc::Update(float dt) {
	const float tileSize = TheClimb::kTileSize;
	if (!isMoving_)
	{
		int nextX = posXTile_;
		int nextY = posYTile_;
		if (dm_.x != 0)
			nextX += (int)dm_.x;
		else if (dm_.y != 0)
			nextY += (int)dm_.y;
		else return;
		if (getMap()->isFree(nextX, nextY))
		{
			targetTileX_ = nextX;
			targetTileY_ = nextY;

			dirX_ = (float)(nextX - posXTile_);
			dirY_ = (float)(nextY - posYTile_);

			isMoving_ = true;
		}
	}
	else {
		if (fabs(targetTileX_ * size_ + size_ / 2 - posX_) <= velocity_ * dt && fabs(targetTileY_ * size_ + size_ / 2 - posY_) <= velocity_ * dt) {
			setPosTileX(targetTileX_);
			setPosTileY(targetTileY_);
			isMoving_ = false;
			return;
		}
		else {
			posX_ += dirX_ * dt * velocity_;
			posY_ += dirY_ * dt * velocity_;
		}
	}
}

void Npc::Interact(Player& player) {
	std::cout << "Pong!" << std::endl;

	dialogueManager_.startDialogue(dialogue_, player, *this);
}

