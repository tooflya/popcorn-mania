#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

class LevelPauseButton : public Entity
{
    public:
        Level* mParent;
    
        LevelPauseButton(Level* pParent) :
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
                this->mParent->addChild(this->mParent->mPauseScreen, 500);
            
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

Level::Level()
    {
        this->mGameOverScreen = new GameOver();
        this->mPauseScreen = new Pause();
        
        this->mTouchPreviousCoordinateX = -1;
        this->mTouchPreviousCoordinateY = -1;
        
        this->mTouchCoordinateX = -10000;
        this->mTouchCoordinateY = -10000;
        
        this->mIsDecorationReverse = false;
        
        this->mIsLevelRunning = false;
        this->mScaleAnimation = false;
        
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
        
        this->mCoinsTime = 10.0f;
        this->mCoinsTimeElapsed = 10.0f;
        
        this->mCoins = new EntityManager(10, new Coin(), this, 5);
        this->mBuckets = new EntityManager(10, new Bucket(), this, 5);
        this->mPopcornsShadows = new BatchEntityManager(200, new Entity(Resources::R_GAME_CORN_SHADOW, 1, 3), this, 4);
        this->mPopcorns = new BatchEntityManager(200, new Popcorn(), this, 5);
        
        this->mPauseButton = new LevelPauseButton(this);
        this->mPauseButton->create()->setCenterPosition(Utils::coord(60), Utils::coord(48));
        this->mPauseButton->setZOrder(501);
        
        this->mBucketsCountIcon = new Entity(Resources::R_LEVEL_BUCKETICON, this);
        this->mBucketsCountIcon->create()->setCenterPosition(Utils::coord(48), Options::CAMERA_HEIGHT - Utils::coord(48));
        this->mBucketsCountIcon->setZOrder(501);
        
        this->mLoseMarks = new BatchEntityManager(3, new Lose(), this);
        
        this->mLargeFont = new BatchEntityManager(10, new Entity(Resources::R_GAME_LARGE_FONT, 10, 1), this, 501);
        
        for(int i = 0; i < 10; i++)
            this->mLargeFont->create()->setCenterPosition(Utils::coord(100) + Utils::coord(30) * i, Options::CAMERA_HEIGHT - Utils::coord(50));
        
        for(int i = 0; i < 10; i++)
            ((Entity*) this->mLargeFont->objectAtIndex(i))->setVisible(false);
        
        this->mSmallFont = new BatchEntityManager(10, new Entity(Resources::R_GAME_SMALL_FONT, 10, 1), this, 501);
        
        for(int i = 0; i < 10; i++)
        this->mSmallFont->create()->setCenterPosition(Utils::coord(115) + Utils::coord(15) * i, Options::CAMERA_HEIGHT - Utils::coord(100));
        
        for(int i = 0; i < 10; i++)
        ((Entity*) this->mSmallFont->objectAtIndex(i))->setVisible(false);
        
        this->mBestLabel = new Entity(Resources::R_LEVEL_LABEL_BEST, 1, 2, this);
        this->mBestLabel->animate(0.2f);
        this->mBestLabel->create()->setCenterPosition(Utils::coord(60), Options::CAMERA_HEIGHT - Utils::coord(100));
        this->mBestLabel->setZOrder(501);
        
        this->mPaused = false;
        
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
        
        this->mLights = new BatchEntityManager(10, new Lights(), this);
        
        this->mLightsTime = Utils::randomf(0.5f, 3.0f);
        this->mLightsTimeElapsed = 0;
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

void Level::continueLevel()
{
    this->mPaused = false;
    this->mIsLevelRunning = true;
    
    this->mBuckets->resumeSchedulerAndActions();
    this->mCoins->resumeSchedulerAndActions();
    this->mPopcorns->resumeSchedulerAndActions();
    this->mPopcorns->resumeSchedulerAndActions();
    this->mPopcornsShadows->resumeSchedulerAndActions();
}

void Level::startLevel()
{
    this->mPaused = false;
    this->mIsLevelRunning = false;
    
    this->mPauseButton->setCurrentFrameIndex(0);
    
    this->mBuckets->clear();
    this->mCoins->clear();
    this->mPopcorns->clear();
    this->mPopcornsShadows->clear();
    this->mLoseMarks->clear();
    
    this->mBuckets->resumeSchedulerAndActions();
    this->mCoins->resumeSchedulerAndActions();
    this->mPopcorns->resumeSchedulerAndActions();
    this->mPopcorns->resumeSchedulerAndActions();
    this->mPopcornsShadows->resumeSchedulerAndActions();
    
    this->mLifes = 3;
    this->mBucketsCount = 0;
    
    this->mBucketsTimeMax = 5.0;
    
    this->updateFonts();
    
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
    
    this->addChild(this->mGameOverScreen, 600);
    this->mGameOverScreen->show();
    
    this->mPaused = true;
    
    this->mBuckets->pauseSchedulerAndActions();
    this->mCoins->pauseSchedulerAndActions();
    this->mPopcorns->pauseSchedulerAndActions();
    this->mPopcorns->pauseSchedulerAndActions();
    this->mPopcornsShadows->pauseSchedulerAndActions();
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Level::updateFonts()
{
    if(this->mBucketsCount < 10)
    {
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setCurrentFrameIndex(this->mBucketsCount);
        
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(1))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 100)
    {
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 10));
        ((Entity*) this->mLargeFont->objectAtIndex(1))->setCurrentFrameIndex(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10);
        
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 1000)
    {
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 100));
        ((Entity*) this->mLargeFont->objectAtIndex(1))->setCurrentFrameIndex(floor(this->mBucketsCount - floor(this->mBucketsCount / 100) * 100) / 10);
        ((Entity*) this->mLargeFont->objectAtIndex(2))->setCurrentFrameIndex(floor(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10));
        
        ((Entity*) this->mLargeFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(2))->setVisible(true);
        ((Entity*) this->mLargeFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mLargeFont->objectAtIndex(5))->setVisible(false);
    }
    
    if(this->mBucketsCount < 10)
    {
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setCurrentFrameIndex(this->mBucketsCount);
        
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(1))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 100)
    {
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 10));
        ((Entity*) this->mSmallFont->objectAtIndex(1))->setCurrentFrameIndex(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10);
        
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 1000)
    {
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 100));
        ((Entity*) this->mSmallFont->objectAtIndex(1))->setCurrentFrameIndex((int) floor((this->mBucketsCount - floor(this->mBucketsCount / 100) * 100) / 10));
        ((Entity*) this->mSmallFont->objectAtIndex(2))->setCurrentFrameIndex((int) floor(this->mBucketsCount % 10));
        
        ((Entity*) this->mSmallFont->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(2))->setVisible(true);
        ((Entity*) this->mSmallFont->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mSmallFont->objectAtIndex(5))->setVisible(false);
    }
}

