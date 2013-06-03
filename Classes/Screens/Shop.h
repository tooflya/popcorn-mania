#ifndef CONST_SHOP_H
#define CONST_SHOP_H

#include "cocos2d.h"

#include "Popscreen.h"

#include "BatchEntityManager.h"

class Menu;

using namespace cocos2d;

class Shop : public Popscreen
{
	protected:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
        // ===========================================================
    
        Entity* mBackgroundDecoration;
    
        Entity* mGetButtonPanel;
        Entity* mGetButtonLabel;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
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

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
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
    
        Shop(Menu* pMenu);

		// ===========================================================
		// Methods
        // ===========================================================
    
        void show();
        void hide();
    
        void update(float pDeltaTime);
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
};

#endif