#include "EndScene.h"

EndScene::EndScene() {

}

void EndScene::Draw() {
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT / 2, 0.0f, RED, kFillModeSolid);
}