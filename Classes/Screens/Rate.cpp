#ifndef CONST_RATE
#define CONST_RATE

#include "Rate.h"

// ===========================================================
// Inner Classes
// ===========================================================

class YesButton : public Entity
{
public:
    Rate* mParent;
    
    YesButton(Rate* pParent) :
    Entity(Resources::R_RATE_BUTTONS_BACKGROUND, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(200), Options::CAMERA_CENTER_Y);
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
        
        Entity* capture = new Entity(Resources::R_RATE_BUTTON_YES, this);
        capture->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(3));
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

class NoButton : public Entity
{
public:
    Rate* mParent;
    
    NoButton(Rate* pParent) :
    Entity(Resources::R_RATE_BUTTONS_BACKGROUND, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
        
        Entity* capture = new Entity(Resources::R_RATE_BUTTON_NO, this);
        capture->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(3));
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

class LaterButton : public Entity
{
public:
    Rate* mParent;
    
    LaterButton(Rate* pParent) :
    Entity(Resources::R_RATE_BUTTONS_BACKGROUND, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(200), Options::CAMERA_CENTER_Y);
        
        this->setRegisterAsTouchable(true);
        this->animate(0.1f);
        
        Entity* capture = new Entity(Resources::R_RATE_BUTTON_LATER, this);
        capture->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(3));
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

Rate::Rate(ScreenManager* pScreenManager) :
    Popscreen(pScreenManager)
    {
        this->mBackgroundDecoration = new Entity(Resources::R_RATE_BACKGROUND_DECORATION, this);
        this->mBackgroundDecoration->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(150));
        
        this->mPanel = new Entity(Resources::R_PAUSE_NAME_PANEL, 2, 2, this);
        this->mName = new Entity(Resources::R_RATE_NAME, 1, 1, this);
        
        this->mPanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(160));
        this->mName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(145));
        
        this->mPanel->animate(0.2f);
        
        this->mName->setStartFrame(0);
        this->mName->setFinishFrame(4);
        
        new YesButton(this);
        new NoButton(this);
        new LaterButton(this);
        
        for(int i = 0; i < this->getChildren()->count(); i++)
        {
            ((Entity*) this->getChildren()->objectAtIndex(i))->setOpacity(0);
        }
        
        this->mShowed = false;
    }

// ===========================================================
// Methods
// ===========================================================

void Rate::hide()
{
    this->mShowed = false;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0.3f));
    }
}

void Rate::show()
{
    this->mShowed = true;
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3f));
    }
}

void Rate::update(float pDeltaTime)
{
    Popscreen::update(pDeltaTime);
    
    this->mBackgroundDecoration->setRotation(this->mBackgroundDecoration->getRotation() + 0.05f);
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif