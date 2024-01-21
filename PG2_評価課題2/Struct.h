#pragma once

const float SCREEN_WIDTH  = 1280;
const float SCREEN_HEIGHT = 720;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct VectorInt {
	int x;
	int y;
}VectorInt;

typedef struct Matrix3x3 {

	float m[3][3];

} Matrix3x3;

typedef struct Vertex {
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;
}Vertex;

typedef struct Affine {
	Vector2 scale;
	float theta;
	Vector2 translate;
}Affine;

typedef struct Speed {
	float growing;
	float rotation;
	Vector2 velocity;
}Speed;