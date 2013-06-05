#ifndef CONST_LOADING
#define CONST_LOADING

#include "Loading.h"

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

Loading::Loading()
{
    this->mBackground = new Entity(Resources::R_LOADING_BACKGROUND, this);
    this->mCoin = new Entity(Resources::R_SCREENS_POPCORN, 3, 2, this);
    
    this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    this->mCoin->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    
    this->mCoin->animate(0.1f);
    
    this->mScreensChangesReverse = false;
}

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

void Loading::update(float pDeltaTime)
{
    Screen::update(pDeltaTime);
    
    if(this->mProceed)
    {
        this->mProceedTimeElapsed += pDeltaTime;
        
        if(this->mProceedTimeElapsed >= 3.0f)
        {
            this->mProceed = false;
            
            AppDelegate::screens->set(0.5f, this->mScreensChangesReverse ? 0 : 2);
            
            this->mScreensChangesReverse = !this->mScreensChangesReverse;
        }
    }
}

void Loading::onEnter()
{
    Screen::onEnter();
    
    this->mProceed = true;
    this->mProceedTimeElapsed = 0;
}

#endif