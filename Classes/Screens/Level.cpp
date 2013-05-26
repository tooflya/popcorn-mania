#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PauseButton : public Entity
{
    public:
        PauseButton(CCNode* pParent) :
            Entity(Resources::R_LEVEL_PAUSE, pParent)
        {
            this->setRegisterAsTouchable(true);
        }
};

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Level::Level(ScreenManager* pScreenManager) :
    Popscreen(pScreenManager)
    {
        this->mTouchPreviousCoordinateX = -1;
        this->mTouchPreviousCoordinateY = -1;
        
        this->mTouchCoordinateX = -1;
        this->mTouchCoordinateY = -1;
        
        this->mBackground = new Entity(Resources::R_LEVEL_BACKGROUND, this);
        
        this->mDusts = new BatchEntityManager(20, new Dust(), this);
        
        for(int i = 0; i < 20; i++)
        {
            this->mDusts->create()->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), Utils::random(0, Options::CAMERA_HEIGHT));
        }
        
        this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        
        this->mBucketTime = 1.2f;
        this->mBucketTimeElapsed = 0;
        
        this->mBuckets = new BatchEntityManager(100, new Bucket(), this);
        this->mPopcorns = new BatchEntityManager(100, new Popcorn(), this);
        
        (new PauseButton(this))->create()->setCenterPosition(Utils::coord(48), Utils::coord(48));
        (new Entity(Resources::R_LEVEL_BUCKETICON, this))->create()->setCenterPosition(Utils::coord(24), Options::CAMERA_HEIGHT - Utils::coord(24));
        
        this->mBucketCountText = CCLabelTTF::create("x 0", "Arial",  Utils::coord(24));
        
        this->mBucketCountText->setPosition(ccp(Utils::coord(55), Options::CAMERA_HEIGHT - Utils::coord(28)));
        
        this->addChild(this->mBucketCountText);
    }

// ===========================================================
// Methods
// ===========================================================

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	this->mTouchPreviousCoordinateX = touch->getLocation().x;
    this->mTouchPreviousCoordinateY = touch->getLocation().y;
    
	return true;
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	this->mTouchCoordinateX = touch->getLocation().x;
    this->mTouchCoordinateY = touch->getLocation().y;
    
	this->mTouchPreviousCoordinateX = touch->getLocation().x;
    this->mTouchPreviousCoordinateY = touch->getLocation().y;
}

void Level::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	this->mTouchCoordinateX = -10000;
    this->mTouchCoordinateY = -10000;
}

void Level::onTouch(CCTouch* touch, CCEvent* event)
{
	this->mTouchCoordinateX = touch->getLocation().x;
    this->mTouchCoordinateY = touch->getLocation().y;
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Level::update(float pDelta)
{
    Popscreen::update(pDelta);
    
    this->mBucketTimeElapsed += pDelta;
    
    if(this->mBucketTimeElapsed >= this->mBucketTime)
    {
        this->mBucketTimeElapsed -= this->mBucketTime;
        
        Bucket* bucket = (Bucket*) this->mBuckets->create();
        
        bucket->mWeight = 20.0f;
        bucket->mImpulsePower = 1200.0f;
        
        bucket->mIsGone = false;
        
        bucket->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
        
        bucket->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
        bucket->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
        
        bucket->mSideImpulse = bucket->getCenterX() < Options::CAMERA_CENTER_X ? -bucket->mSideImpulse : bucket->mSideImpulse;
        
        /*for(int i = 0; i < 50; i++)
        {
            Popcorn* popcorn = (Popcorn*) this->mPopcorns->create();
            popcorn->setCenterPosition(bucket->getCenterX() - Utils::randomf(-60.0f, 60.0f), bucket->getCenterY() + Utils::coord(80) - Utils::randomf(-20.0f, 20.0f));
            
            popcorn->mWeight = bucket->mWeight;
            popcorn->mImpulsePower = bucket->mImpulsePower;
            popcorn->mRotateImpulse = bucket->mRotateImpulse;
            popcorn->mSideImpulse = bucket->mSideImpulse;
        }*/
    }
    
    for(int i = 0; i < this->mBuckets->getCount(); i++)
    {
        Bucket* bucket = (Bucket*) this->mBuckets->objectAtIndex(i);
        
        if(bucket->isCollideWithPoint(this->mTouchCoordinateX, this->mTouchCoordinateY) && !bucket->mIsGone)
        {
            bucket->mIsGone = true;
            
            bucket->mGoneVectorX = this->mTouchCoordinateX;
            bucket->mGoneVectorY = this->mTouchCoordinateY;
            
            bucket->mWeight = 0.1f;
            
            bucket->setCurrentFrameIndex(bucket->getCurrentFrameIndex() + 9);
        }
    }
    
    if(this->mDusts->getCount() < 20)
    {
        this->mDusts->create();
    }
}

#endif