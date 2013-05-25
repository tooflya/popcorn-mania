#ifndef CONST_POPCORN
#define CONST_POPCORN

#include "Popcorn.h"

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
    
    return entity;
}

void Popcorn::update(float pDeltaTime)
{
    ImpulseEntity::update(pDeltaTime);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Popcorn* Popcorn::deepCopy()
{
    return new Popcorn();
}

#endif