#include "Player.h"


Player::Player() {

	//テクスチャ
	texture_ = Novice::LoadTexture("./resource/object/player.png");

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
		{},
		 0,
		{0,-1000},
	};

	//移動のスピード
	speed_ = { 5,5 };
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

	//シェイク
	srand((unsigned int)time(nullptr));
	shake.position = {};
	shake.range = 0;
	shake.isScale = false;
	shake.isShake = false;

	//包含
	for (int i = 0; i < SHOT_NUM; i++){
		for(int j=0;j<BULLET_NUM;j++){
			bullet_[i][j] = new Bullet;//弾
		}
	}

	color_ = WHITE;
	
	damageCoolTime_ = 0;

	isBestPlace_ = false;

	rotateTime_ = 0;

	collision_ = new Collision;//当たり判定
	particle_ = new Particle({ 0,-0.7f });//パーティクル
	hud_ = new Hud;

}

Player::~Player() {
	delete **bullet_;
	delete collision_;
	delete particle_;
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
		(int)screen_.leftTop.x     +shake.position.x, (int)screen_.leftTop.y    +shake.position.y,
		(int)screen_.leftBottom.x  +shake.position.x, (int)screen_.leftBottom.y +shake.position.y,
		(int)screen_.rightTop.x    +shake.position.x, (int)screen_.rightTop.y   +shake.position.y,
		(int)screen_.rightBottom.x +shake.position.x, (int)screen_.rightBottom.y+shake.position.y,
		0, 0, (int)PLAYER_SIZE, (int)PLAYER_SIZE, texture, color_);
	if (isBestPlace_) {
		hud_->DrawHpBar();
	}
}

