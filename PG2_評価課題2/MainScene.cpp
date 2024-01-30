#include "MainScene.h"

MainScene::MainScene() {
	player_ = new Player;
	enemyDown_ = new EnemyDown;
	enemyLeft_ = new EnemyLeft;
	bg_ = new Bg;
	isEnemyLeftMove_ = false;
}

MainScene::~MainScene() {
	delete player_;
	delete enemyDown_;
	delete enemyLeft_;
	delete bg_;
}

void MainScene::MainUpdating(char *keys,char *preKeys, Scene &scene, Score* score) {
  player_->Update(keys, preKeys, enemyDown_, scene,score);
  player_->Update(keys, preKeys, enemyLeft_, scene,score);
	if (player_->GetIsBestPlace()) {
	    for (int i = 0; i < SHOT_NUM; i++) {
	    	for (int k = 0; k < BULLET_NUM; k++) {
	    		enemyLeft_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
	    		enemyDown_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
	    	}
	    }
	    enemyDown_->IsDeath();
	    enemyLeft_->IsDeath();
	    enemyDown_->Update(player_->GetVpVpMatrix(), player_->GetTranslate(), 120);
	    if (score->GetScore()>=500) {
	    	isEnemyLeftMove_ = true;
	    }
	    if (isEnemyLeftMove_) {
	    	enemyLeft_->Update(player_->GetVpVpMatrix(), player_->GetTranslate(), 60);
	    
	    }
	}
}

void MainScene::MainDrawing(Score *score, unsigned int color) {
	    bg_->Update(player_->GetVpVpMatrix(),color);
		for (int i = 0; i < SHOT_NUM; i++) {
			for (int k = 0; k < BULLET_NUM; k++) {
				player_->GetBullet(i, k)->BulletDrawSprite(player_->GetVpVpMatrix());
			}
		}
		player_->GetParticle()->DrawParticle(player_->GetVpVpMatrix());
		player_->PlayerDraw(player_->GetPlayerTexture());
		enemyDown_->Drawing(player_->GetVpVpMatrix(),score);
		enemyLeft_->Drawing(player_->GetVpVpMatrix(),score);
}

void MainScene::MainLoop(char* keys, char* preKeys, Scene &scene, Score* score) {
	MainUpdating(keys, preKeys, scene,score);//更新処理
	MainDrawing(score,WHITE); //描画処理
}
