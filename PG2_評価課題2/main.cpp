#include "GameUpdate.h"

bool Camera::isRotation = false;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameUpdate* game = new GameUpdate;

	game->GameLoop();//ゲームの処理
	
	delete game;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
