#pragma once
#include "Scene.h"
#include "Score.h"
class SceneSwitch
{
private:
	SceneType scene_;
	SceneType preScene_;
	SceneManager* sceneManager;
	Score* score_[2];
	int BGM_[3];
	int soundHandle_[3];
public:
	
	/// <summary>
	/// コンストラクター
	/// </summary>
	SceneSwitch();

	/// <summary>
	/// デストラクター
	/// </summary>
	~SceneSwitch();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	void Scene(char *keys,char *preKeys);

	/// <summary>
	/// 更新処理の初期化
	/// </summary>
	void Ini();

	/// <summary>
	/// 上記の関数をまとめた
	/// </summary>
	void Update(char* keys, char* prekeys);

};

