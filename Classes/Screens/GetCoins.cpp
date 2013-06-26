#ifndef CONST_GETCOINS
#define CONST_GETCOINS

#include "GetCoins.h"

#include "Shop.h"

#include "ScreenManager.h"

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

class ButtonGetCoins1 : public Entity
{
public:
    GetCoins* mParent;
    
    ButtonGetCoins1(GetCoins* pParent) :
    Entity(Resources::R_GETCOINS_BUTTONS_BG, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->animate(0.2f);
        this->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(200), Options::CAMERA_CENTER_Y + Utils::coord(100));
        
        this->setRegisterAsTouchable(true);
        
        Entity* label = new Entity(Resources::R_GETCOINS_BUTTON1, 1, 1, this);
        label->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(12));
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        Entity::setOpacity(pOpacity);
        
        ((Entity*) this->getChildren()->objectAtIndex(0))->setOpacity(pOpacity);
    }
    
};

class ButtonGetCoins2 : public Entity
{
public:
    GetCoins* mParent;
    
    ButtonGetCoins2(GetCoins* pParent) :
    Entity(Resources::R_GETCOINS_BUTTONS_BG, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->animate(0.2f);
        this->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(200), Options::CAMERA_CENTER_Y + Utils::coord(100));
        
        this->setRegisterAsTouchable(true);
        
        Entity* label = new Entity(Resources::R_GETCOINS_BUTTON2, 1, 1, this);
        label->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(12));
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        Entity::setOpacity(pOpacity);
        
        ((Entity*) this->getChildren()->objectAtIndex(0))->setOpacity(pOpacity);
    }
    
};

class ButtonGetCoins3 : public Entity
{
public:
    GetCoins* mParent;
    
    ButtonGetCoins3(GetCoins* pParent) :
    Entity(Resources::R_GETCOINS_BUTTONS_BG, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->animate(0.2f);
        this->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(200), Options::CAMERA_CENTER_Y - Utils::coord(100));
        
        this->setRegisterAsTouchable(true);
        
        Entity* label = new Entity(Resources::R_GETCOINS_BUTTON3, 1, 1, this);
        label->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(12));
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        Entity::setOpacity(pOpacity);
        
        ((Entity*) this->getChildren()->objectAtIndex(0))->setOpacity(pOpacity);
    }
    
};

class ButtonGetCoins4 : public Entity
{
public:
    GetCoins* mParent;
    
    ButtonGetCoins4(GetCoins* pParent) :
    Entity(Resources::R_GETCOINS_BUTTONS_BG, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->animate(0.2f);
        this->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(200), Options::CAMERA_CENTER_Y - Utils::coord(100));
        
        this->setRegisterAsTouchable(true);
        
        Entity* label = new Entity(Resources::R_GETCOINS_BUTTON4, 1, 1, this);
        label->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(12));
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        Entity::setOpacity(pOpacity);
        
        ((Entity*) this->getChildren()->objectAtIndex(0))->setOpacity(pOpacity);
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
GetCoins::GetCoins()
{
        new ButtonGetCoins1(this);
        new ButtonGetCoins2(this);
        new ButtonGetCoins3(this);
        new ButtonGetCoins4(this);
    
        this->hide();
        
        this->mShowed = false;
        this->mNeedToHide = false;
        
        this->mHideTimeElapsed = 0;
    }

// ===========================================================
// Methods
// ===========================================================

void GetCoins::hide()
{
    this->mShowed = false;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0.3f));
    }
    
    this->mNeedToHide = true;
}

void GetCoins::show()
{
    this->mShowed = true;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3f));
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif