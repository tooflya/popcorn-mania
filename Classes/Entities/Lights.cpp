#ifndef CONST_LIGHTS
#define CONST_LIGHTS

#include "Lights.h"

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

Lights::Lights() :
    Entity(Resources::R_LEVEL_PHOTO_LIGHTS, 2, 2)
    {
    
    }

Lights::Lights(CCNode* pParent) :
    Entity(Resources::R_LEVEL_PHOTO_LIGHTS, 2, 2)
    {
        
    }

// ===========================================================
// Methods
// ===========================================================

void Lights::look(float pVectorX, float pVectorY)
{
    this->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), Utils::coord(70));
    
    //this->setRotation(atan2(this->getCenterY() , this->getCenterX() - 0));
}

Entity* Lights::create()
{
    Entity* entity = Entity::create();
    
    entity->setCurrentFrameIndex(Utils::random(0, 3));
    
    this->mLifeTime = Utils::randomf(0.16f, 0.3f);
    this->mLifeTimeElapsed = 0.0f;
    
    return entity;
}

void Lights::onAnimationEnd()
{
    this->destroy();
}

void Lights::update(float pDeltaTime)
{
    if(!this->isVisible()) return;
    
    Entity::update(pDeltaTime);
    
    this->mLifeTimeElapsed += pDeltaTime;
    
    if(this->mLifeTimeElapsed >= this->mLifeTime)
    {
       if(Utils::random(0, 1) == 1 && this->isVisible() || true)
       {
           this->destroy();
       }
       else
       {
           this->mLifeTimeElapsed = 0;
           
           this->setVisible(!this->isVisible());
           
           if(!this->isVisible())
           {
               this->mLifeTime = Utils::randomf(1.0f, 2.5f);
           }
           else
           {
               this->mLifeTime = Utils::randomf(0.16f, 0.3f);
           }
       }
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

Lights* Lights::deepCopy()
{
    return new Lights(this->getParent());
}

#endif