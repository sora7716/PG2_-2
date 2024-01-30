#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene_      = game;
	preScene_   = scene_;
	sceneManager = new SceneManager;
	for (int i = 0; i < 2; i++) {
		score_[i] = new Score;
	}
}

SceneSwitch::~SceneSwitch() {
	delete sceneManager;
	delete *score_;
}

void SceneSwitch::Scene(char* keys, char* preKeys) {
	preScene_ = scene_;
	if (scene_ == title) {
		sceneManager->TitleLoop(keys,preKeys,&scene_);
	}
	else if (scene_ == game) {
		sceneManager->MainLoop(keys,preKeys,scene_,score_[0]);
		if (sceneManager->GetPlayer()->GetIsBestPlace()) {
			score_[0]->Update();
		}
	}
	else if (scene_ == end) {
		sceneManager->EndLoop(keys,preKeys, &scene_);
		score_[1]->resultUpdate(score_[0]->GetScore());
	}
}

void SceneSwitch::Ini() {
	if (scene_ !=preScene_ ) {
		if (scene_ == title) {
			sceneManager = new SceneManager;
		}
		else if (scene_ == game) {
			sceneManager = new SceneManager;
			Camera::isRotation = false;
			score_[0]->SetScore(0);
		}
		else if (scene_ == end) {
			sceneManager = new SceneManager;
		}
	}
	preScene_ = scene_;
}

void SceneSwitch::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
}