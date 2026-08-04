// DialogueManager.h

#ifndef DIALOGUE_MANAGER_H_
#define DIALOGUE_MANAGER_H_

#include "Dialogue.h"
#include <string>
#include "raylib.h"
#include "../TextureManager.h"
#include "../../util.h"

#include <iostream>
#include <nlohmann/json.hpp>


class CameraManager;

class DialogueManager {
public:
	DialogueManager(int screenW, int screenH);
	void startDialogue(std::string dialogueName);
	void Input(Util::HandleInput handleInputData);
	bool isActive() const { return isActive_; }
	void Update(float dt);
	void Render() const;
	void Load(TextureManager& textureManager);

	std::string LoadDialogue(std::string& path, std::string start = "start");
	Dialogue* getDialogue(std::string id) const;
private:
	bool isActive_ = false;
	bool skip_ = false;
	bool choice_ = false;
	int screenW_;
	int screenH_;
	int ChoiceCurrentLine_{ 0 };
	float dy_ = 0.f;

	//id, Dialogue

	Dialogue* currentDialogue_{};
	Texture* texture_border_{};
	Texture* texture_box_{};
	
	DialogueNode currentLine_{};
	
	std::unordered_map<std::string, std::unique_ptr<Dialogue>> dialogues;
};

#endif