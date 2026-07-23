# CMakeList.txt: проект CMake для TheClimb; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TheClimb")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (TheClimb "TheClimb.cpp" "TheClimb.h"  "src/manager/TextureManager.h" "src/world/Tile.h" "src/world/Map.cpp" "src/world/Map.h" "src/ent/Player.cpp" "src/ent/Player.h" "src/core/Game.cpp"  "src/world/Tile.cpp" "src/manager/TextureManager.cpp" "src/ent/Unit.cpp" "src/ent/Npc.h" "src/ent/Npc.cpp"  "src/manager/dialogue/DialogueManager.h" "src/manager/dialogue/Dialogue.h" "src/manager/dialogue/Dialogue.cpp" "src/manager/dialogue/DialogueManager.cpp" "src/manager/renderer.h" "src/consts.h" "src/manager/renderer.cpp" "src/manager/UnitManager.h" "src/manager/UnitManager.cpp")

find_package(raylib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(TheClimb PRIVATE raylib)
target_link_libraries(TheClimb PRIVATE
    nlohmann_json::nlohmann_json
)

add_custom_command(TARGET TheClimb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:TheClimb>/resources
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TheClimb PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
