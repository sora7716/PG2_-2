#include "Scene.h"

SceneManager::SceneManager() {
#pragma region タイトル

title_.position = { 340,-200 };
title_.begin = title_.position;
title_.end = { 340,150 };
title_.frame = 0;
title_.endFrame = 60;
title_.isEasing = true;
title_.isBack = false;
title_.image = Novice::LoadTexture("white1x1.png");
title_.color = WHITE;

space_.position = { 1300,480 };
space_.begin = space_.position;
space_.end = { 480,480 };
space_.frame = 0;
space_.endFrame = 60;
space_.isEasing = true;
space_.isBack = false;
space_.image = Novice::LoadTexture("white1x1.png");
space_.color = WHITE;

explanation_.position = { -1280,0 };
explanation_.begin = explanation_.position;
explanation_.end = { 0,0 };
explanation_.frame = 0;
explanation_.endFrame = 60;
explanation_.isEasing = true;
explanation_.isBack = false;
explanation_.image = Novice::LoadTexture("white1x1.png");
explanation_.color = RED;

startTime_ = 300;

#pragma endregion

#pragma region ゲーム

player_ = new Player;
enemyDown_ = new EnemyDown;
enemyLeft_ = new EnemyLeft;
isEnemyLeftMove_ = false;
time_ = 0;
bgSpeed_ = 0;

#pragma endregion

#pragma region エンド

reTry_.position = { 1300,480 };
reTry_.begin = reTry_.position;
reTry_.end = { 500,480 };
reTry_.frame = 0;
reTry_.endFrame = 60;
reTry_.isEasing = true;
reTry_.isBack = false;
reTry_.image = Novice::LoadTexture("white1x1.png");
reTry_.color = WHITE;

#pragma endregion

bg_ = new Bg;
camera_ = new Camera;
}

SceneManager::~SceneManager() {
	delete bg_;
	delete camera_;
	delete player_;
	delete enemyDown_;
	delete enemyLeft_;
}

#pragma region タイトル

void SceneManager::TitleDrawing() {
	camera_->CameraUpdate();
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
	bg_->Update(camera_->GetVpVpMatrix(), WHITE, 3);
	FontDraw(space_, 300, 100);
	FontDraw(title_, 600, 200);
	FontDraw(explanation_, 1280, 720);
}

void SceneManager::TitleLoop(char* keys, char* preKeys, SceneType* scene) {
	IsTitleEasing(keys, preKeys);
	EasingFont(title_);
	EasingFont(space_);
	if (space_.isBack && space_.frame >= space_.endFrame) {
		EasingFont(explanation_);
	}
	StarTime(scene);
	TitleDrawing();
}

void SceneManager::IsTitleEasing(char* keys, char* preKeys) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (!title_.isBack) {
			Ini(title_, false, true);
			Ini(space_, false, true);
		}
	}
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
		space_.color = 0xFFFFFF55;
	}
	else {
		space_.color = WHITE;
	}
}

void SceneManager::StarTime(SceneType* scene) {
	if (startTime_ > 0) {
		startTime_--;
	}
	else {
		*scene = game;
	}
}

#pragma endregion

#pragma region ゲーム

void SceneManager::MainUpdating(char* keys, char* preKeys, SceneType& scene, Score* score) {
	player_->Update(keys, preKeys, enemyDown_, scene, score);
	player_->Update(keys, preKeys, enemyLeft_, scene, score);
	if (player_->GetIsBestPlace()) {
		for (int i = 0; i < SHOT_NUM; i++) {
			for (int k = 0; k < BULLET_NUM; k++) {
				enemyLeft_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
				enemyDown_->Destroy(player_->GetBullet(i, k), { -2000,-2000 });
			}
		}
		enemyDown_->IsDeath();
		enemyLeft_->IsDeath();
		enemyDown_->Update(player_->GetVpVpMatrix(), player_->GetTranslate(), 120);
		if (score->GetScore() >= 500) {
			isEnemyLeftMove_ = true;
		}
		if (isEnemyLeftMove_) {
			enemyLeft_->Update(player_->GetVpVpMatrix(), player_->GetTranslate(), 60);

		}
	}
}

void SceneManager::MainDrawing(Score* score, unsigned int color) {
	bg_->Update(player_->GetVpVpMatrix(), color, (float)BgSpeed());
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
			player_->GetBullet(i, k)->BulletDrawSprite(player_->GetVpVpMatrix());
		}
	}
	player_->GetParticle()->DrawParticle(player_->GetVpVpMatrix());
	player_->PlayerDraw(player_->GetPlayerTexture());
	enemyDown_->Drawing(player_->GetVpVpMatrix(), score);
	enemyLeft_->Drawing(player_->GetVpVpMatrix(), score);
}

void SceneManager::MainLoop(char* keys, char* preKeys, SceneType& scene, Score* score) {
	MainUpdating(keys, preKeys, scene, score);//更新処理
	MainDrawing(score, WHITE); //描画処理
}

int SceneManager::BgSpeed() {
	time_++;
	if (time_ < 1800) {
		bgSpeed_ = 3;
	}
	else if (time_ < 216000) {
		bgSpeed_ = 6;
	}
	else if (time_ < 216000 * 3) {
		bgSpeed_ = 9;
	}
	else if (time_ < 216000 * 7) {
		bgSpeed_ = 10;
	}
	else {
		bgSpeed_ = 12;
	}
	return bgSpeed_;
}

#pragma endregion

#pragma region エンド

void SceneManager::EndBackgrownd() {
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0.0f, 0x303030FF, kFillModeSolid);
}

void SceneManager::EndDrawing() {
	EndBackgrownd();
	camera_->CameraUpdate();
	bg_->Update(camera_->GetVpVpMatrix(), RED, 3);
	bg_->DrawBg();
	FontDraw(reTry_, 300, 100);
}

void SceneManager::EndLoop(char* keys, char* preKeys, SceneType* scene) {
	IsEndEasing(keys, preKeys);
	EasingFont(reTry_);
	if (reTry_.isBack && reTry_.frame >= reTry_.endFrame) {
		*scene = title;
	}
	EndDrawing();
}

void SceneManager::IsEndEasing(char* keys, char* preKeys) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (!reTry_.isBack) {
			Ini(reTry_, false, true);
		}
	}
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
		reTry_.color = 0xFFFFFF55;
	}
	else {
		reTry_.color = WHITE;
	}
}

#pragma endregion