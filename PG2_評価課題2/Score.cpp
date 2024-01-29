#include "Score.h"

Score::Score(){
	score_ = { 0 };
	score_.image[0] = Novice::LoadTexture("./number/num0.png");
	score_.image[1] = Novice::LoadTexture("./number/num1.png");
	score_.image[2] = Novice::LoadTexture("./number/num2.png");
	score_.image[3] = Novice::LoadTexture("./number/num3.png");
	score_.image[4] = Novice::LoadTexture("./number/num4.png");
	score_.image[5] = Novice::LoadTexture("./number/num5.png");
	score_.image[6] = Novice::LoadTexture("./number/num6.png");
	score_.image[7] = Novice::LoadTexture("./number/num7.png");
	score_.image[8] = Novice::LoadTexture("./number/num8.png");
	score_.image[9] = Novice::LoadTexture("./number/num9.png");
	score_.position[0].x = 60;
	score_.position[1].x = 140;
	score_.position[2].x = 220;
	score_.position[3].x = 300;
	score_.position[4].x = 380;
	time_ = 0;
	addTime_ = 0;
}

void Score::Calculate() {
	score_.cpy= score_.score;
	if (score_.cpy == score_.score) {
		score_.eachScore[0] = score_.cpy / 10000;
		score_.cpy %= 10000;
	}
	if (score_.cpy == score_.score % 10000) {
		score_.eachScore[1] = score_.cpy / 1000;
		score_.cpy %= 1000;
	}
	if (score_.cpy == score_.score % 1000) {
		score_.eachScore[2] = score_.cpy / 100;
		score_.cpy %= 100;
	}
	if (score_.cpy == score_.score % 100) {
		score_.eachScore[3] = score_.cpy / 10;
		score_.cpy %= 10;
	}
	if (score_.cpy == score_.score%10) {
		score_.eachScore[4] = score_.cpy;
		score_.cpy %= 1;
	}
}

void Score::ScoreDraw(int x,int y) {
	for (int i = 0; i < DIGIT; i++) {
		Novice::DrawSprite((int)score_.position[i].x+x, (int)score_.position[i].y+y, score_.image[score_.eachScore[i]], 1.0f, 1.0f, 0.0f, WHITE);
	}
}

void Score::Update() {
	ScoreCount();
	Calculate();
	ScoreDraw(-70,600);
}

void Score::resultUpdate(int score) {
	score_.score = score;
	Calculate();
	ScoreDraw(0,0);
}

void Score::ScoreCount() {
	if (addTime_ > 0) {
		addTime_--;
	}
	else {
		Time();
		score_.score++;
	}
}

int Score::Time() {
	time_++;
	if (time_ < 1800) {
		addTime_ = 200;
	}
	else if (time_ < 216000) {
		addTime_ = 120;
	}
	else if (time_ < 216000*3) {
		addTime_ = 70;
	}
	else if (time_ < 216000 * 7) {
		addTime_ = 30;
	}
	else {
		addTime_ = 15;
	}
	return addTime_;
}

void Score::SetScore(int score) {
	score_.score = score;
}

void Score::AddScore(int add) {
	score_.score += add;
}