#pragma once
#include "SceneSwitch.h"

const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ_title";

const int KYES_NUM = 256;
class GameUpdate:public Novice
{
private:

	char keys_[KYES_NUM];
	char preKeys_[KYES_NUM];

	SceneSwitch* sceneSwitch;
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
	/// ゲームループ
	/// </summary>
	void GameLoop();

};

