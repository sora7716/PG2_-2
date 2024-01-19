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

	/// <summary>
	/// エネミーの削除
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Destroy(char*keys,char*preKeys);

	/// <summary>
	/// エネミーの描画
	/// </summary>
	void EnemySprite();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="vpVpMatrix"></param>
	void Update(char* keys, char* preKeys, Matrix3x3 vpVpMatrix)override;
};

