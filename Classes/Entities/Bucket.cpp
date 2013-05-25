#ifndef CONST_BUCKET
#define CONST_BUCKET

#include "Bucket.h"

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

Bucket::Bucket() :
    ImpulseEntity(Resources::R_LEVEL_BUCKET, 3, 4)
    {
        this->setSpeed(700.0f);
        
        this->setCurrentFrameIndex(Utils::random(0, 2));
    }

// ===========================================================
// Methods
// ===========================================================

void Bucket::update(float pDeltaTime)
{
    if(this->mIsGone)
    {
        float vectorX = this->getCenterX() - this->mGoneVectorX;
        float vectorY = this->getCenterY() - this->mGoneVectorY;
        
        CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));
        
        this->setCenterPosition(this->getCenterX() + vector.x, this->getCenterY() + vector.y - this->mWeight);
        
        this->setRotation(this->getRotation() - this->mSideImpulse * pDeltaTime);
        
        this->mWeight = this->mWeight > 10.0f ? 10.0f : this->mWeight + 0.2f;
    }
    else
    {
        ImpulseEntity::update(pDeltaTime);
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Bucket* Bucket::deepCopy()
{
    return new Bucket();
}

#endif