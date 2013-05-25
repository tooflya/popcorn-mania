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

const char* Resources::R_MENU_BACKGROUND = "menu-background@2x.png";
const char* Resources::R_MENU_STAR = "menu-star@2x.png";
const char* Resources::R_MENU_PEOPLE = "menu-people@2x.png";
const char* Resources::R_MENU_SPOTLIGHT = "menu-spotlight@2x.png";
const char* Resources::R_MENU_NAME_PANEL = "menu-name-panel@2x.png";
const char* Resources::R_MENU_NAME_PART1 = "menu-name-part1@2x.png";
const char* Resources::R_MENU_NAME_PART2 = "menu-name-part2@2x.png";
const char* Resources::R_MENU_PLAY = "menu-play@2x.png";

const char* Resources::R_GAME_CORN = "game-corn@2x.png";

const char* Resources::R_SCREENS_LINES = "screens-lines@2x.png";
const char* Resources::R_SCREENS_POPCORN = "screens-popcorn@2x.png";

const char* Resources::R_LEVEL_BACKGROUND = "level-background@2x.png";

#else

#endif

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif