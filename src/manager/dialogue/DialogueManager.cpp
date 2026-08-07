// DialogueManager

#include "DialogueManager.h"
#include "../CameraManager.h"
#include "../../ent/Npc.h"

using json = nlohmann::json;

DialogueManager::DialogueManager(int screenW, int screenH, CameraManager& cameraManager) : screenW_(screenW), screenH_(screenH), cameraManager_(cameraManager) {

}

void DialogueManager::Input(Util::HandleInput handleInputData) {
	skip_ = handleInputData.skip;
	dy_ = handleInputData.deltaGui.y;
}

void DialogueManager::startDialogue(std::string dialogueName, Player& player, Npc& npc) {
	if (isActive()) return;
	
	auto* dialogue = getDialogue(dialogueName);

	if (!dialogue) return;
	if (dialogue->nodes_.size() == 0) return;
	currentDialogue_ = dialogue;
	auto start_str = dialogue->nodes_.find(dialogue->startNode_);
	if (start_str == dialogue->nodes_.end()) {
		Util::PrintError("cannot read start node", "DIALOGUE MANAGER");
	}
	currentLine_ = dialogue->nodes_.at(dialogue->startNode_);
	isActive_ = true;
	cameraManager_.SetTarget(&npc);
	skip_ = false;
}


void DialogueManager::Update(float dt) {
	if (!isActive_) return;



	if (!choice_ && skip_) {

		DialogueNode next = currentDialogue_->nodes_.at(currentLine_.next);
		if (next.end == true) {
			isActive_ = false;
			cameraManager_.SetTarget();
			ChoiceCurrentLine_ = 0;
			return;
		}
		if (next.choices.size() != 0) {
			choice_ = true;
			
		}
		currentLine_ = next;
	} else if (skip_ && choice_) {
		choice_ = false;
		DialogueNode next = currentDialogue_->nodes_.at(currentLine_.choices[ChoiceCurrentLine_].next);
		if (next.end == true) {
			isActive_ = false;
			cameraManager_.SetTarget();
			ChoiceCurrentLine_ = 0;
			return;
		}
		currentLine_ = next;
	} else if (choice_) {
		if (dy_ == 0) return;
		int next = ChoiceCurrentLine_ + static_cast<int>(dy_);
		if (next < 0) ChoiceCurrentLine_ = currentLine_.choices.size() - 1;
		else if (next > currentLine_.choices.size() - 1) ChoiceCurrentLine_ = 0;
		else ChoiceCurrentLine_ = next;
		return;
	}
	
}

