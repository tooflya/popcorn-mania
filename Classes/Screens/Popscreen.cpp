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

Popscreen::Popscreen(ScreenManager* pScreenManager)
{
    this->mScreenManager = pScreenManager;
    
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
	return true;
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
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void Popscreen::onExit()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

#endif