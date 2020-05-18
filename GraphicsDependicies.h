//
// Created by fox on 3/23/20.
//

#ifndef PLAGUEINC_GRAPHICSDEPENDICIES_H
#define PLAGUEINC_GRAPHICSDEPENDICIES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Trigonometry.h"

#ifdef _WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif

#define ASSETS_ROOT "source"
#define ASSETS_SPRITES ASSETS_ROOT SEP "sprites"
#define ASSETS_DATABASE ASSETS_ROOT SEP "database"
#define ASSETS_COUNTRIES ASSETS_ROOT SEP "countries"
#define ASSETS_THUMBNAILS ASSETS_ROOT SEP "thumbnails"

#define PTH_FONT_MAIN "source" SEP "fonts" SEP "neuropol.ttf"

#define PTH_MENU_FOX ASSETS_SPRITES SEP "fox_logo.png"
#define PTH_MENU_TITLE_1 ASSETS_SPRITES SEP "title_glitch" SEP "frame_"
#define PTH_MENU_LOGO_1 ASSETS_SPRITES SEP "logo_glitch" SEP "frame_"
#define PTH_MENU_BIOHAZARD ASSETS_SPRITES SEP "biohazard_glitch" SEP "frame_"
#define PTH_MENU_PATH_END "_delay-0.05s.gif"

#define PTH_GAME_WORLD ASSETS_SPRITES SEP "map" SEP "world_map.png"
#define PTH_GAME_MASK ASSETS_SPRITES SEP "map" SEP "wold_map_mask.png"
#define PTH_GAME_WIND ASSETS_SPRITES SEP "wind_arr" SEP "wind_00"
#define PTH_GAME_NEWS ASSETS_SPRITES SEP "gui" SEP "breaking_news.png"
#define PTH_GAME_SUSPECTED ASSETS_SPRITES SEP "gui" SEP "suspected.png"
#define PTH_GAME_INFECTED ASSETS_SPRITES SEP "gui" SEP "infected.png"
#define PTH_GAME_RECOVERED ASSETS_SPRITES SEP "gui" SEP "recovered.png"
#define PTH_GAME_DEAD ASSETS_SPRITES SEP "gui" SEP "dead.png"
#define PTH_GAME_PATH_END "-fs8.png"

#define PTH_HUD_WORLD ASSETS_THUMBNAILS SEP "world.jpg"
#define PTH_HUD_MISSING ASSETS_THUMBNAILS SEP "noImage.jpg"
#define PTH_HUD_FRAME ASSETS_THUMBNAILS SEP "frame.png"
#define PTH_HUD_NOICE ASSETS_SPRITES SEP ""

#define PTH_CSV_PART_1 ASSETS_COUNTRIES SEP "part1.csv"
#define PTH_CSV_PART_2 ASSETS_COUNTRIES SEP "part2.csv"

// MENU

#define CNT_FRAMES 80

#define PT_BUTTONS_INIT 0.275f

#define SZ_BUTTONS_OFFSET 110
#define SZ_BUTTONS_ALPHA 550
#define SZ_BUTTONS_BETA 600
#define SZ_BUTTONS_GAMMA 80

#define SP_BUTTON_TRANSLATION 1.2f
#define SP_LOGO_GLITCH 0.012f
#define SP_TITLE_GLICTH 0.02f
#define SP_FADE 0.1f

#define TM_LOGO_FO 2
#define TM_LOGO_GLITCH 3
#define TM_LOGO_FI 5
#define TM_BUTTON_FIRST_APPEAR 2.2f
#define TM_FADE_STOP 2.4f
#define TM_BUTTON_DISAPP 1.2f
#define TM_BUTTON_INIT 1.4f
#define TM_BUTTON_APPEAR 2.6f

// WORLD MAP

//#define CNT_DANGER_SIGNS 3
#define CNT_FRAMES_WIND 100
#define CNT_GUI_BLOCKS 3
#define CNT_TEXT_STRINGS 7
#define CNT_HUD_STRINGS 6
#define CNT_HUD_VERTICES 8
#define CNT_FRAMES_NOICE 14

#define SZ_MAP_FADER 30
#define SZ_TEXT_OFFSET_X 60
#define SZ_TEXT_INIT_Y 30
#define SZ_TEXT_OFFSET_Y 50
#define SZ_ICON_OFFSET_X 300
#define SZ_HUD_HEIGHT 500
#define SZ_HUD_WIDTH 300
#define SZ_HUD_BUTTON 20
#define SZ_HUD_OFFSET_Y -100
#define SZ_HUD_THUMBNAIL_INIT 0.2f
#define SZ_HUD_TEXT_INIT_Y 90
#define SZ_HUD_TEXT_OFFSET_Y 25
#define SZ_HUD_ICN_Y 60
#define SZ_HUD_ICN_OFFSET_X -60
#define SZ_HUD_ICN_TEXT_OFFSET_X 20
#define SZ_HUD_THUMBNAIL 150

#define SP_WIND 0.015f

#define TM_GAME_FO 2

#define MAP_RATIO 10
#define MAP_GUI_RATIO 0.9f
#define RAT_ICONS_SCALE 0.09f
#define RAT_ICONS_HUD 0.1f
#define CLR_GUI_BLOCK_1 Color(60,60,60)
#define CLR_GUI_BLOCK_2 CLR_GUI_BLOCK_1//Color(80,80,80)


//static inline bool tm_interval(double currentTime, double startTime, double endTime);
//
//static inline bool tm_tick(double currentTime, double tick);

static inline bool tm_interval(double currentTime, double startTime, double endTime){
    double sT = startTime * 1000000, eT = endTime * 1000000;
    if(startTime<0)return currentTime < eT;
    else if(endTime<0)return currentTime > sT;
    else return currentTime > sT && currentTime < eT;
}

using namespace sf;

#endif //PLAGUEINC_GRAPHICSDEPENDICIES_H
