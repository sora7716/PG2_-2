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
	/// �R���X�g���N�^�[
	/// </summary>
	Particle();

	/// <summary>
	/// �p�[�e�B�N���̃|�W�V�����̃Z�b�^�[
	/// </summary>
	/// <param name="position"></param>
	Vector2 SetPosition(Vector2 translate);

	void Spawn(Vector2 translate);

	void Effect
};

