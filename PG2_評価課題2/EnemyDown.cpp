#include "EnemyDown.h"

EnemyDown::EnemyDown() {
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy_[i].affine = { {1,1},0,{0,1000}};
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
	texture_ = Novice::LoadTexture("white1x1.png");
	spawnNum_ = 1;
	direction_ = 0;
	addTime_ = 2000;
	tempAddTime_ = addTime_;
	collision_ = new Collision;
	particle_ = new Particle({0,0.7f});
}

EnemyDown::~EnemyDown() {
	delete collision_;
	delete particle_;
}

void EnemyDown::EnemySpawn() {
	if (direction_ == 0) {
		direction_ = Direction();
	}
	for (int i = 0; i < spawnNum_; i++) {
		if (!enemy_[i].isAlive) {
			enemy_[i].isAlive = true;
			enemy_[i].affine = { { 1,1 },0,{ float( ENEMY_SIZE*2 * i* direction_),1000+(ENEMY_SIZE*i)}};
			enemy_[i].shapes.velocity = { 5 * (float)direction_,-5 };
			enemy_[i].tempSpeed.x= fabsf(enemy_[i].shapes.velocity.x);
			enemy_[i].tempSpeed.y= fabsf(enemy_[i].shapes.velocity.y);
			break;
		}
	}
}

void EnemyDown::EnemyTranslate() {
		for (int i = 0; i < spawnNum_; i++) {
			if (enemy_[i].isAlive) {
				enemy_[i].affine.translate.y += enemy_[i].shapes.velocity.y;
				if (enemy_[i].affine.translate.y <= 200) {
					enemy_[i].shapes.velocity.y = -2;
				}
				if (enemy_[i].affine.translate.y <= -400) {
					enemy_[i].shapes.velocity.y = -5;
				}
				if (enemy_[i].affine.translate.y <= -650|| enemy_[i].affine.translate.x >= 640|| enemy_[i].affine.translate.x < -640) {
					enemy_[i].isAlive = false;
					direction_ = 0;
				}
				particle_->Update({ enemy_[i].affine.translate.x,enemy_[i].affine.translate.y+16 }, ENEMY_SIZE * enemy_[i].affine.scale.x,0xFFFFFFFF);
			}
		}

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

void EnemyDown::Destroy(Bullet* bullet,Vector2 translate) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (bullet->GetBulletObject().isAlive) {
				if (collision_->Box(enemy_[i].affine.translate, bullet->GetBulletObject().affine.translate, ENEMY_SIZE, BULLET_SIZE)) {
					enemy_[i].isDeath = true;
					bullet->SetIsAlive(true);
					bullet->SetTranslate(translate);
				}
			}
		}
}

void EnemyDown::IsDeath() {
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

void EnemyDown::Update(Matrix3x3 vpVpMatrix) {
	EnemySpawn();
	EnemyTranslate();
	AddTime();
	EnemyAdd();
    MakeWorldMatrix();
    MakeWvpVp(vpVpMatrix);
    EnemyTransform();
	particle_->DrawParticle(vpVpMatrix);
}