void Player::PlayerMove(char *keys,Score *score) {
#pragma region 移動
	if (isBestPlace_) {
		if (cameraAffine_.theta <= 1.5f) {
			if (keys[DIK_A])
			{
				moveObject_.vector.x = -1;
			}
			else if (keys[DIK_D])
			{
				moveObject_.vector.x = 1;
			}
			else {
				moveObject_.vector.x = 0;
			}
			if (keys[DIK_W])
			{
				moveObject_.vector.y = 1;
			}
			else if (keys[DIK_S])
			{
				moveObject_.vector.y = -1;
			}
			else {
				moveObject_.vector.y = 0;
			}
			if (affine_.translate.x - PLAYER_SIZE / 2.0f <= -640) {
				affine_.translate.x = -640 + PLAYER_SIZE / 2.0f;
			}
			else if (affine_.translate.x + PLAYER_SIZE / 2.0f >= 640) {
				affine_.translate.x = 640 - PLAYER_SIZE / 2.0f;
			}
			if (affine_.translate.y >= -174) {
				affine_.translate.y = -174;
			}
			else if (affine_.translate.y <= -830) {
				affine_.translate.y = -830;
			}
		}
		else {
			if (keys[DIK_A])
			{
				moveObject_.vector.y = -1;
			}
			else if (keys[DIK_D])
			{
				moveObject_.vector.y = 1;
			}
			else {
				moveObject_.vector.y = 0;
			}
			if (keys[DIK_W])
			{
				moveObject_.vector.x = -1;
			}
			else if (keys[DIK_S])
			{
				moveObject_.vector.x = 1;
			}
			else {
				moveObject_.vector.x = 0;
			}
			if (affine_.translate.y >= 116) {
				affine_.translate.y = 116;
			}
			else if (affine_.translate.y <= -1100) {
				affine_.translate.y = -1100;
			}
			if (affine_.translate.x <= -330) {
				affine_.translate.x = -330;
			}
			else if (affine_.translate.x >= 330) {
				affine_.translate.x = 330;
			}
		}
		
	}
#pragma endregion

#pragma region ちょうどいいところ
	if (!isBestPlace_) {
		if (affine_.scale.x <= 1) {
			affine_.scale.x += scale_;
			affine_.scale.y += scale_;
		}
		else {
			isBestPlace_ = true;
		}
		if (affine_.translate.y <= -650) {
			affine_.translate.y += 3;
		}
		
	}
#pragma endregion

#pragma region 画面の回転
	if (Camera::isRotation&&affine_.theta<=-1.56f) {
		affine_.theta -= theta_;
	}
	if (!Camera::isRotation && affine_.theta >0.0f) {
		affine_.theta += theta_;
	}
	RotateTime();
	if (score->GetScore() >= 750) {
		if (!Camera::isRotation && rotateTime_ <= 0) {
			Camera::isRotation = true;
		}
		else if (Camera::isRotation && rotateTime_ <= 0) {
			Camera::isRotation = false;
		}
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
	affine_.translate.x += moveObject_.distance.x * speed_.x;
	affine_.translate.y += moveObject_.distance.y * speed_.y;
}

void Player::Transfer(char *keys,Score *score) {
	PlayerMove(keys,score);
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

void Player::PlayerDamage(Enemy*enemy, SceneType &scene) {
	DamageCooolTime();
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (collision_->Box({ affine_.translate.x + 16,affine_.translate.y - 32 }, enemy->GetEnemyBullet()->GetEnemyBulletObject()[i].rendering.affine.translate, PLAYER_SIZE / 2.0f, ENEMY_BULLET_SIZE) && enemy->GetEnemyBullet()->GetEnemyBulletObject()[i].isAlive && color_ == 0xFFFFFFFF) {
			shake.isShake = true;
			shake.isScale = true;
			IsDamage(scene);
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (collision_->Box(enemy->GetEnemyObject()[i].affine.translate, { affine_.translate.x + 16,affine_.translate.y - 32 }, ENEMY_SIZE, PLAYER_SIZE / 2.0f)&& enemy->GetEnemyObject()[i].isAlive && color_ == 0xFFFFFFFF) {
			shake.isShake = true;
			shake.isScale = true;
			IsDamage(scene);
			
		}
	}
	ShakeRange();
	if (shake.isShake&& damageCoolTime_>0) {
		shake.position = { rand() % shake.range - shake.range/2,rand() % shake.range - shake.range / 2 };
	}
}

void Player::Update(char* keys, char* preKeys,Enemy*enemy,SceneType &scene, Score* score) {
	//レンダリングパイプライン
	RenderingPipeline();

	//プレイヤーの動き
	Action(keys, preKeys, enemy, scene,score);

	CameraMove();//カメラの移動

	//後で消すやつ↓(テストプレイの時だけ使ってる)
	CameraTest();
	//後で消すやつ↑
	
	PlayerTransform();//ワールド座標に変換

}

void Player::BulletSpawn(char* keys, char* preKeys) {
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
			if (!bullet_[i][k]->GetBulletObject().isAlive) {
				bullet_[i][k]->IsShot(keys, preKeys, affine_.translate, i);
				break;
			}
		}
	}
}

void Player::BulletMove() {
	for (int i = 0; i < SHOT_NUM; i++) {
		for (int k = 0; k < BULLET_NUM; k++) {
			bullet_[i][k]->Attack();//攻撃
		}
	}
}

void Player::Action(char* keys, char* preKeys, Enemy* enemy, SceneType &scene, Score* score) {
	Transfer(keys,score);//移動
	if (isBestPlace_) {
		BulletSpawn(keys, preKeys);
		BulletMove();
		PlayerDamage(enemy, scene);
		particle_->Update({ affine_.translate.x-15,affine_.translate.y - 64, }, PLAYER_SIZE/2.0f * affine_.scale.x, 0xF6FFB8FF);
	}
}

void Player::IsDamage(SceneType &scene) {
	if (shake.isShake) {
		color_ = 0xFFFFFF55;
		hud_->Damage(scene);
		damageCoolTime_ = 180;
	}
}

void Player::DamageCooolTime() {
	if (damageCoolTime_ > 0) {
		damageCoolTime_--;
	}
	else {
		color_ = WHITE;
	}
}

void Player::RotateTime() {
	if (rotateTime_ > 0) {
		rotateTime_--;
	}
	else {
		rotateTime_=rand() % 300 + 600;
	}
}