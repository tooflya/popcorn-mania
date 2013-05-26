#ifndef CONST_SCREENMANAGER_H
#define CONST_SCREENMANAGER_H

#include "cocos2d.h"

#include "Screen.h"

#include "Menu.h"
#include "Level.h"

#include "BatchEntityManager.h"

class Popscreen;

using namespace cocos2d;

class ScreenManager : public Screen
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
    
        float mLayersChangesSpeed;
    
        float mLockAnimationTimeElapsed;
    
        float mLockWaitTime;
        float mLockWaitTimeElapsed;
    
        bool mIsLockHiding;
        bool mIsLockShowing;
    
        bool mNeedHideLock;
    
        BatchEntityManager* mLines1;
        BatchEntityManager* mLines2;
    
        Entity* mPopcorn;
    
        CCLabelTTF* mTip1;
        CCLabelTTF* mTip2;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
        // ===========================================================
    
        void generate();
    
        void showLock();
        void hideLock();
    
        void onLockOnFinish();
        void onLockOffFinish();
    
        void onLockOnStart();
        void onLockOffStart();
		
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

		Popscreen* mScreens[5];

        int mCurrentScreenIndex;
        int mNextScreenIndex;

		// ===========================================================
		// Constructors
		// ===========================================================

		ScreenManager();

		// ===========================================================
		// Methods
		// ===========================================================
    
        virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
        virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
        virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
        void onTouch(CCTouch* touch, CCEvent* event);
    
        void set(int pIndex);
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
    
        void update(float pDelta);
    
        virtual void onEnter();
        virtual void onExit();
};

#endif