#ifndef CONST_WEAPON
#define CONST_WEAPON

#include "Weapon.h"

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

Weapon::Weapon(CCNode* pParent) :
    Entity(Resources::R_WEAPON_1, 5, 4, pParent)
    {
        
    }

// ===========================================================
// Methods
// ===========================================================

void Weapon::onAnimationEnd()
{
    this->destroy();
}

void Weapon::animation()
{
    int startFrame = 5;//Utils::random(0, 3) * 5;
    
    this->setStartFrame(startFrame);
    this->setFinishFrame(startFrame + 5);
    
    this->animate(0.07f, 1);
    
    //SimpleAudioEngine::sharedEngine()->playEffect(Resources::SFX_CAT1);
}

// ===========================================================
// Virtual Methods
// ===========================================================

Weapon* Weapon::deepCopy()
{
    return new Weapon(this->getParent());
}

#endif