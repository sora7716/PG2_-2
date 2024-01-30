#pragma once
#include "Bg.h"
#include "Camera.h"
#include "FontMaterial.h"

class TitleScene:public FontMaterial
{
private:
	Font title_;
	Font space_;
	Font explanation_;
	Bg* bg_;
	Camera* camera_;
	int startTime_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクター
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 描画
	/// </summary>
	void Drawing();

	/// <summary>
	/// フォントの登場をまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Update(char *keys,char *preKeys, SceneType* scene);

	/// <summary>
	/// フラグ管理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void IsEasing(char* keys, char* preKeys);

	/// <summary>
	/// タイトルのフレームのゲッター
	/// </summary>
	/// <returns></returns>
	float GetTitleFrame() { return title_.frame; };


	void StarTime(SceneType* scene);
};

