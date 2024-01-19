#include "EnemyDown.h"

EnemyDown::EnemyDown() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].affine = { {1,1},0,{0,0} };
		enemy_[i].local = {
		{ -ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{ -ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		};
		enemy_[i].isAlive = false;
		enemy_[i].speed = -5;
		enemy_[i].theta = 1.0f/100;
		enemy_[i].scale = 1.0f/100;
		enemy_[i].screen = {};
		enemy_[i].worldMatrix = {};
		enemy_[i].wvpVpMatrix = {};
	}
	texture_ = Novice::LoadTexture("white1x1.png");
}

void EnemyDown::EnemySpawn() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemy_[i].isAlive) {
			enemy_[i].isAlive = true;
			enemy_[i].affine.translate = { 0,500 };
			break;
		}
	}
}

void EnemyDown::EnemyTranslate() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy_[i].isAlive) {
			//enemy_[i].affine.translate.y += enemy_[i].speed;
			/*if (enemy_[i].affine.translate.y < 300) {
				enemy_[i].affine.translate.x += enemy_[i].speed;
				if (enemy_[i].affine.translate.x > 1280 - 16) {
					enemy_[i].speed *= -1;
				}
				else if (enemy_[i].affine.translate.x < 16) {
					enemy_[i].speed *= -1;
				}
			}*/
		}
	}

	Novice::ScreenPrintf(0, 0, "x:%f",  enemy_[0].affine.translate.x);
	Novice::ScreenPrintf(0, 20, "y:%f", enemy_[0].affine.translate.y);
}

void EnemyDown::Destroy(char* keys, char* preKeys) {
	if (keys[DIK_R] && !preKeys[DIK_R]) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			enemy_[i].isAlive = false;
		}
	}
}

void EnemyDown::EnemySprite() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy_[i].isAlive) {
			Novice::DrawQuad(
				(int)enemy_[i].screen.leftTop.x, (int)enemy_[i].screen.leftTop.y,
				(int)enemy_[i].screen.leftBottom.x, (int)enemy_[i].screen.leftBottom.y,
				(int)enemy_[i].screen.rightTop.x, (int)enemy_[i].screen.rightTop.y,
				(int)enemy_[i].screen.rightBottom.x, (int)enemy_[i].screen.rightBottom.y,
				0, 0, 1, 1, texture_, BLUE);
		}
	}
}

void EnemyDown::Update(char* keys, char* preKeys,Matrix3x3 vpVpMatrix) {
	EnemySpawn();
	EnemyTranslate();
	Destroy(keys,preKeys);
	if (keys[DIK_L]) {
		enemy_[0].affine.translate.y += 5;
	}
    MakeWorldMatrix();
    MakeWvpVp(vpVpMatrix);
    EnemyTransform(vpVpMatrix);
	EnemySprite();
}