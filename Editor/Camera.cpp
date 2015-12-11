#include "Camera.h"

void Camera::init(int w, int h)
{
	screen_height = h;
	screen_width = w;
}
void Camera::reset()
{
	position.x = 0;
	position.y = 0;
	zoomLevel = 1;
	moveToTargetSpeed_x = 0;
	moveToTargetSpeed_y = 0;
	moveToTargetTime = 0;
}

void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

}

void Camera::setFocus(float x, float y)
{
	position.x = ((x*zoomLevel)*-1) + screen_width / 2;
	position.y = ((y*zoomLevel)*-1) + screen_height / 2;

}

void Camera::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
float Camera::getXPosition()
{
	return position.x;
}

float Camera::getYPosition()
{
	return position.y;
}

void Camera::update(float millisecondFTime)
{
	if (moveToTargetTime > 0)
	{
		if (position.x > targetMovePosition.x)
		{

			position.x -= millisecondFTime*moveToTargetSpeed_x;
			moveToTargetTime -= millisecondFTime;
		}
		else if (position.x < targetMovePosition.x)
		{
			position.x += millisecondFTime*moveToTargetSpeed_x;
			moveToTargetTime -= millisecondFTime;
		}

		if (position.y > targetMovePosition.y)
		{

			position.y -= millisecondFTime*moveToTargetSpeed_y;
			//moveToTargetTime -= millisecondFTime;
		}
		else if (position.y < targetMovePosition.y)
		{
			position.y += millisecondFTime*moveToTargetSpeed_y;
			//moveToTargetTime -= millisecondFTime;
		}
	}
}
bool Camera::checkIfMoveCompleted()
{
	if (moveToTargetTime <= 0)
	{
		return true;
	}

	return false;

}
void Camera::moveCameraTo(float x, float y, int time)
{


	targetMovePosition.x = x;
	targetMovePosition.y = y;
	moveToTargetTime = time;
	moveToTargetSpeed_x = 0;
	moveToTargetSpeed_y = 0;

	int distanceToTravel_X = 0;
	int distanceToTravel_Y = 0;

	if (targetMovePosition.x > position.x)
		distanceToTravel_X = targetMovePosition.x - position.x;
	else
		distanceToTravel_X = position.x - targetMovePosition.x;

	if (targetMovePosition.y > position.y)
		distanceToTravel_Y = targetMovePosition.y - position.y;
	else
		distanceToTravel_Y = position.y - targetMovePosition.y;

	moveToTargetSpeed_x = (float)distanceToTravel_X / (float)moveToTargetTime;
	moveToTargetSpeed_y = (float)distanceToTravel_Y / (float)moveToTargetTime;



}

void Camera::addCameraShake(float strength, int time)
{

}

void Camera::setZoomLevel(float level)
{
	this->zoomLevel = level;
}

float Camera::getZoomLevel()
{
	return this->zoomLevel;
}

void Camera::zoomIn()
{
	this->zoomLevel += 0.125;//0.0625;// 

}
void Camera::zoomOut()
{
	this->zoomLevel -= 0.125;//0.0625;//
}
