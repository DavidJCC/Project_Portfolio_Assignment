#include "Camera.h"


Camera::Camera(void)
{
	mouseX = mouseY = 0;
	toX = camX = (float)(MAP_X*MAP_SCALE) / 2.0f;
	toY = 255.0f;
	camY = 200.0f;
	toZ = camZ = -(float)(MAP_Z*MAP_SCALE) / 2.0f;
	camRad = 250.0f;
}


Camera::~Camera(void)
{
}

void Camera::cameraPos()
{
	// Map the mouse position to two angles
	angNS = ((mouseY + 1) / SCRN_H) * (float)M_PI;
	angEW = (mouseX / SCRN_W) * 2 * (float)M_PI;
	// Calculate the sines and cosines of these angle
	float sinNS = sin(angNS);
	float cosNS = cos(angNS);
	float sinEW = sin(angEW);
	float cosEW = cos(angEW);

	// calculate the camera coordinate
	camZ = toZ + camRad * sinNS * cosEW;
	camY = toY + camRad * cosNS;
	camX = toX + camRad * sinNS * sinEW;

	constrainCam();
}

void Camera::cameraPos(float toX, float toY, float toZ)
{
	// Map the mouse position to two angles
	angNS = ((mouseY + 1) / SCRN_H) * (float)M_PI;
	angEW = (mouseX / SCRN_W) * 2 * (float)M_PI;
	// Calculate the sines and cosines of these angle
	float sinNS = sin(angNS);
	float cosNS = cos(angNS);
	float sinEW = sin(angEW);
	float cosEW = cos(angEW);

	// calculate the camera coordinate
	camZ = toZ + camRad * sinNS * cosEW;
	camY = toY + camRad * cosNS;
	camX = toX + camRad * sinNS * sinEW;

	setToX(toX);
	setToY(toY);
	setToZ(toZ);

	constrainCam();
}

void Camera::constrainCam()
{
	if(camRad < CAM_MIN)
		camRad = CAM_MIN;
	if(camRad > CAM_MAX)
		camRad = CAM_MAX;
}