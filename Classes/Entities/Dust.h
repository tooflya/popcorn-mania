#ifndef CONST_DUST_H
#define CONST_DUST_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Dust : public Entity
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
    
        float mSpeedX;
        float mSpeedY;
    
        float mMustSpeedX;
        float mMustSpeedY;
    
        float mSpeedTime;
        float mSpeedTimeElapsed;
    
        float mAlphaTime;
        float mAlphaTimeElapsed;
    
        float mScaleTime;
        float mScaleTimeElapsed;
    
        bool mIsMustChangeSpeedX;
        bool mIsMustChangeSpeedY;

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

		// ===========================================================
		// Constructors
		// ===========================================================
    
        Dust();

		// ===========================================================
		// Methods
		// ===========================================================
    
        void update(float pDeltaTime);
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
    
        virtual void onCreate();
        virtual void onDestroy();
    
        Dust* deepCopy();
};

#endif