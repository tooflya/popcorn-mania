#ifndef CONST_STAR_H
#define CONST_STAR_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Star : public Entity
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
    
        bool mIsAnimationAlphaReverse;
        bool mIsAnimationScaleReverse;
    
        float mAnimationMaxAlpha;
        float mAnimationMinAlpha;
    
        float mAnimationRotationSpeed;
        float mAnimationAlphaSpeed;
        float mAnimationScaleSpeed;

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
    
        Star();

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Virtual Methods
        // ===========================================================
    
        Entity* create();
    
        void setCurrentFrameIndex(int pIndex);
        void update(float pDelta);
    
        virtual Star* deepCopy();
};

#endif