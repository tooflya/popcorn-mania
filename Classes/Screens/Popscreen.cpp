#ifndef CONST_POPSCREEN
#define CONST_POPSCREEN

#include "Popscreen.h"

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

// ===========================================================
// Constructors
// ===========================================================

Popscreen::Popscreen()
{
	this->scheduleUpdate();
}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

bool Popscreen::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void Popscreen::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	
}

void Popscreen::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	
}

void Popscreen::onTouch(CCTouch* touch, CCEvent* event)
{
    
}

// ===========================================================
// Virtual methods
// ===========================================================

void Popscreen::onEnter()
{
	CCLayer::onEnter();
}

void Popscreen::onExit()
{
	CCLayer::onExit();
}

void Popscreen::update(float pDeltaTime)
{
    CCLayer::update(pDeltaTime);
    
    if(this->mNeedToHide)
    {
        this->mHideTimeElapsed += pDeltaTime;
        
        if(this->mHideTimeElapsed >= 0.35f)
        {
            this->mNeedToHide = false;
            this->mHideTimeElapsed = 0;
            
            this->removeFromParentAndCleanup(false);
        }
    }
}
#endif