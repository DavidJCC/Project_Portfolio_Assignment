#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "LoadTextures.h"
#include "Object.h"
/**
Class to represent a cube.

@author Peter Lager 2011
@version 1.5
*/
class Cube3D : public Object
{
public:
	/**
	Unique identity for each shape type
	If you add new rendermodes for this class add suitable values here
	*/
	static const enum renderModes {	CUBE_ONLY = 0 /**< 0 */,
									SPHERE_ONLY = 1, /**< 1 */  
									CUBE_AND_SPHERE = 2 /**< 1 */  
	};
	
	/// The render mode for all cubes
	static int renderMode;
protected:
	/**
	This is a unique identifier for the game object. <br>
	It will be initialised in the constructor and cannot be changed
	later because no setter method is provided. <br>
	It upto the creator to ensure that it is in fact unique,
	the program does not check for uniqueness.
	*/
	int id;

	/// XYZ coordinates for the corners
	Vector verts[8];

	/// Coordinates of the centre of the cube
	Vector pos;
	/// Velocity of the cube
	Vector vel;

	/// Collision sphere
	GLUquadricObj * colSphere;
	/// Collision radius
	float csRadius;

	unsigned int texNum;
	Vector fNorm;
protected:
	/**
	The default constructor: do not use this to create
	cubes as it will not set a unique identifier.
	*/
	Cube3D(void){}

	/**
	Used to keep the object within it's domain
	*/
	void keepInside();

public:
	/**
	Creates a cube of size 0.2
	@param uid unique identifying number
	*/
	Cube3D(int uid);

	/**
	Creates a cube of the given size
	@param uid unique identifying number
	@param size the size of the cube
	*/
	Cube3D(int uid, float size);

	/**
	Release memory used for the quadric
	*/
	virtual ~Cube3D(void);

	/// Get the unique identifier for this shape
	int getID(){ return id; }

	/// Inline method to get the collision radius
	float getColRadius(){ return csRadius; }

	/// Inline method to get the cubes position
	Vector& getPos(){ return pos; }

	/// Inline method to get the cubes velocity
	Vector& getVel(){ return vel; }

	/**
	Sets the position of the cube centre
	*/
	void setPos(float x, float y, float z);
	/**
	Sets the cubes velocity in 3D space
	*/
	void setVel(float x, float y, float z);

	/**
	Move the cube by (velocity * time)
	@param time elapsed time in seconds
	*/
	void Move(float time);

	/**
	Update the cube's state based on elpased time
	@param time elapsed time in seconds
	*/
	void Update(float time);

	/**
	Draw the cube
	*/
	void Render();

	/**
	Set / change the size of the cube <br>
	Calculates and store the vertex data for a cube based on a given
	size. 
	*/
	void setSize(float size);

	/**
	Test for collision between this cube and another one. <br>
	If a collision occurs then calculate the new velocities for each cube. <br>
	At the moment the velocity vectors are simply swapped.
	@param cube the other cube to test for collision
	@return true if a collision has occured
	*/
	bool Cube3D::collidesWith(Cube3D* cube);

//private:
	/**
	Used internally by the render method to render a single face
	in a given colour.
	*/
	void drawFace(int v0, int v1, int v2, int v3, float r, float g, float b);

};
