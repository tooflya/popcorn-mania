#ifndef CONST_GAMEOVER
#define CONST_GAMEOVER

#include "GameOver.h"

#include "Level.h"

// ===========================================================
// Inner Classes
// ===========================================================

class GameRestartButton : public Entity
{
public:
    GameOver* mParent;
    
    GameRestartButton(GameOver* pParent) :
    Entity(Resources::R_PAUSE_RESTART_BUTTON, 1, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(180), Options::CAMERA_CENTER_Y + Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
    }
    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event)
    {
        if(!this->mParent->mShowed) return false;
        
        return Entity::ccTouchBegan(touch, event);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        Level* level = (Level*) this->mParent->getParent();
        
        level->startLevel();
        
        this->mParent->hide();
    }
};

class GameMenuButton : public Entity
{
public:
    GameOver* mParent;
    
    GameMenuButton(GameOver* pParent) :
    Entity(Resources::R_PAUSE_MENU_BUTTON, 1, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(127), Options::CAMERA_CENTER_Y - Utils::coord(80));
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
    }
    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event)
    {
        if(!this->mParent->mShowed) return false;
        
        return Entity::ccTouchBegan(touch, event);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
    }
};

class GameOverBottomButton : public Entity
{
public:
    CCNode* mParent;
    
    float mRotationSpeed;
    float mRotationMax;
    
    bool mAnimationReverse;
    
    GameOverBottomButton(const char* pFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent) :
    Entity(pFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent)
    {
        this->mParent = pParent;
        
        this->mRotationSpeed = 1.0f;
        this->mRotationMax = 3.0f;
        
        this->setRotation(Utils::randomf(-3.0f, 3.0f));
        
        this->mAnimationReverse = this->getRotation() > 0;
    }
    
    void update(float pDeltaTime)
    {
        Entity::update(pDeltaTime);
        
        if(this->mAnimationReverse)
        {
            this->setRotation(this->getRotation() - this->mRotationSpeed);
            
            if(this->getRotation() <= -this->mRotationMax)
            {
                this->mAnimationReverse = !this->mAnimationReverse;
            }
        }
        else
        {
            this->setRotation(this->getRotation() + this->mRotationSpeed);
            
            if(this->getRotation() >= this->mRotationMax)
            {
                this->mAnimationReverse = !this->mAnimationReverse;
            }
        }
    }
};

class GameOverFacebookButton : public GameOverBottomButton
{
public:
    GameOverFacebookButton(CCNode* pParent) :
    GameOverBottomButton(Resources::R_MENU_BUTTON_FACEBOOK, 1, 1, pParent)
    {
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(100), Options::CAMERA_CENTER_Y - Utils::coord(200));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
    }
};

class GameOverTwitterButton : public GameOverBottomButton
{
public:
    GameOverTwitterButton(CCNode* pParent) :
    GameOverBottomButton(Resources::R_MENU_BUTTON_TWITTER, 1, 1, pParent)
    {
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(200), Options::CAMERA_CENTER_Y - Utils::coord(200));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
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

GameOver::GameOver()
    {
        this->mAnimationNeedShowButtons = false;
        
        this->mLines1 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this);
        this->mLines2 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this);
        
        for(int i = 0; i < 20; i++)
        {
            this->mLines1->create()->setCenterPosition(i * Utils::coord(64) * 2, Options::CAMERA_CENTER_Y);
            
            Entity* line = this->mLines2->create();
            line->setCurrentFrameIndex(1);
            line->setCenterPosition(i * Utils::coord(64) * 2 + Utils::coord(64), Options::CAMERA_CENTER_Y);
        }
        
        this->mPanel = new Entity(Resources::R_GAMEOVER_NAME_PANEL, 2, 2, this);
        this->mName = new Entity(Resources::R_GAMEOVER_NAME, 2, 3, this);
        
        this->mPanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(160));
        this->mName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(150));
        
        this->mPanel->animate(0.2f);
        this->mName->animate(0.1f);
        
        this->mName->setStartFrame(0);
        this->mName->setFinishFrame(4);
        
        this->mLines1->setPosition(ccp(0, Options::CAMERA_HEIGHT));
        this->mLines2->setPosition(ccp(0, -Options::CAMERA_HEIGHT));
        
        this->mRestartButton = new GameRestartButton(this);
        this->mMenuButton = new GameMenuButton(this);
        
        this->mBucketsCountIcon = new Entity(Resources::R_LEVEL_BUCKETICON, this);
        this->mBucketsCountIcon->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(80), Options::CAMERA_CENTER_Y + Utils::coord(50));
        
        this->mCoinsCountIcon = new Entity(Resources::R_LEVEL_COINS_ICON, 3, 2, this);
        this->mCoinsCountIcon->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(80), Options::CAMERA_CENTER_Y - Utils::coord(80));
        this->mCoinsCountIcon->animate(0.1f);
        
        this->mBestLabel = new Entity(Resources::R_LEVEL_LABEL_BEST, 1, 2, this);
        this->mBestLabel->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(90), Options::CAMERA_CENTER_Y - Utils::coord(10));
        this->mBestLabel->animate(0.2f);
        
        this->mBucketsCountText = new EntityManager(10, new Entity(Resources::R_GAME_LARGE_FONT, 10, 1), this);
        this->mCoinsCountText = new EntityManager(10, new Entity(Resources::R_GAME_LARGE_FONT, 10, 1), this);
        this->mBucketsBestCountText = new EntityManager(10, new Entity(Resources::R_GAME_SMALL_FONT, 10, 1), this);
        
        for(int i = 0; i < 10; i++)
        {
            this->mBucketsBestCountText->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(140) + Utils::coord(15) * i, Options::CAMERA_CENTER_Y - Utils::coord(10));
            this->mCoinsCountText->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(130)+ Utils::coord(30) * i, Options::CAMERA_CENTER_Y - Utils::coord(77));
            this->mBucketsCountText->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(130)+ Utils::coord(30) * i, Options::CAMERA_CENTER_Y + Utils::coord(50));
            
            ((Entity*) this->mBucketsBestCountText->objectAtIndex(i))->setVisible(false);
            ((Entity*) this->mCoinsCountText->objectAtIndex(i))->setVisible(false);
            ((Entity*) this->mBucketsCountText->objectAtIndex(i))->setVisible(false);
        }
        
        this->mTwitterButton = new GameOverTwitterButton(this);
        this->mFacebookButton = new GameOverFacebookButton(this);
        
        this->hide();
        
        this->mShowed = false;
        this->mNeedToHide = false;
        
        this->mHideTimeElapsed = 0;
    }

