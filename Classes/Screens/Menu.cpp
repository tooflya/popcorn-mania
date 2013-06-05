#ifndef CONST_MENU
#define CONST_MENU

#include "Menu.h"

#include "ScreenManager.h"

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

class BottomButton : public Entity
{
public:
    Entity* mParent;
    
    float mRotationSpeed;
    float mRotationMax;
    
    bool mAnimationReverse;
    
    BottomButton(const char* pFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Entity* pParent) :
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

class SoundButton : public BottomButton
{
public:
    SoundButton(Menu* pParent) :
    BottomButton(Resources::R_MENU_BUTTON_SOUND, 1, 2, pParent->mSocialPanel)
    {
        this->create()->setCenterPosition(Utils::coord(161), Utils::coord(36));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->nextFrameIndex();
    }
};

class MusicButton : public BottomButton
{
public:
    MusicButton(Menu* pParent) :
    BottomButton(Resources::R_MENU_BUTTON_MUSIC, 1, 2, pParent->mSocialPanel)
    {
        this->create()->setCenterPosition(Utils::coord(68), Utils::coord(36));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->nextFrameIndex();
    }
};

class FacebookButton : public BottomButton
{
public:
    FacebookButton(Menu* pParent) :
    BottomButton(Resources::R_MENU_BUTTON_FACEBOOK, 1, 1, pParent->mSocialPanel)
    {
        this->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(48), Utils::coord(36));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
    }
};

class TwitterButton : public BottomButton
{
public:
    TwitterButton(Menu* pParent) :
    BottomButton(Resources::R_MENU_BUTTON_TWITTER, 1, 1, pParent->mSocialPanel)
    {
        this->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(141), Utils::coord(36));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
    }
};

class ScoreButton : public Entity
{
public:
    Menu* mParent;
    
    ScoreButton(Menu* pParent) :
    Entity(Resources::R_MENU_SCORE, 1, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(270), Options::CAMERA_CENTER_Y - Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
        this->animate(0.2f);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->mParent->showRate();
    }
};

class MoreButton : public BottomButton
{
public:
    MoreButton(Menu* pParent) :
    BottomButton(Resources::R_MENU_BUTTON_MORE_GAMES, 1, 1, pParent->mSocialPanel)
    {
        this->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(234), Utils::coord(36));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
    }
};

class PlayButton : public Entity
{
public:
    Menu* mParent;
    
    PlayButton(Menu* pParent) :
    Entity(Resources::R_MENU_PLAY, 1, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        AppDelegate::screens->set(0.5f, 1);
    }
};

class ShopButton : public Entity
{
public:
    Menu* mParent;
    
    ShopButton(Menu* pParent) :
    Entity(Resources::R_MENU_SHOP, 1, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(240), Options::CAMERA_CENTER_Y - Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
        this->animate(0.2f);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->mParent->showShop();
    }
};

class SocialLabel : public Entity
{
public:
    Entity* mParent;
    
    SocialLabel(Entity* pParent) :
    Entity(Resources::R_MENU_SOCIAL_LABEL, pParent)
    {
        this->mParent = pParent;
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        
    }
    
    
    void ccTouchMoved(CCTouch* touch, CCEvent* event)
    {
        float y = touch->getLocation().y - this->mParent->getHeight() / 2;
        
        y = y > Utils::coord(60) ? Utils::coord(60) : y;
        y = y < Utils::coord(-35) ? Utils::coord(-35) : y;
        
        this->mParent->setCenterPosition(this->mParent->getCenterX(), y);
    }
    