void Level::update(float pDelta)
{
    Screen::update(pDelta);
    
    pDelta *= AppDelegate::mSpeedDecreaseFactor;
    
    if(this->mPaused) return;
    
    if(this->mScaleAnimation)
    {
        //this->setScale(this->getScale() + 0.001);
        //this->runAction(CCFollow::create(((Entity*) this->mBuckets->objectAtIndex(0))));
    }
    
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
            
            this->mBucketTime = Utils::randomf(0.1, this->mBucketsTimeMax);
            
            this->mBucketsTimeMax -= 0.0001;
        
            this->mBuckets->create();
        }
        
        this->mCoinsTimeElapsed += pDelta;
        
        if(this->mCoinsTimeElapsed >= this->mCoinsTime && this->mIsLevelRunning)
        {
            this->mCoinsTimeElapsed -= this->mCoinsTime;
            
            this->mCoinsTime = Utils::randomf(0.0, 7.0);
            
            this->mCoins->create();
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
                
                this->updateFonts();
            }
            else if(bucket->getCenterY() < -bucket->getHeight() / 2 && !bucket->mIsGone && bucket->mImpulsePower <= 0)
            {
                if(bucket->mType != Bucket::TYPE_DANGER)
                {
                    this->mLoseMarks->create()->setCenterPosition(bucket->getCenterX(), Utils::coord(Utils::randomf(30.0f, 60.0f)));
            
                    this->mLifes--;
                    this->mBucketsCount++;
                
                    ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->setCurrentFrameIndex(1);
                    ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->setScale(1.25f);
                    ((Entity*) this->mLifesIcons->objectAtIndex(this->mLifes))->runAction(CCScaleTo::create(0.75f, 1.0f));
            
                    if(this->mLifes <= 0)
                    {
                        this->finishLevel();
                    }
                }
                
                bucket->destroy();
            }
        }
        
        //
        
        for(int i = 0; i < this->mCoins->getCount(); i++)
        {
            Coin* coin = (Coin*) this->mCoins->objectAtIndex(i);
            
            if(coin->isCollideWithPoint(this->mTouchCoordinateX, this->mTouchCoordinateY) && !coin->mIsGone)
            {
                coin->fall();
            }
        }
        
        //
        
        this->mLightsTimeElapsed += pDelta;
        
        if(this->mLightsTimeElapsed >= this->mLightsTime)
        {
            this->mLightsTime = Utils::randomf(0.5f, 3.0f);
            this->mLightsTimeElapsed = 0;
            
            ((Lights*) this->mLights->create())->look(this->mTouchCoordinateX, this->mTouchCoordinateY);
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

void Level::onEnter()
{
    Screen::onEnter();
    
    AppDelegate::mIsAlreadyPlayed = true;
}

#endif