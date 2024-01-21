#pragma once
#include "Player.h"
#include "EnemyDown.h"
#include "Bullet.h"

const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ_title";

const int KYES_NUM = 256;
class GameUpdate:public Novice
{
private:

	char keys_[KYES_NUM];
	char preKeys_[KYES_NUM];

	Player* player_;
	Enemy* enemy_;

public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	GameUpdate();

	/// <summary>
	/// デストラクター
	/// </summary>
	~GameUpdate();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void MainUpdating();
	
	/// <summary>
	/// 描画処理
	/// </summary>
	void MainDrawing();


	void MainLoop();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void GameLoop();

};