    void ccTouchEnded(CCTouch* touch, CCEvent* event)
    {
        Entity::ccTouchEnded(touch, event);
        
        float y = this->mParent->getCenterY();
        
        if(y <= Utils::coord(60) && y > Utils::coord(30))
        {
            this->mParent->runAction(CCMoveTo::create(0.3f, ccp(this->mParent->getCenterX(), Utils::coord(65))));
        }
        else
        {
            this->mParent->runAction(CCMoveTo::create(0.3f, ccp(this->mParent->getCenterX(), Utils::coord(-35))));
        }
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

Menu::Menu() :
    Screen()
    {
        this->mRateScreen = new Rate(this);
        this->mShopScreen = new Shop(this);
        
        this->mBackground1 = new Entity(Resources::R_MENU_BACKGROUND1, this);
    
        this->mStars = new BatchEntityManager(400, new Star(), this);
        
        this->mBackground2 = new Entity(Resources::R_MENU_BACKGROUND2, this);
    
        this->mNamePanel = new Entity(Resources::R_MENU_NAME_PANEL, 2, 2, this);
    
        this->mName = new Entity(Resources::R_MENU_NAME, 2, 3, this);
    
        this->mSpotlights = new BatchEntityManager(2, new Spotlight(), this);
        this->mPeople = new BatchEntityManager(20, new People(), this);
    
        this->mPlay = new PlayButton(this);
        this->mShop = new ShopButton(this);
        this->mScore = new ScoreButton(this);
        
        this->mBackground1->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        this->mBackground2->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    
        this->mSpotlights->create()->setCenterPosition(Utils::coord(50), 0);
        this->mSpotlights->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(50), 0);
    
        ((Entity*) this->mSpotlights->objectAtIndex(1))->setScaleX(-1);
    
        this->mNamePanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(170));
        this->mName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(190));
    
        this->mNamePanel->animate(0.1f);
        this->mName->animate(0.1f);
        this->mName->setStartFrame(0);
        this->mName->setFinishFrame(4);
    
        this->generateStars();
        this->generatePeople();
        
        this->mSocialPanel = new Entity(Resources::R_MENU_SOCIAL_PANEL, this);
        this->mSocialPanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Utils::coord(60));
        
        this->mSocialLabel = new SocialLabel(this->mSocialPanel);
        this->mSocialLabel->create()->setCenterPosition(Utils::coord(50), Utils::coord(100));
        
        this->mMusicButton = new MusicButton(this);
        this->mSoundButton = new SoundButton(this);
        
        this->mMoreButton = new MoreButton(this);
        this->mTwitterButton = new TwitterButton(this);
        this->mFacebookButton = new FacebookButton(this);
        
        this->mTimeToHidePanelElapsed = 0;
    }

// ===========================================================
// Methods
// ===========================================================

void Menu::generateStars()
{
    for (int i = 0; i < 150; i++)
    {
        this->mStars->create()->setCurrentFrameIndex(0);
    }
    
    for (int i = 0; i < 250; i++)
    {
        this->mStars->create()->setCurrentFrameIndex(1);
    }
}

void Menu::generatePeople()
{
    for (int i = 0; i < 7; i++)
    {
        Entity* people = this->mPeople->create();
        people->setCurrentFrameIndex(i);
        people->setCenterPosition((i + 1) * Utils::coord(100.0f), Utils::coord(130.0f));
    }
    
    Entity* people = this->mPeople->create();
    people->setCurrentFrameIndex(0);
    people->setCenterPosition(Options::CAMERA_CENTER_X, Utils::coord(130.0f));
    
    int k = 8;
    for (int i = 7; i >= 0; i--)
    {
        Entity* people = this->mPeople->create();
        people->setCurrentFrameIndex(i);
        people->setCenterPosition(k * Utils::coord(100.0f), Utils::coord(130.0f));
        
        k++;
    }
}

