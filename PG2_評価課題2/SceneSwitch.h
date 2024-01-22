#pragma once
#include "TitleScene.h"
#include "MainScene.h"
enum Scene {
	title,
	game,
	end,
};
class SceneSwitch
{
private:
	Scene scene;
	Scene preScene;

	TitleScene* titleScene;
	MainScene*  mainScene;
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
	/// キー入力することでのシーン切り替え
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Movement(char* keys, char* preKeys);

	/// <summary>
	/// 更新処理の初期化
	/// </summary>
	void Ini();

	/// <summary>
	/// 上記の関数をまとめた
	/// </summary>
	void Update(char* keys, char* prekeys);
};

