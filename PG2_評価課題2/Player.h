#pragma once
#include <stdlib.h>
#include <time.h>
#include "Camera.h"
#include "Bullet.h"
#include "Collision.h"
#include "EnemyDown.h"

const float PLAYER_SIZE = 32;

typedef struct MoveObject {
	Vector2 vector;
	Vector2 distance;
	float len;
}MoveObject;


class Player :public Camera
{
private:

#pragma region プレイヤーの定義しないといけないやつ
	//プレイヤーのローカル座標
	Vertex local_;
	//プレイヤー 拡縮・回転・移動
	Affine affine_;

	//移動のスピード
	float speed_ ;
	//拡縮
	float scale_ ;
	//角度
	float theta_ ;
#pragma endregion

	//スクリーン座標系に変化に使う
	Vertex screen_;
	
	//ワールドマトリックス
	Matrix3x3 worldMatrix_;
	//wvpVp
	Matrix3x3 wvpVpMatrix_;

	//単位ベクトルに使うやつ
	MoveObject moveObject_;

	//テクスチャ
	int texture_;

	//シェイク用のランド
	ShakeObject shake;

	//包含↓
	Bullet* bullet_;//弾
	Collision* collision_;
	//包含↑

public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Player();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Player();

	/// <summary>
	/// ワールドマトリックスの作成
	/// </summary>
	void  MakeWorldMatrix();

	/// <summary>
	/// wvpVpマトリックスの作成
	/// </summary>
	void MakeWvpVp();

	/// <summary>
	/// トランスフォーム
	/// </summary>
	void PlayerTransform();

	/// <summary>
	/// プレイヤーの描画
	/// </summary>
	void PlayerDraw(int texture);

	/// <summary>
	/// キー入力でプレイヤーを動かす
	/// </summary>
	/// <param name="keys"></param>
	void PlayerMove(char *keys);

#pragma region 単位ベクトル
	/// <summary>
	/// 単位ベクトルに変換↓
	/// </summary>
	void Distance();

	void Length();

	void Normalize();

	void PlayerTranslate();
	/// <summary>
	/// 単位ベクトルに変換↑
	/// </summary>
#pragma endregion

	/// <summary>
	/// プレイヤーの移動をまとめてる
	/// </summary>
	/// <param name="keys"></param>
	void Transfer(char* keys);

	/// <summary>
	/// レンダリングパイプラインをまとめている
	/// </summary>
	void RenderingPipeline();
	
	/// <summary>
	/// シェイクするときの幅と実行しているときの時間
	/// </summary>
	void ShakeRange();

	/// <summary>
	/// シェイク
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void PlayerShake(Enemy*enemy);

	/// <summary>
	/// 更新処理をまとめてる
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="texture"></param>
	void Update(char* keys, char* preKeys,Enemy*enemy);

		
	/// <summary>
	///		Bulletのインスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	Bullet* GetBullet() { return bullet_; };

	/// <summary>
	/// プレイヤーのテクスチャのゲッター
	/// </summary>
	/// <returns></returns>
	int GetPlayerTexture() { return texture_; };
	
	/// <summary>
	/// vpVpマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	Matrix3x3 GetVpVpMatrix() { return vpVpMatrix_; };
#pragma region テスト
	float SetPositionY() { return affine_.translate.y; };
#pragma endregion
};

