#pragma once
#include <assert.h>
#include <math.h>
#include "Struct.h"

typedef struct Point {
	float left;
	float top;
	float right;
	float bottom;
}Point;

class Rendering
{
public:
	Matrix3x3 Inverse(Matrix3x3 matrix);

	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

	Matrix3x3 MakeTranslateMatrix(Vector2 translate);

	Matrix3x3 MakeRotateMatrix(float theta);

	Matrix3x3 MakeScaleMatrix(Vector2 scale);

	Vector2 TransForm(Vector2 vector, Matrix3x3 matrix);

	Matrix3x3 MakeOrthographicMatrix(Point vertex);

	Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

	Matrix3x3 MakeAffineMatrix(Affine affine);

};

