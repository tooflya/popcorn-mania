#ifndef CONST_PEOPLE
#define CONST_PEOPLE

#include "People.h"

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

People::People()
    :Entity(Resources::R_MENU_PEOPLE, 4, 2)
    {
        this->mAnimationMoveSpeed = Utils::randomf(10.0f, 20.0f);
        this->mAnimationAmplitude = Utils::random(2.0f, 15.0f);
        
        this->mPositionX = 0;
        
        this->mAnimationMoveReverse = false;
    }

// ===========================================================
// Methods
// ===========================================================

void People::update(float pDelta)
{
    Entity::update(pDelta);
    
    if(this->mPositionX == 0)
    {
        this->mPositionX = this->getCenterX();
    }
    
    this->setCenterPosition(this->getCenterX() - (this->mAnimationMoveReverse ? this->mAnimationMoveSpeed * pDelta : -this->mAnimationMoveSpeed * pDelta), this->getCenterY());
    
    if(abs(this->getCenterX() - this->mPositionX) > this->mAnimationAmplitude)
    {
        this->mAnimationMoveReverse = !this->mAnimationMoveReverse;
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

People* People::deepCopy()
{
    return new People();
}

#endif