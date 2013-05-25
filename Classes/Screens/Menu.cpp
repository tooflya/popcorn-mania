#ifndef CONST_MENU
#define CONST_MENU

#include "Menu.h"

#include "ScreenManager.h"

// ===========================================================
// Inner Classes
// ===========================================================

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
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->mParent->mScreenManager->set(1);
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
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(220), Options::CAMERA_CENTER_Y - Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->mParent->mScreenManager->set(1);
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
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(200), Options::CAMERA_CENTER_Y - Utils::coord(50));
        
        this->setRegisterAsTouchable(true);
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        this->mParent->mScreenManager->set(1);
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

Menu::Menu(ScreenManager* pScreenManager) :
    Popscreen(pScreenManager)
    {
        this->mBackground1 = new Entity(Resources::R_MENU_BACKGROUND1, this);
    
        this->mStars = new BatchEntityManager(400, new Star(), this);
        
        this->mBackground2 = new Entity(Resources::R_MENU_BACKGROUND2, this);
    
        this->mNamePanel = new Entity(Resources::R_MENU_NAME_PANEL, 2, 2, this);
    
        this->mName = new Entity(Resources::R_MENU_NAME, 2, 3, this);
    
        this->mSpotlight1 = new Spotlight(this);
        this->mSpotlight2 = new Spotlight(this);
        this->mShadowDecoration = new Entity(Resources::R_MENU_SHADOW, this);
        this->mPeople = new BatchEntityManager(20, new People(), this);
    
        this->mPlay = new PlayButton(this);
        this->mShop = new ShopButton(this);
        this->mScore = new ScoreButton(this);
        
        this->mBackground1->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        this->mBackground2->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    
        this->mSpotlight1->create()->setCenterPosition(Utils::coord(50), 0);
        this->mSpotlight2->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(50), 0);
    
        this->mSpotlight2->setScaleX(-1);
        
        this->mShadowDecoration->create()->setCenterPosition(Options::CAMERA_CENTER_X, Utils::coord(100));
    
        this->mNamePanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(170));
        this->mName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(190));
    
        this->mNamePanel->animate(0.1f);
        this->mName->animate(0.1f);
        this->mName->setStartFrame(0);
        this->mName->setFinishFrame(4);
    
        this->generateStars();
        this->generatePeople();
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

// ===========================================================
// Virtual Methods
// ===========================================================

#endif