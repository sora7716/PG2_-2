#pragma once
#include "Bg.h"
#include "Camera.h"
#include "FontMaterial.h"
#include "Player.h"
#include "EnemyDown.h"
#include "EnemyLeft.h"
#include "Bullet.h"

class SceneManager:FontMaterial
{
private:

	//クリック音
	int clickSE_;

	//タイトル
	Font title_;
	Font space_;
	Font explanation_;
	Camera* camera_;
	int startTime_;

	//ゲームシーン
	Player* player_;
	Enemy* enemyDown_;
	Enemy* enemyLeft_;
	bool isEnemyLeftMove_;
	int time_;
	int bgSpeed_;

	//エンド
	Font reTry_;

	//背景のパーティクル
	Bg* bg_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクター
	/// </summary>
	~SceneManager();

#pragma region タイトル
	/// <summary>
	/// 描画
	/// </summary>
	void TitleDrawing();

	/// <summary>
	/// フォントの登場をまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void TitleLoop(char* keys, char* preKeys, SceneType* scene);

	/// <summary>
	/// フラグ管理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void IsTitleEasing(char* keys, char* preKeys);

	/// <summary>
	/// タイトルのフレームのゲッター
	/// </summary>
	/// <returns></returns>
	float GetTitleFrame() { return title_.frame; };

	/// <summary>
	/// 始まるまでのタイマー
	/// </summary>
	/// <param name="scene"></param>
	void StartTime(SceneType* scene);

#pragma endregion

#pragma region ゲーム

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void MainUpdating(char* keys, char* preKeys, SceneType& scene, Score* score);

	/// <summary>
	/// 描画処理
	/// </summary>
	void MainDrawing(Score* score, unsigned int color);

	/// <summary>
	/// ゲームループ
	/// </summary>
	void MainLoop(char* keys, char* preKeys, SceneType& scene, Score* score);

	int BgSpeed();

	/// <summary>
	/// プレイヤーのクラスのゲッター
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() { return player_; };

#pragma endregion

#pragma region エンド
	/// <summary>
	/// 描画(背景)
	/// </summary>
	void EndBackgrownd();

	/// <summary>
	/// 描画処理
	/// </summary>
	void EndDrawing();

	/// <summary>
	/// フォントの登場をまとめた
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void EndLoop(char* keys, char* preKeys, SceneType* scene);

	/// <summary>
	/// フラグ管理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void IsEndEasing(char* keys, char* preKeys);
#pragma endregion
};

