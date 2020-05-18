//
// Created by foxfurry on 5/7/20.
//

#include "Game.hpp"

void Game::stringTextSynchronize() {
    gui_text[0].setString("World state: " + world_state);
    gui_text[0].setOrigin(0, gui_text[0].getGlobalBounds().height/2);

    gui_text[1].setString("Epidemic state: " + epidemic_state);
    gui_text[1].setOrigin(0, gui_text[1].getGlobalBounds().height/2);

    countryPeople buffer = database.getAllStats();

    gui_text[2].setString(std::to_string((long long)buffer.suspected));
    gui_text[2].setOrigin(gui_text[2].getGlobalBounds().width, gui_text[2].getGlobalBounds().height/2);

    gui_text[3].setString(std::to_string((long long)buffer.infected));
    gui_text[3].setOrigin(gui_text[3].getGlobalBounds().width, gui_text[3].getGlobalBounds().height/2);

    gui_text[4].setString(std::to_string((long long)buffer.recovered));
    gui_text[4].setOrigin(gui_text[4].getGlobalBounds().width, gui_text[4].getGlobalBounds().height/2);

    gui_text[5].setString(std::to_string((long long)buffer.dead));
    gui_text[5].setOrigin(gui_text[5].getGlobalBounds().width, gui_text[5].getGlobalBounds().height/2);

    gui_text[6].setString(news_feed);
    gui_text[6].setOrigin(gui_text[6].getGlobalBounds().width/2, gui_text[6].getGlobalBounds().height);
}

