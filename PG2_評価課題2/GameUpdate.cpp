#include "GameUpdate.h"

GameUpdate::GameUpdate() {

	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
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

void GameUpdate::GetHitKeyStateAll(){
	Novice::GetHitKeyStateAll(keys_);
}

void GameUpdate::Memcpy() {
	memcpy(preKeys_, keys_, 256);
}

void GameUpdate::GameLoop() {
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		///
		/// ↓更新処理ここから
		///
		player_->Update(keys_, preKeys_);
		enemy_->Update(keys_, preKeys_, player_->GetVpVpMatrix());
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
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}
}