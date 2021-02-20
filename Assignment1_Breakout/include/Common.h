#ifndef COMMON_H_
#define COMMON_H_

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float PADDLE_SPEED = 1.0f;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const float BALL_SPEED = 1.0f;
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};


enum class CollisionType
{
	None,
	Top,
	Middle,
	Bottom,
	Left,
	Right
};


struct Contact
{
	CollisionType type;
	float penetration;
};

#endif // COMMON_H_
