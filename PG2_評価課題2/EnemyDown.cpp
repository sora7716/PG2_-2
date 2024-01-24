#include "EnemyDown.h"

EnemyDown::EnemyDown() {
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].affine = { {1,1},0,{0,1000} };
		enemy_[i].local = {
		{ -ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{ -ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		};
		enemy_[i].isAlive = false;
		enemy_[i].shapes = { 1.0f / 50,1.0f / 20 ,{0,0} };
		enemy_[i].screen = {};
		enemy_[i].worldMatrix = {};
		enemy_[i].wvpVpMatrix = {};
		enemy_[i].tempSpeed = {};
		enemy_[i].isDeath = false;
	}
	texture_ = Novice::LoadTexture("white1x1.png");
	collision_ = new Collision;
}

void EnemyDown::EnemySpawn() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemy_[i].isAlive) {
			enemy_[i].isAlive = true;
			int direction = Direction();
			enemy_[i].affine = { { 1,1 },0,{ 0,1000 } };
			enemy_[i].shapes.velocity = { 5 * (float)direction,-5 };
			enemy_[i].tempSpeed.x= fabsf(enemy_[i].shapes.velocity.x);
			enemy_[i].tempSpeed.y= fabsf(enemy_[i].shapes.velocity.y);
			break;
		}
	}
}

void EnemyDown::EnemyTranslate() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy_[i].isAlive) {
			enemy_[i].affine.translate.y += enemy_[i].shapes.velocity.y;
			if (enemy_[i].affine.translate.y < 300) {
				enemy_[i].shapes.velocity.y = 0;
				enemy_[i].affine.translate.x += enemy_[i].shapes.velocity.x;
				if (enemy_[i].affine.translate.x > 640) {
					enemy_[i].shapes.velocity.x = -enemy_[i].tempSpeed.x;
				}
				if (enemy_[i].affine.translate.x < -640) {
					enemy_[i].shapes.velocity.x = enemy_[i].tempSpeed.x;
				}
			}
		}
	}
}

int EnemyDown::Direction() {
	int random = rand()%2;
	if (random == 0) {
		return -1;
	}
	return 1;
}

void EnemyDown::EnemyDraw() {
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

void EnemyDown::Destroy(Bullet* bullet) {
	for (int i = 0; i < ENEMY_NUM; i++) {
		for (int j = 0; j < BULLET_NUM; j++) {
			if (collision_->Box(enemy_[i].affine.translate, bullet->GetBulletObject()[j].affine.translate, ENEMY_SIZE, BULLET_SIZE)) {
				enemy_[i].isDeath = true;
				bullet->GetBulletObject()[j].isAlive = false;
				bullet->GetBulletObject()[j].affine.translate = { 0 };
			}
			if (enemy_[i].isDeath) {
				enemy_[i].shapes.velocity = { 0,-1 };
				enemy_[i].affine.theta += enemy_[i].shapes.rotation;
				if (enemy_[i].affine.scale.x > 0 && enemy_[i].affine.scale.y > 0) {
					enemy_[i].affine.scale.x -= enemy_[i].shapes.growing;
					enemy_[i].affine.scale.y -= enemy_[i].shapes.growing;
					break;
				}
				else {
					enemy_[i].isAlive = false;
					enemy_[i].isDeath = false;
				}
			}
		}
	}
}

void EnemyDown::Update(Matrix3x3 vpVpMatrix, Bullet* bullet) {
	EnemySpawn();
	EnemyTranslate();
	Destroy(bullet);
    MakeWorldMatrix();
    MakeWvpVp(vpVpMatrix);
    EnemyTransform();
}