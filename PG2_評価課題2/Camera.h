#pragma once
#include <Novice.h>
#include "Rendering.h"

typedef struct Line {
	Vector2 begin;
	Vector2 end;
}Line;

typedef struct LeftAndSize {
	float left;
	float top;
	float width;
	float height;
}LeftAndSize;

typedef struct LinePosition {
	Line lateral;
	Line vert;
}LinePosition;

class Camera:public Rendering
{
protected:

#pragma region 定義しないといけない
	//カメラポジションの 拡縮・回転・移動
	Affine cameraAffine_;
	//切り取る範囲の左上と右上
	Point vertex_;
	//ラインの座標(ローカル座標)
	LinePosition local_ ;
	//カメラのスピード
	float speed_ ;
	float scale_ ;
	float theta_ ;
#pragma endregion

	//ラインの座標(スクリーン座標)
	LinePosition screen_;
	//左上とサイズ(HD:1280x720)
	LeftAndSize leftTop_;
	
	//カメラのマトリックス
	Matrix3x3 cameraMatrix_;
	//ビューマトリックス
	Matrix3x3 viewMatrix_;
	//正規化デバイス座標系
	Matrix3x3 orthoMatrix_;
	//ビューポートマトリックス
	Matrix3x3 viewportMatrix_;
	//vpVp
	Matrix3x3 vpVpMatrix_;

public:

	static bool isRotation;//画面の回転フラグ
	/// <summary>
	/// コンストラクター
	/// </summary>
	Camera();

	/// <summary>
	/// カメラのワールドマトリックスの作成
	/// </summary>
	void CameraMatrix();
	/// <summary>
	/// ビューマトリックスの作成
	/// </summary>
	void ViewMatrix();
	/// <summary>
	/// 正規化デバイスの作成
	/// </summary>
	void OrthoMatrix();
	/// <summary>
	/// ビューポートマトリックスの作成
	/// </summary>
	void ViewportMatrix();
	/// <summary>
	/// vpVpマトリックスの作成
	/// </summary>
	void vpVpMatrix();
	/// <summary>
	/// ラインをローカルからスクリーンに変換
	/// </summary>
	void CameraTransform();
	/// <summary>
	/// ラインの描画
	/// </summary>
	void CameraDraw();
	/// <summary>
	/// カメラの移動
	/// </summary>
	void CameraMove(char keys[]);

	/// <summary>
	/// レンダリングパイプラインをまとめた
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// カメラの更新処理
	/// </summary>
	/// <param name="keys"></param>
	void CameraTest();

	/// <summary>
	/// vpVpMatrixのゲッター
	/// </summary>
	/// <returns></returns>
	Matrix3x3 GetVpVpMatrix() { return vpVpMatrix_; };
};

