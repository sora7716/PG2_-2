#pragma once
#include <stdlib.h>
#include <time.h>
#include "Camera.h"

const int BG_NUM = 300;
const int BG_SIZE = 8;
typedef struct BgObject {
	Renderer rendering;
	float speed;
	VectorInt random;
	unsigned int color;
	bool isAdd;
	bool isAlive;
}BgObject;

class Bg:public Rendering
{
private:
	BgObject bg_[BG_NUM];
	int texture_;
public:

	/// <summary>
	/// コンストラクター
	/// </summary>
	Bg();

	/// <summary>
	/// パーティクルの初期化
	/// </summary>
	void BgSpawn(unsigned int color, float speed);

	/// <summary>
	/// パーティクルを上に動かす
	/// </summary>
	void BgMove();

	/// <summary>
	/// パーティクルの色を薄くしたり濃くしたりする
	/// </summary>
	void BgColor(unsigned int color);

	/// <summary>
	/// レンダリングパイプライン↓
	/// </summary>
	void MakeWorldMatrix();

	void MakeWvpVp(Matrix3x3 vpVpMatrix);

	void BgTransform();
	/// <summary>
	/// レンダリングパイプライン↑
	/// </summary>
	
	/// <summary>
	/// 描画
	/// </summary>
	void DrawBg();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="vpVpMatrix"></param>
	void Update(Matrix3x3 vpVpMatrix, unsigned int color, float speed);
};

