// Dialogue.cpp

#include "Dialogue.h"

Dialogue::Dialogue(std::string name, std::vector<std::string> text) : speaker_(name), text_(text) {}
Dialogue::Dialogue() : speaker_(""), text_({ "" }) {}

