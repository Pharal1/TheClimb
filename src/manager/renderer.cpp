// renderer.cpp

#include "renderer.h"

//Renderer::Renderer(TextureManager* textureManager) : textureManager_(textureManager) {}
 
void Renderer::Render(Map& map, UnitManager& entities, DialogueManager& dialogueManager) const {
	RenderGrownd(map);
	RenderDynamic(entities);
	RenderUpper(map);
	//RenderGui(dialogueManager);
}