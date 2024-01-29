#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene_ = game;
	preScene_   = scene_;
	mainScene_  = new MainScene;
	titleScene_ = new TitleScene;
	endScene_ = new EndScene;
}

SceneSwitch::~SceneSwitch() {
	delete titleScene_;
	delete mainScene_;
	delete endScene_;
}

void SceneSwitch::Scene(char* keys, char* preKeys) {
	preScene_ = scene_;
	if (scene_ == title) {
		titleScene_->TitleDraw();
	}
	else if (scene_ == game) {
		mainScene_->MainLoop(keys,preKeys,scene_);
	}
	else if (scene_ == end) {
		endScene_->Draw();
	}
}

void SceneSwitch::Movement(char* keys, char* preKeys) {
	if (scene_ == title && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		scene_ = game;
	}
	else if (scene_ == game && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		Camera::isRotation = false;
		scene_ = title;
	}
}

void SceneSwitch::Ini() {
	if (scene_ !=preScene_ ) {
		if (scene_ == title) {
			titleScene_ = new TitleScene;
		}
		else if (scene_ == game) {
			mainScene_ = new MainScene;
		}
		else if (scene_ == end) {
			endScene_ = new EndScene;
		}
	}
	preScene_ = scene_;
}

void SceneSwitch::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
	Movement(keys, preKeys);
}