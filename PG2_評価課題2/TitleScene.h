#pragma once
#include "Bg.h"
#include "Camera.h"
#include "Easing.h"

typedef struct Font {
	Vector2 position;
	Vector2 begin;
	Vector2 end;
	float frame;
	float endFrame;
	unsigned int color;
	bool isEasing;
	bool isBack;
	int image;
}Font;

class TitleScene:public Camera
{
private:
	Font title_;
	Font space_;
	Font explanation_;
	Bg* bg_;
	Easing* easing_;
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

	void FontDraw(Font font,float width,float height);

	/// <summary>
	/// フォントのイージング
	/// </summary>
	/// <param name="font"></param>
	void EasingFont(Font &font);

	/// <summary>
	/// フォントの登場をまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Update(char *keys,char *preKeys);

	/// <summary>
	/// フラグ管理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void IsEasing(char* keys, char* preKeys);

	void Ini(Font& font,bool isEasing,bool isBack);

	/// <summary>
	/// タイトルのフレームのゲッター
	/// </summary>
	/// <returns></returns>
	float GetTitleFrame() { return title_.frame; };

};

