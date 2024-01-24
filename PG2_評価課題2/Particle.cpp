#include "Particle.h"

Particle::Particle() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].affine       = { {1,1},0,{0,0} };
		particle_[i].velocity     = {};
		particle_[i].acceleration = {0,-0.7f};
		particle_[i].radius       = 0;
		particle_[i].random       = {};
		particle_[i].worldMatrix  = {};
		particle_[i].wvpVpMatrix  = {};
		particle_[i].screen       = {};
		particle_[i].local = {
		  { -PARTICLE_SIZE / 2.0f ,-PARTICLE_SIZE / 2.0f  },
		  { -PARTICLE_SIZE / 2.0f , PARTICLE_SIZE / 2.0f  },
		  {  PARTICLE_SIZE / 2.0f ,-PARTICLE_SIZE / 2.0f  },
		  {  PARTICLE_SIZE / 2.0f , PARTICLE_SIZE / 2.0f  },
		};
		particle_[i].isAlive      = false;
		particle_[i].color        = WHITE;
	}
	srand((unsigned int)time(nullptr));
	texture_ = Novice::LoadTexture("white1x1.png");
}

Vector2 Particle::SetPosition(Vector2 translate) {
	Vector2 result = translate;
	return result;
}

void Particle::Spawn(Vector2 translate,int size,unsigned int color) {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (!particle_[i].isAlive) {
			particle_[i].isAlive          = true;
			particle_[i].velocity.y       = 0;
			particle_[i].color            = color;
			particle_[i].random.x         = rand() % (int)size + (int)SetPosition(translate).x - (int)size/2;
			particle_[i].random.y         = rand() % (int)size + (int)SetPosition(translate).y - (int)size/2;
			particle_[i].radius           = rand() % 2 + 1;
			particle_[i].affine.scale     = { (float)particle_[i].radius ,(float)particle_[i].radius };
			particle_[i].affine.translate = { (float)particle_[i].random.x,(float)particle_[i].random.y };
			break;
		}
	}
}

void Particle::Movement(Vector2 translate,unsigned int color) {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (particle_[i].isAlive) {
			particle_[i].affine.translate.y += particle_[i].velocity.y;
			particle_[i].velocity.y += particle_[i].acceleration.y;
			ColorSubtract(color);
		}
	}
	Novice::ScreenPrintf(0, 0, "%f", translate.y);
}

void Particle::ColorSubtract(unsigned int color) {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (particle_[i].color > color-0x000000FF) {
			particle_[i].color -= 0x00000001;
		}
		else {
			particle_[i].isAlive = false;
		}
	}
}

void Particle::Update(Vector2 translate,int size,unsigned int color) {
	Spawn(translate,size, color);
	Movement(translate,color);
}

void Particle::MakeWorleMatrix() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].worldMatrix = MakeAffineMatrix(particle_[i].affine);
	}
}

void Particle::wvpVpMatrix(Matrix3x3 vpVpMatrix){
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].wvpVpMatrix = Multiply(particle_[i].worldMatrix, vpVpMatrix);
	}
}

void Particle::ParticleTransform(){
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].screen.leftTop     = TransForm(particle_[i].local.leftTop,     particle_[i].wvpVpMatrix);
		particle_[i].screen.leftBottom  = TransForm(particle_[i].local.leftBottom,  particle_[i].wvpVpMatrix);
		particle_[i].screen.rightTop    = TransForm(particle_[i].local.rightTop,    particle_[i].wvpVpMatrix);
		particle_[i].screen.rightBottom = TransForm(particle_[i].local.rightBottom, particle_[i].wvpVpMatrix);
	}
}

void Particle::ParticleQuad(){
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (particle_[i].isAlive) {
			Novice::DrawQuad(
				(int)particle_[i].screen.leftTop.x ,     (int)particle_[i].screen.leftTop.y,
				(int)particle_[i].screen.rightTop.x ,    (int)particle_[i].screen.rightTop.y,
				(int)particle_[i].screen.leftBottom.x ,  (int)particle_[i].screen.leftBottom.y,
				(int)particle_[i].screen.rightBottom.x , (int)particle_[i].screen.rightBottom.y,
				0, 0, 1, 1, texture_, particle_[i].color
			);
		}
	}
}

void Particle::DrawParticle(Matrix3x3 vpVpMatrix) {
	MakeWorleMatrix();
	wvpVpMatrix(vpVpMatrix);
	ParticleTransform();
	ParticleQuad();
}