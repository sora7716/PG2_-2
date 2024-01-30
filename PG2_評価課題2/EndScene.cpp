#include "EndScene.h"

EndScene::EndScene() {
	reTry_.position = { 1300,480 };
	reTry_.begin = reTry_.position;
	reTry_.end = { 500,480 };
	reTry_.frame = 0;
	reTry_.endFrame = 60;
	reTry_.isEasing = true;
	reTry_.isBack = false;
	reTry_.image = Novice::LoadTexture("white1x1.png");
	reTry_.color = WHITE;

	bg_ = new Bg;
	camera_ = new Camera;
}

EndScene::~EndScene() {
	delete bg_;
	delete camera_;
}

void EndScene::Draw() {
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH , (int)SCREEN_HEIGHT , 0.0f, 0x303030FF, kFillModeSolid);
}

void EndScene::Drawing() {
	Draw();
	camera_->CameraUpdate();
	bg_->Update(camera_->GetVpVpMatrix(), RED,3);
	bg_->DrawBg();
	FontDraw(reTry_, 300, 100);
}

void EndScene::Update(char* keys, char* preKeys,Scene*scene) {
	IsEasing(keys, preKeys);
	EasingFont(reTry_);
	if (reTry_.isBack && reTry_.frame >= reTry_.endFrame) {
		*scene = title;
	}
	Drawing();
}

void EndScene::IsEasing(char* keys, char* preKeys) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (!reTry_.isBack) {
			Ini(reTry_, false, true);
		}
	}
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
		reTry_.color = 0xFFFFFF55;
	}
	else {
		reTry_.color = WHITE;
	}
}