#ifndef CONST_APPDELEGATE
#define CONST_APPDELEGATE

#include "AppDelegate.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

float AppDelegate::mSpeedDecreaseFactor = 1.0f;

bool AppDelegate::mIsAlreadyPlayed = false;

ScreenManager* AppDelegate::screens = NULL;

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

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* director 	= CCDirector::sharedDirector();
	CCEGLView*  EGLView 	= CCEGLView::sharedOpenGLView();
	CCSize 	screenSize 		= EGLView->getFrameSize();
    
	director->setOpenGLView(EGLView);
    
	director->setContentScaleFactor(MIN(designResolutionSize.width / screenSize.width, designResolutionSize.height / screenSize.height));

	vector <string> searchPath;
    
	searchPath.push_back(resources1280x720.directory);

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	Options::CAMERA_WIDTH  = screenSize.width;
	Options::CAMERA_HEIGHT = screenSize.height;

	Options::CAMERA_CENTER_X  = screenSize.width / 2;
	Options::CAMERA_CENTER_Y = screenSize.height / 2;
    
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0f / 60.0f);
	director->setProjection(kCCDirectorProjection2D);
    
    AppDelegate::screens = new ScreenManager();

	director->runWithScene(AppDelegate::screens->mScreens[0]);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

#endif