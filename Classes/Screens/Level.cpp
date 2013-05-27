#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PauseButton : public Entity
{
    public:
        CCNode* mParent;
    
        PauseButton(CCNode* pParent) :
            Entity(Resources::R_LEVEL_PAUSE, pParent)
        {
            this->mParent = pParent;
            
            this->setRegisterAsTouchable(true);
        }
    
        void onTouch(CCTouch* touch, CCEvent* event)
        {
            ((Level*) this->mParent)->mPauseScreen->show();
            ((Level*) this->mParent)->mPaused = true;
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
        this->mPauseScreen = new Pause(pScreenManager);
        this->mGameOverScreen = new GameOver(pScreenManager);
        
        this->mTouchPreviousCoordinateX = -1;
        this->mTouchPreviousCoordinateY = -1;
        
        this->mTouchCoordinateX = -10000;
        this->mTouchCoordinateY = -10000;
        
        this->mIsDecorationReverse = false;
        
        this->mBackground = new Entity(Resources::R_LEVEL_BACKGROUND, this);
        this->mBackgroundDecoration = new Entity(Resources::R_LEVEL_DECORATION1, this);
        
        this->mDusts = new BatchEntityManager(20, new Dust(), this);
        
        for(int i = 0; i < 20; i++)
        {
            this->mDusts->create()->setCenterPosition(Utils::random(0, Options::CAMERA_WIDTH), Utils::random(0, Options::CAMERA_HEIGHT));
        }
        
        this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        this->mBackgroundDecoration->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        
        this->mBucketTime = 1.2f;
        this->mBucketTimeElapsed = 0;
        
        this->mCoins = new EntityManager(100, new Coin(), this, 5);
        this->mBuckets = new EntityManager(10, new Bucket(), this, 5);
        this->mPopcorns = new EntityManager(500, new Popcorn(), this, 5);
        
        (new PauseButton(this))->create()->setCenterPosition(Utils::coord(48), Utils::coord(48));
        (new Entity(Resources::R_LEVEL_BUCKETICON, this))->create()->setCenterPosition(Utils::coord(24), Options::CAMERA_HEIGHT - Utils::coord(24));
        
        this->mLoseMarks = new BatchEntityManager(3, new Lose(), this);
        
        this->mBucketCountText = CCLabelTTF::create("x 0", "Arial",  Utils::coord(24));
        this->mBucketCountText->setPosition(ccp(Utils::coord(55), Options::CAMERA_HEIGHT - Utils::coord(28)));
        this->addChild(this->mBucketCountText);
        
        this->mPaused = false;
        
        this->startLevel();
        
        this->addChild(this->mPauseScreen, 500);
        this->addChild(this->mGameOverScreen, 600);
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
    
    this->mLifes = 3;
}

void Level::finishLevel()
{
    this->mIsLevelRunning = false;
    
    this->mGameOverScreen->show();
    
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
    
    if(this->mPaused) return;
    
    this->mBackgroundDecoration->setRotation(this->mBackgroundDecoration->getRotation() + (this->mIsDecorationReverse ? -0.05f : 0.05f));
    
    if(this->mIsDecorationReverse)
    {
        if(this->mBackgroundDecoration->getRotation() <= -30.0f)
        {
            this->mIsDecorationReverse = !this->mIsDecorationReverse;
        }
    }
    else
    {
        if(this->mBackgroundDecoration->getRotation() >= 30.0f)
        {
            this->mIsDecorationReverse = !this->mIsDecorationReverse;
        }
    }
    
    this->mBucketTimeElapsed += pDelta;
    
    if(this->mBucketTimeElapsed >= this->mBucketTime && this->mIsLevelRunning)
    {
        this->mBucketTimeElapsed -= this->mBucketTime;
        
        Bucket* bucket = (Bucket*) this->mBuckets->create();
        Coin* coin = (Coin*) this->mCoins->create();
        
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
            bucket->fall(this->mTouchCoordinateX, this->mTouchCoordinateY, this->mTouchCoordinateX < bucket->getCenterX());
        }
    }
    
    if(this->mDusts->getCount() < 200)
    {
        this->mDusts->create();
    }
}

#endif