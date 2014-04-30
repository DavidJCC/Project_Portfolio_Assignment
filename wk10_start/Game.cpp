#include "Game.h"

Game::Game(void)
{
	fCount = 0;
	drawLight = true;
	gameState = START;
	font1 = NULL;
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
	//calcNormalFrom3Points(p1, p2, p3);
}

void Game::calcNormalFrom3Points(Vector p1, Vector p2, Vector p3)
{
	Vector l1, l2, n1, n2, rotAxis;
	l1 = p1-p2;
	l2 = p3-p2;
	n1 = (l1).CrossProduct(l2);
	n1.Normalize();
	
	n2.x = 0.0f; n2.y = -1.0f; n2.z = 0.0f;
	rotAxis = n2.CrossProduct(n1);
	rotAxis.Normalize();
	player->setRotAxis(rotAxis);
	calcRotAngle(n1, n2);
	player->setAngle(calcRotAngle(n1, n2));
}

float Game::calcRotAngle(Vector v1, Vector v2)
{
	float rotAngle;
	rotAngle = v1.DotProduct(v2);
	return rotAngle;
}

Game::~Game(void)
{
}

void Game::InitOpenGL()
{
	DebugOut("Game::InitOpenGL being called");
	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING);
}


void Game::Initialise()
{
	DebugOut("Game::Initialise being called");
	font1 = new BFont(hDC, "Courier", 20);
	timer = new Timer();

	//camera setup
	cam = new Camera();

	//terrain
	terrain = new Terrain();
	terrain->init("Images/terrain.bmp", "Images/rock.bmp");

	//skybox setup
	skybox = new Skybox();
	skybox->loadTextures();

	//energy coils setup
	for(int i = 0; i < NUM_COILS; i++)
	{
		//as no models files or texures are loaded the coils will be represented as a gluquadric shape. If I find a good model to use replace it
		energyCoils[i] = new EnergyCoil(rnd.number(10.0f, MAP_X * MAP_SCALE * 0.9f), 275.0f, -rnd.number(10.0f, MAP_Z * MAP_SCALE * 0.9f));
	}

	//audio setup
	audioPlayer = new AudioPlayer("sounds/background.mp3");
	audioPlayer->playSound();

	//player setup
	player = new Player(PLR_START_X, 0.0f, PLR_START_Z, "Data/Sodf8/Tris.md2", "Data/pKnight/pknight.bmp");

	//enemies setup
	for(int i = 0; i < NUM_ZOMBIES; i++)
		zombies[i] = new Zombie(rnd.number(10.0f, MAP_X * MAP_SCALE * 0.9f), 275.0f, -rnd.number(10.0f, MAP_Z * MAP_SCALE * 0.9f), "Data/Phantom/tris.md2", "Data/Phantom/texture.bmp");

	float matSpec[] = {1.0f, 1.0f, 1.0f, 1.0f };
	float matShiny[] = {5.0f};  //128 is max value
	lightPos[0]= player->getPos().x; lightPos[1]=1900.0f; lightPos[2]= player->getPos().z; lightPos[3]=0.1f;
	float whiteLight[] = { 0.5f, 0.5f, 0.7f, 0.0f };
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

	//hides the mouse cursor
	ShowCursor(false);
}

void Game::Shutdown()
{
	DebugOut("Game::Shutdown being called");
	delete font1;
	delete timer;
	delete terrain;
	skybox->kill();
	delete skybox;
	delete cam;
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
		//GAME OVER IF HEALTH EQUALS OR LESS
		if(player->getHealth() == 0)
			gameState = OVER;

		//COLLISION DETECTION HERE		
		for(int i = 0; i < NUM_ZOMBIES; i++)
		{
			if(player->collidesWith(zombies[i]))
			{
				player->updateHealth(-5);
			}
		}

		for(int i = 0; i < NUM_COILS; i++)
		{
			if(energyCoils[i]->collidesWith(player))
			{
				PostQuitMessage(0);
				energyCoils[i]->setCollected(true);
			}
		}

		//UPDATE GAME OBJECTS HERE
		player->update(tbf);
		calcYFromCubeCtr(player, player->bb.ySize()  / 2.0f);

		for(int i = 0; i < NUM_COILS; i++)
		{
			calcYFromCubeCtr(energyCoils[i], energyCoils[i]->bb.ySize() / 2.0f);
			energyCoils[i]->update(tbf);
		}

		for(int i = 0; i < NUM_ZOMBIES; i++)
		{
			calcYFromCubeCtr(zombies[i], zombies[i]->bb.ySize() / 2.0f);  
			zombies[i]->update(tbf);
		}

		cam->cameraPos(player->getPos().x, player->getPos().y, player->getPos().z); 
	}
	//======================================//
}

