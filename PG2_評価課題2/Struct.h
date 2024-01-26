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

typedef struct ShakeObject {
	VectorInt position;
	int range;
	bool isScale;
	bool isShake;
}ShakeObject;

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

typedef struct MoveObject {
	Vector2 vector;
	Vector2 distance;
	float len;
}MoveObject;


typedef struct Renderer {
	Vertex local;
	Affine affine;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;
	Vertex screen;
}Renderer;
	