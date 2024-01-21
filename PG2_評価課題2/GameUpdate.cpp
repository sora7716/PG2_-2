#include "GameUpdate.h"

GameUpdate::GameUpdate() {

	Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	for (int i = 0; i < KYES_NUM; i++) {
		keys_[i]    = { 0 };
		preKeys_[i] = { 0 };
	}
	player_ = new Player;
	enemy_ = new EnemyDown;
}

GameUpdate::~GameUpdate(){
	delete player_;
	delete enemy_;
}

void GameUpdate::GameLoop() {
	while (ProcessMessage() == 0) {
		// フレームの開始
		BeginFrame();
		memcpy(preKeys_, keys_, 256);
		GetHitKeyStateAll(keys_);
		///
		/// ↓更新処理ここから
		///
		player_->Update(keys_, preKeys_);
		enemy_->Update(player_->GetVpVpMatrix(), player_->GetBullet());
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}
}

