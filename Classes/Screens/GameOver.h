#ifndef CONST_GAMEOVER_H
#define CONST_GAMEOVER_H

#include "cocos2d.h"

#include "Popscreen.h"

#include "BatchEntityManager.h"

using namespace cocos2d;

class GameOver : public Popscreen
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
    
        GameOver(ScreenManager* pScreenManager);

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