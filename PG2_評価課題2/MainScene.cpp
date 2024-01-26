#include "MainScene.h"

MainScene::MainScene() {
	player_ = new Player;
	enemyDown_ = new EnemyDown;
	enemyLeft_ = new EnemyLeft;
	isEnemyLeftMove_ = false;
}

MainScene::~MainScene() {
	delete player_;
	delete enemyDown_;
	delete enemyLeft_;
}

void MainScene::MainUpdating(char *keys,char *preKeys) {
	player_->Update(keys, preKeys, enemyDown_);
	player_->Update(keys, preKeys, enemyLeft_);
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
			enemyLeft_->Destroy(player_->GetBullet(i, k),{-2000,-2000});
			enemyDown_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
		}
	}
	enemyDown_->IsDeath();
	enemyLeft_->IsDeath();
	enemyDown_->Update(player_->GetVpVpMatrix(),player_->GetTranslate(),120);
	if (Camera::isRotation) {
		isEnemyLeftMove_ = true;
	}
	if (isEnemyLeftMove_) {
		enemyLeft_->Update(player_->GetVpVpMatrix(), player_->GetTranslate(),60);

	}
}

void MainScene::MainDrawing() {
		for (int i = 0; i < SHOT_NUM; i++) {
			for (int k = 0; k < BULLET_NUM; k++) {
				player_->GetBullet(i, k)->BulletDrawSprite(player_->GetVpVpMatrix());
			}
		}
		player_->GetParticle()->DrawParticle(player_->GetVpVpMatrix());
		player_->PlayerDraw(player_->GetPlayerTexture());
		enemyDown_->Drawing(player_->GetVpVpMatrix());
		enemyLeft_->Drawing(player_->GetVpVpMatrix());
}

void MainScene::MainLoop(char* keys, char* preKeys) {
	MainUpdating(keys, preKeys);//更新処理
	MainDrawing(); //描画処理
}
