#pragma once
#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Struct.h"
#include "Rendering.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Collision.h"

const int ENEMY_NUM = 8;//エネミーの数

const float ENEMY_SIZE = 32;//エネミーのピクセル数
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
	int direction_;
	int spawnNum_;
	int texture_;//テクスチャ1
	Collision* collision_;
	EnemyObject enemy_[ENEMY_NUM];//エネミーの変数
	float addTime_;
	float tempAddTime_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Enemy();

	/// <summary>
	/// enemyを追加するまでの時間
	/// </summary>
	void AddTime();

	/// <summary>
	/// enemyの数を増やす
	/// </summary>
	void EnemyAdd();

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

	int Direction();

	/// <summary>
	/// 仮想の関数
	/// </summary>
	virtual void EnemyDraw();

	/// <summary>
	/// 仮想の消去
	/// </summary>
	/// <param name="bullet"></param>
	/// <param name="translate"></param>
	virtual void Destroy(Bullet* bullet, Vector2 translate);

	virtual void IsDeath();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	virtual void Update(Matrix3x3 vpVpMatrix);

	/// <summary>
	/// enemy_のゲッター
	/// </summary>
	/// <returns></returns>
	EnemyObject* GetEnemyObject() { return enemy_; };
};

