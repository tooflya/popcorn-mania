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

class Weapon : public Entity
{
public:
    Weapon(CCNode* pParent) :
    Entity(Resources::R_WEAPON_1, 5, 1, pParent)
    {
       
    }
    
    void onAnimationEnd()
    {
        this->destroy();
        
        this->removeFromParent();
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
        
        this->mTouchCoordinateX = -10000;
        this->mTouchCoordinateY = -10000;
        
        this->mBackground = new Entity(Resources::R_LEVEL_BACKGROUND, this);
        
        this->mDusts = new BatchEntityManager(20, new Dust(), this);
        
        for(int i = 0; i < 20; i++)
        {
            this->mDusts->create()->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), Utils::random(0, Options::CAMERA_HEIGHT));
        }
        
        this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        
        this->mBucketTime = 1.2f;
        this->mBucketTimeElapsed = 0;
        
        this->mBuckets = new EntityManager(100, new Bucket(), this, 5);
        this->mPopcorns = new EntityManager(100, new Popcorn(), this, 5);
        
        (new PauseButton(this))->create()->setCenterPosition(Utils::coord(48), Utils::coord(48));
        (new Entity(Resources::R_LEVEL_BUCKETICON, this))->create()->setCenterPosition(Utils::coord(24), Options::CAMERA_HEIGHT - Utils::coord(24));
        
        this->mLoseMarks = new BatchEntityManager(3, new Lose(), this);
        
        this->mGameOver = new Entity(Resources::R_LEVEL_GAMEOVER, this);
        this->mGameOver->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT + Utils::coord(200));
        
        this->mBucketCountText = CCLabelTTF::create("x 0", "Arial",  Utils::coord(24));
        this->mBucketCountText->setPosition(ccp(Utils::coord(55), Options::CAMERA_HEIGHT - Utils::coord(28)));
        this->addChild(this->mBucketCountText);
        
        this->startLevel();
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

void Level::startLevel()
{
    this->mIsLevelRunning = true;
    
    this->mLifes = 30;
}

void Level::finishLevel()
{
    this->mIsLevelRunning = false;
    
    this->mGameOver->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y)));
    
    for(int i = 0; i < this->mBuckets->getCount(); i++)
    {
        Bucket* bucket = (Bucket*) this->mBuckets->objectAtIndex(i);
        
        bucket->runAction(CCFadeOut::create(0.5f));
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Level::update(float pDelta)
{
    Popscreen::update(pDelta);
    
    this->mBucketTimeElapsed += pDelta;
    
    if(this->mBucketTimeElapsed >= this->mBucketTime && this->mIsLevelRunning)
    {
        this->mBucketTimeElapsed -= this->mBucketTime;
        
        Bucket* bucket = (Bucket*) this->mBuckets->create();
        
        bucket->mIsDown = false;
        bucket->mTimeUntilDownElapsed = 0;
        bucket->setScaleX(1);
        bucket->mWeight = 20.0f;
        bucket->mImpulsePower = 1200.0f;
        
        bucket->mIsGone = false;
        
        bucket->setCenterPosition(Utils::randomf(0.0f, Options::CAMERA_WIDTH), 0);
        
        bucket->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
        bucket->mRotateImpulse = 0;//Utils::randomf(-60.0f, 60.0f);
        
        bucket->mSideImpulse = bucket->getCenterX() < Options::CAMERA_CENTER_X ? -bucket->mSideImpulse : bucket->mSideImpulse;
        
        for(int i = 0; i < 20; i++)
        {
            Popcorn* popcorn = (Popcorn*) this->mPopcorns->create();
            popcorn->setCenterPosition(bucket->getCenterX() - Utils::randomf(-60.0f, 60.0f), bucket->getCenterY() + Utils::coord(80) - Utils::randomf(-20.0f, 20.0f));
            
            popcorn->mWeight = bucket->mWeight;
            popcorn->mImpulsePower = bucket->mImpulsePower;
            
            popcorn->mSideImpulse   = Utils::randomf(100.0f, 300.0f);
            popcorn->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
        }
    }
    
    for(int i = 0; i < this->mBuckets->getCount(); i++)
    {
        Bucket* bucket = (Bucket*) this->mBuckets->objectAtIndex(i);
        
        if(bucket->getCenterY() < -bucket->getHeight() / 2 && !bucket->mIsGone && bucket->mImpulsePower <= 0 && this->mIsLevelRunning)
        {
            this->mLoseMarks->create()->setCenterPosition(bucket->getCenterX(), Utils::coord(Utils::randomf(30.0f, 60.0f)));
            
            bucket->destroy();
            
            this->mLifes--;
            
            if(this->mLifes <= 0)
            {
                this->finishLevel();
            }
        }
        
        if(bucket->isCollideWithPoint(this->mTouchCoordinateX, this->mTouchCoordinateY) && !bucket->mIsGone)
        {
            bucket->mIsGone = true;
            
            bucket->mGoneVectorX = this->mTouchCoordinateX;
            bucket->mGoneVectorY = this->mTouchCoordinateY;
            
            for(int i = 0; i < 50; i++)
            {
                Popcorn* popcorn = (Popcorn*) this->mPopcorns->create();
                popcorn->setCenterPosition(bucket->getCenterX() - Utils::randomf(-60.0f, 60.0f), bucket->getCenterY() + Utils::coord(80) - Utils::randomf(-20.0f, 20.0f));
                
                popcorn->mWeight = Utils::randomf(10.0f, 20.0f);
                popcorn->mImpulsePower = Utils::randomf(100.0f, 300.0f);
                
                popcorn->mSideImpulse   = Utils::randomf(-150.0f, 150.0f);
                popcorn->mRotateImpulse = Utils::randomf(-60.0f, 60.0f);
            }
            
            Weapon* a = new Weapon(bucket);
            a->create()->setCenterPosition(bucket->getWidth()/2 + Utils::coord(110), bucket->getHeight()/2 - Utils::coord(190));
            a->animate(0.05f, 1);
            a->setZOrder(1000);
            
            if(this->mTouchCoordinateX < bucket->getCenterX())
            {
                bucket->mIsMustReverse = true;
            }
            else
            {
                bucket->mIsMustReverse = false;
            }
        }
    }
    
    if(this->mDusts->getCount() < 20)
    {
        this->mDusts->create();
    }
}

#endif