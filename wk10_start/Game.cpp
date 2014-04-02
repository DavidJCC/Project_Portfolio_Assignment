#include "Game.h"

Game::Game(void)
{
	mouseX = mouseY = 0;
	toX = camX = (float)(MAP_X*MAP_SCALE) / 2.0f;
	toY = 255.0f;
	camY = 400.0f;
	toZ = camZ = -(float)(MAP_Z*MAP_SCALE) / 2.0f;
	camRad = 250.0f;
	fCount = 0;
	picking = drawLight = false;
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


void Game::Initialise(){
	DebugOut("Game::Initialise being called");
	font1 = new BFont(hDC, "Courier", 14);
	timer = new Timer();

	//terrain
	terrain = new Terrain();
	terrain->init("Images/terrain.bmp", "Images/rock.bmp");

	//skybox setup
	skybox = new Skybox();
	skybox->loadTextures();

	//player setup
	player = new Player("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp", 340.0f, 275.0f, -300.0f );
	player->alpha = 1.0f;

	//enemies setup
	for(int i = 0; i < NUM_OBJS; i++){
		npc[i] = new MD2Model();
		npc[i]->LoadMD2Model("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp");
		npc[i]->pos = Vector(rnd.number(10.0f, MAP_X * MAP_SCALE * 0.9f), 275.0f, -rnd.number(10.0f, MAP_Z * MAP_SCALE * 0.9f));
		npc[i]->alpha = 1.0f;
	}

	float matSpec[] = {0.0f, 1.0f, 0.0f, 1.0f };
	float matShiny[] = {128.0f};  //128 is max value
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSpec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);
	lightPos[0]=100; lightPos[1]=400; lightPos[2]= -200; lightPos[3]=1.0f;
	float whiteLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	lSphere = gluNewQuadric();	//to show where light pos is
	gluQuadricDrawStyle(lSphere, GLU_FILL);
	gluQuadricNormals(lSphere, GLU_NONE);
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
	delete font1;
	delete timer;
	delete terrain;
	if(lSphere != NULL)
		gluDeleteQuadric(lSphere);
	DebugOut("TERMINATED");
}

void Game::Update(){
	cft = timer->getElapsedTime();
	tbf = cft - lft;
	lft = cft;
	// Perform collision detection here

	for(int i = 0; i < NUM_OBJS; i++)
		calcYFromCubeCtr(npc[i], npc[i]->bb.ySize() / 2.0f);

	calcYFromCubeCtr(player, player->bb.ySize()  / 2.0f);

	toX = player->getPos().x; toY = player->getPos().y; toZ = player->getPos().z;
	CameraPos();
}

void Game::drawLightSource(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		gluSphere(lSphere, 20.0f, 20, 12);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

// and now render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	skybox->draw(0, 0, 0,5000,5000,5000);
	// set camera position 
	useCamera();
	terrain->render();
	if(drawLight)
		drawLightSource();	
	player->render();
	renderPlayer();
	// Display statistics
	RenderHUD();

	glFlush();
	fCount++;	// increment frame counter
}

void Game::RenderHUD(){
	// Change to 2D view and use 1:1 pixel resolution with
	// [0,0] origin being at the top-left corner.
	Set2D(0, m_width, m_height, 0);
	// Disable depth testing so the HUD will not be hidden
	// by the 3D graphics
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	// Semi transparent background for frame rate stats
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(m_width, 50);
		glVertex2f(m_width, 0);
	glEnd();
	glDisable(GL_BLEND);

	// Calc stats - FPS etc
	fps = 1.0f / tbf;
	avgFps = fCount / cft;
	// Print the statistics
	sprintf_s(text, "  Score: %i Lives: %i Has Flag: ", player->getScore(), player->getLives());
	font1->setColor(1.0f, 1.0f, 1.0f);
	font1->printString(4, 20, text);
	sprintf_s(text, "%6.1f FPS  Time: %4.1f", avgFps, cft );
	font1->setColor(1.0f, 1.0f, 1.0f);
	font1->printString(4, 40, text);

	// Set back to 3D
	Set3D(60, 0.1, 3000);
}

void Game::CameraPos(){
	// Map the mouse position to two angles
	angNS = ((mouseY + 1) / m_height) * (float)M_PI;
	angEW = (mouseX / m_width) * 2 * (float)M_PI;
	// Calculate the sines and cosines of these angle
	float sinNS = sin(angNS);
	float cosNS = cos(angNS);
	float sinEW = sin(angEW);
	float cosEW = cos(angEW);
	// calculate the camera coordinate

	camZ = toZ + camRad * sinNS * cosEW;
	camY = toY + camRad * cosNS;
	camX = toX + camRad * sinNS * sinEW;

	if(camRad < CAM_MIN)
		camRad = CAM_MIN;
	if(camRad > CAM_MAX)
		camRad = CAM_MAX;
}

void Game::useCamera(){
	gluLookAt(camX, camY, camZ, player->getPos().x, player->getPos().y, player->getPos().z, 0.0f, 1.0f, 0.0f);
}

void Game::renderPlayer(){
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	for(int i = 0; i < NUM_OBJS; i++){
		glPushMatrix();
			glTranslatef(npc[i]->pos.x, npc[i]->pos.y, npc[i]->pos.z);
			//npc[i]->bb.render();
			glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
			npc[i]->DisplayMD2Interpolate(0, 0, 0.07);
		glPopMatrix();
	}
}

/*
  UnProject Based on Ch. 3 in OpenGL red book.
  Note: they must be used AFTER the camera position has been set.
  From current mouseX and mouseY, calc. where it would intersect near / far plane, as req’d.
  Function returns 3D pos, if a ray was directed from the curr. camera pos to the far plane.
*/
Vector Game::unProject(){
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16], fx,fy,fz;

	GLint realy;    //OpenGL y coordinate position

	glGetIntegerv (GL_VIEWPORT, viewport); //get viewport and transform matrices
	glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
	realy = viewport[3]-(GLint)mouseY-1;  //viewport[3] is hgt of window in pixels
	gluUnProject((GLdouble)mouseX, (GLdouble)realy, 1.0, mvmatrix, projmatrix, viewport, &fx, 	&fy, &fz); //1.0 for FAR plane co-ordinates
	return Vector(fx, fy, fz);
}



