#ifndef CONST_SHOP
#define CONST_SHOP

#include "Shop.h"
#include "Menu.h"
#include "GetCoins.h"

// ===========================================================
// Inner Classes
// ===========================================================

class Layer : public CCLayerRGBA
{
public:
    Layer()
    {
        
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        CCLayerRGBA::setOpacity(pOpacity);
        
        for(int i=0; i<this->getChildrenCount(); i++)
        {
            ((Entity*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
            
            for(int j=0; j<((Entity*) this->getChildren()->objectAtIndex(i))->getChildrenCount(); j++)
            {
                ((Entity*) ((Entity*) this->getChildren()->objectAtIndex(i))->getChildren()->objectAtIndex(j))->setOpacity(pOpacity);
            }
        }
    }
};

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
        if(this->mParent->mGetCoinsScreen->mShowed)
        {
            this->mParent->mGetCoinsScreen->hide();
            
            this->mParent->mListLayer->runAction(CCFadeIn::create(0.3f));
        }
        else
        {
            this->mMenu->hideShop();
        }
    }
};

class ShopCoinsButton : public Entity
{
public:
    Shop* mParent;
    
    ShopCoinsButton(Shop* pParent) :
    Entity(Resources::R_SHOP_BUTTON_GET_PANEL, 2, 2, pParent)
    {
        this->mParent = pParent;
        
        this->create()->animate(0.2f);
        this->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(120), Utils::coord(52));
        
        
        this->setRegisterAsTouchable(true);
        
        Entity* label = new Entity(Resources::R_SHOP_BUTTON_GET_NAME, 1, 2, this);
        label->create()->animate(0.2f);
        label->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(8));
    }
    
    void onTouch(CCTouch* touch, CCEvent* event)
    {
        if(this->mParent->mGetCoinsScreen->mShowed)
        {
            this->mParent->mGetCoinsScreen->hide();
            
            this->mParent->mListLayer->runAction(CCFadeIn::create(0.3f));
        }
        else
        {
            this->mParent->addChild(this->mParent->mGetCoinsScreen, 500);
            this->mParent->mGetCoinsScreen->show();
            
            this->mParent->mListLayer->runAction(CCFadeOut::create(0.3f));
        }
    }
    
    void setOpacity(GLubyte pOpacity)
    {
        Entity::setOpacity(pOpacity);
        
        for(int i=0; i<this->getChildrenCount(); i++)
            ((Entity*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
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
        
        this->mListLayer = new Layer();
        
        this->addChild(this->mListLayer);
        
        new BackButton(this, pMenu);
        
        new ShopCoinsButton(this);
        
        for(int i = 0 ; i < 4; i++)
        {
            Entity* entity = new Entity(Resources::R_SHOP_STROKE, 1, 4, this->mListLayer);
            entity->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(160) * i - Utils::coord(100));
            entity->setCurrentFrameIndex(i);
            
            Entity* b = new Entity(Resources::R_SHOP_BUY_BUTTON, 3, 1, entity);
            b->create()->setCenterPosition(entity->getWidth() - b->getWidth() / 2 - Utils::coord(20), entity->getHeight() / 2);
            b->setCurrentFrameIndex(i);
        }
        
        this->hide();
        
        this->mShowed = false;
        this->mNeedToHide = false;
        
        this->mHideTimeElapsed = 0;
        
        this->mGetCoinsScreen = new GetCoins();
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