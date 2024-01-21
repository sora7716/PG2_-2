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

void GameUpdate::MainUpdating() {
	player_->Update(keys_, preKeys_,enemy_);
	enemy_->Update(player_->GetVpVpMatrix(), player_->GetBullet());
}

void GameUpdate::MainDrawing() {
	player_->PlayerDraw(player_->GetPlayerTexture());
	player_->GetBullet()->BulletDrawSprite(player_->GetVpVpMatrix());
	enemy_->EnemyDraw();
}

void GameUpdate::MainLoop() {
	MainUpdating();//更新処理
	MainDrawing(); //描画処理
}

void GameUpdate::GameLoop() {
	while (ProcessMessage() == 0) {
		// フレームの開始
		BeginFrame();
		memcpy(preKeys_, keys_, 256);
		GetHitKeyStateAll(keys_);

		//ゲームのループ↓
		MainLoop();
		//ゲームのループ↑
		

		// フレームの終了
		EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}
}

