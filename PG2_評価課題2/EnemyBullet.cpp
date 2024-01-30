#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].rendering.affine = { {1,1},0,{} };
		enemyBullet_[i].rendering.local = {
			{ -ENEMY_BULLET_SIZE / 2.0f ,-ENEMY_BULLET_SIZE / 2.0f  },
			{ -ENEMY_BULLET_SIZE / 2.0f , ENEMY_BULLET_SIZE / 2.0f  },
			{  ENEMY_BULLET_SIZE / 2.0f ,-ENEMY_BULLET_SIZE / 2.0f  },
			{  ENEMY_BULLET_SIZE / 2.0f , ENEMY_BULLET_SIZE / 2.0f  },
		};
		enemyBullet_[i].rendering.screen = {};
		enemyBullet_[i].rendering.worldMatrix = {};
		enemyBullet_[i].rendering.wvpVpMatrix = {};
		enemyBullet_[i].meters.distance = {};
		enemyBullet_[i].meters.len = 0;
		enemyBullet_[i].meters.vector = {};
		enemyBullet_[i].velocity = { 1,-1 };
		enemyBullet_[i].rotateSpeed= 300.0f;
		enemyBullet_[i].isAlive = false;
	}
	texture_ = Novice::LoadTexture("white1x1.png");
	coolTime_ = 60;
	particle_ = new Particle({ 0,0.7f });
}

EnemyBullet::~EnemyBullet() {
	delete particle_;
}

Vector2 EnemyBullet::EnemyPosition(Vector2 translate) {
	Vector2 result = translate;
	return translate;
}

Vector2 EnemyBullet::PlayerPosition(Vector2 translate) {
	Vector2 result = translate;
	return result;
}

void EnemyBullet::Distance(Vector2 translate) {
	Vector2 player = PlayerPosition(translate);
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].meters.distance.x = enemyBullet_[i].rendering.affine.translate.x - player.x;
		enemyBullet_[i].meters.distance.y = enemyBullet_[i].rendering.affine.translate.y - player.y;
	}
}

void EnemyBullet::Length() {
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].meters.len = sqrtf(float(pow(enemyBullet_[i].meters.distance.x, 2) + pow(enemyBullet_[i].meters.distance.y, 2)));
	}
}

void EnemyBullet::Normalize() {
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (enemyBullet_[i].meters.len != 0.0f) {
			if (!enemyBullet_[i].isAlive) {
				enemyBullet_[i].meters.vector.x = enemyBullet_[i].meters.distance.x / enemyBullet_[i].meters.len;
				enemyBullet_[i].meters.vector.y = enemyBullet_[i].meters.distance.y / enemyBullet_[i].meters.len;
			}
		}
	}
}

void EnemyBullet::ShotTime(int coolTime) {
	if (coolTime_ > 0) {
		coolTime_--;
	}
	else {
		coolTime_ = coolTime;
	}
}

void EnemyBullet::BulletSpawn(Vector2 player,Vector2 enemy,int coolTime) {
	ShotTime(coolTime);
	if (coolTime_<=0) {
		Distance(player);
		Length();
		Normalize();
		for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
			if (!enemyBullet_[i].isAlive) {
				enemyBullet_[i].rendering.affine.translate = EnemyPosition(enemy);
				enemyBullet_[i].isAlive = true;
				break;
			}
		}
	}
}

void EnemyBullet::BulletMove() {
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].rendering.affine.theta += enemyBullet_[i].rotateSpeed;
		if (enemyBullet_[i].isAlive) {
			enemyBullet_[i].rendering.affine.translate.x += enemyBullet_[i].velocity.x * -enemyBullet_[i].meters.vector.x;
			enemyBullet_[i].rendering.affine.translate.y += enemyBullet_[i].velocity.y *  enemyBullet_[i].meters.vector.y;
			//particle_->Update(enemyBullet_[i].rendering.affine.translate, ENEMY_BULLET_SIZE, GREEN);
		}
		if (enemyBullet_[i].rendering.affine.translate.y <= -650 - 500 || enemyBullet_[i].rendering.affine.translate.y >= 650 - 500 ||
			enemyBullet_[i].rendering.affine.translate.x <= -650|| enemyBullet_[i].rendering.affine.translate.x >= 650) {
			enemyBullet_[i].isAlive = false;
			enemyBullet_[i].rendering.affine.translate = {};
			enemyBullet_[i].meters = {};
		}
	}
}

void EnemyBullet::MakeWorleMatrix(){
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].rendering.worldMatrix = MakeAffineMatrix(enemyBullet_[i].rendering.affine);
	}
}

void EnemyBullet::wvpVpMatrix(Matrix3x3 vpVpMatrix){
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].rendering.wvpVpMatrix = Multiply(enemyBullet_[i].rendering.worldMatrix, vpVpMatrix);
	}
}

void EnemyBullet::BulletTransform(){
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		enemyBullet_[i].rendering.screen.leftTop     = TransForm(enemyBullet_[i].rendering.local.leftTop,     enemyBullet_[i].rendering.wvpVpMatrix);
		enemyBullet_[i].rendering.screen.leftBottom  = TransForm(enemyBullet_[i].rendering.local.leftBottom,  enemyBullet_[i].rendering.wvpVpMatrix);
		enemyBullet_[i].rendering.screen.rightTop    = TransForm(enemyBullet_[i].rendering.local.rightTop,    enemyBullet_[i].rendering.wvpVpMatrix);
		enemyBullet_[i].rendering.screen.rightBottom = TransForm(enemyBullet_[i].rendering.local.rightBottom, enemyBullet_[i].rendering.wvpVpMatrix);
	}
}

void EnemyBullet::BulletDraw(unsigned int color){
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (enemyBullet_[i].isAlive) {
			Novice::DrawQuad(
				(int)enemyBullet_[i].rendering.screen.leftTop.x,     (int)enemyBullet_[i].rendering.screen.leftTop.y,
				(int)enemyBullet_[i].rendering.screen.rightTop.x,    (int)enemyBullet_[i].rendering.screen.rightTop.y,
				(int)enemyBullet_[i].rendering.screen.leftBottom.x,  (int)enemyBullet_[i].rendering.screen.leftBottom.y,
				(int)enemyBullet_[i].rendering.screen.rightBottom.x, (int)enemyBullet_[i].rendering.screen.rightBottom.y,
				0, 0, 1, 1, texture_, color
			);
		}
	}
}

void EnemyBullet::EnemyAttack(Vector2 player,Vector2 enemy, int coolTime) {
	BulletSpawn(player, enemy,coolTime);
	BulletMove();
}

void EnemyBullet::BulletDrawing(Matrix3x3 vpVpMatrix,unsigned int color) {
	MakeWorleMatrix();
	wvpVpMatrix(vpVpMatrix);
	BulletTransform();
	BulletDraw(color);
	//particle_->DrawParticle(vpVpMatrix);
}

