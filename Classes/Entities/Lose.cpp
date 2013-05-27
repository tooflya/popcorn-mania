#ifndef CONST_LOSE
#define CONST_LOSE

#include "Lose.h"

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

Lose::Lose() :
Entity(Resources::R_LEVEL_LOSE)
{
    this->mTime = 3.0f;
}

// ===========================================================
// Methods
// ===========================================================

Entity* Lose::create()
{
    Entity* entity = Entity::create();
    
    this->setScale(0.1f);
    this->runAction(CCScaleTo::create(0.1f, 1.0f));
    
    this->mTimeElapsed = 0;
    
    return entity;
}

void Lose::update(float pDeltaTime)
{
    Entity::update(pDeltaTime);
    
    this->mTimeElapsed += pDeltaTime;
    
    if(this->mTimeElapsed >= this->mTime)
    {
        this->mTimeElapsed = 0;
        
        this->runAction(CCScaleTo::create(0.1f, 0.0f));
    }
    
    if(this->getScale() <= 0.0f)
    {
        this->destroy();
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Lose* Lose::deepCopy()
{
    return new Lose();
}

#endif