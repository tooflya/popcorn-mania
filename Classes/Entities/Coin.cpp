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
        this->mHand = new Hand();
        
        this->mIsGone = false;
        
        this->setShadowed(Resources::R_LEVEL_COIN_SHADOW);
        
        this->animate(0.1f);
    }

// ===========================================================
// Methods
// ===========================================================

void Coin::fall()
{
    this->mIsGone = true;
    
    this->mHandPadding = 80.0;
    
    this->mHand->create();
    this->mHand->animation();
    
    this->runAction(CCScaleTo::create(0.3, 0.0));
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("coins", CCUserDefault::sharedUserDefault()->getIntegerForKey("coins") + 1);
}

void Coin::onCreate()
{
    this->mIsGone = false;
    
    this->setScaleX(1);
    
    this->mWeight = 20.0f;
    this->mImpulsePower = 1200.0f;
    
    this->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    this->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
    this->mRotateImpulse = Utils::randomf(-360.0f, 360.0f);
    
    this->mSideImpulse = this->getCenterX() < Options::CAMERA_CENTER_X ? -this->mSideImpulse : this->mSideImpulse;
    
    this->setCurrentFrameIndex(Utils::random(0, 2));
    
    if(this->mHand->getParent() == false)
    {
        this->getParent()->addChild(this->mHand, 4);
    }
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
    
    if(this->mIsGone)
    {
        this->mHand->setCenterPosition(this->getCenterX(), this->getCenterY() - this->mHandPadding);
        
        this->mHandPadding -= 5.0;
        
        if(this->getScaleX() <= 0.0)
        {
            this->destroy();
        }
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Coin* Coin::deepCopy()
{
    return new Coin();
}

#endif