#pragma once
#include "Struct.h"
#include <Novice.h>
#include "Rendering.h"

const int ENEMY_NUM = 1;//エネミーの数

const int ENEMY_SIZE = 32;
//エネミーに使う型
typedef struct EnemyObject {
	Vertex local;
	Affine affine;
	float speed;
	float theta;
	float scale;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex screen;
	bool isAlive;
}EnemyObject;

class Enemy:public Rendering
{
protected:
	EnemyObject enemy_[ENEMY_NUM];
	int texture_;
public:

	void MakeWorldMatrix();

	void MakeWvpVp(Matrix3x3 vpVpMatrix);

	void EnemyTransform(Matrix3x3 vpVpMatrix);

	virtual void Update(char* keys, char* preKeys, Matrix3x3 vpVpMatrix);
};

