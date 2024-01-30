#include "Bullet.h"

Bullet::Bullet() {
	bullet_.affine = { {1,1},0,{0,0} };

	bullet_.local =
	{
	  { -BULLET_SIZE / 2.0f ,-BULLET_SIZE / 2.0f  },
	  { -BULLET_SIZE / 2.0f , BULLET_SIZE / 2.0f  },
	  {  BULLET_SIZE / 2.0f ,-BULLET_SIZE / 2.0f  },
	  {  BULLET_SIZE / 2.0f , BULLET_SIZE / 2.0f  },
	};
	bullet_.speed = 10;
	bullet_.rotation = 10.0f;
	bullet_.isAlive = false;
	bullet_.worldMatrix = {};
	bullet_.screen = {};
	bullet_.wvpVpMatrix = {};
	texture_ = Novice::LoadTexture("white1x1.png");
	particle_ = new Particle({ 0,-0.7f });
	shotTime_ = 0;
}

Bullet::~Bullet() {
	delete particle_;
}

Vector2 Bullet::PlayerTranslate(Vector2 translate) {
	Vector2 result = translate;
	return result;
}

void Bullet::ShotTime() {
	if (shotTime_ > 0) {
		shotTime_--;
	}
}

void Bullet::IsShot(char* keys, char* preKeys, Vector2 translate,int i ){
	ShotTime();
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]&&shotTime_<=0) {

			bullet_.isAlive = true;
			if (i == 0) {
				bullet_.affine.translate = PlayerTranslate(translate);
			}
			else if (i == 1) {
				bullet_.affine.translate = { PlayerTranslate(translate).x + 32,PlayerTranslate(translate).y };
			}
			else {
				bullet_.affine.translate = { PlayerTranslate(translate).x - 32,PlayerTranslate(translate).y };
			}
			shotTime_ = 30;
	}
}

void Bullet::Move() {
	if (bullet_.isAlive) {
		bullet_.affine.translate.y += bullet_.speed;
		bullet_.affine.theta += bullet_.rotation;
		if (bullet_.affine.translate.y >= 700) {
			bullet_.isAlive = false;
			bullet_.affine.translate = { 0 };
		}
	}
}

void Bullet::Attack() {
	Move();
	if (bullet_.isAlive) {
		particle_->Update(bullet_.affine.translate, BULLET_SIZE, 0xFF7007FF);
	}
}

void Bullet::MakeWorleMatrix() {
	bullet_.worldMatrix = MakeAffineMatrix(bullet_.affine);
}

void Bullet::wvpVpMatrix(Matrix3x3 vpVpMatrix) {
	bullet_.wvpVpMatrix = Multiply(bullet_.worldMatrix, vpVpMatrix);
}

void Bullet::BulletTransform() {
	bullet_.screen.leftTop     = TransForm(bullet_.local.leftTop,     bullet_.wvpVpMatrix);
	bullet_.screen.leftBottom  = TransForm(bullet_.local.leftBottom,  bullet_.wvpVpMatrix);
	bullet_.screen.rightTop    = TransForm(bullet_.local.rightTop,    bullet_.wvpVpMatrix);
	bullet_.screen.rightBottom = TransForm(bullet_.local.rightBottom, bullet_.wvpVpMatrix);
}

void Bullet::BulletDraw(Matrix3x3 vpVpMatrix) {

	if (bullet_.isAlive) {
		Novice::DrawQuad(
			(int)bullet_.screen.leftTop.x,     (int)bullet_.screen.leftTop.y,
			(int)bullet_.screen.rightTop.x,    (int)bullet_.screen.rightTop.y,
			(int)bullet_.screen.leftBottom.x,  (int)bullet_.screen.leftBottom.y,
			(int)bullet_.screen.rightBottom.x, (int)bullet_.screen.rightBottom.y,
			0, 0, 1, 1, texture_, GREEN
		);
		particle_->DrawParticle(vpVpMatrix);
	}
}

void Bullet::BulletDrawSprite(Matrix3x3 vpVpMatrix) {
	MakeWorleMatrix();
	wvpVpMatrix(vpVpMatrix);
	BulletTransform();
	BulletDraw(vpVpMatrix);
}

void Bullet::SetIsAlive(bool isAlive){
	bullet_.isAlive = isAlive;
}

void Bullet::SetTranslate(Vector2 translate) {
	bullet_.affine.translate = { translate.x,translate.y };
}

