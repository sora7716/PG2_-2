#pragma once
#include "Particle.h"

const int ENEMY_BULLET_NUM = 10;
const int ENEMY_BULLET_SIZE = 16;

typedef struct EnemyBulletObject {
	Renderer rendering;
	MoveObject meters;
	Vector2 velocity;
	float rotateSpeed;
	bool isAlive;
}EnemyBulletObject;

class EnemyBullet :public Rendering
{
private:
	EnemyBulletObject enemyBullet_[ENEMY_BULLET_NUM];
	int texture_;
	int coolTime_;
	Particle* particle_;

public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	EnemyBullet();

	/// <summary>
	/// デストラクター
	/// </summary>
	~EnemyBullet();

	/// <summary>
	/// バレットのポジションを初期化
	/// </summary>
	/// <param name="translate"></param>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	Vector2 EnemyPosition(Vector2 translate);

	/// <summary>
	/// プレイヤーのポジション
	/// </summary>
	/// <param name="translate"></param>
	Vector2 PlayerPosition(Vector2 translate);

	/// <summary>
	/// プレイヤーと弾との距離
	/// </summary>
	void Distance(Vector2 translate);

	/// <summary>
	/// プレイヤーと弾との距離の長さ
	/// </summary>
	void Length();

	/// <summary>
	/// プレイヤーの位置のベクトル
	/// </summary>
	void Normalize();

	void ShotTime(int coolTime);

	/// <summary>
	/// バレットのスポーン
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void BulletSpawn(Vector2 player, Vector2 enemy,int coolTime);

	/// <summary>
	/// バレットの移動
	/// </summary>
	void BulletMove();

#pragma region 描画
	void MakeWorleMatrix();
	void wvpVpMatrix(Matrix3x3 vpVpMatrix);
	void BulletTransform();
	void BulletDraw();
#pragma endregion

	/// <summary>
	/// バレットの更新処理をまとめた
	/// </summary>
	void EnemyAttack(Vector2 player, Vector2 tanslate, int coolTime);

	/// <summary>
	/// バレットの描画処理をまとめた
	/// </summary>
	void BulletDrawing(Matrix3x3 vpVpMatrix);

	/// <summary>
	/// バレットのゲッター
	/// </summary>
	EnemyBulletObject* GetEnemyBulletObject() { return enemyBullet_; };
};

