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

const char* Resources::R_MENU_BACKGROUND1 = "bg@2x.png";
const char* Resources::R_MENU_BACKGROUND2 = "bg-scene@2x.png";
const char* Resources::R_MENU_STAR = "star-sprite@2x.png";
const char* Resources::R_MENU_PEOPLE = "dark-body-sprite@2x.png";
const char* Resources::R_MENU_SPOTLIGHT = "light-big@2x.png";
const char* Resources::R_MENU_NAME_PANEL = "bg-name@2x.png";
const char* Resources::R_MENU_NAME = "name-sprite@2x.png";
const char* Resources::R_MENU_PLAY = "btn-play@2x.png";
const char* Resources::R_MENU_SCORE = "btn-score@2x.png";
const char* Resources::R_MENU_SHOP = "btn-shop@2x.png";
const char* Resources::R_MENU_SHADOW = "dark-line@2x.png";

const char* Resources::R_GAME_CORN = "game-corn@2x.png";
const char* Resources::R_GAME_STREAK = "level-streak@2x.png";

const char* Resources::R_SCREENS_LINES = "preload-lines@2x.png";
const char* Resources::R_SCREENS_POPCORN = "screens-popcorn@2x.png";

const char* Resources::R_LEVEL_BACKGROUND = "level-bg@2x.png";
const char* Resources::R_LEVEL_BUCKET = "bucket@2x.png";
const char* Resources::R_LEVEL_DUST = "level-dust@2x.png";

#else

#endif

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif