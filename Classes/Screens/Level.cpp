#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PauseButton : public Entity
{
    public:
        Level* mParent;
    
        PauseButton(Level* pParent) :
            Entity(Resources::R_LEVEL_PAUSE, 1, 2, pParent)
        {
            this->mParent = pParent;
            
            this->setRegisterAsTouchable(true);
        }
    
        void onTouch(CCTouch* touch, CCEvent* event)
        {
            if(this->mParent->mPaused)
            {
                this->mParent->mPauseScreen->hide();
                
                this->mParent->mBuckets->resumeSchedulerAndActions();
                this->mParent->mCoins->resumeSchedulerAndActions();
                this->mParent->mPopcorns->resumeSchedulerAndActions();
                
                this->setCurrentFrameIndex(0);
            }
            else
            {
                this->mParent->mPauseScreen->show();
            
                this->mParent->mBuckets->pauseSchedulerAndActions();
                this->mParent->mCoins->pauseSchedulerAndActions();
                this->mParent->mPopcorns->pauseSchedulerAndActions();
                
                this->setCurrentFrameIndex(1);
            }
            
            this->mParent->mPaused = !this->mParent->mPaused;
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
        
        this->mIsLevelRunning = false;
        
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
        
        PauseButton* pauseButton = new PauseButton(this);
        pauseButton->create()->setCenterPosition(Utils::coord(60), Utils::coord(48));
        pauseButton->setZOrder(501);
        
        this->mBucketsCountIcon = new Entity(Resources::R_LEVEL_BUCKETICON, this);
        this->mBucketsCountIcon->create()->setCenterPosition(Utils::coord(48), Options::CAMERA_HEIGHT - Utils::coord(48));
        this->mBucketsCountIcon->setZOrder(501);
        
        /*Entity* coinsCount = new Entity(Resources::R_LEVEL_COINS_ICON, 3, 2, this);
        coinsCount->create()->setCenterPosition(Utils::coord(48), Options::CAMERA_HEIGHT - Utils::coord(124));
        coinsCount->animate(0.1f);
        coinsCount->setZOrder(501);*/
        
        this->mLoseMarks = new BatchEntityManager(3, new Lose(), this);
        
        this->mBucketCountText = CCLabelTTF::create("41", "Arial",  Utils::coord(72));
        this->mBucketCountText->setPosition(ccp(Utils::coord(120), Options::CAMERA_HEIGHT - Utils::coord(48)));
        this->addChild(this->mBucketCountText, 501);
        
        this->mCoinsCountText = CCLabelTTF::create("Best: 14401", "Arial",  Utils::coord(36));
        this->mCoinsCountText->setPosition(ccp(Utils::coord(120), Options::CAMERA_HEIGHT - Utils::coord(100)));
        this->addChild(this->mCoinsCountText, 501);
        
        this->mPaused = false;
        
        this->addChild(this->mPauseScreen, 500);
        this->addChild(this->mGameOverScreen, 600);
        
        this->mStartLevelBackground = new Entity(Resources::R_LEVEL_START_BACKGROUND, 2, 1, this);
        this->mStartLevelNumbers = new Entity(Resources::R_LEVEL_START_NUMBERS, 3, 1, this);
        
        this->mStartLevelBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        this->mStartLevelBackground->animate(0.1f);
        
        this->mStartLevelNumbers->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        
        this->mCounterBeforeStart = 0;
        
        this->mLifesIcons = new BatchEntityManager(3, new Entity(Resources::R_LEVEL_LIFES, 1, 2), this);
        
        for(int i = 0; i < 3; i++)
        {
            this->mLifesIcons->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(40) - Utils::coord(50) * i, Options::CAMERA_HEIGHT - Utils::coord(40));
        }
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
    this->mPaused = false;
    this->mIsLevelRunning = false;
    
    this->mBuckets->clear();
    this->mCoins->clear();
    this->mPopcorns->clear();
    
    this->mBuckets->resumeSchedulerAndActions();
    this->mCoins->resumeSchedulerAndActions();
    this->mPopcorns->resumeSchedulerAndActions();
    
    this->mLifes = 3;
    this->mBucketsCount = 0;
    
    this->mCounterBeforeStart = 3;
    this->mCounterBeforeStartTimeElapsed = 0.0f;
    
    this->mStartLevelBackground->setOpacity(255.0f);
    this->mStartLevelNumbers->setOpacity(255.0f);
    
    this->mStartLevelNumbers->setCurrentFrameIndex(0);
    
    this->mStartLevelNumbers->setScale(1.25f);
    this->mStartLevelNumbers->runAction(CCScaleTo::create(1.0f, 0.75f));
    
    for(int i = 0; i < 3; i++)
    {
        ((Entity*) this->mLifesIcons->objectAtIndex(i))->setCurrentFrameIndex(0);
    }
}

void Level::finishLevel()
{
    this->mIsLevelRunning = false;
    
    this->mGameOverScreen->show();
    
    this->mPaused = true;
    
    this->mBuckets->pauseSchedulerAndActions();
    this->mCoins->pauseSchedulerAndActions();
    this->mPopcorns->pauseSchedulerAndActions();
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
    
    if(this->mIsLevelRunning)
    {
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
            
            if(bucket->isCollideWithPoint(this->mTouchCoordinateX, this->mTouchCoordinateY) && !bucket->mIsGone)
            {
                bucket->fall(this->mTouchCoordinateX, this->mTouchCoordinateY, this->mTouchCoordinateX < bucket->getCenterX());
                
                this->mBucketsCount++;
                
                this->mBucketsCountIcon->setScale(1.25f);
                this->mBucketsCountIcon->runAction(CCScaleTo::create(0.3f, 1.0f));
            }
            else if(bucket->getCenterY() < -bucket->getHeight() / 2 && !bucket->mIsGone && bucket->mImpulsePower <= 0)
            {
                this->mLoseMarks->create()->setCenterPosition(bucket->getCenterX(), Utils::coord(Utils::randomf(30.0f, 60.0f)));
            
                bucket->destroy();
            
                this->mLifes--;
                
                ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->setCurrentFrameIndex(1);
                ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->setScale(1.25f);
                ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->runAction(CCScaleTo::create(0.75f, 1.0f));
            
                if(this->mLifes <= 0)
                {
                    this->finishLevel();
                }
            }
        }
    }
    else
    {
        if(this->mCounterBeforeStart == 0)
        {
            this->startLevel();
        }
        
        this->mCounterBeforeStartTimeElapsed += pDelta;
        
        if(this->mCounterBeforeStartTimeElapsed >= 1.0f)
        {
            this->mCounterBeforeStartTimeElapsed -= 1.0f;
            this->mCounterBeforeStart--;
            
            this->mStartLevelNumbers->nextFrameIndex();
            
            this->mStartLevelNumbers->setScale(1.5f);
            this->mStartLevelNumbers->runAction(CCScaleTo::create(1.0f, 0.5f));
            
            if(this->mCounterBeforeStart <= 1)
            {
                this->mIsLevelRunning = true;
                
                this->mStartLevelBackground->runAction(CCFadeOut::create(0.3f));
                this->mStartLevelNumbers->runAction(CCFadeOut::create(0.5f));
            }
        }
    }
    
    if(this->mDusts->getCount() < 200)
    {
        this->mDusts->create();
    }
}

#endif