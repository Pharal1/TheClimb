// util.h

#pragma once

#include <raylib.h>

#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace Util {

    
#ifdef _DEBUG
    inline bool debug = true;
#else
    inline bool debug = false;
#endif

	bool LoadJson(std::string& path, json& out);

	//name in caps
	bool Contains(json data, std::string name, std::string item, bool warning = 0, bool display = 1);
	//name in caps
	bool Contains(json data, std::string name, std::string item, std::string tree, bool warning = 0, bool display = 1);

    //Prints error depends on type 
    //(2nd arg = this)
    void PrintError(std::string text, std::string type);

    namespace Color {
        inline const char* Reset = "\033[0m";
        inline const char* Red = "\033[31m";
        inline const char* Green = "\033[32m";
        inline const char* Yellow = "\033[33m";
        inline const char* Blue = "\033[34m";
        inline const char* Magenta = "\033[35m";
        inline const char* Cyan = "\033[36m";

        // Стили
        inline const char* Bold = "\033[1m";
    }

    struct HandleInput {
        bool isRunning = false;
        bool isEPressed = false;
        bool skip = false;
        Vector2 deltaPlayer = Vector2{ 0, 0 };
        Vector2 deltaGui = Vector2{ 0, 0 };
    };
}

