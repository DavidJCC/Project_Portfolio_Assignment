#pragma once
#include "basegame.h"
#include "bfont.h"
#include <cmath>
#include <vector>
#include <string>
#include "cube3d.h"
#include "DebugPrint.h"
#include "Ackley.h"
#include "LoadTextures.h"
#include "Player.h"
#include "Zombie.h"
#include "MD2Model.h"
#include "Object.h"
#include "Skybox.h"
#include "GameConstants.h"
#include "Terrain.h"
#include "Camera.h"
#include "AudioPlayer.h"
#include "EnergyCoil.h"

#include "timer.h"
#include "random.h"
using namespace random;
using namespace timer;

/*************************
		GAME STATES
*************************/
enum gameStates
{
	START = 0, //initial splashscreen
	PLAYING, //game is playing
	PAUSED, //game paused 
	OVER //game is over (either game over or game won)
};

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
	BFont* font1;
	char text[256];

	int gameState;
	Timer* timer;
	float cft, lft, tbf, fps, avgFps;
	unsigned int fCount;

	float lightPos[4];
	GLUquadricObj* lSphere;
	Camera* cam;
	Player* player;
	Zombie* zombies[NUM_ZOMBIES];
	//EnergyCoil* energyCoils[NUM_COILS];
	std::vector<EnergyCoil*>energyCoils;
	bool objSelected, picking, drawLight;
	int objectPicked;
	Skybox* skybox;
	Terrain* terrain;
	AudioPlayer* audioPlayer;
	bool keys[256];
	bool d;
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
	The main rendering method - renders a single frame
	*/
	void Game::Render();

	/**
	This method is used to provide a 'haed up display' for showing
	various game statistics, primarily FPS
	*/
	void RenderHUD();
	
	/*
	Draws the lightsource and the gluSphere
	*/
	void drawLightSource();

	/*
	Updates the frames per second. To be used in Update()
	*/
	void UpdateFps();

	/*
	Guess what this function does? :)
	*/
	void PauseGame();

	/*
	Output the relevant information like health, score, etc..
	*/
	void HudOutput();	

	/*
	Sets the game to playing
	*/
	void StartGame();

	/*
	Switches the lights on/off. Lights off == SPOOKY
	*/
	void DrawLightSwitch();

	/*
	Create the game objects. Useful for resetting the game. Call this in initialise first.
	*/
	void CreateGameObjects();

	/*
	Set up game lighting
	*/
	void SetupLighting();

	/*
	Setup the fog
	*/
	void SetupFog();

	/*
	Reset the game
	*/
	void ResetGame();

	void ProcessInput();

	/**************************************************************
			FIND OUT WHERE TO PUT THESE DONT LEAVE THEM HERE
	**************************************************************/
	float calcY(float x, float z, Vector p1, Vector p2, Vector p3);
	void calcYFromCubeCtr(Object *c, float halfHeight);
	Vector calcAvgNormal(int x, int z);
};
