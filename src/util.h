// util.h

#pragma once

#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace Util {

	bool LoadJson(std::string& path, json& out) {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "ERROR Failed to open json, file: " << path << "\n";
			return false;
		}

		try {
			file >> out;
		}
		catch (const json::parse_error& e) {
			std::cerr << "ERROR broken json, file: " << path << ", error: " << e.what() << "\n";
			return false;
		}
		return true;
	}

	//name in caps
	bool Contains(json data, std::string name, std::string item, bool display = 1) {
		if (!data.contains(item)) {
			if (display) std::cerr << "ERROR JSON" << name << " cannot read " << item << "\n";
			return false;
		}
		return true;
	}
	bool Contains(json data, std::string name, std::string item, std::string tree) {
		if (!data.contains(item)) {
			std::cerr << "ERROR JSON" << name << " cannot read " << tree << item << "\n";
			return false;
		}
		return true;
	}
}