static void DrawNineSlice(Texture2D& texture, Rectangle dest,int sourceBorder, int border)
{
	int w = texture.width;
	int h = texture.height;

	Rectangle topLeft = { 0, 0, sourceBorder, sourceBorder };
	Rectangle topRight = { w - sourceBorder, 0, sourceBorder, sourceBorder };
	Rectangle bottomLeft = { 0, h - sourceBorder, sourceBorder, sourceBorder };
	Rectangle bottomRight = { w - sourceBorder, h - sourceBorder, sourceBorder, sourceBorder };

	Rectangle top = { sourceBorder, 0, w - sourceBorder * 2, sourceBorder };
	Rectangle bottom = { sourceBorder, h - sourceBorder, w - sourceBorder * 2, sourceBorder };
	Rectangle left = { 0, sourceBorder, sourceBorder, h - sourceBorder * 2 };
	Rectangle right = { w - sourceBorder, sourceBorder, sourceBorder, h - sourceBorder * 2 };

	Rectangle center = {
		sourceBorder,
		sourceBorder,
		w - sourceBorder * 2,
		h - sourceBorder * 2
	};

	DrawTexturePro(
		texture,
		topLeft,
		{
			dest.x,
			dest.y,
			(float)border,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		topRight,
		{
			dest.x + dest.width - border,
			dest.y,
			(float)border,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		bottomLeft,
		{
			dest.x,
			dest.y + dest.height - border,
			(float)border,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		bottomRight,
		{
			dest.x + dest.width - border,
			dest.y + dest.height - border,
			(float)border,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);


	DrawTexturePro(
		texture,
		left,
		{
			dest.x,
			dest.y + border,
			(float)border,
			dest.height - border * 2
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		right,
		{
			dest.x + dest.width - border,
			dest.y + border,
			(float)border,
			dest.height - border * 2
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		top,
		{
			dest.x + border,
			dest.y,
			dest.width - border * 2,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);
	DrawTexturePro(
		texture,
		bottom,
		{
			dest.x + border,
			dest.y + dest.height - border,
			dest.width - border * 2,
			(float)border
		},
		{ 0,0 },
		0,
		WHITE
	);

	DrawTexturePro(
		texture,
		center,
		{
			dest.x + border,
			dest.y + border,
			dest.width - border * 2,
			dest.height - border * 2
		},
		{0,0},
		0,
		WHITE
	);
}

void DialogueManager::Render() const {
	if (!isActive_) return;
	const int screenBorderSize = 9;

	Rectangle dialogueBox =
	{
		GetScreenWidth() / 20,
		GetScreenHeight() * 2 / 3,
		GetScreenWidth() - GetScreenWidth() / 20 * 2,
		GetScreenHeight() / 3 - GetScreenHeight() / 100
	};

	DrawNineSlice(*texture_box_, dialogueBox, 3, screenBorderSize);

	DrawTextEx(font_, currentLine_.text.c_str(), Vector2{static_cast<float>(GetScreenWidth() / 18), static_cast<float>(GetScreenHeight() * 8 / 12)}, 32, 1, WHITE);
	if (choice_) {
		for (int i = 0; i < currentLine_.choices.size(); i++) {
			DrawTextEx(font_, currentLine_.choices[i].text.c_str(), Vector2{ static_cast<float>(GetScreenWidth() / 18), static_cast<float>(GetScreenHeight() * 8 / 12 + (i + 1) * 32) }, 24, 1, WHITE);
		}
		DrawRectangle(GetScreenWidth() / 20, GetScreenHeight() * 2 / 3 + (ChoiceCurrentLine_ + 1) * 32, GetScreenWidth() - GetScreenWidth() / 20 * 2, 32, Color{0, 0, 0, 128});
	}
}

void DialogueManager::Load(TextureManager& textureManager) {
	textureManager.load("dialogue_border", "resources/gui/dialogue_frame.png");
	textureManager.load("dialogue_box", "resources/gui/dialogue_border_9_slice.png");
	texture_border_ = &textureManager.get("dialogue_border");
	texture_box_ = &textureManager.get("dialogue_box");

	font_ = *textureManager.GetFont();
}

std::string DialogueManager::LoadDialogue(std::string& path, std::string start) {
	json data;

	if (!Util::LoadJson(path, data)) return "";
	if (!Util::Contains(data, "DIALOGUE MANAGER", "id")) return "";
	if (!Util::Contains(data, "DIALOGUE MANAGER", "nodes")) return "";
																												
	std::string id = data.value<std::string>("id", "");

	std::unordered_map<std::string, DialogueNode> nodes{};
	//DialogueNode node;

	for (auto& [nodeKey, value] : data["nodes"].items()) {
		std::vector<DialogueChoice> choice{};
		if (value.contains("choices")) {
			for (auto& item : value["choices"]) {
				choice.push_back({ item.value("text", ""), item.value("next", "end") });
			}
		}
		nodes.insert({ nodeKey, DialogueNode{ 
			value.value("speaker", ""), 
			value.value("text", ""), 
			value.value("next", "end"), 
			std::move(choice),
			value.value("end", false)
		} });
		
	}
	dialogues.emplace(id, std::make_unique<Dialogue>(std::move(nodes), start));
	return id;
}

Dialogue* DialogueManager::getDialogue(std::string id) const {
	auto item = dialogues.find(id);

	if (item == dialogues.end()) return nullptr;
	return item->second.get();
}