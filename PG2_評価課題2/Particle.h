#pragma once
#include <stdlib.h>
#include <time.h>
#include "Rendering.h"
#include <Novice.h>

const int PARTICLE_NUM = 100;
const int PARTICLE_SIZE = 7;

typedef struct ParticleObject {
	Affine affine;
	Vector2 velocity;
	Vector2 acceleration;
	int radius;
	VectorInt random;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex local;
	Vertex screen;
	bool isAlive;
	unsigned int color;
}ParticleObject;

class Particle:public Rendering
{
private:
	ParticleObject particle_[PARTICLE_NUM];
	int texture_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Particle(Vector2 acceleration);

	/// <summary>
	/// パーティクルのポジションのセッター
	/// </summary>
	/// <param name="position"></param>
	Vector2 SetPosition(Vector2 translate);

	void Spawn(Vector2 translate,float size,unsigned int color);

	void Movement(unsigned int color);

	void ColorSubtract(unsigned int color);

	void Update(Vector2 translate, float size, unsigned int color);

#pragma region 描画
	void MakeWorleMatrix();
	void wvpVpMatrix(Matrix3x3 vpVpMatrix);
	void ParticleTransform();
	void ParticleQuad();
#pragma endregion 

	void DrawParticle(Matrix3x3 vpVpMatrix);
};

