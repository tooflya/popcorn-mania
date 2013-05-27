#ifndef CONST_BUCKET
#define CONST_BUCKET

#include "Bucket.h"

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

Bucket::Bucket() :
    ImpulseEntity(Resources::R_LEVEL_BUCKET, 3, 4)
    {
        this->mWeapon = new Weapon(this);
        
        this->setSpeed(700.0f);
        
        this->mTimeUntilDown = 0.17f;
        
        this->setShadowed();
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Bucket::create()
{
    Bucket* entity = (Bucket*) Entity::create();
    
    entity->mIsDown = false;
    entity->mTimeUntilDownElapsed = 0;
    entity->setScaleX(1);
    entity->mWeight = 20.0f;
    entity->mImpulsePower = 1200.0f;
    
    entity->mIsGone = false;
    
    entity->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    entity->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
    entity->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
    
    entity->mSideImpulse = entity->getCenterX() < Options::CAMERA_CENTER_X ? -entity->mSideImpulse : entity->mSideImpulse;

    entity->setCurrentFrameIndex(Utils::random(0, 2));
    
    return entity;
}

void Bucket::fall(float pVectorX, float pVectorY, bool pMustReverse)
{
    this->mIsGone = true;
    
    this->mGoneVectorX = pVectorX;
    this->mGoneVectorY = pVectorY;
    
    this->mIsMustReverse = false;//pMustReverse;
    
    this->mWeapon->create()->animate(0.05f, 1);
    this->mWeapon->setCenterPosition(this->getWidth() / 2 + Utils::coord(110), this->getHeight() / 2 - Utils::coord(190));
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
            else
            {
                this->setScaleX(1);
            }
            
            // Explosion
            
            for(int i = 0; i < 50; i++)
            {
                Level* a = (Level*) this->getParent();
                Popcorn* popcorn = (Popcorn*) a->mPopcorns->create();
                popcorn->setCenterPosition(this->getCenterX() - Utils::randomf(-60.0f, 60.0f), this->getCenterY() + Utils::coord(80) - Utils::randomf(-20.0f, 20.0f));
                
                popcorn->mWeight = Utils::randomf(10.0f, 20.0f);
                popcorn->mImpulsePower = Utils::randomf(100.0f, 500.0f);
                
                popcorn->mSideImpulse   = Utils::randomf(-150.0f, 150.0f);
                popcorn->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
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
            
            Entity::update(pDeltaTime);
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