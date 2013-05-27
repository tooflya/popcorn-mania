#ifndef CONST_LOSE_H
#define CONST_LOSE_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Lose : public Entity
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
    
        float mTime;
        float mTimeElapsed;

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
    
        Lose();

		// ===========================================================
		// Methods
		// ===========================================================
    
        Entity* create();
    
        void update(float pDeltaTime);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
    
        Lose* deepCopy();
};

#endif