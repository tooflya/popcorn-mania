#ifndef CONST_PAUSE_H
#define CONST_PAUSE_H

#include "cocos2d.h"

#include "Popscreen.h"

#include "BatchEntityManager.h"

using namespace cocos2d;

class Pause : public Popscreen
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
    
        BatchEntityManager* mLines1;
        BatchEntityManager* mLines2;
    
        Entity* mPanel;
        Entity* mName;
    
        Entity* mContinueButton;
        Entity* mRestartButton;
        Entity* mMenuButton;

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
    
        Pause();

		// ===========================================================
		// Methods
        // ===========================================================
    
        void show();
        void hide();
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
};

#endif