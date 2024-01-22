#include "Particle.h"

Particle::Particle() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].affine       = { {1,1},0,{0,0} };
		particle_[i].velocity     = {};
		particle_[i].acceleration = {0,-0.3f};
		particle_[i].radius       = 0;
		particle_[i].random       = {};
		particle_[i].worldMatrix  = {};
		particle_[i].wvpVpMatrix  = {};
		particle_[i].screen       = {};
		particle_[i].isAlive      = false;
		particle_[i].local =
		{
		  { -PARTICLE_SIZE / 2.0f ,-PARTICLE_SIZE / 2.0f  },
		  { -PARTICLE_SIZE / 2.0f , PARTICLE_SIZE / 2.0f  },
		  {  PARTICLE_SIZE / 2.0f ,-PARTICLE_SIZE / 2.0f  },
		  {  PARTICLE_SIZE / 2.0f , PARTICLE_SIZE / 2.0f  },
		};
	}
	srand((unsigned int)time(nullptr));
	texture_ = Novice::LoadTexture("white1x1.png");
}

void Particle::SetPosition(BulletObject bullet) {
    for (int i = 0; i < PARTICLE_NUM; i++) {
		if (!particle_[i].isAlive) {
			particle_[i].affine.translate = bullet.affine.translate;
		}
    }
}

void Particle::Spawn(BulletObject bullet) {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (!particle_[i].isAlive) {
			particle_[i].isAlive = true;
		    SetPosition(bullet);
			break;
		}
	}
}

void Particle::Effect(BulletObject bullet){
	for (int i = 0; i < BULLET_NUM; i++) {
		for (int j = 0; j < PARTICLE_NUM; j++) {
			if (particle_[j].isAlive) {
				particle_[j].affine.translate.y += particle_[j].velocity.y;
				particle_[j].velocity.y += particle_[j].acceleration.y;
				if (particle_[j].affine.translate.y >= bullet.affine.translate.y + 16) {
					particle_[j].isAlive = false;
				}
			}
		}
	}
}

void Particle::MakeWorleMatrix() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].worldMatrix = MakeAffineMatrix(particle_[i].affine);
	}
}

void Particle::wvpVpMatrix(Matrix3x3 vpVpMatrix) {
	for (int i = 0; i < BULLET_NUM; i++) {
		particle_[i].wvpVpMatrix = Multiply(particle_[i].worldMatrix, vpVpMatrix);
	}
}

void Particle::ParticleTransform() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particle_[i].screen.leftTop     = TransForm(particle_[i].local.leftTop,     particle_[i].wvpVpMatrix);
		particle_[i].screen.leftBottom  = TransForm(particle_[i].local.leftBottom,  particle_[i].wvpVpMatrix);
		particle_[i].screen.rightTop    = TransForm(particle_[i].local.rightTop,    particle_[i].wvpVpMatrix);
		particle_[i].screen.rightBottom = TransForm(particle_[i].local.rightBottom, particle_[i].wvpVpMatrix);
	}
}

void Particle::ParticleDraw() {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (particle_[i].isAlive) {
			Novice::DrawQuad(
				(int)particle_[i].screen.leftTop.x,     (int)particle_[i].screen.leftTop.y,
				(int)particle_[i].screen.rightTop.x,    (int)particle_[i].screen.rightTop.y,
				(int)particle_[i].screen.leftBottom.x,  (int)particle_[i].screen.leftBottom.y,
				(int)particle_[i].screen.rightBottom.x, (int)particle_[i].screen.rightBottom.y,
				0, 0, 1, 1, texture_, GREEN
			);
		}
	}
}

void Particle::ParticleDrawSprite(Matrix3x3 vpVpMatrix) {
	MakeWorleMatrix();
	wvpVpMatrix(vpVpMatrix);
	ParticleTransform();
	ParticleDraw();
}

void Particle::ParticleUpdate(BulletObject bullet) {
	Spawn(bullet);
	Effect(bullet);
}