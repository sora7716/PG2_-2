#include "FullScreen.h"

FullScreen::FullScreen() {
	isFullScreen_ = true;
}

void FullScreen::Push(char* keys, char* preKeys){
	if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && !isFullScreen_) {
		isFullScreen_ = true;
	}
	else if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && isFullScreen_) {
		isFullScreen_ = false;
	}
	if (isFullScreen_) {
		Novice::SetWindowMode(kFullscreen);
	}
	else {
		Novice::SetWindowMode(kWindowed);
	}
}
