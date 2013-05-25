#ifndef CONST_SCREENMANAGER
#define CONST_SCREENMANAGER

#include "ScreenManager.h"

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

ScreenManager::ScreenManager()
{
	this->generate();
    
    this->mLayersChangesSpeed = 0.3f;
    
    this->mLockAnimationTimeElapsed = 0;
    
    this->mLockWaitTime = 1.5f;
    this->mLockWaitTimeElapsed = 0;
    
    this->mIsLockHiding = false;
    this->mIsLockShowing = false;
    
    this->mNeedHideLock = false;
    
    this->mLines1 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this, 10);
    this->mLines2 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this, 10);
    
    this->mPopcorn = new Entity(Resources::R_SCREENS_POPCORN, 3, 2);
    this->mPopcorn->animate(0.1f);
    this->mPopcorn->setOpacity(0);
    this->addChild(this->mPopcorn, 10);
    
    this->mLines1->setPosition(ccp(0, Options::CAMERA_HEIGHT));
    this->mLines2->setPosition(ccp(0, -Options::CAMERA_HEIGHT));
    
    this->mPopcorn->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    
    for(int i = 0; i < 20; i++)
    {
        this->mLines1->create()->setCenterPosition(i * Utils::coord(64) * 2, Options::CAMERA_CENTER_Y);
        
        Entity* line = this->mLines2->create();
        line->setCurrentFrameIndex(1);
        line->setCenterPosition(i * Utils::coord(64) * 2 + Utils::coord(64), Options::CAMERA_CENTER_Y);
    }
    
    this->setRegisterAsTouchable(true);
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

bool ScreenManager::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    return this->mScreens[this->mCurrentScreenIndex]->ccTouchBegan(touch, event);
}

void ScreenManager::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    this->mScreens[this->mCurrentScreenIndex]->ccTouchMoved(touch, event);
}

void ScreenManager::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    this->mScreens[this->mCurrentScreenIndex]->ccTouchEnded(touch, event);
}

void ScreenManager::onTouch(CCTouch* touch, CCEvent* event)
{
    this->mScreens[this->mCurrentScreenIndex]->onTouch(touch, event);
}

void ScreenManager::generate()
{
	this->mScreens[0] = new Menu(this);
	this->mScreens[1] = new Level(this);
    
    this->addChild(this->mScreens[0]);
    
    this->mCurrentScreenIndex = 0;
    this->mNextScreenIndex = 0;
}

void ScreenManager::showLock()
{
    if(this->mIsLockShowing || this->mIsLockHiding) return;
    
    this->mLines1->runAction(CCMoveTo::create(this->mLayersChangesSpeed, ccp(0, 0)));
    this->mLines2->runAction(CCMoveTo::create(this->mLayersChangesSpeed, ccp(0, 0)));
    
    this->mIsLockShowing = true;
    this->mLockAnimationTimeElapsed = 0;
    
    this->onLockOnStart();
}

void ScreenManager::hideLock()
{
    if(this->mIsLockShowing || this->mIsLockHiding) return;
    
    this->mLines1->runAction(CCMoveTo::create(this->mLayersChangesSpeed, ccp(0, Options::CAMERA_HEIGHT)));
    this->mLines2->runAction(CCMoveTo::create(this->mLayersChangesSpeed, ccp(0, -Options::CAMERA_HEIGHT)));
    
    this->mIsLockHiding = true;
    this->mLockAnimationTimeElapsed = 0;
    
    this->onLockOffStart();
}

void ScreenManager::onLockOnStart()
{
    this->mPopcorn->runAction(CCFadeIn::create(0.5f));
}

void ScreenManager::onLockOffStart()
{
    this->mPopcorn->runAction(CCFadeOut::create(0.5f));
}

void ScreenManager::onLockOnFinish()
{
    this->removeChild(this->mScreens[this->mCurrentScreenIndex]);
    this->addChild(this->mScreens[this->mNextScreenIndex]);
    
    this->mCurrentScreenIndex = this->mNextScreenIndex;
    
    this->mNeedHideLock = true;
    
    this->mLockWaitTimeElapsed = 0;
}

void ScreenManager::onLockOffFinish()
{
    
}

void ScreenManager::set(int pIndex)
{
    this->mNextScreenIndex = pIndex;
    
    this->showLock();
}

// ===========================================================
// Virtual methods
// ===========================================================

void ScreenManager::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCScene::onEnter();
}

void ScreenManager::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCScene::onExit();
}

void ScreenManager::update(float pDelta)
{
    Screen::update(pDelta);
    
    this->mLockAnimationTimeElapsed += pDelta;
    
    if(this->mLockAnimationTimeElapsed >= this->mLayersChangesSpeed * 2.0f)
    {
        if(this->mIsLockShowing)
        {
            this->mIsLockShowing = false;
            
            this->onLockOnFinish();
        }
        else if(this->mIsLockHiding)
        {
            this->mIsLockHiding = false;
            
            this->onLockOffFinish();
        }
    }
    
    if(this->mNeedHideLock)
    {
        this->mLockWaitTimeElapsed += pDelta;
        
        if(this->mLockWaitTimeElapsed >= this->mLockWaitTime)
        {
            this->hideLock();
            
            this->mNeedHideLock = false;
        }
    }
}

#endif