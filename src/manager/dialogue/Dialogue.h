// Dialogue.h

#ifndef DIALOGUE_H_
#define DIALOGUE_H_

#include <string>
#include <vector>
#include <unordered_map>

struct DialogueChoice
{
	std::string text;
	std::string next;

	DialogueChoice(std::string text, std::string next);
};


struct DialogueNode
{
	std::string speaker;
	std::string text;
	std::string next;
	std::vector<DialogueChoice> choices;
	
	bool end = false;

	DialogueNode(
		std::string speaker, 
		std::string text,
		std::string next,
		std::vector<DialogueChoice> choices,
		bool end = false
	);
	DialogueNode() = default;
};

class Dialogue {
public:
	Dialogue() = default;
	Dialogue(std::unordered_map<std::string, DialogueNode> nodes, std::string startNode);
	//bool Load(std::string& path);
	
	std::unordered_map<std::string, DialogueNode> nodes_;
	std::string startNode_;
private:
};

#endif // !DIALOGUE_H_
