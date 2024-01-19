#include "GameUpdate.h"

GameUpdate::GameUpdate() {

	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	for (int i = 0; i < KYES_NUM; i++) {
		keys_[i]    = { 0 };
		preKeys_[i] = { 0 };
	}
	player_ = new Player;
	enemy_ = new EnemyDown;
}