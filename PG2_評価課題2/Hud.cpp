#include "Hud.h"

Hud::Hud() {
	for (int i = 0; i < HP_NUM; i++) {
		hpBar_[i].color = WHITE;
		hpBar_[i].isAlive = false;
	}
	hpBar_[0].position = { 100,600 };
	hpBar_[1].position = { 200,600 };
	HP_ = HP_NUM;
	texture_ = Novice::LoadTexture("white1x1.png");
}

void Hud::Damage() {
	HP_ -= 1;
	hpBar_[HP_].color = RED;
}

void Hud::DrawHpBar() {
	for (int i = 0; i < HP_NUM; i++) {
		Novice::DrawSprite((int)hpBar_[i].position.x, (int)hpBar_[i].position.y, texture_, 64, 64, 0.0f, hpBar_[i].color);
	}
}