#include "GameUpdate.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameUpdate* game = new GameUpdate;

	game->GameLoop();

	delete game;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
