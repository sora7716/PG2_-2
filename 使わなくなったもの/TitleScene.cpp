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
	
	startTime_ = 300;

	bg_     = new Bg;
	camera_ = new Camera;
}

TitleScene::~TitleScene() {
	delete bg_;
	delete camera_;
}

void TitleScene::Drawing() {
	camera_->CameraUpdate();
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
	bg_->Update(camera_->GetVpVpMatrix(), WHITE,3);
	FontDraw(space_, 300, 100);
	FontDraw(title_, 600, 200);
	FontDraw(explanation_,1280, 720);
}

void TitleScene::Update(char* keys, char* preKeys,SceneType*scene) {
	IsEasing(keys, preKeys);
	EasingFont(title_);
	EasingFont(space_);
	if (space_.isBack&&space_.frame>=space_.endFrame) {
		EasingFont(explanation_);
	}
	StarTime(scene);
	Drawing();
}

void TitleScene::IsEasing(char* keys, char* preKeys){
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (!title_.isBack) {
			Ini(title_, false, true);
			Ini(space_, false, true);
		}
	}
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
		space_.color = 0xFFFFFF55;
	}
	else {
		space_.color = WHITE;
	}
}

void TitleScene::StarTime(SceneType* scene) {
	if (startTime_ > 0) {
		startTime_--;
	}
	else {
		*scene = game;
	}
}

