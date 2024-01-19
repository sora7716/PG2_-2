#pragma once
#include "Struct.h"
#include <Novice.h>
#include "Rendering.h"

const int ENEMY_NUM = 1;//エネミーの数

const int ENEMY_SIZE = 32;//エネミーのピクセル数
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
	EnemyObject enemy_[ENEMY_NUM];//エネミーの変数
	int texture_;//テクスチャ1
public:
	/// <summary>
	/// ワールドマトリックスの作成
	/// </summary>
	void MakeWorldMatrix();

	/// <summary>
	/// wvpVpマトリックスの作成
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void MakeWvpVp(Matrix3x3 vpVpMatrix);

	/// <summary>
	/// スクリーン座標に変換
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void EnemyTransform(Matrix3x3 vpVpMatrix);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	virtual void Update(char* keys, char* preKeys, Matrix3x3 vpVpMatrix);
};

