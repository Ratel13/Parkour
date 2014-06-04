#pragma once

#include <ctime>


//���Ʒ���;
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
