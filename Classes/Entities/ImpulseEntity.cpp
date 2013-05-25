#ifndef CONST_IMPULSEENTITY
#define CONST_IMPULSEENTITY

#include "ImpulseEntity.h"

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

ImpulseEntity::ImpulseEntity(const char* pTextureFileName) :
    Entity(pTextureFileName)
    {
        this->mWeight = 0;
        this->mSideImpulse = 0;
        this->mImpulsePower = 0;
        this->mRotateImpulse = 0;
    }

ImpulseEntity::ImpulseEntity(const char* pTextureFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
    Entity(pTextureFileName, pHorizontalFramesCount, pVerticalFramesCount)
    {
        this->mWeight = 0;
        this->mSideImpulse = 0;
        this->mImpulsePower = 0;
        this->mRotateImpulse = 0;
    }

// ===========================================================
// Methods
// ===========================================================

void ImpulseEntity::update(float pDelta)
{
    Entity::update(pDelta);
    
    if(this->mImpulsePower > 0)
    {
        this->setCenterPosition(this->getCenterX(), this->getCenterY() + this->mImpulsePower * pDelta);
        
        this->mImpulsePower -= this->mWeight;
    }
    else
    {
        this->setCenterPosition(this->getCenterX(), this->getCenterY() - this->mWeight * pDelta);
        
        this->mWeight += 5.0f;
    }
    
    this->setCenterPosition(this->getCenterX() - this->mSideImpulse * pDelta, this->getCenterY());
    this->setRotation(this->getRotation() - this->mRotateImpulse * pDelta);
    
    if(this->getCenterY() < 0 && this->mImpulsePower < 0)
    {
        this->destroy();
    }
}

bool ImpulseEntity::isCollideWithPoint(float pX, float pY)
{
    float x = pX - this->getCenterX();
    float y = pY - this->getCenterY();
    
    return x * x + y * y <= Utils::coord(500.0f) + Utils::coord(10.0f) * Utils::coord(500.0f) + Utils::coord(10.0f);
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif