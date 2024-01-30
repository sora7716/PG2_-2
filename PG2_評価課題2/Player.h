#pragma once
#include <stdlib.h>
#include <time.h>
#include "Camera.h"
#include "Bullet.h"
#include "Collision.h"
#include "EnemyDown.h"
#include "Particle.h"
#include "Hud.h"

const float PLAYER_SIZE = 64;

class Player :public Camera
{
private:

#pragma region プレイヤーの定義しないといけないやつ
	//プレイヤーのローカル座標
	Vertex local_;
	//プレイヤー 拡縮・回転・移動
	Affine affine_;

	//移動のスピード
	Vector2 speed_ ;
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

	//プレイヤーのカラー
	unsigned int color_;

	//シェイク用のランド
	ShakeObject shake;

	//無敵時間
	int damageCoolTime_;
	
	//プレイヤーが最初の位置についたか
	bool isBestPlace_;

	//回転のタイマー
	int rotateTime_;

	//包含↓
	Bullet* bullet_[SHOT_NUM][BULLET_NUM];//弾
	Collision* collision_;
	Particle* particle_;
	Hud* hud_;
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
	void PlayerMove(char *keys,Score* score);

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
	void Transfer(char* keys,Score* score);

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
	void PlayerDamage(Enemy*enemy, SceneType &scene);

	/// <summary>
	/// 更新処理をまとめてる
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="texture"></param>
	void Update(char* keys, char* preKeys,Enemy*enemy, SceneType &scene, Score* score);

	/// <summary>
	/// バレットの召喚
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void BulletSpawn(char* keys, char* preKeys);

	/// <summary>
	/// バレットの動き
	/// </summary>
	void BulletMove();

	/// <summary>
	/// プレイヤーの動きをまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="enemy"></param>
	void Action(char* keys, char* preKeys, Enemy* enemy, SceneType &scene,Score* score);
		
	/// <summary>
	/// ダメージを食らった後の処理
	/// </summary>
	/// <param name="scene"></param>
	void IsDamage(SceneType &scene);

	/// <summary>
	/// 無敵時間
	/// </summary>
	void DamageCooolTime();

	/// <summary>
	///		Bulletのインスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	Bullet* GetBullet(int i,int k) { return bullet_[i][k]; };

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

	/// <summary>
	/// パーティクルのゲッター
	/// </summary>
	/// <returns></returns>
	Particle* GetParticle() { return particle_; };

	/// <summary>
	/// トランスレートのゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetTranslate() { return affine_.translate; };

	/// <summary>
	/// プレイヤーのスケールのゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetScale() { return affine_.scale; };

	/// <summary>
	/// プレイヤーがちょうどいい位置に来たかどうかのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetIsBestPlace() { return isBestPlace_; };

	void RotateTime();
#pragma region テスト
	//float SetPositionY() { return affine_.translate.y; };
#pragma endregion
};

