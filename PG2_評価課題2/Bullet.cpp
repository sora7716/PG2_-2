#include "Bullet.h"

Bullet::Bullet() {
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet_[i].affine = { {1,1},0,{0,0} };

		bullet_[i].local = 
		{
		  { -BULLET_SIZE / 2.0f ,-BULLET_SIZE / 2.0f  },
		  { -BULLET_SIZE / 2.0f , BULLET_SIZE / 2.0f  },
		  {  BULLET_SIZE / 2.0f ,-BULLET_SIZE / 2.0f  },
		  {  BULLET_SIZE / 2.0f , BULLET_SIZE / 2.0f  },
		};
		bullet_[i].speed       = 10;
		bullet_[i].isAlive     = false;
		bullet_[i].worldMatrix = {};
		bullet_[i].screen      = {};
		bullet_[i].wvpVpMatrix = {};
	}
	texture_ = Novice::LoadTexture("white1x1.png");
}

Vector2 Bullet::SetTranslate(Vector2 translate) {
	Vector2 result = translate;
	return result;
}

void Bullet::IsShot(char* keys, char* preKeys, Vector2 translate) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		for (int i = 0; i < BULLET_NUM; i++) {
			if (!bullet_[i].isAlive) {
				bullet_[i].isAlive = true;
				bullet_[i].affine.translate = SetTranslate(translate);
				break;
			}
		}
	}
}

void Bullet::Move() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet_[i].isAlive) {
			bullet_[i].affine.translate.y += bullet_[i].speed;
			if (bullet_[i].affine.translate.y >= 600) {
				bullet_[i].isAlive = false;
				bullet_[i].affine.translate = { 0 };
			}
		}
	}
}

void Bullet::Attack(char* keys, char* preKeys, Vector2 translate) {
	IsShot(keys,preKeys,translate);
	Move();
}

void Bullet::MakeWorleMatrix() {
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet_[i].worldMatrix = MakeAffineMatrix(bullet_[i].affine);
	}
}

void Bullet::wvpVpMatrix(Matrix3x3 vpVpMatrix) {
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet_[i].wvpVpMatrix = Multiply(bullet_[i].worldMatrix, vpVpMatrix);
	}
}

void Bullet::BulletTransform() {
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet_[i].screen.leftTop     = TransForm(bullet_[i].local.leftTop,     bullet_[i].wvpVpMatrix);
		bullet_[i].screen.leftBottom  = TransForm(bullet_[i].local.leftBottom,  bullet_[i].wvpVpMatrix);
		bullet_[i].screen.rightTop    = TransForm(bullet_[i].local.rightTop,    bullet_[i].wvpVpMatrix);
		bullet_[i].screen.rightBottom = TransForm(bullet_[i].local.rightBottom, bullet_[i].wvpVpMatrix);
	}
}

void Bullet::BulletDraw() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet_[i].isAlive) {
			Novice::DrawQuad(
				(int)bullet_[i].screen.leftTop.x,     (int)bullet_[i].screen.leftTop.y,
				(int)bullet_[i].screen.rightTop.x,    (int)bullet_[i].screen.rightTop.y,
				(int)bullet_[i].screen.leftBottom.x,  (int)bullet_[i].screen.leftBottom.y,
				(int)bullet_[i].screen.rightBottom.x, (int)bullet_[i].screen.rightBottom.y,
				0, 0, 1, 1, texture_, RED
			);
		}
	}
}

void Bullet::BulletDrawSprite(Matrix3x3 vpVpMatrix) {
	MakeWorleMatrix();
	wvpVpMatrix(vpVpMatrix);
	BulletTransform();
	BulletDraw();
}

