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
	}
	srand((unsigned int)time(nullptr));
}

Vector2 Particle::SetPosition(Vector2 translate) {
	Vector2 result = translate;
	return result;
}

void Particle::Spawn(Vector2 translate) {
	for (int i = 0; i < PARTICLE_NUM; i++) {
		if (!particle_[i].isAlive) {
			particle_[i].isAlive = true;
			particle_[i].affine.translate = SetPosition(translate);
			break;
		}
	}
}