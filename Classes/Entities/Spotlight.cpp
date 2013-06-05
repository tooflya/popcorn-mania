#ifndef CONST_SPOTLIGHT
#define CONST_SPOTLIGHT

#include "Spotlight.h"

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

Spotlight::Spotlight()
    :Entity(Resources::R_MENU_SPOTLIGHT)
    {
        this->mAnimationRotateSpeed = Utils::randomf(0.01f, 0.03f);
        
        this->mIsAnimationRotateReverse = true;
        
        this->mAnimationRotateMaxAngle = 10.0f;
        this->mAnimationRotateMinAngle = -10.0f;
        
        this->setAnchorPoint(ccp(0.0f, 0.0f));
    }

// ===========================================================
// Methods
// ===========================================================

void Spotlight::update(float pDelta)
{
    Entity::update(pDelta);
    
    if(this->mIsAnimationRotateReverse)
    {
        this->setRotation(this->getRotation() + this->mAnimationRotateSpeed);
        
        if(this->getRotation() >= this->mAnimationRotateMaxAngle)
        {
            this->mIsAnimationRotateReverse = !this->mIsAnimationRotateReverse;
        }
    }
    else
    {
        this->setRotation(this->getRotation() - this->mAnimationRotateSpeed);
        
        if(this->getRotation() <= this->mAnimationRotateMinAngle)
        {
            this->mIsAnimationRotateReverse = !this->mIsAnimationRotateReverse;
        }
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Spotlight* Spotlight::deepCopy()
{
    return new Spotlight();
}

#endif