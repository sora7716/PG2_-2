#pragma once
#include "Struct.h"
#include "Camera.h"

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

class Enemy:public Camera
{

protected:

	void MakeWorldMatrix(EnemyObject enemy);

	void MakeWvpVp(EnemyObject enemy);

	void EnemyTransform(EnemyObject enemy);

	virtual void Update(EnemyObject enemy);
};