// ===========================================================
// Methods
// ===========================================================

void GameOver::hide()
{
    this->mShowed = false;
    
    this->mLines1->runAction(CCMoveTo::create(0.3f, ccp(0, Options::CAMERA_HEIGHT)));
    this->mLines2->runAction(CCMoveTo::create(0.3f, ccp(0, -Options::CAMERA_HEIGHT)));
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0.3f));
    }
    
    this->mNeedToHide = true;
    
    //this->mRestartButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(250) - Utils::coord(500));
    //this->mMenuButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(50) - Utils::coord(500));
}

void GameOver::show()
{
    this->mShowed = true;
    
    this->mLines1->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
    this->mLines2->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3f));
    }
    
    //this->mAnimationNeedShowButtons = true;
    
    this->mAnimationsCountElapsed = 0;
    this->mAnimationButtonTimeElapsed = 0;
}

// ===========================================================
// Virtual Methods
// ===========================================================

void GameOver::update(float pDeltaTime)
{
    Popscreen::update(pDeltaTime);
    
    if(!this->mShowed) return;
    
    if(this->mAnimationNeedShowButtons)
    {
        this->mAnimationButtonTimeElapsed += pDeltaTime;
    
        if(this->mAnimationButtonTimeElapsed >= 0.5f && this->mAnimationsCountElapsed == 0)
        {
            this->mRestartButton->runAction(CCMoveTo::create(0.3f, ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(250))));
            this->mMenuButton->runAction(CCMoveTo::create(0.3f, ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(50))));
            
            this->mAnimationsCountElapsed++;
        }
        else if(this->mAnimationButtonTimeElapsed >= 1.8f && this->mAnimationsCountElapsed == 1)
        {
            this->mRestartButton->runAction(CCMoveTo::create(0.3f, ccp(Options::CAMERA_CENTER_X - Utils::coord(250), Options::CAMERA_CENTER_Y - Utils::coord(250))));
            this->mMenuButton->runAction(CCMoveTo::create(0.3f, ccp(Options::CAMERA_CENTER_X - Utils::coord(250), Options::CAMERA_CENTER_Y - Utils::coord(50))));
            
            this->mAnimationsCountElapsed++;
        }
    }
    
    //
    
    this->mBucketsCount = 123;
    
    if(this->mBucketsCount < 10)
    {
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setCurrentFrameIndex(this->mBucketsCount);
        
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(1))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 100)
    {
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 10));
        ((Entity*) this->mBucketsCountText->objectAtIndex(1))->setCurrentFrameIndex(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10);
        
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 1000)
    {
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 100));
        ((Entity*) this->mBucketsCountText->objectAtIndex(1))->setCurrentFrameIndex(floor(this->mBucketsCount - floor(this->mBucketsCount / 100) * 100) / 10);
        ((Entity*) this->mBucketsCountText->objectAtIndex(2))->setCurrentFrameIndex(floor(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10));
        
        ((Entity*) this->mBucketsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(2))->setVisible(true);
        ((Entity*) this->mBucketsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsCountText->objectAtIndex(5))->setVisible(false);
    }
    
    if(this->mBucketsCount < 10)
    {
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setCurrentFrameIndex(this->mBucketsCount);
        
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(1))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 100)
    {
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 10));
        ((Entity*) this->mCoinsCountText->objectAtIndex(1))->setCurrentFrameIndex(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10);
        
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 1000)
    {
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 100));
        ((Entity*) this->mCoinsCountText->objectAtIndex(1))->setCurrentFrameIndex((int) floor((this->mBucketsCount - floor(this->mBucketsCount / 100) * 100) / 10));
        ((Entity*) this->mCoinsCountText->objectAtIndex(2))->setCurrentFrameIndex((int) floor(this->mBucketsCount % 10));
        
        ((Entity*) this->mCoinsCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(2))->setVisible(true);
        ((Entity*) this->mCoinsCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mCoinsCountText->objectAtIndex(5))->setVisible(false);
    }
    
    if(this->mBucketsCount < 10)
    {
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setCurrentFrameIndex(this->mBucketsCount);
        
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(1))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 100)
    {
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 10));
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(1))->setCurrentFrameIndex(this->mBucketsCount - floor(this->mBucketsCount / 10) * 10);
        
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(2))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(5))->setVisible(false);
    }
    else if(this->mBucketsCount < 1000)
    {
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setCurrentFrameIndex(floor(this->mBucketsCount / 100));
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(1))->setCurrentFrameIndex((int) floor((this->mBucketsCount - floor(this->mBucketsCount / 100) * 100) / 10));
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(2))->setCurrentFrameIndex((int) floor(this->mBucketsCount % 10));
        
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(0))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(1))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(2))->setVisible(true);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(3))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(4))->setVisible(false);
        ((Entity*) this->mBucketsBestCountText->objectAtIndex(5))->setVisible(false);
    }
}

#endif