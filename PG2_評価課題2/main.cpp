#include "Player.h"
#include "EnemyDown.h"

const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ_title";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256]    = {0};
	char preKeys[256] = {0};

	Player* player = new Player;
	Enemy* enemy   = new EnemyDown;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		player->Update(keys,preKeys);
		enemy->Update(keys, preKeys,player->GetVpVpMatrix());
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
