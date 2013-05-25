#ifndef CONST_RESOURCES
#define CONST_RESOURCES

#include "Resources.h"

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

#if TARGET_PLATFORM == PLATFORM_MACOS || TARGET_PLATFORM == PLATFORM_IOS

const char* Resources::R_MENU_BACKGROUND = "bg@2x.png";
const char* Resources::R_MENU_STAR = "bg-big-star@2x.png";
const char* Resources::R_MENU_PEOPLE = "bg-big-star@2x.png";
const char* Resources::R_MENU_SPOTLIGHT = "bg-big-star@2x.png";
const char* Resources::R_MENU_NAME_PANEL = "bg-big-star@2x.png";
const char* Resources::R_MENU_NAME_PART1 = "bg-big-star@2x.png";
const char* Resources::R_MENU_NAME_PART2 = "bg-big-star@2x.png";
const char* Resources::R_MENU_PLAY = "bg-big-star@2x.png";

const char* Resources::R_GAME_CORN = "bg-big-star@2x.png";

const char* Resources::R_SCREENS_LINES = "bg-big-star@2x.png";
const char* Resources::R_SCREENS_POPCORN = "bg-big-star@2x.png";

const char* Resources::R_LEVEL_BACKGROUND = "bg-big-star@2x.png";

#else

#endif

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif