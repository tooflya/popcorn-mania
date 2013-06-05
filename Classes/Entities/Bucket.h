#ifndef CONST_BUCKET_H
#define CONST_BUCKET_H

#include "cocos2d.h"

#include "ImpulseEntity.h"
#include "Popcorn.h"
#include "Weapon.h"

using namespace cocos2d;

class Bucket : public ImpulseEntity
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
    
        int mType;
    
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
    
        Bucket();

		// ===========================================================
		// Methods
		// ===========================================================
    
        void fall(float pVectorX, float pVectorY, bool pMustReverse);
        void update(float pDelta);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
    
        virtual void onCreate();
        virtual void onDestroy();
    
        virtual Bucket* deepCopy();
};

#endif