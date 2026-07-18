// DialogueManager

#include "DialogueManager.h"
#include "raylib.h"

#include <iostream>

void DialogueManager::startDialogue(Dialogue* dialogue) {
	if (dialogue == nullptr) return;
	currentDialogue_ = dialogue;
	currentLine_ = 0;
	isActive_ = true;
}


void DialogueManager::Update(float dt) {
	if (!isActive_) return;
	if (skip_) {
		currentLine_++;
		std::cout << "skipped!" << std::endl;

		if (currentLine_ >= currentDialogue_->getText().size()) {
			isActive_ = false;
		}
	}
}

void DialogueManager::Render() {
	if (!isActive_) return;
	DrawText(currentDialogue_->getText()[currentLine_].c_str(), 640, 360, 32, BLACK);
	
}
