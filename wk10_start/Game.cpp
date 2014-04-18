#include "Game.h"
#include <iostream>
Game::Game(void)
{
	fCount = 0;
	drawLight = true;
	gameState = START;
}

//
// Given x and z value and 3 pts of a plane.  For a,b,c calcs, see handout.
// returns calculated y value from x & z pts on the plane
//
float Game::calcY(float x, float z, Vector p1, Vector p2, Vector p3)
{
	float a,b,c;
	a = (p2.y-p1.y)*(p3.z-p1.z)-(p3.y-p1.y)*(p2.z-p1.z);
	b = (p2.x-p1.x)*(p3.z-p1.z)-(p3.x-p1.x)*(p2.z-p1.z);
	c = (p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y);

	return (a*x - a*p1.x + b*p1.y + c*z - c*p1.z) / b; //y value
}

void Game::calcYFromCubeCtr(Object *c, float halfHeight)
{
	float ltx, ltz, rtx, rtz;  //for left triangle & right triangle
	int xi1 = c->getPos().x/MAP_SCALE;  //calc left triangle array coords
	int zi1 = -c->getPos().z/MAP_SCALE; 

	ltx = xi1 * MAP_SCALE;  ltz = -zi1 * MAP_SCALE; //get x & z coords of triangles
	rtx = (xi1+1) * MAP_SCALE; rtz = -(zi1 + 1) * MAP_SCALE;
//
// find triangle to calculate plane from
	Vector p1, p2, p3; //3 points of plane
	if((ltx-c->getPos().x)*(ltx-c->getPos().x) + (ltz-c->getPos().z)*(ltz-c->getPos().z)
		<= (rtx-c->getPos().x)*(rtx-c->getPos().x) + (rtz-c->getPos().z)*(rtz-c->getPos().z)){
		p1.x = ltx; p1.y = terrain->terrain[zi1 * MAP_Z + xi1]; p1.z = ltz;  //left triangle
		p2.x = ltx; p2.y = terrain->terrain[(zi1+1) * MAP_Z + xi1]; p2.z = rtz;
		p3.x = rtx; p3.y = terrain->terrain[zi1 * MAP_Z + xi1 + 1]; p3.z = ltz;
	}else{
		p1.x = rtx; p1.y = terrain->terrain[(zi1+1) * MAP_Z + xi1 + 1]; p1.z = rtz; //right triangle
		p2.x = rtx; p2.y = terrain->terrain[zi1 * MAP_Z + xi1 + 1]; p2.z = ltz;
		p3.x = ltx; p3.y = terrain->terrain[(zi1+1) * MAP_Z + xi1]; p3.z = rtz;
	}
	c->getPos().y = calcY(c->getPos().x, c->getPos().z, p1, p2, p3) + halfHeight;
}

Game::~Game(void)
{
}

void Game::InitOpenGL()
{
	DebugOut("Game::InitOpenGL being called");
	Set3D(60, 0.1, 3000);
}


void Game::Initialise()
{
	DebugOut("Game::Initialise being called");
	font1 = new BFont(hDC, "Courier", 14);
	timer = new Timer();

	//camera setup
	cam = new Camera();

	//terrain
	terrain = new Terrain();
	terrain->init("Images/terrain.bmp", "Images/rock.bmp");

	//skybox setup
	skybox = new Skybox();
	skybox->loadTextures();

	//player setup
	player = new Player("Player", PLR_START_X, 275.0f, PLR_START_Z);
	player->alpha = 1.0f;
	entities.push_back(player);

	//enemies setup
	for(int i = 0; i < NUM_ZOMBIES; i++)
	{
		npc[i] = new MD2Model();
		npc[i]->LoadMD2Model("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp");
		npc[i]->pos = Vector(rnd.number(10.0f, MAP_X * MAP_SCALE * 0.9f), 275.0f, -rnd.number(10.0f, MAP_Z * MAP_SCALE * 0.9f));
		npc[i]->alpha = 1.0f;
		entities.push_back(npc[i]);
	}

	float matSpec[] = {1.0f, 1.0f, 1.0f, 1.0f };
	float matShiny[] = {5.0f};  //128 is max value
	lightPos[0]=player->getPos().x; lightPos[1]=player->getPos().y+5; lightPos[2]= player->getPos().z; lightPos[3]=1.0f; //attach lightsource to player to mimic torch
	float whiteLight[] = { 0.5f, 0.5f, 0.7f, 1.0f };
	float ambLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSpec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	lSphere = gluNewQuadric();	//to show where light pos is
	gluQuadricDrawStyle(lSphere, GLU_FILL);
	gluQuadricNormals(lSphere, GLU_NONE);

	//controls the cursor
	POINT p;
	p.x = SCRN_W/2; p.y = SCRN_H/2;
	ClientToScreen(hWnd, &p);
	SetCursorPos(p.x, p.y);
}

void Game::Shutdown()
{
	DebugOut("Game::Shutdown being called");
	delete font1;
	delete timer;
	delete terrain;
	delete skybox;
	delete cam;
	entities.clear();
	if(lSphere != NULL)
		gluDeleteQuadric(lSphere);
	DebugOut("TERMINATED");
}

