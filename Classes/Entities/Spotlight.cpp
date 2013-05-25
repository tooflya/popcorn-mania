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

Spotlight::Spotlight(CCNode* pParent)
    :Entity(Resources::R_MENU_SPOTLIGHT, pParent)
    {
        this->mAnimationRotateSpeed = 0.01f; // Utils::random(10.0f, 100.0f);
        
        this->mIsAnimationRotateReverse = true;
        
        this->mAnimationRotateMaxAngle = 10.0f;
        this->mAnimationRotateMinAngle = -10.0f;
        
        this->setAnchorPoint(ccp(0.75f, 0.5f));
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
    return new Spotlight(this->getParent());
}

#endif