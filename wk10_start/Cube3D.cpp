#include "Cube3D.h"

int Cube3D::renderMode = CUBE_ONLY;

Cube3D::Cube3D(int uid){
	id = uid;
	colSphere = gluNewQuadric();
	gluQuadricDrawStyle(colSphere, GLU_LINE);
	gluQuadricNormals(colSphere, GLU_NONE);
	setSize(0.2f);
}

Cube3D::Cube3D(int uid, float size){
	id = uid;
	colSphere = gluNewQuadric();
	gluQuadricDrawStyle(colSphere, GLU_LINE);
	gluQuadricNormals(colSphere, GLU_NONE);
	setSize(size);
	LoadTextures *lt = new LoadTextures("Images/rock.bmp");
	texNum = lt->getTexture();
	delete lt;
}

Cube3D::~Cube3D(void){
	if(colSphere != NULL)
		gluDeleteQuadric(colSphere);
}

void Cube3D::setPos(float x, float y, float z){
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Cube3D::setVel(float x, float y, float z){
	vel.x = x;
	vel.y = y;
	vel.z = z;
}

void Cube3D::Move(float time){
	pos.x += vel.x * time;
	pos.y += vel.y * time;
	pos.z += vel.z * time;
}

void Cube3D::Update(float time){
	Move(time);
}

void Cube3D::Render(){
	float matSpec[] = {1.0f, 0.0f, 0.0f, 1.0f };
	float matShiny[] = {100.0 };  //128 is max value
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, matSpec);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);

		// Perform transformations here in TRS order
		glTranslatef(pos.x, pos.y, pos.z);
		if(renderMode == CUBE_ONLY || renderMode == CUBE_AND_SPHERE){
			fNorm = Vector(0.0f, 0.0f, 1.0f); drawFace(0, 4, 5, 1, 0.5f, 0.5f, 1.0f);  // Draw each face with a different colour
			fNorm = Vector(-1.0f, 0.0f, 0.0f); drawFace(3, 7, 4, 0, 0.5f, 1.0f, 0.5f);
			fNorm = Vector(0.0f, 0.0f, -1.0f); drawFace(2, 6, 7, 3, 0.5f, 1.0f, 1.0f);
			fNorm = Vector(1.0f, 0.0f, 0.0f); drawFace(1, 5, 6, 2, 1.0f, 0.5f, 0.5f);
			fNorm = Vector(0.0f, 1.0f, 0.0f); drawFace(3, 0, 1, 2, 1.0f, 0.5f, 1.0f);
			fNorm = Vector(0.0f, -1.0f, 0.0f); drawFace(4, 7, 6, 5, 1.0f, 1.0f, 0.5f);
		}
		if(renderMode == SPHERE_ONLY || renderMode == CUBE_AND_SPHERE){  // Draw collision sphere
			glColor3f(1.0f, 0.0f, 0.5f);
			gluSphere(colSphere, csRadius, 10 ,6);
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cube3D::drawFace(int v0, int v1, int v2, int v3, float r, float g, float b){
//	glColor3f(r, g, b);
	glBindTexture(GL_TEXTURE_2D, texNum);
	glNormal3f(fNorm.x, fNorm.y, fNorm.z);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(verts[v2].x, verts[v2].y, verts[v2].z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(verts[v3].x, verts[v3].y, verts[v3].z);
	glEnd();
}

void Cube3D::setSize(float size){
	float s = (float) size;
	float hs = size / 2;
	verts[0].set(-hs, hs, hs);
	verts[1].set( hs, hs, hs);
	verts[2].set( hs, hs,-hs);
	verts[3].set(-hs, hs,-hs);
	verts[4].set(-hs,-hs, hs);
	verts[5].set( hs,-hs, hs);
	verts[6].set( hs,-hs,-hs);
	verts[7].set(-hs,-hs,-hs);

	csRadius = hs * sqrt(3.0f);
}

bool Cube3D::collidesWith(Cube3D* cube){
	// Square of distance between cube centres
	float d2 = Vector::Dist2(pos, cube->pos);
	// Square of the sum of the collision radii
	float sr2 = (csRadius + cube->csRadius) * (csRadius + cube->csRadius);
	// Swap velocities
	if(d2 < sr2){
		Vector v = vel;
		vel = cube->vel;
		cube->vel = v;
		return true;
	}
	return false;
}
