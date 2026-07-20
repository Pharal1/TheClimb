// DialogueManager

#include "DialogueManager.h"

void DialogueManager::startDialogue(Dialogue* dialogue) {
	if (dialogue == nullptr) return;
	currentDialogue_ = dialogue;
	currentLine_ = 0;
	isActive_ = true;
}


void DialogueManager::Update(float dt) {
	if (!isActive_) return;
	if (skip_) {
		currentLine_++;
		std::cout << "skipped!" << std::endl;

		if (currentLine_ >= currentDialogue_->getText().size()) {
			isActive_ = false;
		}
	}
}

static void DrawNineSlice(Texture2D& texture, Rectangle dest,int sourceBorder, int border)
{
	int w = texture.width;
	int h = texture.height;

	// углы
	Rectangle topLeft = { 0, 0, sourceBorder, sourceBorder };
	Rectangle topRight = { w - sourceBorder, 0, sourceBorder, sourceBorder };
	Rectangle bottomLeft = { 0, h - sourceBorder, sourceBorder, sourceBorder };
	Rectangle bottomRight = { w - sourceBorder, h - sourceBorder, sourceBorder, sourceBorder };

	// стороны
	Rectangle top = { sourceBorder, 0, w - sourceBorder * 2, sourceBorder };
	Rectangle bottom = { sourceBorder, h - sourceBorder, w - sourceBorder * 2, sourceBorder };
	Rectangle left = { 0, sourceBorder, sourceBorder, h - sourceBorder * 2 };
	Rectangle right = { w - sourceBorder, sourceBorder, sourceBorder, h - sourceBorder * 2 };

	// центр
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

void DialogueManager::Render(int screenW, int screenH) const {
	if (!isActive_) return;
	const int screenBorderSize = 9;
	Rectangle dialogueBox =
	{
		screenW / 20,
		screenH*2/3,
		screenW - screenW / 20 * 2,
		screenH/3 - screenH / 100
	};

	DrawNineSlice(*texture_box_, dialogueBox, 3, screenBorderSize);

}

void DialogueManager::Load(TextureManager& textureManager) {
	textureManager.load("dialogue_border", "resources/gui/dialogue_frame.png");
	textureManager.load("dialogue_box", "resources/gui/dialogue_border_9_slice.png");
	texture_border_ = &textureManager.get("dialogue_border");
	texture_box_ = &textureManager.get("dialogue_box");
	
}