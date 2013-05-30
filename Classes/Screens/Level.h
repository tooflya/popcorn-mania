#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Popscreen.h"
#include "Pause.h"
#include "GameOver.h"

#include "Bucket.h"
#include "Popcorn.h"
#include "Dust.h"
#include "Lose.h"
#include "Weapon.h"
#include "Coin.h"
#include "Lights.h"

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
    
        float mLightsTime;
        float mLightsTimeElapsed;

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
    
        BatchEntityManager* mDusts;
        BatchEntityManager* mLoseMarks;
        BatchEntityManager* mLights;
        BatchEntityManager* mLargeFont;
        BatchEntityManager* mSmallFont;
    
        Entity* mBestLabel;
    
        BatchEntityManager* mLifesIcons;
    
        Entity* mBucketsCountIcon;

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
    
        EntityManager* mPopcorns;
    
        float mTouchPreviousCoordinateX;
        float mTouchPreviousCoordinateY;
    
        float mTouchCoordinateX;
        float mTouchCoordinateY;
    
        int mLifes;
        int mBucketsCount;
    
        bool mIsLevelRunning;
    
        Pause* mPauseScreen;
        GameOver* mGameOverScreen;
    
        bool mPaused;
    
        EntityManager* mBuckets;
        EntityManager* mCoins;
        
        Entity* mStartLevelBackground;
        Entity* mStartLevelNumbers;
    
        float mCounterBeforeStartTimeElapsed;
    
        int mCounterBeforeStart;
    
		// ===========================================================
		// Constructors
        // ===========================================================
    
        Level(ScreenManager* pScreenManager);

		// ===========================================================
		// Methods
        // ===========================================================
    
        void startLevel();
        void finishLevel();
    
        void updateFonts();
		
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