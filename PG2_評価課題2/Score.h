#pragma once
#include <Novice.h>
#include "Struct.h"
const int NUM = 10;
const int DIGIT = 5;
typedef struct ScoreObject {
	int score;
	int cpy;
	int eachScore[DIGIT];
	Vector2 position[DIGIT];
	int image[NUM];
}ScoreObject;

class Score
{
private:
	ScoreObject score_;
	int time_;
	int addTime_;
public:

	/// <summary>
	/// コンストラクター
	/// </summary>
	Score();

	/// <summary>
	/// 桁の計算
	/// </summary>
	void Calculate();

	/// <summary>
	/// スコアの表示
	/// </summary>
	void ScoreDraw(int x, int y);

	/// <summary>
	/// すべてをまとめた
	/// </summary>
	void Update();

	/// <summary>
	/// 最後の測定用
	/// </summary>
	/// <param name="score"></param>
	void resultUpdate(int score);

	/// <summary>
	/// スコアの偏移
	/// </summary>
	void ScoreCount();

	/// <summary>
	/// 時間によってスコアの進み方を変える
	/// </summary>
	/// <returns></returns>
	int Time();

	/// <summary>
	/// スコアのゲッター
	/// </summary>
	/// <returns></returns>
	int GetScore() { return score_.score; };

	/// <summary>
	/// スコアのセッター
	/// </summary>
	void SetScore(int score);

	/// <summary>
	/// スコアの加算
	/// </summary>
	/// <param name="add"></param>
	void AddScore(int add);

};

