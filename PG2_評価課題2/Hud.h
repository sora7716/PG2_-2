#pragma once
#include <Novice.h>
#include "Struct.h"

const int HP_NUM = 2;

typedef struct HpObject {
	Vector2 position;
	unsigned int color;
	bool isAlive;
}HpObject;

class Hud
{
private:
	HpObject hpBar_[HP_NUM];
	int HP_;
	int texture_;
public:
	Hud();

	void Damage();

	void DrawHpBar();

};

