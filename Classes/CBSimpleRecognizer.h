#pragma once

#include <ctime>


//手势方向;
typedef enum
{
	kGestureDirectionUp = 0,
	kGestureDirectionDown,
	kGestureDirectionLeft,
	kGestureDirectionRight,
	kGestureDirectionError
}GestureDirection;


class CBSimpleRecognizer
{
public:

	void beginPoint(float x, float y);

	GestureDirection endPoint(float x, float y);

protected:

	float m_posBeginX;
	float m_posBeginY;
	clock_t m_clockBegin;
	clock_t m_clockEnd;
};
