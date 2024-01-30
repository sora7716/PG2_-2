#pragma once
#include <Novice.h>
class FullScreen
{
private:
	bool isFullScreen_;

public:

	FullScreen();

	void Push(char* keys, char* preKeys);
};

