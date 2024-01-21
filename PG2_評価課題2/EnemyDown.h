#pragma once
#include "Enemy.h"
class EnemyDown:public Enemy
{
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	EnemyDown();
	
	/// <summary>
	/// エネミーのスポーン
	/// </summary>
	void EnemySpawn();

	/// <summary>
	/// エネミーの移動
	/// </summary>
	void EnemyTranslate();

	int Direction();

	/// <summary>
	/// エネミーの描画
	/// </summary>
	void EnemyDraw()override;

	/// <summary>
	/// エネミーの削除
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Destroy(Bullet* bullet);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	void Update(Matrix3x3 vpVpMatrix,Bullet*bullet)override;
};

