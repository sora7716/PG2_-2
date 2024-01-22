#pragma once
#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Struct.h"
#include "Rendering.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Collision.h"

const int ENEMY_NUM = 1;//エネミーの数

const int ENEMY_SIZE = 32;//エネミーのピクセル数
//エネミーに使う型
typedef struct EnemyObject {
	Vertex local;
	Affine affine;
	Speed shapes;
	Vector2 tempSpeed;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex screen;
	bool isAlive;
	bool isDeath;//当たったかどうのフラグ
}EnemyObject;

class Enemy :public Rendering
{
protected:
	int texture_;//テクスチャ1
	Collision* collision_;
	EnemyObject enemy_[ENEMY_NUM];//エネミーの変数
public:

	~Enemy();

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
	void EnemyTransform();

	/// <summary>
	/// 仮想の関数
	/// </summary>
	virtual void EnemyDraw();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	virtual void Update(Matrix3x3 vpVpMatrix, Bullet* bullet);

	/// <summary>
	/// enemy_のゲッター
	/// </summary>
	/// <returns></returns>
	EnemyObject* GetEnemyObject() { return enemy_; };
};