void Game::Update()
{
	UpdateFps();

	/***********************************
		IF GAME IS PLAYING UPDATE
	***********************************/
	if(gameState == PLAYING)
	{
		// Perform collision detection here

		for(int i = 0; i < NUM_ZOMBIES; i++)
			calcYFromCubeCtr(npc[i], npc[i]->bb.ySize() / 2.0f);
		calcYFromCubeCtr(player, player->bb.ySize()  / 2.0f);

		cam->setToX(player->getPos().x); cam->setToY(player->getPos().y); cam->setToZ(player->getPos().z); 
		player->update(tbf);
		cam->CameraPos();

		lightPos[0]=player->getPos().x; lightPos[1]=player->getPos().y+30; lightPos[2]= player->getPos().z; lightPos[3]=1.0f;
	}

	/******************************************
			IF GAME IS OVER
	*****************************************/
	if(player->getHealth() == 0)
	{
		gameState = OVER;
	}
}

void Game::drawLightSource()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		//gluSphere(lSphere, 20.0f, 20, 12);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

// and now render the objects in their current state.
void Game::Render()
{
	//glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/*********************************************************
		IF GAME IS PLAYING RENDER OBJECTS, TERRAIN AND SKYBOX
	*********************************************************/
	if(gameState == PLAYING)
	{
		// set camera position 
		gluLookAt(cam->getCamX(), cam->getCamY(), cam->getCamZ(), cam->getToX(), cam->getToY(), cam->getToZ(), 0.0f, 1.0f, 0.0f);
		skybox->render( 20.0f, cam->getCamX(), -100, -cam->getCamZ() );		if(drawLight)	drawLightSource();	
	
		terrain->render();
		player->render();
	}

	RenderHUD();

	glFlush();
	fCount++;	// increment frame counter
}

void Game::RenderHUD()
{
	// Change to 2D view and use 1:1 pixel resolution with
	// [0,0] origin being at the top-left corner.
	Set2D(0, SCRN_W, SCRN_H, 0);
	// Disable depth testing so the HUD will not be hidden
	// by the 3D graphics
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	// Semi transparent background for frame rate stats
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(m_width, 50);
		glVertex2f(m_width, 0);
	glEnd();
	glDisable(GL_BLEND);

	// Print the statistics
	if(gameState == START)
	{
		sprintf_s(text, "Welcome to the game");
		font1->printString(SCRN_W/2-70, 20, text);
		sprintf_s(text, "Press ENTER to continue");
		font1->printString(SCRN_W/2-90, SCRN_H-100, text);
		PrintInstructions();
	}

	if(gameState == PAUSED)
	{
		sprintf_s(text, "Game Paused");
		font1->printString(SCRN_W/2-70, 20, text);
		sprintf_s(text, "Press P to continue");
		font1->printString(SCRN_W/2-90, SCRN_H-100, text);	
	}


	if(gameState == PLAYING)
	{
		sprintf_s(text, "Score: %f   Lives: %i", player->getScore(), player->getLives());
		font1->printString(4, 20, text);
		sprintf_s(text, "Health: %i", player->getHealth());
		font1->printString(4, 40, text);
		sprintf_s(text, "%6.1f FPS", avgFps);
		font1->printString(SCRN_W - 110, 20, text);
	}

	if(gameState == OVER)
	{
		if(player->getHealth() < 1)
		{
			font1->printString(SCRN_W/2-70, 20, text);
			sprintf_s(text, "You collected all the energy coils.");
			font1->printString(SCRN_W/2-150, SCRN_H / 2, text);
			sprintf_s(text, "You can now power your ship and go home!");
			font1->printString(SCRN_W/2-175, SCRN_H / 2 + 20, text);
		}
		else
		{
			font1->printString(SCRN_W/2-50, 20, text);
			sprintf_s(text, "You failed in your task and got killed.");
			font1->printString(SCRN_W/2-170, SCRN_H / 2, text);
			sprintf_s(text, "You are a failure, you don't deserve to go home.");
			font1->printString(SCRN_W/2-195, SCRN_H / 2 + 20, text);
		}
		sprintf_s(text, "Game Over");
		sprintf_s(text, "Press ESC to exit or ENTER to restart");
		font1->printString(SCRN_W/2-150, SCRN_H-100, text);
	}

	// Set back to 3D
	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING);
}

void Game::UpdateFps()
{
	cft = timer->getElapsedTime();
	tbf = cft - lft;
	lft = cft;

	// Calc stats - FPS etc
	fps = 1.0f / tbf;
	avgFps = fCount / cft;
}

void Game::PauseGame()
{
	if(gameState == PAUSED)
		gameState = PLAYING;
	else
		gameState = PAUSED;
}

void Game::PrintInstructions()
{
	sprintf_s(text, "OBJECTIVE: You have crashed your ship in a canyon");
	font1->printString(SCRN_W/2-220, SCRN_H/2-80, text);
	sprintf_s(text, "on a distant planet and lost all of");
	font1->printString(SCRN_W/2-170, SCRN_H/2-60, text);	
	sprintf_s(text, "the ships energy coils. Go and find them.");
	font1->printString(SCRN_W/2-170, SCRN_H/2-40, text);
	sprintf_s(text, "Initial scans of planet show there are hostiles.");
	font1->printString(SCRN_W/2-210, SCRN_H/2+20, text);
	sprintf_s(text, "You have no weapons so avoid them or they'll eat your face.");
	font1->printString(SCRN_W/2-260, SCRN_H/2+40, text);
	sprintf_s(text, "WASD - Move Player    SHIFT - SPRINT");
	font1->printString(SCRN_W/2-170, SCRN_H/2+150, text);	
}
