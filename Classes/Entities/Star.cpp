#ifndef CONST_STAR
#define CONST_STAR

#include "Star.h"

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

Star::Star()
    :Entity(Resources::R_MENU_STAR, 1, 2)
    {
        this->mIsAnimationAlphaReverse = true;
        this->mIsAnimationScaleReverse = true;
        
        this->mAnimationMaxAlpha = 252.0f;
        this->mAnimationMinAlpha = 125.0f;
        
        this->mAnimationRotationSpeed = Utils::randomf(1.0f, 2.0f);
        this->mAnimationAlphaSpeed = Utils::random(0.1f, 3.0f);
        this->mAnimationScaleSpeed = Utils::randomf(0.001f, 0.01f);
    }

// ===========================================================
// Methods
// ===========================================================

Entity* Star::create()
{
    Entity* entity = Entity::create();
    
    entity->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), Utils::random(0, Options::CAMERA_HEIGHT));
    
    return entity;
}

void Star::setCurrentFrameIndex(int pIndex)
{
    Entity::setCurrentFrameIndex(pIndex);
    
    switch (pIndex)
    {
        case 0:
            
        break;
            
        case 1:
            this->setOpacity(Utils::random(this->mAnimationMinAlpha, this->mAnimationMaxAlpha));
        break;
    }
}

void Star::update(float pDelta)
{
    Entity::update(pDelta);
    
    switch(this->getCurrentFrameIndex())
    {
        case 0:
            this->setRotation(this->getRotation() + this->mAnimationRotationSpeed);
            
            if(this->mIsAnimationScaleReverse)
            {
                this->setScale(this->getScale() + this->mAnimationScaleSpeed);
                
                if(this->getScale() >= 1.0f)
                {
                    this->mIsAnimationScaleReverse = !this->mIsAnimationScaleReverse;
                }
            }
            else
            {
                this->setScale(this->getScale() - this->mAnimationScaleSpeed);
                
                if(this->getScale() <= 0.2f)
                {
                    this->mIsAnimationScaleReverse = !this->mIsAnimationScaleReverse;
                }
            }
        break;
            
        case 1:
            if(this->mIsAnimationAlphaReverse)
            {
                this->setOpacity(this->getOpacity() + this->mAnimationAlphaSpeed);
                
                if(this->getOpacity() >= this->mAnimationMaxAlpha)
                {
                    this->mIsAnimationAlphaReverse = !this->mIsAnimationAlphaReverse;
                }
            }
            else
            {
                this->setOpacity(this->getOpacity() - this->mAnimationAlphaSpeed);
                
                if(this->getOpacity() < this->mAnimationMinAlpha)
                {
                    this->mIsAnimationAlphaReverse = !this->mIsAnimationAlphaReverse;
                }
            }
        break;
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Star* Star::deepCopy()
{
    return new Star();
}

#endif