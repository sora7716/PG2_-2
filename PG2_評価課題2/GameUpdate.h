#pragma once
#include "Player.h"
#include "EnemyDown.h"

const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ_title";

const int KYES_NUM = 256;
class GameUpdate
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
	///キーの取得 
	/// </summary>
	void GetHitKeyStateAll();
	
	/// <summary>
	/// preKeysの取得
	/// </summary>
	void Memcpy();

	void GameLoop();

};

