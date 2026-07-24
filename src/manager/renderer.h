// renderer.h

#pragma once

#include "../world/Map.h"
#include "../ent/Unit.h"
#include "dialogue/dialogueManager.h"
#include "UnitManager.h"

class Renderer {
public:
	//Renderer();
	void setTextureManager(TextureManager* textureManager) { textureManager_ = textureManager; }
	void Render(Map& map, UnitManager& entities, DialogueManager& dialogueManager, Player& player) const;

	void RenderGrownd(Map& map) const { map.RenderGround(*textureManager_); }
	void RenderDynamic(UnitManager& entities, Player& player) const { entities.Render(player); }
	void RenderUpper(Map& map) const {}
	//void RenderGui(DialogueManager& dialogueManager) const { dialogueManager.Render(); }
private:
	TextureManager* textureManager_ = nullptr;
};