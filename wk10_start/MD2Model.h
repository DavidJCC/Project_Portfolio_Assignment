/*
	Code Based on OpenGL Game Programming Ch. 18
	by Kevin Hawkins and Dave Astle
*/
#ifndef MD2MODEL_H
#define MD2MODEL_H

#include "md2.h"
#include "LoadTextures.h"
#include "Vector.h"
#include "AABB3.h"
#include "Object.h"

class MD2Model : public Object
{
	protected:
		modelData_t *myModel;
		float interValue;
		//int m_state;        // current model animation state
		//int m_nextState;    // state to automatically transition to after the current state is finished
		//int m_currentFrame; // current frame # in animation
		//int m_nextFrame;    // next frame # in animation
		//int m_startFrame;   // first frame in current animation
		//int m_endFrame;     // last frame in current animation
		//float m_interpol;          // percent through current frame  
		//int m_numVertices;
		//int m_numWeaponVertices;
		//int m_numFrames;
	public:
		AABB3 bb;  //****added by SM for easy access
		float alpha;
		MD2Model();
		~MD2Model();
		Vector m_pos;
		Vector &getPos() { return m_pos; }
		modelData_t* LoadMD2Model(char *filename, char *textureName);

		void DisplayMD2(int frameNum);
		void DisplayMD2Interpolate();
		void DisplayMD2Interpolate(int startFrame, int endFrame, float percent);
		void Render() {}
	private:
		texture_t* LoadBMPTexture(char *filename);
		void getTriPoints(modelData_t *model, int tIdx);
};

#endif