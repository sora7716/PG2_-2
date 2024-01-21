#pragma once
#include "Struct.h"

class Collision
{
public:
	//bool Box(Vertex standard, Vertex attached);

	bool Box(Vector2 standard, Vector2 attached, float standardSize, float attachedSize);
};

