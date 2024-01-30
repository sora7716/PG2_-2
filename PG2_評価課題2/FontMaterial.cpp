#include "FontMaterial.h"

FontMaterial::FontMaterial() {
	easing_ = new Easing;
}

FontMaterial::~FontMaterial() {
	delete easing_;
}

void FontMaterial::FontDraw(Font font, float width, float height) {
	Novice::DrawSprite((int)font.position.x, (int)font.position.y, font.image, width, height, 0.0f, font.color);
}

void FontMaterial::EasingFont(Font& font) {
	if (font.frame < font.endFrame) {
		font.frame++;
	}
	if (font.isEasing) {
		font.position.x = font.begin.x + (font.end.x - font.begin.x) * easing_->outBack(font.frame / font.endFrame);
		font.position.y = font.begin.y + (font.end.y - font.begin.y) * easing_->outBack(font.frame / font.endFrame);
	}
	if (font.isBack) {
		font.position.x = font.end.x + (font.begin.x - font.end.x) * easing_->InBack(font.frame / font.endFrame);
		font.position.y = font.end.y + (font.begin.y - font.end.y) * easing_->InBack(font.frame / font.endFrame);
	}
}

void FontMaterial::Ini(Font& font, bool isEasing, bool isBack) {
	font.isEasing = isEasing;
	font.isBack = isBack;
	font.frame = 0;
}