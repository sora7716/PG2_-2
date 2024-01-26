#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene_      = game;
	preScene_   = scene_;
	mainScene_  = new MainScene;
	titleScene_ = new TitleScene;
}

SceneSwitch::~SceneSwitch() {
	delete mainScene_;
	delete titleScene_;
}

void SceneSwitch::Scene(char* keys, char* preKeys) {
	preScene_ = scene_;
	if (scene_ == title) {
		titleScene_->TitleDraw();
	}
	else if (scene_ == game) {
		mainScene_->MainLoop(keys,preKeys);
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
	}
	preScene_ = scene_;
}

void SceneSwitch::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
	Movement(keys, preKeys);
}