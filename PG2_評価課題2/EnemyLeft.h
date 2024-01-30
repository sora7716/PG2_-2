#pragma once
#include "Enemy.h"
class EnemyLeft:public Enemy
{
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	EnemyLeft();

	/// <summary>
	/// デストラクター
	/// </summary>
	~EnemyLeft();

	/// <summary>
    /// エネミーのスポーン
    /// </summary>
	void EnemySpawn();

	/// <summary>
	/// エネミーの移動
	/// </summary>
	void EnemyTranslate();

	/// <summary>
	/// エネミーの描画
	/// </summary>
	void EnemyDraw()override;

	/// <summary>
	/// エネミーの削除
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Destroy(Bullet* bullet, Vector2 translate)override;

	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	void IsDeath()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	void Update(Matrix3x3 vpVpMatrix,Vector2 player,int coolTime)override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void Drawing(Matrix3x3 vpVpMatrix,Score*score)override;
};