void Menu::showRate()
{
    this->mRateScreen->retain();
    this->addChild(this->mRateScreen, 500);
    
    this->mMusicButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMusicButton->getCenterX(), this->mMusicButton->getCenterY() - Utils::coord(100))));
    this->mSoundButton->runAction(CCMoveTo::create(0.3f, ccp(this->mSoundButton->getCenterX(), this->mSoundButton->getCenterY() - Utils::coord(100))));
    
    this->mMoreButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMoreButton->getCenterX(), this->mMoreButton->getCenterY() - Utils::coord(100))));
    this->mTwitterButton->runAction(CCMoveTo::create(0.3f, ccp(this->mTwitterButton->getCenterX(), this->mTwitterButton->getCenterY() - Utils::coord(100))));
    this->mFacebookButton->runAction(CCMoveTo::create(0.3f, ccp(this->mFacebookButton->getCenterX(), this->mFacebookButton->getCenterY() - Utils::coord(100))));
    
    this->mPlay->runAction(CCMoveTo::create(0.3f, ccp(this->mPlay->getCenterX(), this->mPlay->getCenterY() + Utils::coord(500))));
    this->mShop->runAction(CCMoveTo::create(0.3f, ccp(this->mShop->getCenterX() + Utils::coord(500), this->mShop->getCenterY())));
    this->mScore->runAction(CCMoveTo::create(0.3f, ccp(this->mScore->getCenterX() - Utils::coord(500), this->mScore->getCenterY())));
    
    this->mName->runAction(CCMoveTo::create(0.3f, ccp(this->mName->getCenterX(), this->mName->getCenterY() + Utils::coord(500))));
    this->mNamePanel->runAction(CCMoveTo::create(0.3f, ccp(this->mNamePanel->getCenterX(), this->mNamePanel->getCenterY() + Utils::coord(500))));
    
    this->mSocialPanel->runAction(CCMoveTo::create(0.3f, ccp(this->mSocialPanel->getCenterX(), Utils::coord(-160))));
    
    this->mRateScreen->show();
}

void Menu::hideRate()
{
    this->mMusicButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMusicButton->getCenterX(), this->mMusicButton->getCenterY() + Utils::coord(100))));
    this->mSoundButton->runAction(CCMoveTo::create(0.3f, ccp(this->mSoundButton->getCenterX(), this->mSoundButton->getCenterY() + Utils::coord(100))));
    
    this->mMoreButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMoreButton->getCenterX(), this->mMoreButton->getCenterY() + Utils::coord(100))));
    this->mTwitterButton->runAction(CCMoveTo::create(0.3f, ccp(this->mTwitterButton->getCenterX(), this->mTwitterButton->getCenterY() + Utils::coord(100))));
    this->mFacebookButton->runAction(CCMoveTo::create(0.3f, ccp(this->mFacebookButton->getCenterX(), this->mFacebookButton->getCenterY() + Utils::coord(100))));
    
    this->mPlay->runAction(CCMoveTo::create(0.3f, ccp(this->mPlay->getCenterX(), this->mPlay->getCenterY() - Utils::coord(500))));
    this->mShop->runAction(CCMoveTo::create(0.3f, ccp(this->mShop->getCenterX() - Utils::coord(500), this->mShop->getCenterY())));
    this->mScore->runAction(CCMoveTo::create(0.3f, ccp(this->mScore->getCenterX() + Utils::coord(500), this->mScore->getCenterY())));
    
    this->mName->runAction(CCMoveTo::create(0.3f, ccp(this->mName->getCenterX(), this->mName->getCenterY() - Utils::coord(500))));
    this->mNamePanel->runAction(CCMoveTo::create(0.3f, ccp(this->mNamePanel->getCenterX(), this->mNamePanel->getCenterY() - Utils::coord(500))));
    
    this->mSocialPanel->runAction(CCMoveTo::create(0.3f, ccp(this->mSocialPanel->getCenterX(), Utils::coord(60))));
    this->mTimeToHidePanelElapsed = 0;
    
    this->mRateScreen->hide();
}

