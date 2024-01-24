#include "Enemy.h"

Enemy::Enemy()
{
	direction_ = 0;
	spawnNum_ = 0;
	texture_ = 0;
	collision_ = nullptr;
	addTime_ = 0;
	tempAddTime_ = 0;
	particle_ = nullptr;
}

Enemy::~Enemy() {
	delete collision_;
	delete particle_;
}

void Enemy::AddTime() {
	if (addTime_ > 0) {
		addTime_--;
	}
}

void Enemy::EnemyAdd() {
	if (addTime_ <= 0) {
		if (spawnNum_ < 7) {
			spawnNum_ ++;
		}
		addTime_ = tempAddTime_ /= 2;
	}
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

int Enemy::Direction() {
	int random = rand() % 2;
	if (random == 0) {
		return -1;
	}
	return 1;
}

void Enemy::EnemyTransform() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].screen.leftTop     = TransForm(enemy_[i].local.leftTop,     enemy_[i].wvpVpMatrix);
		enemy_[i].screen.leftBottom  = TransForm(enemy_[i].local.leftBottom,  enemy_[i].wvpVpMatrix);
		enemy_[i].screen.rightTop    = TransForm(enemy_[i].local.rightTop,    enemy_[i].wvpVpMatrix);
		enemy_[i].screen.rightBottom = TransForm(enemy_[i].local.rightBottom, enemy_[i].wvpVpMatrix);
	}
}

void Enemy::EnemyDraw() {

}

void Enemy::Destroy(Bullet* bullet,Vector2 translate)
{
	bullet->BulletDraw();
	translate = {};
}

void Enemy::IsDeath()
{
}


void Enemy::Update(Matrix3x3 vpVpMatrix) {
		vpVpMatrix = { 100 };
}