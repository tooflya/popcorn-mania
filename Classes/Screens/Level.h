#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Screen.h"
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

class LevelPauseButton;

using namespace cocos2d;

class Level : public Screen
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
    
        float mCoinsTime;
        float mCoinsTimeElapsed;
    
        float mBucketsTimeMax;
    
        LevelPauseButton* mPauseButton;

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
        BatchEntityManager* mLifesIcons;
    
        Entity* mBucketsCountIcon;
        Entity* mBestLabel;

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
    
        BatchEntityManager* mPopcorns;
        BatchEntityManager* mPopcornsShadows;
        BatchEntityManager* mWater;
    
        float mTouchPreviousCoordinateX;
        float mTouchPreviousCoordinateY;
    
        float mTouchCoordinateX;
        float mTouchCoordinateY;
    
        int mLifes;
        int mBucketsCount;
        int mBestBucketsCount;
    
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
    
        bool mScaleAnimation;
    
		// ===========================================================
		// Constructors
        // ===========================================================
    
        Level();

		// ===========================================================
		// Methods
        // ===========================================================
    
        void startLevel();
        void finishLevel();
    
        void continueLevel();
    
        void updateFonts();
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
    
        virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
        virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
        virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
        virtual void onTouch(CCTouch* touch, CCEvent* event);
    
        void update(float pDelta);
    
        void onEnter();
};

#endif