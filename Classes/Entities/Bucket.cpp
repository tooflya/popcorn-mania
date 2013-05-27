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
        
        this->mTimeUntilDown = 0.17f;
        
        this->mShadow = new Entity(Resources::R_LEVEL_BUCKET_SHADOW, 3, 4);
        this->mShadow->setOpacity(230.0f);
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Bucket::create()
{
    if(!this->mShadow->getParent())
    {
        this->getParent()->addChild(this->mShadow, 1);
    }
    
    this->mShadow->create();
    
    Entity* entity = Entity::create();
    
    entity->setCurrentFrameIndex(Utils::random(0, 2));
    
    return entity;
}

void Bucket::update(float pDeltaTime)
{
    if(!this->isVisible()) return;
    
    if(this->mIsGone)
    {
        this->mTimeUntilDownElapsed += pDeltaTime;
        
        if(this->mTimeUntilDownElapsed >= this->mTimeUntilDown && !this->mIsDown)
        {
            this->mTimeUntilDownElapsed = 0;
            
            this->mWeight = 0.1f;
            
            this->setCurrentFrameIndex(this->getCurrentFrameIndex() + (Utils::random(0, 1) == 1 ? 9 : 9));
            
            this->mIsDown = true;
            
            if(this->mIsMustReverse)
            {
                this->setScaleX(-1);
            }
            else{
                this->setScaleX(1);
            }
        }
        
        if(this->mIsDown)
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
    else
    {
        ImpulseEntity::update(pDeltaTime);
    }
    
    this->mShadow->setCenterPosition(this->getCenterX() - Utils::coord(30.0f), this->getCenterY() - Utils::coord(30.0f));
    this->mShadow->setScale(this->getScaleX() - 0.1f);
    this->mShadow->setRotation(this->getRotation());
    this->mShadow->setCurrentFrameIndex(this->getCurrentFrameIndex());
    
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

Bucket* Bucket::deepCopy()
{
    return new Bucket();
}

#endif