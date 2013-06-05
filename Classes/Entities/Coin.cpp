#ifndef CONST_COIN
#define CONST_COIN

#include "Coin.h"

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

Coin::Coin() :
    ImpulseEntity(Resources::R_LEVEL_COIN, 3, 2)
    {
        this->setShadowed(Resources::R_LEVEL_COIN_SHADOW);
        //this->setRegisterAsTouchable(true);
        
        this->animate(0.1f);
    }

// ===========================================================
// Methods
// ===========================================================

void Coin::onCreate()
{
    this->setScaleX(1);
    this->mWeight = 20.0f;
    this->mImpulsePower = 1200.0f;
    
    this->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    this->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
    this->mRotateImpulse = Utils::randomf(-360.0f, 360.0f);
    
    this->mSideImpulse = this->getCenterX() < Options::CAMERA_CENTER_X ? -this->mSideImpulse : this->mSideImpulse;
    
    this->setCurrentFrameIndex(Utils::random(0, 2));
}

void Coin::onDestroy()
{
}

void Coin::onTouch(CCTouch* touch, CCEvent* event)
{
    this->destroy();
}

void Coin::update(float pDeltaTime)
{
    if(!this->isVisible()) return;
    
    ImpulseEntity::update(pDeltaTime);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Coin* Coin::deepCopy()
{
    return new Coin();
}

#endif