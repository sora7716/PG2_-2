#include "EnemyLeft.h"

EnemyLeft::EnemyLeft() {
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].affine = { {1,1},0,{0,100} };
		enemy_[i].local = {
		{ -ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{ -ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f ,-ENEMY_SIZE / 2.0f  },
		{  ENEMY_SIZE / 2.0f , ENEMY_SIZE / 2.0f  },
		};
		enemy_[i].isAlive = false;
		enemy_[i].shapes = { 1.0f / 30,1.0f / 20 ,{0,0} };
		enemy_[i].screen = {};
		enemy_[i].worldMatrix = {};
		enemy_[i].wvpVpMatrix = {};
		enemy_[i].tempSpeed = {};
		enemy_[i].isDeath = false;
	}
	texture_ = Novice::LoadTexture("./resource/object/enemy.png");
	spawnNum_ = 1;
	direction_ = 0;
	addTime_ = 950;
	tempAddTime_ = addTime_;
	collision_ = new Collision;
	particle_ = new Particle({ 0,0.7f });
	enemyBullet_ = new EnemyBullet;
	hud_ = new Hud;
}

EnemyLeft::~EnemyLeft() {
	delete collision_;
	delete particle_;
}

void EnemyLeft::EnemySpawn(){
	for (int i = 0; i < spawnNum_; i++) {
		if (!enemy_[i].isAlive) {
			enemy_[i].isAlive = true;
			enemy_[i].affine = { { 1,1 },0,{ float(ENEMY_SIZE * 2 * i)+400, -100 + (ENEMY_SIZE * i)} };
			int randomX = rand() % 5 + 1;
			enemy_[i].shapes.velocity = { (float)randomX,-20};
			enemy_[i].tempSpeed.x = fabsf(enemy_[i].shapes.velocity.x);
			enemy_[i].tempSpeed.y = fabsf(enemy_[i].shapes.velocity.y);
			break;
		}
	}
}

void EnemyLeft::EnemyTranslate(){
	for (int i = 0; i < spawnNum_; i++) {
		if (enemy_[i].isAlive) {
			enemy_[i].affine.translate.x -= enemy_[i].shapes.velocity.x;
			enemy_[i].affine.translate.y += enemy_[i].shapes.velocity.y;
			if (enemy_[i].affine.translate.y <= 200) {
				enemy_[i].shapes.velocity.y = -2;
			}
			if (enemy_[i].affine.translate.y <= -1200 || enemy_[i].affine.translate.x >= 800 || enemy_[i].affine.translate.x < -800) {
				enemy_[i].isAlive = false;
				direction_ = 0;
			}
			particle_->Update({ enemy_[i].affine.translate.x,enemy_[i].affine.translate.y + 16 }, ENEMY_SIZE * enemy_[i].affine.scale.x, 0xCCCCCCFF);
		}
	}
}

void EnemyLeft::EnemyDraw(){
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy_[i].isAlive) {
			Novice::DrawQuad(
				(int)enemy_[i].screen.leftTop.x, (int)enemy_[i].screen.leftTop.y,
				(int)enemy_[i].screen.leftBottom.x, (int)enemy_[i].screen.leftBottom.y,
				(int)enemy_[i].screen.rightTop.x, (int)enemy_[i].screen.rightTop.y,
				(int)enemy_[i].screen.rightBottom.x, (int)enemy_[i].screen.rightBottom.y,
				0, 0, (int)ENEMY_SIZE, (int)ENEMY_SIZE, texture_, WHITE);
		}
	}
}

void EnemyLeft::Destroy(Bullet* bullet, Vector2 translate){

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (bullet->GetBulletObject().isAlive) {
			if (collision_->Box(enemy_[i].affine.translate, bullet->GetBulletObject().affine.translate, ENEMY_SIZE, BULLET_SIZE)) {
				enemy_[i].isDeath = true;
				bullet->SetIsAlive(true);
				bullet->SetTranslate(translate);
				hud_->SetScoreIsAlive(true);
			}
		}
		
	}

}

void EnemyLeft::IsDeath() {
	for (int i = 0; i < ENEMY_NUM; i++) {
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

void EnemyLeft::Update(Matrix3x3 vpVpMatrix, Vector2 player,int coolTime){
	AddTime();
	EnemyAdd();
	EnemySpawn();
	EnemyTranslate();
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemyBullet_->EnemyAttack(player,enemy_[i].affine.translate,coolTime);
	}
	MakeWorldMatrix();
	MakeWvpVp(vpVpMatrix);
	EnemyTransform();
}

void EnemyLeft::Drawing(Matrix3x3 vpVpMatrix, Score* score) {
	particle_->DrawParticle(vpVpMatrix);
	enemyBullet_->BulletDrawing(vpVpMatrix,0x870805FF);
	EnemyDraw();
	hud_->ScoreUpdate(score);
	hud_->DrawScore();
}
