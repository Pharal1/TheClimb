// Dialogue.cpp

#include "Dialogue.h"
#include "../../util.h"



//Dialogue::Dialogue(std::string name, std::vector<std::string> text) : speaker_(name), text_(text) {}
Dialogue::Dialogue(std::unordered_map<std::string, DialogueNode> nodes, std::string startNode) : nodes_(nodes), startNode_(startNode){
	
}

DialogueChoice::DialogueChoice(std::string text, std::string next) : text(text), next(next) {}

DialogueNode::DialogueNode(
	std::string speaker,
	std::string text,
	std::string next,
	std::vector<DialogueChoice> choices,
	bool end
) :
	speaker(std::move(speaker)),
	text(std::move(text)),
	next(std::move(next)),
	choices(std::move(choices)),
	end(end) 
{}