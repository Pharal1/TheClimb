// renderer.cpp

#include "renderer.h"

//Renderer::Renderer(TextureManager* textureManager) : textureManager_(textureManager) {}
 
void Renderer::Render(Map& map, UnitManager& entities, DialogueManager& dialogueManager, Player& player, const CameraManager& cameraManager) const {
	//RenderGrownd(map, camera);
	RenderDynamic(entities, player);
	
	//RenderGui(dialogueManager);
}

void Renderer::PreRender(Map& map) const {
	RenderGrownd(map);
	RenderUpper(map);
}
void Renderer::PostRender(DialogueManager& dialogueManager) const {
	RenderGui(dialogueManager);
}