#include "GameDomain.h"

GameDomain::GameDomain()
{
	lowX = lowY = lowZ = -1e10;
	highX = highY = highZ = 1e10;
}

GameDomain::GameDomain(float size)
{
	this->lowX = -size;
	this->highX = size;
	this->lowY = -size;
	this->highY = size;
	this->lowZ = -size;
	this->highZ = size;
	setColor(0.5f, 0.8f, 0.5f, 1.0f);
	calcCoordinates();
}

void GameDomain::setColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void GameDomain::Render()
{	glDisable(GL_LIGHTING);
	glPushMatrix();
	//draw egdes
	glColor4f(r, g, b, a);
		glLineWidth(2);
		drawEdge(0, 1);
		drawEdge(1, 2);
		drawEdge(2, 3);
		drawEdge(3, 0);
		drawEdge(4, 5);
		drawEdge(5, 6);
		drawEdge(6, 7);
		drawEdge(7, 4);
		drawEdge(0, 4);
		drawEdge(1, 5);
		drawEdge(2, 6);
		drawEdge(3, 7);
	//draw faces
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(r, g, b, a);
		drawFace(0, 4, 5, 1);
		drawFace(3, 7, 4, 0);
		drawFace(2, 6, 7, 3);
		drawFace(1, 5, 6, 2);
		drawFace(3, 0, 1, 2);
		drawFace(4, 7, 6, 5);
		glDisable(GL_BLEND);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void GameDomain::drawFace(int v0, int v1, int v2, int v3)
{
	glColor4f(r, g, b, a);
	glBegin(GL_QUADS);
		glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
		glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
		glVertex3f(verts[v2].x, verts[v2].y, verts[v2].z);
		glVertex3f(verts[v3].x, verts[v3].y, verts[v3].z);
	glEnd();
}

void GameDomain::drawEdge(int v0, int v1)
{
	glBegin(GL_LINES);
		glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
		glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
	glEnd();
}

void GameDomain::calcCoordinates()
{
	verts[0].set(lowX, highY, highZ);
	verts[1].set(highX, highY, highZ);
	verts[2].set(highX, highY, lowZ);
	verts[3].set(lowX, highY, lowZ);
	verts[4].set(lowX, lowY, highZ);
	verts[5].set(highX, lowY, highZ);
	verts[6].set(highX, lowY, lowZ);
	verts[7].set(lowX, lowY, lowZ);
}