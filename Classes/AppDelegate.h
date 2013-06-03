#ifndef CONST_APPDELEGATE_H
#define CONST_APPDELEGATE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "ScreenManager.h"

#include <vector>

#include "Options.h"

class ScreenManager;

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

typedef struct tagResource {
	CCSize size;
	char directory[100];
} Resource;

static Resource resources480x320 	= { CCSizeMake(480, 320),    "Graphics/480x320"   };
static Resource resources1280x720 	= { CCSizeMake(1280, 720),   "Graphics/1280x720"  };
static Resource resources1920x1080 	= { CCSizeMake(1920, 1080),  "Graphics/1920x1080" };
static CCSize   designResolutionSize  = CCSizeMake(1280, 720);

class AppDelegate : private CCApplication
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
    
        static float mSpeedDecreaseFactor;
    
        static bool mIsAlreadyPlayed;
    
        static ScreenManager* screens;

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

		bool applicationDidFinishLaunching();

		void applicationDidEnterBackground();
		void applicationWillEnterForeground();
};

#endif