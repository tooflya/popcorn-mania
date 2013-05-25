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
            Entity(Resources::R_MENU_PLAY, pParent)
            {
                this->mParent = pParent;
                
                this->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150));
                
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
        this->mBackground = new Entity(Resources::R_MENU_BACKGROUND, this);
    
        this->mStars = new BatchEntityManager(100, new Star(), this);
    
        this->mNamePanel = new Entity(Resources::R_MENU_NAME_PANEL, 1, 4, this);
    
        this->mNamePart1 = new Entity(Resources::R_MENU_NAME_PART1, 1, 4, this);
        this->mNamePart2 = new Entity(Resources::R_MENU_NAME_PART2, 1, 4, this);
    
        this->mSpotlight1 = new Spotlight(this);
        this->mSpotlight2 = new Spotlight(this);
    
        this->mPeople = new BatchEntityManager(20, new People(), this);
    
        this->mPlay = new PlayButton(this);
    
        this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
    
        this->mSpotlight1->create()->setCenterPosition(Utils::coord(128), Utils::coord(270));
        this->mSpotlight2->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(128), Utils::coord(270));
    
        this->mSpotlight1->setScaleX(-1);
    
        this->mNamePanel->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(100));
        this->mNamePart1->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(150));
        this->mNamePart2->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(50));
    
        this->mNamePanel->animate(0.1f);
        this->mNamePart1->animate(0.1f);
        this->mNamePart2->animate(0.1f);
    
        this->generateStars();
        this->generatePeople();
    }

// ===========================================================
// Methods
// ===========================================================

void Menu::generateStars()
{
    for (int i = 0; i < 50; i++)
    {
        this->mStars->create()->setCurrentFrameIndex(0);
    }
    
    for (int i = 0; i < 50; i++)
    {
        this->mStars->create()->setCurrentFrameIndex(1);
    }
}

void Menu::generatePeople()
{
    for (int i = 0; i < 20; i++)
    {
        Entity* people = this->mPeople->create();
        people->setCurrentFrameIndex(i);
        people->setCenterPosition(i * Utils::coord(150.0f), Utils::coord(130.0f));
    }
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif