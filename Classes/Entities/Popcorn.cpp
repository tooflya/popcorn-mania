#ifndef CONST_POPCORN
#define CONST_POPCORN

#include "Popcorn.h"

#include "Level.h"

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

Popcorn::Popcorn() :
    ImpulseEntity(Resources::R_GAME_CORN, 1, 3)
    {
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Popcorn::create()
{
    Entity* entity = Entity::create();
    
    entity->setCurrentFrameIndex(Utils::random(0, 3));
    
    if(!this->mIsShadowed)
    {
        Level* a = (Level*) this->getParent()->getParent();
        this->mShadow = a->mPopcornsShadows->create();
    
        this->mIsShadowed = true;
    }
    else
    {
        this->mShadow->create();
    }
    
    return entity;
}

void Popcorn::update(float pDeltaTime)
{
    if(!this->isVisible()) return;
    
    ImpulseEntity::update(pDeltaTime);
    
    if(this->mImpulsePower <= 0)
    {
        if(this->getCenterY() < -this->getHeight())
        {
            this->destroy();
        }
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Popcorn* Popcorn::deepCopy()
{
    return new Popcorn();
}

#endif