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
const char* Resources::R_MENU_BUTTON_SOUND = "button-sound@2x.png";
const char* Resources::R_MENU_BUTTON_MUSIC = "button-music@2x.png";
const char* Resources::R_MENU_BUTTON_FACEBOOK = "button-facebook@2x.png";
const char* Resources::R_MENU_BUTTON_TWITTER = "button-twitter@2x.png";
const char* Resources::R_MENU_BUTTON_MORE_GAMES = "button-more-games@2x.png";
const char* Resources::R_MENU_SOCIAL_PANEL = "soc-btns-bg@2x.png";
const char* Resources::R_MENU_SOCIAL_LABEL = "soc-btns-bg-tong@2x.png";

const char* Resources::R_LOADING_BACKGROUND = "preload-background@2x.png";

const char* Resources::R_RATE_NAME = "rate-text@2x.png";
const char* Resources::R_RATE_BUTTONS_BACKGROUND = "rate-btn-bg@2x.png";
const char* Resources::R_RATE_BACKGROUND_DECORATION = "rate-bg-wh@2x.png";
const char* Resources::R_RATE_BUTTON_NO = "rate-btn-no@2x.png";
const char* Resources::R_RATE_BUTTON_YES = "rate-btn-yes@2x.png";
const char* Resources::R_RATE_BUTTON_LATER = "rate-btn-later@2x.png";

const char* Resources::R_GAME_CORN = "game-corn@2x.png";
const char* Resources::R_GAME_CORN_SHADOW = "game-corn-shdw@2x.png";
const char* Resources::R_GAME_LARGE_FONT = "num-sprite-big@2x.png";
const char* Resources::R_GAME_SMALL_FONT = "num-sprite-small@2x.png";

const char* Resources::R_SCREENS_LINES = "preload-lines@2x.png";
const char* Resources::R_SCREENS_POPCORN = "preload-bar-sprite@2x.png";

const char* Resources::R_LEVEL_BACKGROUND = "level-bg@2x.png";
const char* Resources::R_LEVEL_BUCKET = "stuff-sprite@2x.png";
const char* Resources::R_LEVEL_BUCKET_SHADOW = "stuff-sprite-shadow@2x.png";
const char* Resources::R_LEVEL_DUST = "process-dust@2x.png";
const char* Resources::R_LEVEL_PAUSE = "process-pause@2x.png";
const char* Resources::R_LEVEL_BUCKETICON = "process-bucket-icon@2x.png";
const char* Resources::R_LEVEL_LOSE = "process-lose@2x.png";
const char* Resources::R_LEVEL_GAMEOVER = "process-gameover@2x.png";
const char* Resources::R_LEVEL_CORN_SHADOW = "game-corn-shadow@2x.png";
const char* Resources::R_LEVEL_DECORATION1 = "wh-bg@2x.png";
const char* Resources::R_LEVEL_DECORATION2 = "wh-bg2@2x.png";
const char* Resources::R_LEVEL_COIN = "process-coin@2x.png";
const char* Resources::R_LEVEL_COIN_SHADOW = "process-coin-shdw@2x.png";
const char* Resources::R_LEVEL_COINS_ICON = "process-coin-count-ico@2x.png";
const char* Resources::R_LEVEL_START_BACKGROUND = "frames-count@2x.png";
const char* Resources::R_LEVEL_START_NUMBERS = "frames-count-num-sprite@2x.png";
const char* Resources::R_LEVEL_LIFES = "process-life-ticket-counter-sprite@2x.png";
const char* Resources::R_LEVEL_PHOTO_LIGHTS = "photo-lights@2x.png";
const char* Resources::R_LEVEL_LABEL_BEST = "best-score-text@2x.png";

const char* Resources::R_SHOP_BUTTON_BACK = "shop-btn-back@2x.png";
const char* Resources::R_SHOP_BUTTON_GET_PANEL = "shop-btn-get-coins-bg@2x.png";
const char* Resources::R_SHOP_BUTTON_GET_NAME = "shop-btn-get-coins-text@2x.png";
const char* Resources::R_SHOP_STROKE = "shop-stroke-sprite@2x.png";

const char* Resources::R_PAUSE_NAME = "pause-text-sprite@2x.png";
const char* Resources::R_PAUSE_NAME_PANEL = "pause-bg@2x.png";
const char* Resources::R_PAUSE_MENU_BUTTON = "pause-menu-btn@2x.png";
const char* Resources::R_PAUSE_RESTART_BUTTON = "pause-rs-btn@2x.png";
const char* Resources::R_PAUSE_CONTINUE_BUTTON = "pause-cont-btn@2x.png";

const char* Resources::R_GAMEOVER_NAME = "game-over-text-sprite@2x.png";
const char* Resources::R_GAMEOVER_NAME_PANEL = "pause-bg@2x.png";

const char* Resources::R_WEAPON_1 = "weapon-sprite@2x.png";

const char* Resources::SFX_CAT1 = "cat1.mp3";
const char* Resources::SFX_KICK1 = "kick1.mp3";

#else

const char* Resources::SFX_CAT1 = "assets/Sound/cat1.ogg";
const char* Resources::SFX_KICK1 = "assets/Sound/kick1.ogg";

#endif

const char* Resources::S_SCREENS_TIP1 = "Be careful and you will be able to earn";
const char* Resources::S_SCREENS_TIP2 = "bonuses for future plays!";

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif