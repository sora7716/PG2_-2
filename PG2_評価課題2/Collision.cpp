#include "Collision.h"

//bool Collision::Box(Vertex standard, Vertex attached) {
//	bool a = standard.leftTop.x <= attached.rightTop.x;
//	bool b = attached.leftTop.x <= standard.rightTop.x;
//	bool c = standard.leftTop.y <= attached.leftBottom.y;
//	bool d = attached.leftTop.y <= standard.leftBottom.y;
//	if (a && b && c && d) {
//		return true;
//	}
//	return false;
//}

bool Collision::Box(Vector2 standard, Vector2 attached, float standardSize, float attachedSize) {
	bool a = standard.x - (standardSize / 2.0f) <= attached.x + (attachedSize / 2.0f);
	bool b = attached.x - (attachedSize / 2.0f) <= standard.x + (standardSize / 2.0f);
	bool c = standard.y - (standardSize / 2.0f) <= attached.y + (attachedSize / 2.0f);
	bool d = attached.y - (attachedSize / 2.0f) <= standard.y + (standardSize / 2.0f);
	return a && b && c && d;
}
