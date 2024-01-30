#pragma once
#include <Novice.h>
#include "Easing.h"

class FontMaterial
{
private:
	Easing* easing_;
protected:

	FontMaterial();

	~FontMaterial();
	/// <summary>
	/// フォントの描画
	/// </summary>
	/// <param name="font"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void FontDraw(Font font, float width, float height);

	/// <summary>
	/// フォントのイージング
	/// </summary>
	/// <param name="font"></param>
	void EasingFont(Font& font);

	/// <summary>
	/// フォトの初期化
	/// </summary>
	/// <param name="font"></param>
	/// <param name="isEasing"></param>
	/// <param name="isBack"></param>
	void Ini(Font& font, bool isEasing, bool isBack);
};

