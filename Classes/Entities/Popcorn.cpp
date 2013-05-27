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
        this->mShadow = new Entity(Resources::R_LEVEL_CORN_SHADOW, 1, 3);
        this->mShadow->setOpacity(230.0f);
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Popcorn::create()
{
    if(!this->mShadow->getParent())
    {
        this->getParent()->addChild(this->mShadow, 1);
    }
    
    this->mShadow->create();
    
    Entity* entity = Entity::create();
    
    entity->setCurrentFrameIndex(Utils::random(0, 3));
    
    return entity;
}

void Popcorn::update(float pDeltaTime)
{
    ImpulseEntity::update(pDeltaTime);
    
    this->mShadow->setCenterPosition(this->getCenterX() - Utils::coord(30.0f), this->getCenterY() - Utils::coord(30.0f));
    this->mShadow->setScale(this->getScale() - 0.1f);
    this->mShadow->setRotation(this->getRotation());
    this->mShadow->setCurrentFrameIndex(this->getCurrentFrameIndex());
    
    if(this->mImpulsePower <= 0)
    {
        if(this->getCenterY() < -this->getHeight() / 2)
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