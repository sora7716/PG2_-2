#include "Enemy.h"

Enemy::~Enemy() {
	delete collision_;
}

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

void Enemy::EnemyDraw() {

}

void Enemy::EnemyTransform() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].screen.leftTop     = TransForm(enemy_[i].local.leftTop,     enemy_[i].wvpVpMatrix);
		enemy_[i].screen.leftBottom  = TransForm(enemy_[i].local.leftBottom,  enemy_[i].wvpVpMatrix);
		enemy_[i].screen.rightTop    = TransForm(enemy_[i].local.rightTop,    enemy_[i].wvpVpMatrix);
		enemy_[i].screen.rightBottom = TransForm(enemy_[i].local.rightBottom, enemy_[i].wvpVpMatrix);
	}
}

void Enemy::Update(Matrix3x3 vpVpMatrix, Bullet* bullet) {
		vpVpMatrix = { 100 };
		bullet->Inverse(vpVpMatrix);
}