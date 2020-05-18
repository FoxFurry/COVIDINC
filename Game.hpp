//
// Created by foxfurry on 5/6/20.
//

#ifndef PLAGUEINC_GAME_HPP
#define PLAGUEINC_GAME_HPP

#include "GraphicsDependicies.h"
#include "DataFrame.h"

class Game{
private:
    Image image_buffer, map_mask, visualizer;
    Texture world_map, gui_news, suspected, infected, recovered, dead, thumbnail, frame, visualSpread;
    Sprite  world_s, wind_s, gui_news_s, suspected_s, infected_s, recovered_s, dead_s,
            suspected_hud, infected_hud, recovered_hud, dead_hud, thumbnail_s, frame_s,
            visualSpread_s;
    View world_map_view, ui_view;
    VertexArray static_map_fader, gui_main_border, hudLeft, hudRight;
    RectangleShape fader;
    Font gui_font, hud_font;

    Color colorBuffer;

    DataFrame database;
    std::string world_state, epidemic_state, news_feed;
    std::vector<Texture> wind;
    std::vector<point> hudPoly;
    std::vector<Text> gui_text, hud_text;

    Vector2i mouseBuffer, mouseBufferStatic;
    Vector2f activeCoords;
    int viewScale, selectedCountry, currentCountry;

    double frameCounter, resoX, resoY, scaleFactorX, scaleFactorY, fadeCoef, timeBuffer;
    bool loadComplete, moveMode, hudRightState, timeGiven, mapClicked;

    void draw(RenderWindow &target){
        View buffer = target.getView();
        // WORLD MAP OBJECTS
        target.setView(world_map_view);
        target.draw(world_s);
        target.draw(wind_s);
        // GUI OBJECTS
        target.setView(ui_view);
        target.draw(gui_main_border);
        target.draw(gui_news_s);
        target.draw(suspected_s);
        target.draw(infected_s);
        target.draw(recovered_s);
        target.draw(dead_s);
        for(int i = 0; i < CNT_TEXT_STRINGS; i++)
            target.draw(gui_text[i]);
        // STATIC OBJECTS
        target.setView(buffer);
        target.draw(hudRight);
        target.draw(thumbnail_s);
        target.draw(frame_s);
        target.draw(suspected_hud);
        target.draw(infected_hud);
        target.draw(recovered_hud);
        target.draw(dead_hud);
        for(int i = 0; i < CNT_HUD_STRINGS; i++)
            target.draw(hud_text[i]);
        //target.draw(hudLeft);
        target.draw(static_map_fader);
        target.draw(fader);
    }
    void mapInitialize(RenderWindow &target);
    void GUIInitialize(RenderWindow &target);
    void HUDInitialize(RenderWindow &target);
    void activeMap(int scrollStatus, Event event);
    void moveMap(Vector2f offset);
    void activeGUI(int scrollStatus);
    void stringTextSynchronize();
    void moveHUD(bool status);
    void hudPolySynchronize();
    void loadThumbnail(std::string path);
    void idToHud(int countryID);
public:
    Game(RenderWindow &target){
        database.universalCSVReader();
        resoX = target.getSize().x;
        resoY = target.getSize().y;
        loadComplete = 0;
        mapInitialize(target);
        GUIInitialize(target);
        HUDInitialize(target);
    }
    void update(RenderWindow &target, double timePerFrame, double timeElapsed, Event event){
        double scrollStatus = event.mouseWheelScroll.delta;
        if(!timeGiven){
            timeBuffer = timeElapsed;
            timeGiven = true;

        }
        double timeElapsedGame = timeElapsed - timeBuffer;
        if(tm_interval(timeElapsedGame, -1, TM_GAME_FO)){
            fadeCoef += timePerFrame * SP_FADE;
            if (fadeCoef > 255)fadeCoef = 255;
        }
        int tempFrame = frameCounter;
        frameCounter+=timePerFrame * SP_WIND;
        frameCounter >= (double)CNT_FRAMES_WIND? frameCounter = 0 : 0;
        if(tempFrame!=(int)frameCounter)wind_s.setTexture(wind[int(frameCounter)]);

        point mousePos = point(Mouse::getPosition(target).x, Mouse::getPosition(target).y);
        if(Mouse::isButtonPressed(Mouse::Left) && inPolygon(mousePos, hudPoly) && !moveMode){
            hudRightState=!hudRightState;
            moveHUD(hudRightState);
        }
        else if(world_s.getGlobalBounds().contains(Mouse::getPosition(target).x, Mouse::getPosition(target).y)){
            activeMap(scrollStatus, event);
        }
        else activeGUI(scrollStatus);
        stringTextSynchronize();

        if(mapClicked){
            Vector2i temp = Mouse::getPosition(target);
            activeCoords = target.mapPixelToCoords(temp, world_map_view);
            activeCoords.x /= scaleFactorX;
            activeCoords.y /= scaleFactorY;
            colorBuffer = map_mask.getPixel(activeCoords.x, activeCoords.y);
            int green = colorBuffer.g;
            int red = colorBuffer.r;
            if(red==100)
                selectedCountry = (green-100)/2;
            else if(red == 200)
                selectedCountry = (green-100)/2+78;
            else selectedCountry = -1;
            mapClicked = 0;
        }
        if(currentCountry!=selectedCountry)idToHud(selectedCountry);


        fader.setFillColor(Color(0, 0, 0, 255 - fadeCoef));
        draw(target);
    }

