#ifndef CONST_SHOP
#define CONST_SHOP

#include "Shop.h"
#include "Menu.h"

// ===========================================================
// Inner Classes
// ===========================================================

class BackButton : public Entity
{
public:
    Shop* mParent;
    Menu* mMenu;
    
    BackButton(Shop* pParent, Menu* pMenu) :
    Entity(Resources::R_SHOP_BUTTON_BACK, 1, 2, pParent)
    {
        this->mParent = pParent;
        this->mMenu = pMenu;
        
        this->create()->setCenterPosition(Utils::coord(64), Utils::coord(64));
        
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
        this->mMenu->hideShop();
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

Shop::Shop(Menu* pMenu)
    {
        this->mBackgroundDecoration = new Entity(Resources::R_RATE_BACKGROUND_DECORATION, this);
        this->mBackgroundDecoration->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(150));
        
        new BackButton(this, pMenu);
        
        this->mGetButtonPanel = new Entity(Resources::R_SHOP_BUTTON_GET_PANEL, 2, 2, this);
        this->mGetButtonLabel = new Entity(Resources::R_SHOP_BUTTON_GET_NAME, 1, 2, this);
        
        this->mGetButtonPanel->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(120), Utils::coord(52));
        this->mGetButtonLabel->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(120), Utils::coord(60));
        
        this->mGetButtonPanel->animate(0.2f);
        this->mGetButtonLabel->animate(0.2f);
        
        for(int i = 0 ; i < 3; i++)
        {
            (new Entity(Resources::R_SHOP_STROKE, this))->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(160) * i - Utils::coord(100));
        }
        
        this->hide();
        
        this->mShowed = false;
        this->mNeedToHide = false;
        
        this->mHideTimeElapsed = 0;
    }

// ===========================================================
// Methods
// ===========================================================

void Shop::hide()
{
    this->mShowed = false;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0.3f));
    }
    
    this->mNeedToHide = true;
}

void Shop::show()
{
    this->mShowed = true;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3f));
    }
}

void Shop::update(float pDeltaTime)
{
    Popscreen::update(pDeltaTime);
    
    this->mBackgroundDecoration->setRotation(this->mBackgroundDecoration->getRotation() + 0.05f);
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif