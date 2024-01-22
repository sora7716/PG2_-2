#pragma once
#include <stdlib.h>
#include <time.h>
#include "Rendering.h"
#include "Bullet.h"

const int PARTICLE_NUM = 100;
const int PARTICLE_SIZE = 16;

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
	Particle();

	/// <summary>
	/// パーティクルのポジションのセッター
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(BulletObject bullet);

	/// <summary>
	/// パーティクルの初期化
	/// </summary>
	/// <param name="translate"></param>
	void Spawn(BulletObject bullet);

	/// <summary>
	/// パーティクルの挙動
	/// </summary>
	/// <param name="bullet"></param>
	void Effect(BulletObject bullet);

#pragma region 描画
	void MakeWorleMatrix();
	void wvpVpMatrix(Matrix3x3 vpVpMatrix);
	void ParticleTransform();
	void ParticleDraw();
#pragma endregion

	/// <summary>
	/// パーティクルの描画処理
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void ParticleDrawSprite(Matrix3x3 vpVpMatrix);

	void ParticleUpdate(BulletObject bullet);
};

