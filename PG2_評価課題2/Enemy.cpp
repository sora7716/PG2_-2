#include "Enemy.h"

void Enemy::MakeWorldMatrix(EnemyObject enemy) {
	enemy.worldMatrix = MakeAffineMatrix(enemy.affine);
}

void Enemy::MakeWvpVp(EnemyObject enemy) {
	enemy.wvpVpMatrix = Multiply(enemy.worldMatrix, vpVpMatrix_);
}

void Enemy::EnemyTransform(EnemyObject enemy) {
	enemy.screen.leftTop     = TransForm(enemy.local.leftTop,     enemy.wvpVpMatrix);
	enemy.screen.leftBottom  = TransForm(enemy.local.leftBottom,  enemy.wvpVpMatrix);
	enemy.screen.rightTop    = TransForm(enemy.local.rightTop,    enemy.wvpVpMatrix);
	enemy.screen.rightBottom = TransForm(enemy.local.rightBottom, enemy.wvpVpMatrix);
}

void Enemy::Update(EnemyObject enemy) {

}