void Game::GUIInitialize(RenderWindow &target) {
    gui_main_border.setPrimitiveType(Quads);
    gui_main_border.resize(CNT_GUI_BLOCKS * 4);
    double  null_Y = target.getSize().y * (1-MAP_GUI_RATIO),
            null_X = target.getSize().x / CNT_GUI_BLOCKS;
    for(int i = 0; i < CNT_GUI_BLOCKS; i++)
        for(int j = 0; j < 4; j++) {
            gui_main_border[i * 4 + j].position = Vector2f((j%3==0?i:i+1) * null_X,(j > 1 ? null_Y: 0));
            if(i!=1)gui_main_border[i*4+j].color = (j>1?CLR_GUI_BLOCK_1:Color::Black);
            else gui_main_border[i*4+j].color = (j>1?CLR_GUI_BLOCK_2:Color::Black);
        }

    if(!image_buffer.loadFromFile(PTH_GAME_SUSPECTED))
        throw(PTH_GAME_SUSPECTED);
    suspected.loadFromImage(image_buffer);
    suspected.setSmooth(true);
    suspected_s.setTexture(suspected);
    suspected_s.setScale(RAT_ICONS_SCALE,RAT_ICONS_SCALE);
    suspected_s.setOrigin(suspected_s.getTextureRect().width, suspected_s.getTextureRect().height/2);

    suspected_hud.setTexture(suspected);
    suspected_hud.setOrigin(0, suspected_hud.getTextureRect().height/2);
    suspected_hud.setScale(RAT_ICONS_HUD, RAT_ICONS_HUD);

    if(!image_buffer.loadFromFile(PTH_GAME_INFECTED))
        throw(PTH_GAME_INFECTED);
    infected.loadFromImage(image_buffer);
    infected.setSmooth(true);
    infected_s.setTexture(infected);
    infected_s.setScale(RAT_ICONS_SCALE,RAT_ICONS_SCALE);
    infected_s.setOrigin(infected_s.getTextureRect().width, infected_s.getTextureRect().height/2);

    infected_hud.setTexture(infected);
    infected_hud.setOrigin(0, infected_hud.getTextureRect().height/2);
    infected_hud.setScale(RAT_ICONS_HUD, RAT_ICONS_HUD);

    if(!image_buffer.loadFromFile(PTH_GAME_RECOVERED))
        throw(PTH_GAME_RECOVERED);
    recovered.loadFromImage(image_buffer);
    recovered.setSmooth(true);
    recovered_s.setTexture(recovered);
    recovered_s.setScale(RAT_ICONS_SCALE,RAT_ICONS_SCALE);
    recovered_s.setOrigin(recovered_s.getTextureRect().width, recovered_s.getTextureRect().height/2);

    recovered_hud.setTexture(recovered);
    recovered_hud.setOrigin(0, recovered_hud.getTextureRect().height/2);
    recovered_hud.setScale(RAT_ICONS_HUD, RAT_ICONS_HUD);

    if(!image_buffer.loadFromFile(PTH_GAME_DEAD))
        throw(PTH_GAME_DEAD);
    dead.loadFromImage(image_buffer);
    dead.setSmooth(true);
    dead_s.setTexture(dead);
    dead_s.setScale(RAT_ICONS_SCALE,RAT_ICONS_SCALE);
    dead_s.setOrigin(dead_s.getTextureRect().width, dead_s.getTextureRect().height/2);

    dead_hud.setTexture(dead);
    dead_hud.setOrigin(0, dead_hud.getTextureRect().width/2);
    dead_hud.setScale(RAT_ICONS_HUD, RAT_ICONS_HUD);

    suspected_s.setPosition(target.getSize().x - SZ_TEXT_OFFSET_X - SZ_ICON_OFFSET_X, SZ_TEXT_INIT_Y);
    infected_s.setPosition(suspected_s.getPosition().x, suspected_s.getPosition().y + SZ_TEXT_OFFSET_Y);
    recovered_s.setPosition(target.getSize().x - SZ_TEXT_OFFSET_X, SZ_TEXT_INIT_Y);
    dead_s.setPosition(recovered_s.getPosition().x, recovered_s.getPosition().y + SZ_TEXT_OFFSET_Y);

        if(!image_buffer.loadFromFile(PTH_GAME_NEWS))
        throw(PTH_GAME_NEWS);
    gui_news.loadFromImage(image_buffer);
    gui_news.setSmooth(1);
    gui_news_s.setTexture(gui_news);
    gui_news_s.setOrigin(gui_news_s.getTextureRect().width/2, gui_news_s.getTextureRect().height/2);
    gui_news_s.setScale(0.4f, 0.4f);
    gui_news_s.setPosition((gui_main_border[4].position.x + gui_main_border[5].position.x)/2, (1-MAP_GUI_RATIO)*target.getSize().y - SZ_TEXT_INIT_Y);

    world_state = "Calm";
    epidemic_state = "Missing";
    news_feed = "News feed here, lmao";

    if(!gui_font.loadFromFile(PTH_FONT_MAIN))
        throw(PTH_FONT_MAIN);

    gui_text.resize(CNT_TEXT_STRINGS);
    for(int i = 0; i < CNT_TEXT_STRINGS; i++){
        gui_text[i].setFont(gui_font);
        gui_text[i].setCharacterSize(20);
    }



    gui_text[0].setPosition(SZ_TEXT_OFFSET_X, SZ_TEXT_INIT_Y);
    gui_text[1].setPosition(SZ_TEXT_OFFSET_X, SZ_TEXT_INIT_Y*2);
    gui_text[2].setPosition(suspected_s.getPosition()); gui_text[2].move(-SZ_TEXT_OFFSET_X, 0);
    gui_text[3].setPosition(infected_s.getPosition()); gui_text[3].move(-SZ_TEXT_OFFSET_X, 0);
    gui_text[4].setPosition(recovered_s.getPosition()); gui_text[4].move(-SZ_TEXT_OFFSET_X, 0);
    gui_text[5].setPosition(dead_s.getPosition()); gui_text[5].move(-SZ_TEXT_OFFSET_X, 0);

    gui_text[6].setPosition(gui_news_s.getPosition().x, gui_news_s.getPosition().y - SZ_TEXT_OFFSET_Y);

    stringTextSynchronize();


    //gui_text[0].setPosition(gui_main_border[0].position.x + gui_main_border[1].position.x)/2, )
//    gui_main_border[0].position = Vector2f(0, 0);
//    gui_main_border[1].position = Vector2f(null_X,  0);
//    gui_main_border[2].position = Vector2f(null_X, null_Y);
//    gui_main_border[3].position = Vector2f(0, null_Y);
}