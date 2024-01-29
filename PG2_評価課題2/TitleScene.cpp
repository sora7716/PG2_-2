#include "TitleScene.h"

TitleScene::TitleScene() {
	title_.position  = {340,-200};
	title_.begin     = title_.position;
	title_.end       = {340,150};
	title_.frame     = 0;
	title_.endFrame  = 60;
	title_.isEasing  = true;
	title_.isBack    = false;
	title_.image = Novice::LoadTexture("white1x1.png");
	title_.color = WHITE;

	space_.position = { 1300,480 };
	space_.begin    = space_.position;
	space_.end      = { 480,480 };
	space_.frame    = 0;
	space_.endFrame = 60;
	space_.isEasing = true;
	space_.isBack   = false;
	space_.image    = Novice::LoadTexture("white1x1.png");
	space_.color    = WHITE;

	explanation_.position = { -1280,0 };
	explanation_.begin    = explanation_.position;
	explanation_.end      = { 0,0 };
	explanation_.frame    = 0;
	explanation_.endFrame = 60;
	explanation_.isEasing = true;
	explanation_.isBack   = false;
	explanation_.image    = Novice::LoadTexture("white1x1.png");
	explanation_.color    = RED;
	
	bg_     = new Bg;
	easing_ = new Easing;
}

TitleScene::~TitleScene() {
	delete bg_;
	delete easing_;
}

void TitleScene::Drawing() {
	CameraUpdate();
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
	bg_->Update(vpVpMatrix_);
	FontDraw(space_, 300, 100);
	FontDraw(title_, 600, 200);
	FontDraw(explanation_,1280, 720);
}

void TitleScene::FontDraw(Font font, float width, float height){
	Novice::DrawSprite((int)font.position.x, (int)font.position.y, font.image, width, height, 0.0f, font.color);
}

void TitleScene::EasingFont(Font &font) {
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

void TitleScene::Update(char* keys, char* preKeys) {
	IsEasing(keys, preKeys);
	EasingFont(title_);
	EasingFont(space_);
	if (space_.isBack&&space_.frame>=space_.endFrame) {
		EasingFont(explanation_);
	}
	Drawing();
	Novice::ScreenPrintf(0, 0, "%f", explanation_.frame);
	Novice::ScreenPrintf(0, 20, "%f", explanation_.position.x);
}

void TitleScene::IsEasing(char* keys, char* preKeys){
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]&&!title_.isEasing) {
		Ini(title_, true, false);
		Ini(space_, true, false);
	}
	else if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !title_.isBack) {
		Ini(title_, false, true);
		Ini(space_, false, true);
	}
}

void TitleScene::Ini(Font& font,bool isEasing, bool isBack) {
	font.isEasing = isEasing;
	font.isBack = isBack;
	font.frame = 0;
}
