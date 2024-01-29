#pragma once
#include "Player.h"
#include "EnemyDown.h"
#include "EnemyLeft.h"
#include "Bullet.h"
class MainScene
{
private:
	Player* player_;
	Enemy* enemyDown_;
	Enemy* enemyLeft_;
	bool isEnemyLeftMove_;
	/*int count_;*/
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	MainScene();

	/// <summary>
	/// デストラクター
	/// </summary>
	~MainScene();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void MainUpdating(char *keys,char *preKeys);

	/// <summary>
	/// 描画処理
	/// </summary>
	void MainDrawing();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void MainLoop(char* keys, char* preKeys);

	/// <summary>
	/// プレイヤーのクラスのゲッター
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() { return player_; };
};

