#include "Bg.h"

Bg::Bg() {
	for (int i = 0; i < BG_NUM; i++) {
		bg_[i].rendering.local = 
        {
		  { -BG_SIZE / 2.0f ,-BG_SIZE / 2.0f  },
		  { -BG_SIZE / 2.0f , BG_SIZE / 2.0f  },
		  {  BG_SIZE / 2.0f ,-BG_SIZE / 2.0f  },
		  {  BG_SIZE / 2.0f , BG_SIZE / 2.0f  },
		};
		bg_[i].rendering.affine = { {1,1},0,{} };
		bg_[i].rendering.screen = {};
		bg_[i].rendering.worldMatrix = {};
		bg_[i].rendering.wvpVpMatrix = {};
		bg_[i].random = {};
		bg_[i].speed = 3;
		bg_[i].color = WHITE;
		bg_[i].isAlive = false;
		bg_[i].isAdd = false;
	}
	srand((unsigned int)time(nullptr));
	texture_ = Novice::LoadTexture("white1x1.png");
}

void Bg::BgSpawn(unsigned int color,float speed) {
	for (int i = 0; i < BG_NUM; i++) {
		if (!bg_[i].isAlive) {
			bg_[i].isAlive = true;
			bg_[i].random = { rand() % 1280 - 640,rand()%1400-1280};
			bg_[i].rendering.affine.translate = { (float)bg_[i].random.x,(float)bg_[i].random.y };
			float size = float(rand() % 2 + 1);
			bg_[i].rendering.affine.scale = {size,size};
			bg_[i].color = color-0x000000FF;
			bg_[i].speed = speed;
			if (Camera::isRotation) {
				bg_[i].speed *= -1;
			}
			else {
				bg_[i].speed *= -1;
			}
			break;
		}
	}
}

void Bg::BgMove() {
	for (int i = 0; i < BG_NUM; i++) {
		if (bg_[i].isAlive) {
			bg_[i].rendering.affine.translate.y += bg_[i].speed;
			if (bg_[i].rendering.affine.translate.y > 100|| bg_[i].rendering.affine.translate.y<-1280) {
				bg_[i].isAlive = false;
			}
		}
	}
}

void Bg::BgColor(unsigned int color) {
	for (int i = 0; i < BG_NUM; i++) {
		if (!bg_[i].isAdd) {
			if (bg_[i].color > color-0x000000FF) {
				bg_[i].color -= 0x000000005;
			}
		}
		else {
			if (bg_[i].color < 0xFFFFFF88) {
				bg_[i].color += 0x00000001;
			}
		}
		if (bg_[i].color <= color - 0x000000FF) {
			bg_[i].isAdd = true;
		}
		else if (bg_[i].color >= 0xFFFFFF55) {
			bg_[i].isAdd = false;
		}
	}
}

void Bg::MakeWorldMatrix() {
	for (int i = 0; i < BG_NUM; i++) {
		bg_[i].rendering.worldMatrix = MakeAffineMatrix(bg_[i].rendering.affine);
	}
}

void Bg::MakeWvpVp(Matrix3x3 vpVpMatrix) {
	for (int i = 0; i < BG_NUM; i++) {
		bg_[i].rendering.wvpVpMatrix = Multiply(bg_[i].rendering.worldMatrix, vpVpMatrix);
	}
}

void Bg::BgTransform() {
	for (int i = 0; i < BG_NUM; i++) {
		bg_[i].rendering.screen.leftTop     = TransForm(bg_[i].rendering.local.leftTop,     bg_[i].rendering.wvpVpMatrix);
		bg_[i].rendering.screen.leftBottom  = TransForm(bg_[i].rendering.local.leftBottom,  bg_[i].rendering.wvpVpMatrix);
		bg_[i].rendering.screen.rightTop    = TransForm(bg_[i].rendering.local.rightTop,    bg_[i].rendering.wvpVpMatrix);
		bg_[i].rendering.screen.rightBottom = TransForm(bg_[i].rendering.local.rightBottom, bg_[i].rendering.wvpVpMatrix);
	}
}

void Bg::DrawBg() {
	for (int i = 0; i < BG_NUM; i++) {
		Novice::DrawQuad(
			(int)bg_[i].rendering.screen.leftTop.x, (int)bg_[i].rendering.screen.leftTop.y,
			(int)bg_[i].rendering.screen.leftBottom.x, (int)bg_[i].rendering.screen.leftBottom.y,
			(int)bg_[i].rendering.screen.rightTop.x, (int)bg_[i].rendering.screen.rightTop.y,
			(int)bg_[i].rendering.screen.rightBottom.x, (int)bg_[i].rendering.screen.rightBottom.y,
			0, 0, 1, 1, texture_, bg_[i].color);
	}
}

void Bg::Update(Matrix3x3 vpVpMatrix, unsigned int color, float speed) {
	Novice::DrawBox(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0.0f, 0x000000FF, kFillModeSolid);
	BgSpawn(color,speed);
	BgColor(color);
	BgMove();
	MakeWorldMatrix();
	MakeWvpVp(vpVpMatrix);
	BgTransform();
	DrawBg();
}