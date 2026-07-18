// DialogueManager.h

#ifndef DIALOGUE_MANAGER_H_
#define DIALOGUE_MANAGER_H_

#include "Dialogue.h"
#include "string"

class DialogueManager {
public:
	//DialogueManager();

	void startDialogue(Dialogue* dialogue);
	void skip(bool skip) { skip_ = skip; }
	bool isActive() { return isActive_; }
	void Update(float dt);
	void Render();
private:
	bool isActive_ = false;
	bool skip_ = false;

	int currentLine_ = 0;

	Dialogue* currentDialogue_{};
};

#endif