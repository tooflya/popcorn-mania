#ifndef CONST_COLA
#define CONST_COLA

#include "Cola.h"

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

Cola::Cola() :
    ImpulseEntity(Resources::R_LEVEL_COLA, 3, 2)
    {
        this->mWeapon = new Weapon(this);
        
        this->setSpeed(700.0f);
        
        this->mTimeUntilDown = 0.17f;
        
        this->setShadowed(Resources::R_LEVEL_COLA_SHADOW);
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Cola::create()
{
    Cola* entity = (Cola*) Entity::create();
    
    entity->mIsDown = false;
    entity->mTimeUntilDownElapsed = 0;
    entity->setScaleX(1);
    entity->mWeight = Utils::coord(20.0f);
    entity->mImpulsePower = Utils::coord(1200.0f);
    
    entity->mIsGone = false;
    
    entity->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    entity->mSideImpulse   = Utils::coord(Utils::randomf(100.0f, 300.0f));
    entity->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
    
    entity->mSideImpulse = entity->getCenterX() < Options::CAMERA_CENTER_X ? -entity->mSideImpulse : entity->mSideImpulse;

    entity->setCurrentFrameIndex(Utils::random(0, 2));
    
    return entity;
}

void Cola::fall(float pVectorX, float pVectorY, bool pMustReverse)
{
    this->mIsGone = true;
    
    this->mGoneVectorX = pVectorX;
    this->mGoneVectorY = pVectorY;
    
    this->mIsMustReverse = pMustReverse;
    
    this->mWeapon->create()->animate(0.05f, 1);
    
    if(pMustReverse)
    {
        this->mWeapon->setCenterPosition(this->getWidth() / 2 - Utils::coord(110), this->getHeight() / 2 - Utils::coord(190));
        this->mWeapon->setScaleX(-1);
    }
    else
    {
        this->mWeapon->setCenterPosition(this->getWidth() / 2 + Utils::coord(110), this->getHeight() / 2 - Utils::coord(190));
        this->mWeapon->setScaleX(1);
    }
}

void Cola::update(float pDeltaTime)
{
    if(!this->isVisible()) return;
    
    if(this->mIsGone)
    {
        this->mTimeUntilDownElapsed += pDeltaTime;
        
        if(this->mTimeUntilDownElapsed >= this->mTimeUntilDown && !this->mIsDown)
        {
            this->mTimeUntilDownElapsed = 0;
            
            this->mWeight = Utils::coord(0.1f);
            
            this->setCurrentFrameIndex(this->getCurrentFrameIndex() + (Utils::random(0, 1) == 1 ? 3 : 3));
            
            this->mIsDown = true;
            
            if(this->mIsMustReverse)
            {
                this->setScaleX(1);
            }
            else
            {
                this->setScaleX(-1);
            }
            
            this->mWeapon->destroy();
        }
        
        if(this->mIsDown)
        {
            float vectorX = this->getCenterX() - this->mGoneVectorX;
            float vectorY = this->getCenterY() - this->mGoneVectorY;
        
            CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));
        
            this->setCenterPosition(this->getCenterX() + vector.x, this->getCenterY() + vector.y - this->mWeight);
        
            this->setRotation(this->getRotation() - this->mSideImpulse * pDeltaTime);
        
            this->mWeight = this->mWeight >= Utils::coord(10.0f) ? Utils::coord(10.0f) : this->mWeight + Utils::coord(0.2f);
            
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
    
    if(this->getCenterY() < -Utils::coord(200))
    {
        this->destroy();
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Cola* Cola::deepCopy()
{
    return new Cola();
}

#endif