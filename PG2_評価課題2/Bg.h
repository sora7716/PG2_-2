#pragma once
#include "Rendering.h"

const int BG_NUM = 300;

typedef struct BgObject {
	Renderer rendering;
	float speed;
	VectorInt random;
}BgObject;

class Bg:public Rendering
{
private:
	BgObject bg_[BG_NUM];
public:

	Bg();

};

