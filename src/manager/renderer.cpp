// renderer.cpp

#include "renderer.h"

//Renderer::Renderer(TextureManager* textureManager) : textureManager_(textureManager) {}
 
void Renderer::Render(Map& map, UnitManager& entities, DialogueManager& dialogueManager, Player& player) const {
	RenderGrownd(map);
	RenderDynamic(entities, player);
	RenderUpper(map);
	//RenderGui(dialogueManager);
}