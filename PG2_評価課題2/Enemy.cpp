#include "Enemy.h"

void Enemy::MakeWorldMatrix() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].worldMatrix = MakeAffineMatrix(enemy_[i].affine);
	}
}

void Enemy::MakeWvpVp(Matrix3x3 vpVpMatrix) {
	for (int i = 0; i < ENEMY_NUM; i++) {
	enemy_[i].wvpVpMatrix = Multiply(enemy_[i].worldMatrix, vpVpMatrix);
	}
}

void Enemy::EnemyTransform(Matrix3x3 vpVpMatrix) {
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].screen.leftTop     = TransForm(enemy_[i].local.leftTop,     vpVpMatrix);
		enemy_[i].screen.leftBottom  = TransForm(enemy_[i].local.leftBottom,  vpVpMatrix);
		enemy_[i].screen.rightTop    = TransForm(enemy_[i].local.rightTop,    vpVpMatrix);
		enemy_[i].screen.rightBottom = TransForm(enemy_[i].local.rightBottom, vpVpMatrix);
	}
}

void Enemy::Update(char* keys, char* preKeys, Matrix3x3 vpVpMatrix) {
	if (keys[DIK_A] && preKeys[DIK_A]) {
		vpVpMatrix = { 100 };
	}
}