#pragma once
#include <stdlib.h>
#include <time.h>
#include "Rendering.h"

const int PARTICLE_NUM = 100;

typedef struct ParticleObject {
	Affine affine;
	Vector2 velocity;
	Vector2 acceleration;
	int radius;
	VectorInt random;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex screen;
	bool isAlive;
}ParticleObject;

class Particle:public Rendering
{
private:
	ParticleObject particle_[PARTICLE_NUM];
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Particle();

	/// <summary>
	/// パーティクルのポジションのセッター
	/// </summary>
	/// <param name="position"></param>
	Vector2 SetPosition(Vector2 translate);

	void Spawn(Vector2 translate);

	void Effect
};

