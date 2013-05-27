#ifndef CONST_PAUSE
#define CONST_PAUSE

#include "Pause.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Pause::Pause(ScreenManager* pScreenManager) :
    Popscreen(pScreenManager)
    {
        this->mLines1 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this);
        this->mLines2 = new BatchEntityManager(20, new Entity(Resources::R_SCREENS_LINES, 2, 1), this);
        
        for(int i = 0; i < 20; i++)
        {
            this->mLines1->create()->setCenterPosition(i * Utils::coord(64) * 2, Options::CAMERA_CENTER_Y);
            
            Entity* line = this->mLines2->create();
            line->setCurrentFrameIndex(1);
            line->setCenterPosition(i * Utils::coord(64) * 2 + Utils::coord(64), Options::CAMERA_CENTER_Y);
        }
        
        this->mPanel = new Entity(Resources::R_PAUSE_NAME_PANEL, 2, 2, this);
        this->mName = new Entity(Resources::R_PAUSE_NAME, 2, 3, this);
        
        this->mPanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(160));
        this->mName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(150));
        
        this->mPanel->animate(0.2f);
        this->mName->animate(0.1f);
        
        this->mName->setStartFrame(0);
        this->mName->setFinishFrame(4);
        
        this->mLines1->setPosition(ccp(0, Options::CAMERA_HEIGHT));
        this->mLines2->setPosition(ccp(0, -Options::CAMERA_HEIGHT));
        
        this->hide();
    }

// ===========================================================
// Methods
// ===========================================================

void Pause::hide()
{
    this->mLines1->runAction(CCMoveTo::create(0.3f, ccp(0, Options::CAMERA_HEIGHT)));
    this->mLines2->runAction(CCMoveTo::create(0.3f, ccp(0, -Options::CAMERA_HEIGHT)));
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0.3f));
    }
}

void Pause::show()
{
    this->mLines1->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
    this->mLines2->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
    
    for(int i = 0; i < this->getChildren()->count(); i++)
    {
        ((CCNode*) this->getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3f));
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif