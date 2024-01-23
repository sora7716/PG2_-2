#include "Camera.h"

Camera::Camera() {
	affine_ = {
	   {1.0f,1.0f},
		0,
	   {0,0},
	};
	//画面の切り取る範囲
	vertex_ = {
		 -SCREEN_WIDTH /2.0f,
		  SCREEN_HEIGHT/2.0f,
		  SCREEN_WIDTH /2.0f,
		 -SCREEN_HEIGHT/2.0F,
	};

#pragma region カメラの線を出すときに使う
	local_ = {
		{
		 { -10000,0 },
		 {  10000,0 },
		},
		{
		 { 0, -10000},
		 { 0,  10000},
		},
	};
#pragma endregion
	
	//SRTに加算するスピード
	speed_ = 5.0f;
	scale_ = 1.0f / 100.0f;
	theta_ = 1.0f / 100.0f;

	screen_ = {};//最後の結果を格納する変数

	leftTop_ = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//画面のサイズ

#pragma region 変換結果を格納するマトリックス
	cameraMatrix_ = {};

	viewMatrix_ = {};

	orthoMatrix_ = {};

	viewportMatrix_ = {};

	vpVpMatrix_ = {};
#pragma endregion

}

/// <summary>
/// カメラのワールドマトリックスの作成
/// </summary>
void Camera::CameraMatrix() {
	cameraMatrix_ = MakeAffineMatrix(affine_);
}

/// <summary>
/// ビューマトリックスの作成
/// </summary>
void Camera::ViewMatrix() {
	viewMatrix_ = Inverse(cameraMatrix_);
}

/// <summary>
/// 正規化デバイスマトリックスの作成
/// </summary>
void Camera::OrthoMatrix() {
	orthoMatrix_ = MakeOrthographicMatrix(vertex_);
}

/// <summary>
/// ビューポートマトリックスの作成
/// </summary>
void Camera::ViewportMatrix() {
	viewportMatrix_ = MakeViewportMatrix(leftTop_.left, leftTop_.top, leftTop_.width, leftTop_.height);
}

/// <summary>
/// vs = vpVp
/// </summary>
void Camera::vpVpMatrix() {
	/*ワールド座標系*/
	vpVpMatrix_ = Multiply(viewMatrix_,orthoMatrix_);
	/*ビュー座標系*/
	vpVpMatrix_ = Multiply(vpVpMatrix_,viewportMatrix_);
}
/// <summary>
/// ラインをローカルからスクリーンに変換
/// </summary>
void Camera::CameraTransform() {
	screen_.lateral.begin = TransForm(local_.lateral.begin, vpVpMatrix_);
	screen_.lateral.end   = TransForm(local_.lateral.end,   vpVpMatrix_);
	screen_.vert.begin    = TransForm(local_.vert.begin,    vpVpMatrix_);
	screen_.vert.end      = TransForm(local_.vert.end,      vpVpMatrix_);
}
/// <summary>
/// ラインの描画
/// </summary>
void Camera::CameraDraw() {
	Novice::DrawLine((int)screen_.lateral.begin.x, (int)screen_.lateral.begin.y, (int)screen_.lateral.end.x, (int)screen_.lateral.end.y, RED);
	Novice::DrawLine((int)screen_.vert.begin.x,    (int)screen_.vert.begin.y,    (int)screen_.vert.end.x,    (int)screen_.vert.end.y,    GREEN);
}
/// <summary>
/// カメラの移動
/// </summary>
void Camera::CameraMove(char keys[]) {
	if (keys[DIK_LEFT]) {
		affine_.translate.x += speed_;
	}
	if (keys[DIK_RIGHT]) {
		affine_.translate.x -= speed_;
	}
	if (keys[DIK_UP]) {
		affine_.translate.y -= speed_;
	}
	if (keys[DIK_DOWN]) {
		affine_.translate.y += speed_;
	}

	if (keys[DIK_E]&&!keys[DIK_LSHIFT]) {
		if (affine_.scale.x > 0.3f || affine_.scale.y > 0.3f) {
			affine_.scale.x -= scale_;
			affine_.scale.y -= scale_;
		}
	}
	if (keys[DIK_Q] && !keys[DIK_LSHIFT]) {
		affine_.scale.x += scale_;
		affine_.scale.y += scale_;
	}

	if (keys[DIK_C] && !keys[DIK_LSHIFT]) {
		affine_.theta -= theta_;
	}
	if (keys[DIK_Z] && !keys[DIK_LSHIFT]) {
		affine_.theta += theta_;
	}
}

void Camera::CameraTest(){
	CameraTransform();
	CameraDraw();
}