void Menu::showShop()
{
    this->mShopScreen->retain();
    this->addChild(this->mShopScreen, 500);
    
    this->mMusicButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMusicButton->getCenterX(), this->mMusicButton->getCenterY() - Utils::coord(100))));
    this->mSoundButton->runAction(CCMoveTo::create(0.3f, ccp(this->mSoundButton->getCenterX(), this->mSoundButton->getCenterY() - Utils::coord(100))));
    
    this->mMoreButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMoreButton->getCenterX(), this->mMoreButton->getCenterY() - Utils::coord(100))));
    this->mTwitterButton->runAction(CCMoveTo::create(0.3f, ccp(this->mTwitterButton->getCenterX(), this->mTwitterButton->getCenterY() - Utils::coord(100))));
    this->mFacebookButton->runAction(CCMoveTo::create(0.3f, ccp(this->mFacebookButton->getCenterX(), this->mFacebookButton->getCenterY() - Utils::coord(100))));
    
    this->mPlay->runAction(CCMoveTo::create(0.3f, ccp(this->mPlay->getCenterX(), this->mPlay->getCenterY() + Utils::coord(500))));
    this->mShop->runAction(CCMoveTo::create(0.3f, ccp(this->mShop->getCenterX() + Utils::coord(500), this->mShop->getCenterY())));
    this->mScore->runAction(CCMoveTo::create(0.3f, ccp(this->mScore->getCenterX() - Utils::coord(500), this->mScore->getCenterY())));
    
    this->mName->runAction(CCMoveTo::create(0.3f, ccp(this->mName->getCenterX(), this->mName->getCenterY() + Utils::coord(500))));
    this->mNamePanel->runAction(CCMoveTo::create(0.3f, ccp(this->mNamePanel->getCenterX(), this->mNamePanel->getCenterY() + Utils::coord(500))));
    
    this->mSocialPanel->runAction(CCMoveTo::create(0.3f, ccp(this->mSocialPanel->getCenterX(), Utils::coord(-160))));
    
    this->mShopScreen->show();
}

void Menu::hideShop()
{
    this->mMusicButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMusicButton->getCenterX(), this->mMusicButton->getCenterY() + Utils::coord(100))));
    this->mSoundButton->runAction(CCMoveTo::create(0.3f, ccp(this->mSoundButton->getCenterX(), this->mSoundButton->getCenterY() + Utils::coord(100))));
    
    this->mMoreButton->runAction(CCMoveTo::create(0.3f, ccp(this->mMoreButton->getCenterX(), this->mMoreButton->getCenterY() + Utils::coord(100))));
    this->mTwitterButton->runAction(CCMoveTo::create(0.3f, ccp(this->mTwitterButton->getCenterX(), this->mTwitterButton->getCenterY() + Utils::coord(100))));
    this->mFacebookButton->runAction(CCMoveTo::create(0.3f, ccp(this->mFacebookButton->getCenterX(), this->mFacebookButton->getCenterY() + Utils::coord(100))));
    
    this->mPlay->runAction(CCMoveTo::create(0.3f, ccp(this->mPlay->getCenterX(), this->mPlay->getCenterY() - Utils::coord(500))));
    this->mShop->runAction(CCMoveTo::create(0.3f, ccp(this->mShop->getCenterX() - Utils::coord(500), this->mShop->getCenterY())));
    this->mScore->runAction(CCMoveTo::create(0.3f, ccp(this->mScore->getCenterX() + Utils::coord(500), this->mScore->getCenterY())));
    
    this->mName->runAction(CCMoveTo::create(0.3f, ccp(this->mName->getCenterX(), this->mName->getCenterY() - Utils::coord(500))));
    this->mNamePanel->runAction(CCMoveTo::create(0.3f, ccp(this->mNamePanel->getCenterX(), this->mNamePanel->getCenterY() - Utils::coord(500))));
    
    this->mSocialPanel->runAction(CCMoveTo::create(0.3f, ccp(this->mSocialPanel->getCenterX(), Utils::coord(60))));
    this->mTimeToHidePanelElapsed = 0;
    
    this->mShopScreen->hide();
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Menu::onEnter()
{
    Screen::onEnter();
    
    if(AppDelegate::mIsAlreadyPlayed)
    {
        this->showRate();
    }
}

void Menu::update(float pDeltaTime)
{
    this->mTimeToHidePanelElapsed += pDeltaTime;
    
    if(this->mTimeToHidePanelElapsed >= 1.0f)
    {
        this->mTimeToHidePanelElapsed = -1000;
        
        this->mSocialPanel->runAction(CCMoveTo::create(0.3f, ccp(this->mSocialPanel->getCenterX(), this->mSocialPanel->getCenterY() - Utils::coord(95))));
    }
}

#endif