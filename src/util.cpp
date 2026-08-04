#include "util.h"

namespace Util {
	bool LoadJson(std::string& path, json& out) {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << Color::Red << "ERROR JSON Failed to open file: " << path << Color::Reset << "\n";
			return false;
		}

		try {
			file >> out;
		}
		catch (const json::parse_error& e) {
			std::cerr << Color::Red << "ERROR JSON " << e.what() << " in " << path << Color::Reset << "\n";
			return false;
		}
		return true;
	}

	bool Contains(json data, std::string name, std::string item, bool warning, bool display) {
		if (!data.contains(item)) {
			if (display) {
				if (!warning) std::cerr << Color::Red << "ERROR JSON" << name << " cannot read " << item << Color::Reset << "\n";
				else std::cerr << Color::Yellow << "Warning JSON" << name << " cannot read " << item << Color::Reset << "\n";
			}
			return false;
		}
		return true;
	}
	bool Contains(json data, std::string name, std::string item, std::string tree, bool warning, bool display) {
		if (!data.contains(item)) {
			std::cerr << Color::Red << "ERROR JSON" << name << " cannot read " << tree << item << Color::Reset << "\n";
			return false;
		}
		return true;
	}
	void PrintError(std::string text, std::string type) {
		std::cout << Color::Red << "ERROR " << type << ": " << text << Color::Reset << "\n";
	}
}