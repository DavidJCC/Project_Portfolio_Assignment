#include "Terrain.h"


Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}

void Terrain::init(char* terrBMP, char* terrTexture)
{
	LoadTextures *lt = new LoadTextures(false);  //don't create texture
	lt->LoadBMP(terrBMP);
	unsigned char *imageData = new unsigned char[MAP_X * MAP_Z];

// As a Greyscale bmp has the same R, G & B values, only use every 3rd value
	for (int i = 0; i < MAP_X*MAP_Z*3; i += 3)
		imageData[i/3] = lt->textureImageData[i];

// loop through all of the heightfield points & load to terrain array
	for (int z = 0; z < MAP_Z; z++)
		for (int x = 0; x < MAP_X; x++)
			terrain[z * MAP_Z + x] = (float)imageData[z * MAP_Z + x];

	for (int z = 0; z < MAP_Z; z++)	//calc normals after ALL heights loaded.
		for (int x = 0; x < MAP_X; x++)
			terrNorms[z * MAP_Z + x] = calcAvgNormal(x, z);

	delete lt;
	delete imageData;

	lt = new LoadTextures(terrTexture);
	land = lt->getTexture();
	delete lt;
}

/*
Calc. avg normal around p0.  Points arranged as follows
         p3
         |
	p2 -- p0 -- p4
         |
	      p1
*/
Vector Terrain::calcAvgNormal(int x, int z)
{
	Vector p0, p1, p2, p3, p4, n1, n2, n3, n4, sn;
	p0.x = x * MAP_SCALE; p0.y = terrain[x + z*MAP_Z]; p0.z = -z * MAP_SCALE;
	p1 = p2 = p3 = p4 = p0;
	if(z != 0){
		p1.y=terrain[x + (z-1)*MAP_Z]; //p1 below p0
		p1.z = -(z-1) * MAP_SCALE;
	}
	if(x != 0){
		p2.x=(x-1)*MAP_SCALE; //p2 left of p0
		p2.y=terrain[x-1 + z*MAP_Z];
	}
	if(z < MAP_Z){ 
		p3.y=terrain[x + (z+1)*MAP_Z]; //p3 above p0
		p3.z = -(z+1) * MAP_SCALE;
	}
	if(x < MAP_X){ 
		p4.x = (x+1)*MAP_SCALE; //p4 right of p0
		p4.y=terrain[x+1 + z*MAP_Z];
	}

	n1 = normToPlane(p0, p1, p2); //calc normals for each pt around p0
	n2 = normToPlane(p0, p2, p3); 
	n3 = normToPlane(p0, p3, p4); 
	n4 = normToPlane(p0, p4, p1); 

	sn = n1 + n2 + n3 + n4;  // sum normals
	sn.Normalize();
	return sn;
}

//pl, p2 & p3 should be in CW order.  Returns unit normal to plane
Vector Terrain::normToPlane(Vector p1, Vector p2, Vector p3)
{	
	Vector v1, v2, n;
	v1 = p1 - p2;
	v2 = p3 - p2;
	n = v1.CrossProduct(v2);
	if(n.Length() > 0) n.Normalize();
	return n;
}

void Terrain::render()
{
	float matSpec[] = {0.0f, 1.0f, 0.0f, 1.0f };
	float matShiny[] = {50.0 };  //128 is max value
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSpec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, land);
	float xp, zp;
	glPushMatrix();
		for (int x = 0; x < MAP_X-1; x++){
			glBegin(GL_TRIANGLE_STRIP);
			for (int z = 0; z < MAP_Z-1; z++){
				xp = (float)x * MAP_SCALE;
				zp = (float)z * MAP_SCALE;
			/* for each vertex, calc the greyscale shade colour & draw the vertex.
			   the vertices are drawn in this order:
					2 -> 3
					  <
					0 -> 1  */
		
				// draw vertex 0
				float c = terrain[x + z*MAP_Z]/MAP_Y;
				glColor3f(c,c,c);
				glNormal3f(terrNorms[x + z*MAP_Z].x, terrNorms[x + z*MAP_Z].y, terrNorms[x + z*MAP_Z].z);
				glTexCoord2f(0.0f, 0.0f);  glVertex3f(xp, terrain[x + z*MAP_Z], -zp);

				// draw vertex 1
				c = terrain[x+1 + z*MAP_Z]/MAP_Y;
				glColor3f(c,c,c);
				glNormal3f(terrNorms[x+1 + z*MAP_Z].x, terrNorms[x+1 + z*MAP_Z].y, terrNorms[x+1 + z*MAP_Z].z);
				glTexCoord2f(1.0f, 0.0f);  glVertex3f(xp+MAP_SCALE, terrain[x+1 + z*MAP_Z], -zp);

				// draw vertex 2
				c = terrain[x + (z+1)*MAP_Z]/MAP_Y;
				glColor3f(c,c,c);
				glNormal3f(terrNorms[x + (z+1)*MAP_Z].x, terrNorms[x + (z+1)*MAP_Z].y, terrNorms[x + (z+1)*MAP_Z].z);
				glTexCoord2f(0.0f, 1.0f);  glVertex3f(xp, terrain[x + (z+1)*MAP_Z], -(zp+MAP_SCALE));

				// draw vertex 3
				c = terrain[x+1 + (z+1)*MAP_Z]/MAP_Y;
				glColor3f(c,c,c);
				glNormal3f(terrNorms[x+1 + (z+1)*MAP_Z].x, terrNorms[x+1 + (z+1)*MAP_Z].y, terrNorms[x+1 + (z+1)*MAP_Z].z);
				glTexCoord2f(1.0f, 1.0f);  glVertex3f(xp+MAP_SCALE, terrain[x+1+(z+1)*MAP_Z], -(zp+MAP_SCALE));
			}
			glEnd();
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
