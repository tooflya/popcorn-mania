#ifndef CONST_DUST
#define CONST_DUST

#include "Dust.h"

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

Dust::Dust() :
Entity(Resources::R_LEVEL_DUST)
{
    this->mSpeedTime = Utils::randomf(1.0f, 5.0f);
    this->mSpeedTimeElapsed = 10.0f;
    
    this->mAlphaTime = Utils::randomf(1.0f, 5.0f);
    this->mAlphaTimeElapsed = 10.0f;
    
    this->mScaleTime = Utils::randomf(1.0f, 5.0f);
    this->mScaleTimeElapsed = 10.0f;
    
    this->mIsMustChangeSpeedX = false;
    this->mIsMustChangeSpeedY = false;
}

// ===========================================================
// Methods
// ===========================================================

Entity* Dust::create()
{
    Entity* entity = Entity::create();
    
    entity->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), 0);
    
    entity->setOpacity(Utils::random(100, 255));
    entity->setScale(Utils::randomf(0.1f, 1.0f));
    
    this->mSpeedX = Utils::randomf(0.1f, 100.0f);
    this->mSpeedY = Utils::randomf(0.1f, 100.0f);
    
    return entity;
}

void Dust::update(float pDeltaTime)
{
    Entity::update(pDeltaTime);
    
    if(this->mIsMustChangeSpeedX || this->mIsMustChangeSpeedY)
    {
        if(this->mIsMustChangeSpeedX)
        {
            if(abs(this->mMustSpeedX - this->mSpeedX) > 1.0f)
            {
                this->mSpeedX = this->mMustSpeedX > this->mSpeedX ? this->mSpeedX + 0.5f : this->mSpeedX - 0.5f;
            }
            else
            {
                this->mIsMustChangeSpeedX = false;
            }
        }
        if(this->mIsMustChangeSpeedY)
        {
            if(abs(this->mMustSpeedY - this->mSpeedY) > 1.0f)
            {
                this->mSpeedY = this->mMustSpeedY > this->mSpeedY ? this->mSpeedY + 0.5f : this->mSpeedY - 0.5f;
            }
            else
            {
                this->mIsMustChangeSpeedY = false;
            }
        }
    }
    else
    {
        this->mSpeedTimeElapsed += pDeltaTime;
    
        if(this->mSpeedTimeElapsed >= this->mSpeedTime)
        {
            this->mSpeedTimeElapsed = 0;
        
            this->mMustSpeedX = Utils::randomf(-50.0f, 50.0f);
            this->mMustSpeedY = Utils::randomf(-50.0f, 50.0f);
        
            this->mSpeedTime = Utils::randomf(1.0f, 5.0f);
            
            this->mIsMustChangeSpeedX = true;
            this->mIsMustChangeSpeedY = true;
        }
    }
    
    this->mAlphaTimeElapsed += pDeltaTime;
    
    if(this->mAlphaTimeElapsed >= this->mAlphaTime)
    {
        this->mAlphaTimeElapsed = 0;
        
        this->mAlphaTime = Utils::randomf(1.0f, 5.0f);
        
        this->runAction(CCFadeTo::create(3.0f, Utils::random(50, 255)));
    }
    
    this->mScaleTimeElapsed += pDeltaTime;
    
    if(this->mScaleTimeElapsed >= this->mScaleTime)
    {
        this->mScaleTimeElapsed = 0;
        
        this->mScaleTime = Utils::randomf(1.0f, 5.0f);
        
        this->runAction(CCScaleTo::create(3.0f, Utils::randomf(0.1f, 1.0f)));
    }
    
    this->setCenterPosition(this->getCenterX() - this->mSpeedX * pDeltaTime, this->getCenterY() - this->mSpeedY * pDeltaTime);
    
    if(
       this->getOpacity() <= 50.0f ||
       this->getCenterX() < -Utils::coord(100.0f) ||
       this->getCenterX() > Options::CAMERA_WIDTH + Utils::coord(100.0f) ||
       this->getCenterY() < -Utils::coord(100.0f) ||
       this->getCenterY() > Options::CAMERA_HEIGHT + Utils::coord(100.0f) ||
       this->getScale() < 0.1f)
    {
        this->destroy();
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Dust* Dust::deepCopy()
{
    return new Dust();
}

#endif