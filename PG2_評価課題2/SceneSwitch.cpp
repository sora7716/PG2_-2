#include "SceneSwitch.h"

SceneSwitch::SceneSwitch() {
	scene      = title;
	preScene   = scene;
	mainScene  = new MainScene;
	titleScene = new TitleScene;
}

SceneSwitch::~SceneSwitch() {
	delete mainScene;
	delete titleScene;
}

void SceneSwitch::Scene(char* keys, char* preKeys) {
	preScene = scene;
	if (scene == title) {
		titleScene->TitleDraw();
	}
	else if (scene == game) {
		mainScene->MainLoop(keys,preKeys);
	}
}

void SceneSwitch::Movement(char* keys, char* preKeys) {
	if (scene == title && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		scene = game;
	}
	else if (scene == game && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		scene = title;
	}
}

void SceneSwitch::Ini() {
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

void SceneSwitch::Update(char* keys, char* preKeys) {
	Ini();
	Scene(keys, preKeys);
	Movement(keys, preKeys);
}