    void loadResources();
    bool getLoadStatus(){return loadComplete;}
};

#endif //PLAGUEINC_GAME_HPP



// 100 RED / 100 BLUE / VAR GREEN
/*
 *100 - russia
 *102 - mongolia
 *104 - china
 *106 - burma
 *108 - laos
 *110 - thailand
 *112 - cambodia
 *114 - vietnam
 *116 - indonesia
 *118 - malaysia
 *120 - australia
 *122 - new zealand
 *124 - nepal
 *126 - india
 *128 - bangl
 *130 - pakistan
 *132 - afganistan
 *134 - tadjikistan
 *136 - kirgizstan
 *138 - kazakhstan
 *140 - uzbekistan
 *142 - turkmenistan
 *144 - iran
 *146 - azerbajan
 *148 - turkey
 *150 - iraq
 *152 - syria
 *154 - saudi arabia
 *156 - oman
 *158 - yemen
 *160 - somalia
 *162 - ethiopia
 *164 - kenya
 *166 - uganda
 *168 - tanzania
 *170 - mozambique
 *172 - madagascar
 *174 - south africa
 *176 - lesotho
 *178 - namibia
 *180 - botswana
 *182 - zimbabwe
 *184 - zambia
 *186 - angola
 *188 - democratic congo
 *190 - congo
 *192 - gabon
 *194 - sudan
 *196 - C A R
 *198 - cam
 *200 - nigeria
 *202 - niger
 *204 - chad
 *206 - egypt
 *208 - libya
 *210 - algeria
 *212 - mali
 *214 - morocco
 *216 - western sahara
 *218 - mauritania
 *220 - senegal
 *222 - sierra leone
 *224 - ukraine
 *226 - belarus
 *228 - romania
 *230 - moldova
 *232 - bulgaria
 *234 - finland
 *236 - sweden
 *238 - norway
 *240 - united kingdom
 *242 - ireland
 *244 - portugal
 *246 - spain
 *248 - france
 *250 - germany
 *252 - poland
 *254 - czech
 *
 */

// 200 RED / 100 BLUE / VAR GREEN
/*
 *100 - lithuania
 *102 - latvia
 *104 - estonia
 *106 - italy
 *108 - hungary
 *110 - slovakia
 *112 - austria
 *114 - switzerland
 *116 - greece
 *118 - serbia
 *120 - bosnia
 *122 - slovenia
 *124 - belgium
 *126 - netherlands
 *128 - brazil
 *130 - bolivia
 *132 - paraguay
 *134 - argentina
 *136 - uruguay
 *138 - chile
 *140 - peru
 *142 - ecuador
 *144 - colombia
 *146 - venesuala
 *148 - guyana
 *150 - suriname
 *152 - french guyana
 *154 - mexico
 *156 - united states
 *158 - canada
 *160 - greenland
 *162 - iceland
 *164 - guatemala
 *166 - honduras
 *168 - nicaragua
 *170 - costa rica
 *172 - panama
 */
