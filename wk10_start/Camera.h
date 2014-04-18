#pragma once
#include "GameConstants.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Camera
{
private:
	float toX, toY, toZ;
	float mouseX, mouseY;
	float camX, camY, camZ;
	float angEW, angNS;
public:
	float camRad;

	Camera(void);
	~Camera(void);

	float getCamX() { return camX; }
	float getCamY() { return camY; }
	float getCamZ() { return camZ; }

	float getToX() { return toX; }
	void setToX(float toX) { this->toX = toX; }
	float getToY() { return toY; }
	void setToY(float toY) { this->toY = toY; }
	float getToZ() { return toZ; }
	void setToZ(float toZ) { this->toZ = toZ; }

	float getMouseX() { return mouseX; }
	void setMouseX(float mouseX) { this->mouseX = mouseX; }
	float getMouseY() { return mouseY; }
	void setMouseY(float mouseY) { this->mouseY = mouseY; }

	void setCamRad(float camRad) { this->camRad = camRad; }
	
	/**
	Used to update the camera position based on the mouse position
	*/
	void CameraPos();

	/**
	Keeps the camera contrained
	**/
	void constrainCam();
};

