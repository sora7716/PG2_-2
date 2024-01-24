#include "MainScene.h"

MainScene::MainScene() {
	player_ = new Player;
	enemyDown_ = new EnemyDown;
	enemyLeft_ = new EnemyLeft;
}

MainScene::~MainScene() {
	delete player_;
	delete enemyDown_;
	delete enemyLeft_;
}

void MainScene::MainUpdating(char *keys,char *preKeys) {
	player_->Update(keys, preKeys, enemyDown_);
	player_->Update(keys, preKeys, enemyLeft_);
	player_->GetParticle()->DrawParticle(player_->GetVpVpMatrix());
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
			enemyLeft_->Destroy(player_->GetBullet(i, k),{-2000,-2000});
			enemyDown_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
		}
	}
	enemyDown_->IsDeath();
	enemyLeft_->IsDeath();
	enemyDown_->Update(player_->GetVpVpMatrix());
	if (Camera::isRotation) {
		enemyLeft_->Update(player_->GetVpVpMatrix());

	}
}

void MainScene::MainDrawing() {
	player_->PlayerDraw(player_->GetPlayerTexture());
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
	         player_->GetBullet(i,k)->BulletDrawSprite(player_->GetVpVpMatrix());
		}
	}
	enemyDown_->EnemyDraw();
	enemyLeft_->EnemyDraw();
}

void MainScene::MainLoop(char* keys, char* preKeys) {
	MainUpdating(keys,preKeys);//更新処理
	MainDrawing(); //描画処理
}
