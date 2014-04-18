#pragma once
#include "basegame.h"
#include "bfont.h"
#include "timer.h"
using namespace timer;
#define _USE_MATH_DEFINES
#include <cmath>

#include "DebugPrint.h"
#include "Ackley.h"
#include "LoadTextures.h"
#include "Entity.h"
#include "MD2Model.h"
#include "Player.h"
#include "Skybox.h"
#include "GameConstants.h"
#include "Terrain.h"
#include <vector>

#include "random.h"
using namespace random;

/**
The class inherits from BaseGame and provides the game data model
and the game logic
*/
class Game : public BaseGame{

	// Allow event handler direct access to these attributes
	// (copied from BaseGame since frienship is not inherited)
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	// HERE WE DECLARE ANY FONTS, TIMERS OR OTHER VARIABLES WE WANT
	float mouseX, mouseY;

	float camX, camY, camZ, camRad;
	float angEW, angNS;

	BFont* font1;
	char text[256];

	Timer* timer;
	float cft, lft, tbf, fps, avgFps;
	unsigned int fCount;

	float toX, toY, toZ;

	float lightPos[4];
	GLUquadricObj * lSphere;

	Entity* player;
	Entity* npc[NUM_ZOMBIES];
	bool objSelected, picking, drawLight;
	int objectPicked;

	Skybox* skybox;
	Terrain* terrain;

	// -- STORES THE MD2Model entities to make updating and rendering easier -- /
	std::vector<Entity*>entities;
public:

	Game(void);
	virtual ~Game(void);

	/**
	This is executed just once and is used to perform any first time
	initialisation of the OpenGL environment. 
	*/
	void InitOpenGL();

	/**
	Use this method to create timers, fonts and all game objects. Do NOT 
	execute any OpenGL commands in this method used initOpenGL instead.
	*/
	void Initialise();

	/**
	Use this method to perform any clean up of objects created for 
	the game -including fonts and timers.
	*/
	void Shutdown();

	/**
	Use this method to create any game objects and initialise the
	game's state
	*/
	bool InitGame();

	/**
	Use this method to update the games state but do not use for 
	rendering
	*/
	void Game::Update();

	/**
	The nain rendering method - renders a single frame
	*/
	void Game::Render();


	/**
	This method is used to provide a 'haed up display' for showing
	various game statistics, primarily FPS
	*/
	void RenderHUD();

	/**
	Used to update the camera position based on the mouse position
	*/
	void CameraPos();

	/**
	Sets the look at vector for the camera. Could enhanced to deal
	with multiple cameras.
	*/
	void useCamera();

	void loadAckley();
	void InitialiseTerrain();
	void renderTerrain();
	float calcY(float x, float z, Vector p1, Vector p2, Vector p3);
	void calcYFromCubeCtr(Entity *c, float halfHeight);
	Vector calcAvgNormal(int x, int z);
	void drawLightSource();
	void renderPlayer();
	Vector unProject();
	void constrainCam();
};
