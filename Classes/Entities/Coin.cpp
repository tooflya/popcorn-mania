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

Entity* Coin::create()
{
    Coin* entity = (Coin*) Entity::create();
    
    entity->setScaleX(1);
    entity->mWeight = 20.0f;
    entity->mImpulsePower = 1200.0f;
    
    entity->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    entity->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
    entity->mRotateImpulse = Utils::randomf(-360.0f, 360.0f);
    
    entity->mSideImpulse = entity->getCenterX() < Options::CAMERA_CENTER_X ? -entity->mSideImpulse : entity->mSideImpulse;
    
    entity->setCurrentFrameIndex(Utils::random(0, 2));
    
    return entity;
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