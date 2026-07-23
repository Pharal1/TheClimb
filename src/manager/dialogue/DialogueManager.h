// DialogueManager.h

#ifndef DIALOGUE_MANAGER_H_
#define DIALOGUE_MANAGER_H_

#include "Dialogue.h"
#include <string>
#include "raylib.h"
#include "../TextureManager.h"

#include <iostream>

class DialogueManager {
public:
	DialogueManager(int screenW, int screenH);
	void startDialogue(Dialogue* dialogue);
	void skip(bool skip) { skip_ = skip; }
	bool isActive() const { return isActive_; }
	void Update(float dt);
	void Render() const;
	void Load(TextureManager& textureManager);
private:
	bool isActive_ = false;
	bool skip_ = false;
	int screenW_;
	int screenH_;
	int currentLine_ = 0;

	Dialogue* currentDialogue_{};
	Texture* texture_border_{};
	Texture* texture_box_{};
};

#endif