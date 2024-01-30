﻿#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene_ = title;
	preScene_   = scene_;
	mainScene_  = new MainScene;
	titleScene_ = new TitleScene;
	endScene_ = new EndScene;
	for (int i = 0; i < 2; i++) {
		score_[i] = new Score;
	}
}

SceneSwitch::~SceneSwitch() {
	delete titleScene_;
	delete mainScene_;
	delete endScene_;
	delete *score_;
}

void SceneSwitch::Scene(char* keys, char* preKeys) {
	preScene_ = scene_;
	if (scene_ == title) {
		titleScene_->Update(keys,preKeys,&scene_);
	}
	else if (scene_ == game) {
		mainScene_->MainLoop(keys,preKeys,scene_,score_[0]);
		if (mainScene_->GetPlayer()->GetIsBestPlace()) {
			score_[0]->Update();
		}
	}
	else if (scene_ == end) {
		endScene_->Update(keys,preKeys, &scene_);
		score_[1]->resultUpdate(score_[0]->GetScore());
	}
}

void SceneSwitch::Ini() {
	if (scene_ !=preScene_ ) {
		if (scene_ == title) {
			titleScene_ = new TitleScene;
		}
		else if (scene_ == game) {
			mainScene_ = new MainScene;
			Camera::isRotation = false;
			score_[0]->SetScore(0);
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
}