#include "CBSimpleRecognizer.h"
#include <math.h>


#define MAX_TOUCH_DURATION (0.5f)
#define MIN_TOUCH_DISTANCE (10.0f)


void CBSimpleRecognizer::beginPoint( float x, float y )
{
	m_posBeginX = x;
	m_posBeginY = y;
	m_clockBegin = clock();
}

GestureDirection CBSimpleRecognizer::endPoint( float x, float y )
{
	m_clockEnd = clock();

	double duration = (double)(m_clockEnd - m_clockBegin) / CLOCKS_PER_SEC;
	if (fabs(duration) > MAX_TOUCH_DURATION)
	{
		return kGestureDirectionError;
	}

	float distanceX = x - m_posBeginX;
	float distanceY = y - m_posBeginY;
	float distancePos = sqrt(distanceX*distanceX + distanceY*distanceY);
	if (distancePos < MIN_TOUCH_DISTANCE)
	{
		return kGestureDirectionError;
	}

	if (fabs(distanceX) > fabs(distanceY))
	{
		if (distanceX > 0)
		{
			return kGestureDirectionRight;
		}
		else
		{
			return kGestureDirectionLeft;
		}
	}
	else
	{
		if (distanceY > 0)
		{
			return kGestureDirectionUp;
		}
		else
		{
			return kGestureDirectionDown;
		}
	}

	return kGestureDirectionError;
}
