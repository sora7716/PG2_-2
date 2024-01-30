#pragma once
#include "Player.h"
#include "EnemyDown.h"
#include "EnemyLeft.h"
#include "Bullet.h"
#include "Bg.h"
class MainScene
{
private:
	Player* player_;
	Enemy* enemyDown_;
	Enemy* enemyLeft_;
	Bg* bg_;
	bool isEnemyLeftMove_;
	int time_;
	int bgSpeed_;
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
	void MainUpdating(char *keys,char *preKeys, Scene &scene, Score* score);

	/// <summary>
	/// 描画処理
	/// </summary>
	void MainDrawing(Score* score, unsigned int color);

	/// <summary>
	/// ゲームループ
	/// </summary>
	void MainLoop(char* keys, char* preKeys, Scene &scene, Score* score);

	int BgSpeed();

	/// <summary>
	/// プレイヤーのクラスのゲッター
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() { return player_; };
};

