#include "SceneManager.h"

SceneManager::SceneManager() {
	scene      = title;
	preScene   = scene;
	mainScene  = new MainScene;
	titleScene = new TitleScene;
}

SceneManager::~SceneManager() {
	delete mainScene;
	delete titleScene;
}

void SceneManager::Scene(char* keys, char* preKeys) {
	preScene = scene;
	if (scene == title) {
		titleScene->TitleDraw();
	}
	else if (scene == game) {
		mainScene->MainLoop(keys,preKeys);
	}
}

void SceneManager::Movement(char* keys, char* preKeys) {
	if (scene == title && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		scene = game;
	}
	else if (scene == game && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		scene = title;
	}
}

void SceneManager::Ini() {
	if (scene !=preScene ) {
		if (scene == title) {
			titleScene = new TitleScene;
		}
		else if (scene == game) {
			mainScene = new MainScene;
		}
	}
	preScene = scene;
}

void SceneManager::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
	Movement(keys, preKeys);
}