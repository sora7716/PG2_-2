#include "MainScene.h"

MainScene::MainScene() {
	player_ = new Player;
	enemy_ = new EnemyDown;
}

MainScene::~MainScene() {
	delete player_;
	delete enemy_;
}

void MainScene::MainUpdating(char *keys,char *preKeys) {
	player_->Update(keys, preKeys, enemy_);
	player_->GetParticle()->DrawParticle(player_->GetVpVpMatrix());
	enemy_->Update(player_->GetVpVpMatrix(), player_->GetBullet());
}

void MainScene::MainDrawing() {
	player_->PlayerDraw(player_->GetPlayerTexture());
	player_->GetBullet()->BulletDrawSprite(player_->GetVpVpMatrix());
	enemy_->EnemyDraw();
}

void MainScene::MainLoop(char* keys, char* preKeys) {
	MainUpdating(keys,preKeys);//更新処理
	MainDrawing(); //描画処理
}