void Game::DrawLightSwitch()
{
	if(drawLight)
		drawLight = false;
	else drawLight = true;
}

void Game::drawLightSource()
{
	if(drawLight)
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
			glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
			gluSphere(lSphere, 10.0f, 20, 12);
		glPopMatrix();

		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	}
}

/*************************************
RENDER OBJECTS IN THEIR CURRENT STATE
*************************************/
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
		//LOOK AT/UPDATE THE CAMERA POSITION
		gluLookAt(cam->getCamX(), cam->getCamY(), cam->getCamZ(), cam->getToX(), cam->getToY(), cam->getToZ(), 0.0f, 1.0f, 0.0f);
		skybox->render( 20.0f, cam->getCamX(), -100, -cam->getCamZ() );		
		
		drawLightSource();	
		//gd->Render();
		terrain->render();
		player->render();

		for(int i = 0; i < NUM_ZOMBIES; i++)
			zombies[i]->render();
		for(int i = 0; i < NUM_COILS; i++)
			energyCoils[i]->render();
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
	HudOutput();

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
	if(gameState == PLAYING || gameState == PAUSED)
	{
		if(gameState == PAUSED)
			gameState = PLAYING;
		else
			gameState = PAUSED;
	}
}

void Game::HudOutput()
{
	if(gameState == START)
	{
		sprintf_s(text, "STRANDED!");
		font1->printString(SCRN_W/2-20, 60, text);
		sprintf_s(text, "Press ENTER to continue");
		font1->printString(SCRN_W/2-90, SCRN_H-100, text);
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

	if(gameState == PLAYING)
	{
		sprintf_s(text, "Score: %i   Lives: %i ", player->getScore(), player->getLives());
		font1->printString(4, 20, text);
		sprintf_s(text, "Health: %i", player->getHealth());
		font1->printString(4, 40, text);
		sprintf_s(text, "%6.1f FPS", avgFps);
		font1->printString(SCRN_W - 150, 20, text);		
	}

	if(gameState == OVER)
	{
		if(player->getHealth() < 1)
		{
			sprintf_s(text, "You collected all the energy coils.");
			font1->printString(SCRN_W/2-160, SCRN_H / 2 - 20, text);
			sprintf_s(text, "You can now power your ship and go home!");
			font1->printString(SCRN_W/2-180, SCRN_H / 2, text);
		}
		else
		{			
			sprintf_s(text, "You failed in your task and got killed.");
			font1->printString(SCRN_W/2-200, SCRN_H / 2 - 20, text);
			sprintf_s(text, "You are a failure, your body will now be eaten.");
			font1->printString(SCRN_W/2-230, SCRN_H / 2, text);
		}

		sprintf_s(text, "Game Over");
		font1->printString(SCRN_W/2-50, 20, text);			
		sprintf_s(text, "Press ESC to exit or ENTER to restart");
		font1->printString(SCRN_W/2-180, SCRN_H-10, text);			
	}

	if(gameState == PAUSED)
	{
		sprintf_s(text, "Game Paused");
		font1->printString(SCRN_W/2-70, 20, text);
		sprintf_s(text, "Press P to continue");
		font1->printString(SCRN_W/2-90, SCRN_H-100, text);	
	}
}

void Game::StartGame()
{
	if(gameState != PLAYING)
		gameState = PLAYING;
}