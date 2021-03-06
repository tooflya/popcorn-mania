#ifndef CONST_POPCORN_H
#define CONST_POPCORN_H

#include "cocos2d.h"

#include "ImpulseEntity.h"

using namespace cocos2d;

class Popcorn : public ImpulseEntity
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
    
        Popcorn();

		// ===========================================================
		// Methods
		// ===========================================================
    
        Entity* create();
    
        void update(float pDelta);
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================
    
        virtual Popcorn* deepCopy();
};

#endif