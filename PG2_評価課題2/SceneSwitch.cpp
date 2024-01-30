#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene_      = title;
	preScene_   = scene_;
	BGM_[0] = Novice::LoadAudio("./resource/sound/game.mp3");
	BGM_[1] = Novice::LoadAudio("./resource/sound/sentou.mp3");
	BGM_[2] = Novice::LoadAudio("./resource/sound/end.mp3");
	for (int i = 0; i < 3; i++) {
		soundHandle_[i] = 0;
	}
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
		if (Novice::IsPlayingAudio(soundHandle_[0]) <= 0) {
			soundHandle_[0]= Novice::PlayAudio(BGM_[0], true, 0.5f);
		}
		sceneManager->TitleLoop(keys,preKeys,&scene_);
	}
	else if (scene_ == game) {
		if (Novice::IsPlayingAudio(soundHandle_[1]) <= 0) {
			soundHandle_[1] = Novice::PlayAudio(BGM_[1], true, 0.5f);
		}
		sceneManager->MainLoop(keys,preKeys,scene_,score_[0]);
		if (sceneManager->GetPlayer()->GetIsBestPlace()) {
			score_[0]->Update();
		}
	}
	else if (scene_ == end) {
		if (Novice::IsPlayingAudio(soundHandle_[2]) <= 0) {
			soundHandle_[2] = Novice::PlayAudio(BGM_[2], true, 0.7f);
		}
		sceneManager->EndLoop(keys,preKeys, &scene_);
		score_[1]->resultUpdate(score_[0]->GetScore());
	}
}

void SceneSwitch::Ini() {
	if (scene_ !=preScene_ ) {
		if (scene_ == title) {
			Novice::StopAudio(soundHandle_[2]);
			sceneManager = new SceneManager;
		}
		else if (scene_ == game) {
			Novice::StopAudio(soundHandle_[0]);
			sceneManager = new SceneManager;
			Camera::isRotation = false;
			score_[0]->SetScore(0);
		}
		else if (scene_ == end) {
			Novice::StopAudio(soundHandle_[1]);
			sceneManager = new SceneManager;
		}
	}
	preScene_ = scene_;
}

void SceneSwitch::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
}