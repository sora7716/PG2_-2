#pragma once
#include "Bg.h"
#include "Camera.h"
#include "FontMaterial.h"

class EndScene:public FontMaterial
{
private:
	Camera* camera_;
	Bg* bg_;
	Font reTry_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	EndScene();

	/// <summary>
	/// デストラクター
	/// </summary>
	~EndScene();

	/// <summary>
	/// 描画(背景)
	/// </summary>
	void Draw();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Drawing();

	/// <summary>
	/// フォントの登場をまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Update(char* keys, char* preKeys, SceneType* scene);

	/// <summary>
	/// フラグ管理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void IsEasing(char* keys, char* preKeys);
};

