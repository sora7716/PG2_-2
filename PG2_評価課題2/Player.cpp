﻿#include "Player.h"


Player::Player() {
#pragma region 定義しないといけない
	//プレイヤーのローカル座標
	local_={
		{ -PLAYER_SIZE/2.0f ,-PLAYER_SIZE/2.0f  },
		{ -PLAYER_SIZE/2.0f , PLAYER_SIZE/2.0f  },
		{  PLAYER_SIZE/2.0f ,-PLAYER_SIZE/2.0f  },
		{  PLAYER_SIZE/2.0f , PLAYER_SIZE/2.0f  },
	};
	//プレイヤー 拡縮・回転・移動
	affine_={
		{1,1},
		 0,
		{},
	};

	//移動のスピード
    speed_ = 5;
	//拡縮
	scale_ = 1.0f / 100.0f;
	//角度
	theta_ = 1.0f / 100.0f;
#pragma endregion

	moveObject_ = {};

	//スクリーン座標系に変化に使う
	screen_={};

	//ワールドマトリックス
	worldMatrix_ = {};
	//wvpVp
	wvpVpMatrix_ = {};

	//テクスチャ
	texture_ = Novice::LoadTexture("white1x1.png");

	//シェイク
	srand((unsigned int)time(nullptr));
	shake.position = {};
	shake.range = 0;
	shake.isScale = false;
	shake.isShake = false;

	//包含
	bullet_ = new Bullet;//弾
	collision_ = new Collision;//当たり判定
}

Player::~Player() {
	delete bullet_;
	delete collision_;
}

void Player::MakeWorldMatrix() {
	worldMatrix_ = MakeAffineMatrix(affine_);
}

void Player::MakeWvpVp() {
  wvpVpMatrix_ = Multiply(worldMatrix_, vpVpMatrix_);
}

void Player::PlayerTransform() {
	screen_.leftTop     = TransForm(local_.leftTop,    wvpVpMatrix_);
	screen_.leftBottom  = TransForm(local_.leftBottom, wvpVpMatrix_);
	screen_.rightTop    = TransForm(local_.rightTop,   wvpVpMatrix_);
	screen_.rightBottom = TransForm(local_.rightBottom,wvpVpMatrix_);
}

void Player::PlayerDraw(int texture) {
	Novice::DrawQuad(
		(int)screen_.leftTop.x     + shake.position.x,     (int)screen_.leftTop.y     + shake.position.y,
		(int)screen_.leftBottom.x  + shake.position.x,     (int)screen_.leftBottom.y  + shake.position.y,
		(int)screen_.rightTop.x    + shake.position.x,     (int)screen_.rightTop.y    + shake.position.y,
		(int)screen_.rightBottom.x + shake.position.x,     (int)screen_.rightBottom.y + shake.position.y,
		0, 0, 1, 1, texture, WHITE);
}

void Player::PlayerMove(char *keys) {
#pragma region 移動
	if (keys[DIK_A])
	{
		//affine_.translate.x -= speed_;
		moveObject_.vector.x = -1;
	}
	else if (keys[DIK_D])
	{
		//affine_.translate.x += speed_;
		moveObject_.vector.x = 1;
	}
	else {
		moveObject_.vector.x = 0;
	}
	if (keys[DIK_W])
	{
		//affine_.translate.y += speed_;
		moveObject_.vector.y = 1;
	}
	else if (keys[DIK_S])
	{
		//affine_.translate.y -= speed_;
		moveObject_.vector.y = -1;
	}
	else {
		moveObject_.vector.y = 0;
	}
#pragma endregion

#pragma region 拡縮
	if (keys[DIK_E] && keys[DIK_LSHIFT]) {
		if (affine_.scale.x > 0 || affine_.scale.y > 0) {
			affine_.scale.x -= scale_;
			affine_.scale.y -= scale_;
		}
	}
	if (keys[DIK_Q] && keys[DIK_LSHIFT]) {
		affine_.scale.x += scale_;
		affine_.scale.y += scale_;
	}
#pragma endregion

#pragma region 回転
	if (keys[DIK_C] && keys[DIK_LSHIFT]) {
		affine_.theta -= theta_;
	}
	if (keys[DIK_Z] && keys[DIK_LSHIFT]) {
		affine_.theta += theta_;
	}
#pragma endregion
}

void Player::Distance() {
	moveObject_.distance.x = powf(moveObject_.vector.x, 2);
	moveObject_.distance.y = powf(moveObject_.vector.y, 2);
}

void Player::Length() {
	moveObject_.len = sqrtf(moveObject_.distance.x + moveObject_.distance.y);
}

void Player::Normalize() {
	if (moveObject_.len != 0) {
		moveObject_.distance.x = moveObject_.vector.x / moveObject_.len;
		moveObject_.distance.y = moveObject_.vector.y / moveObject_.len;
	}
}

void Player::PlayerTranslate() {
	affine_.translate.x += moveObject_.distance.x * speed_;
	affine_.translate.y += moveObject_.distance.y * speed_;
}

void Player::Transfer(char *keys) {
	PlayerMove(keys);
	Distance();
	Length();
	Normalize();
	PlayerTranslate();
}

void Player::RenderingPipeline() {
	//アフィン変換↓
	MakeWorldMatrix();//ワールドマトリックスの作成
	CameraMatrix();   //カメラマトリックスの作成
	//アフィン変換↑

	ViewMatrix();//逆行列を使ってviewマトリックスの作成
	OrthoMatrix();//正射影行列の作成
	ViewportMatrix();//viewportマトリックスの作成
	vpVpMatrix();//ワールドマトリックス以外をかけている
	MakeWvpVp();//最後にワールドマトリックスをかけている
}

void Player::ShakeRange() {
	if (shake.isScale) {
		if (shake.range <= 25) {
			shake.range++;
		}
		else {
			shake.isScale = false;
		}
	}
	else {
		if (shake.range > 1) {
			shake.range--;
		}
		else {
			shake.isShake = false;
			shake.position = {};
		}
	}
}

void Player::PlayerShake(Enemy*enemy) {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (collision_->Box(enemy->GetEnemyObject()[i].affine.translate,affine_.translate,ENEMY_SIZE, PLAYER_SIZE)) {
			shake.isShake = true;
			shake.isScale = true;
		}
	}
	ShakeRange();
	if (shake.isShake) {
		shake.position = { rand() % shake.range - shake.range/2,rand() % shake.range - shake.range / 2 };
	}
	Novice::ScreenPrintf(0, 0, "%d", shake.range);
}

void Player::Update(char* keys, char* preKeys,Enemy*enemy) {

#pragma region プレイヤー
	Transfer(keys);//移動
	bullet_->Attack(keys, preKeys, affine_.translate,vpVpMatrix_);//攻撃
	PlayerShake(enemy);
#pragma endregion 

	CameraMove(keys);//カメラの移動

	RenderingPipeline();

	//後で消すやつ↓
	CameraTest();
	//後で消すやつ↑
	
	PlayerTransform();//ワールド座標に変換
}
