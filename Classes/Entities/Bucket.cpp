#ifndef CONST_BUCKET
#define CONST_BUCKET

#include "Bucket.h"

#include "Level.h"

#include "AppDelegate.h"

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
    ImpulseEntity(Resources::R_LEVEL_BUCKET, 3, 8)
    {
        this->mWeapon = new Weapon(this);
        
        this->setSpeed(700.0f);
        
        this->mTimeUntilDown = 0.22;
        
        this->setShadowed(Resources::R_LEVEL_BUCKET_SHADOW);
    }

// ===========================================================
// Methods
// ===========================================================

void Bucket::fall(float pVectorX, float pVectorY, bool pMustReverse)
{
    this->mIsGone = true;
    
    this->mGoneVectorX = pVectorX;
    this->mGoneVectorY = pVectorY;
    
    this->mIsMustReverse = pMustReverse;
    
    this->mWeapon->create();
    this->mWeapon->animation();
    
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
    
    //SimpleAudioEngine::sharedEngine()->playEffect(Resources::SFX_KICK1);
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
            
            this->mWeight = Utils::coord(0.1f);
            
            this->setCurrentFrameIndex(this->getCurrentFrameIndex() + (this->mType == TYPE_BUCKET ? 2 : 1));
            
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
            
            if(this->mType == TYPE_BUCKET)
            {
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
            
            /*Level* level = (Level*) this->getParent();
            Water* water = (Water*) level->mWater->create();
            water->setCenterPosition(this->getCenterX() - water->getWidth() / 2 + Utils::coord(30), this->getCenterY() + water->getHeight() / 2 + Utils::coord(30));
            water->create();
            water->animation();
            water->setAnchorPoint(ccp(0.5, 0.5));
            water->setRotation(this->getRotation());*/
            
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

void Bucket::onCreate()
{
    this->mType = Utils::random(0, 3);
    
    this->mIsDown = false;
    this->mTimeUntilDownElapsed = 0;
    this->setScaleX(1);
    this->mWeight = Utils::coord(20.0f);
    this->mImpulsePower = Utils::coord(1200.0f);
    
    this->mIsGone = false;
    
    this->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
    
    this->mSideImpulse   = Utils::coord(Utils::randomf(100.0f, 300.0f));
    this->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
    
    this->mSideImpulse = this->getCenterX() < Options::CAMERA_CENTER_X ? -this->mSideImpulse : this->mSideImpulse;
    
    switch(this->mType)
    {
        case Bucket::TYPE_BUCKET:
            this->setCurrentFrameIndex(Utils::random(0, 2) * 3);
            break;
            
        case Bucket::TYPE_COLA:
            this->setCurrentFrameIndex(Utils::random(3, 5) * 3);
            break;
            
        case Bucket::TYPE_SUPER:
            this->setCurrentFrameIndex(18);
            break;
            
        case Bucket::TYPE_DANGER:
            this->setCurrentFrameIndex(21);
            break;
    }
    
    if(this->mType == TYPE_BUCKET)
    {
        for(int i = 0; i < 20; i++)
        {
            Level* a = (Level*) this->getParent();
            Popcorn* popcorn = (Popcorn*) a->mPopcorns->create();

            popcorn->setCenterPosition(this->getCenterX() - Utils::randomf(-60.0f, 60.0f), this->getCenterY() + Utils::coord(80) - Utils::randomf(-20.0f, 20.0f));
        
            popcorn->mWeight = this->mWeight;
            popcorn->mImpulsePower = this->mImpulsePower;
        
            popcorn->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
            popcorn->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
        }
    }
}

void Bucket::onDestroy()
{
    
}

Bucket* Bucket::deepCopy()
{
    return new Bucket();
}

#endif