#pragma once
#include <Novice.h>
#include "Rendering.h"
#include "Particle.h"

const int SHOT_NUM = 3;
const int BULLET_NUM  = 100;
const int BULLET_SIZE = 16;

typedef struct BulletObject {
	Vertex local;
	Affine affine;
	float speed;
	float rotation;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex screen;
	bool isAlive;
}BulletObject;

class Bullet:public Rendering 
{
private:
	int texture_;
	BulletObject bullet_;
	int shotTime_;
	Particle* particle_;
public:
	/// <summary>
	/// コンストラクター
	/// </summary>
	Bullet();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Bullet();

	/// <summary>
	/// セッターbulletのtranslate
	/// </summary>
	/// <param name="translate"></param>
	Vector2 PlayerTranslate(Vector2 translate);
	
	void ShotTime();

	/// <summary>
	/// 攻撃をしたかどうか
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="translate"></param>
	void IsShot(char *keys,char *preKeys, Vector2 translate, int i);

	/// <summary>
	/// 弾の動き
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="translate"></param>
	void Attack();
	
#pragma region 描画
	void MakeWorleMatrix();
	void wvpVpMatrix(Matrix3x3 vpVpMatrix);
	void BulletTransform();
	void BulletDraw(Matrix3x3 vpVpMatrix);
#pragma endregion

	/// <summary>
	/// 描画に必要な処理をすべてまとめた
	/// </summary>
	void BulletDrawSprite(Matrix3x3 vpVpMatrix);

	/// <summary>
	/// bulletのゲッター
	/// </summary>
	/// <returns></returns>
	BulletObject GetBulletObject() { return bullet_; };

	void SetIsAlive(bool isAlive);

	void SetTranslate(Vector2 translate);
};

