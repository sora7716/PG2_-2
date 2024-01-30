#pragma once
#include "Score.h"

const int HP_NUM = 3;
const int SCORE_KILL = 4;

typedef struct HadObject {
	Vector2 position;
	Vector2 velocity;
	unsigned int color;
	bool isAlive;
}HadObject;

class Hud
{
private:
	HadObject hpBar_[HP_NUM];
	int HP_;
	int hpTexture_;

	HadObject killScore_[SCORE_KILL];
	int killScoreTexture_;
	int isHit_[SCORE_KILL];
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Hud();

	/// <summary>
	/// ダメージを食らったか
	/// </summary>
	void Damage(SceneType &scene);

	/// <summary>
	/// HPの描画
	/// </summary>
	void DrawHpBar();

	/// <summary>
	/// 倒したときのスコアのスポーン
	/// </summary>
	void ScoreSpawn(Score* score);

	/// <summary>
	/// 倒したときのスコアの動き
	/// </summary>
	void ScoreMove();

	void ScoreColorSubtract();

	void DrawScore();

	void ScoreUpdate(Score* score);

	void SetScoreIsAlive(bool isAlive);

};

