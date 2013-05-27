#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Popscreen.h"

#include "Bucket.h"
#include "Popcorn.h"
#include "Dust.h"
#include "Lose.h"
#include "Weapon.h"

#include "EntityManager.h"
#include "BatchEntityManager.h"

using namespace cocos2d;

class Level : public Popscreen
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
    
        Entity* mBackground;
        Entity* mBackgroundDecoration;
    
        bool mIsDecorationReverse;

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
    
        float mBucketTime;
        float mBucketTimeElapsed;
    
        Entity* mGameOver;
    
        EntityManager* mBuckets;
    
        EntityManager* mPopcorns;
        BatchEntityManager* mDusts;
        BatchEntityManager* mLoseMarks;
    
        CCLabelTTF* mBucketCountText;

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
    
        float mTouchPreviousCoordinateX;
        float mTouchPreviousCoordinateY;
    
        float mTouchCoordinateX;
        float mTouchCoordinateY;
    
        int mLifes;
    
        bool mIsLevelRunning;

		// ===========================================================
		// Constructors
        // ===========================================================
    
        Level(ScreenManager* pScreenManager);

		// ===========================================================
		// Methods
        // ===========================================================
    
        void startLevel();
        void finishLevel();
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
    
        virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
        virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
        virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
        virtual void onTouch(CCTouch* touch, CCEvent* event);
    
        void update(float pDelta);
};

#endif