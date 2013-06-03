#ifndef CONST_COLA_H
#define CONST_COLA_H

#include "cocos2d.h"

#include "ImpulseEntity.h"
#include "Popcorn.h"
#include "Weapon.h"

using namespace cocos2d;

class Cola : public ImpulseEntity
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
    
        Weapon* mWeapon;

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
    
        bool mIsGone;
    
        bool mIsDown;
        bool mIsMustReverse;
    
        float mGoneVectorX;
        float mGoneVectorY;
    
        float mTimeUntilDown;
        float mTimeUntilDownElapsed;

		// ===========================================================
		// Constructors
		// ===========================================================
    
        Cola();

		// ===========================================================
		// Methods
		// ===========================================================
    
        Entity* create();
        void fall(float pVectorX, float pVectorY, bool pMustReverse);
        void update(float pDelta);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
    
        virtual Cola* deepCopy();
};

#endif