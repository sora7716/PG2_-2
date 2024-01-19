#pragma once
#include "Enemy.h"
class EnemyDown:public Enemy
{
public:
	EnemyDown();
	void EnemySpawn();
	void EnemyTranslate();
	void Destroy(char*keys,char*preKeys);
	void EnemySprite();
	void Update(char* keys, char* preKeys, Matrix3x3 vpVpMatrix)override;
};

