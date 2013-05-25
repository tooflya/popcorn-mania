#ifndef CONST_IMPULSEENTITY_H
#define CONST_IMPULSEENTITY_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class ImpulseEntity : public Entity
{
	protected:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================
    
        float mImpulsePower;
        float mSideImpulse;
        float mRotateImpulse;
        
        float mWeight;

		// ===========================================================
		// Constructors
        // ===========================================================
    
        ImpulseEntity(const char* pTextureFileName);
        ImpulseEntity(const char* pTextureFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		// ===========================================================
		// Methods
		// ===========================================================
    
        bool isCollideWithPoint(float pX, float pY);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
    
        void update(float pDelta);
};

#endif