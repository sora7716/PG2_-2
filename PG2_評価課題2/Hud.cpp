#include "Hud.h"

Hud::Hud() {
	for (int i = 0; i < HP_NUM; i++) {
		hpBar_[i].color = WHITE;
		hpBar_[i].isAlive = false;
		hpBar_[i].velocity = {};
	}
	hpBar_[0].position = { 420,480 };
	hpBar_[1].position = { 420,512 };
	hpBar_[2].position = { 420,544 };
	HP_ = HP_NUM;
	hpTexture_ = Novice::LoadTexture("white1x1.png");
	for (int i = 0; i < SCORE_KILL; i++) {
		killScore_[i].position = { 10,500 };
		killScore_[i].velocity={};
		killScore_[i].color = WHITE;
		killScore_[i].isAlive = false;
		isHit_[i] = false;
	}
	killScoreTexture_ = Novice::LoadTexture("white1x1.png");
	
}

void Hud::Damage(Scene &scene) {
	HP_ -= 1;
	hpBar_[HP_].color = RED;
	if (hpBar_[0].color == RED) {
		scene = end;
	}
}

void Hud::DrawHpBar() {
	for (int i = 0; i < HP_NUM; i++) {
		Novice::DrawSprite((int)hpBar_[i].position.x, (int)hpBar_[i].position.y+132, hpTexture_, 32, 32, 0.0f, hpBar_[i].color);
	}
}

void Hud::ScoreSpawn(Score*score) {
    for (int i = 0; i < SCORE_KILL; i++) {
    	if (isHit_[i]) {
    		if (!killScore_[i].isAlive) {
    			killScore_[i].position = { 10,600 };
    			killScore_[i].velocity = { 0,-3 };
    			killScore_[i].color = WHITE;
    			killScore_[i].isAlive = true;
				score->AddScore(40);
    			break;
    		}
    	}
    }
}

void Hud::ScoreMove() {
	for (int i = 0; i < SCORE_KILL; i++) {
		if (killScore_[i].isAlive) {
			killScore_[i].position.y += killScore_[i].velocity.y;
			if (killScore_[i].position.y <= 550) {
				killScore_[i].position.y = 550;
			    ScoreColorSubtract();
			}
		}
	}
}

void Hud::ScoreColorSubtract() {
	for (int i = 0; i < SCORE_KILL; i++) {
		if (killScore_[i].color > 0xFFFFFF00) {
			killScore_[i].color -= 0x00000003;
		}
		else {
			killScore_[i].isAlive = false;
			isHit_[i] = false;
		}
	}
}

void Hud::DrawScore() {
	for (int i = 0; i < SCORE_KILL; i++) {
		if (killScore_[i].isAlive) {
			Novice::DrawSprite((int)killScore_[i].position.x, (int)killScore_[i].position.y,killScoreTexture_,128, 32, 0.0f, killScore_[i].color);
		}
	}
}

void Hud::ScoreUpdate(Score*score) {
	ScoreSpawn(score);
	ScoreMove();
}

void Hud::SetScoreIsAlive(bool isAlive) {
	for (int i = 0; i < SCORE_KILL; i++) {
		isHit_[i] = isAlive;
		if (isHit_[i]) {
			break;
		}
	}
}