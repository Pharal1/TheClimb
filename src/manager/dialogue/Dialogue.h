// Dialogue.h

#ifndef DIALOGUE_H_
#define DIALOGUE_H_

#include <string>
#include <vector>

class Dialogue {
public:
	Dialogue(std::string name, std::vector<std::string> text);
	Dialogue();

	std::string getSpeakerName() { return speaker_; }
	std::vector<std::string> getText() { return text_; }

private:
	std::string speaker_;
	std::vector<std::string> text_;
};

#endif // !DIALOGUE_H_
