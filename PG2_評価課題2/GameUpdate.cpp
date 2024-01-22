#include "GameUpdate.h"

GameUpdate::GameUpdate() {

	Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	for (int i = 0; i < KYES_NUM; i++) {
		keys_[i]    = { 0 };
		preKeys_[i] = { 0 };
	}
	sceneManager = new SceneManager;
}

GameUpdate::~GameUpdate(){
	delete sceneManager;
}

void GameUpdate::GameLoop() {
	while (ProcessMessage() == 0) {
		// フレームの開始
		BeginFrame();
		memcpy(preKeys_, keys_, 256);
		GetHitKeyStateAll(keys_);

		//ゲームのループ↓
		sceneManager->Update(keys_,preKeys_);
		//ゲームのループ↑
		

		// フレームの終了
		EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}
}
