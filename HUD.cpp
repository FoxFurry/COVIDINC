//
// Created by foxfurry on 5/11/20.
//

#include "Game.hpp"

void Game::idToHud(int countryID) {
    if(countryID==-1){
        if(!image_buffer.loadFromFile(std::string(ASSETS_THUMBNAILS) + SEP + "world" + ".jpg"))
            image_buffer.loadFromFile(PTH_HUD_MISSING);
        hud_text[0].setString("N/A");
        hud_text[1].setString("N/A");
        hud_text[2].setString("N/A");
        hud_text[3].setString("N/A");
        hud_text[4].setString("N/A");
        hud_text[5].setString("N/A");

    }
    else {
        hud_text[0].setString(database.getCountryName(countryID));
        hud_text[1].setString(database.getCountryState(countryID));
        countryPeople buffer = database.getCountryPeople(countryID);
        hud_text[2].setString(std::to_string((long long)buffer.suspected));
        hud_text[3].setString(std::to_string((long long)buffer.infected));
        hud_text[4].setString(std::to_string((long long)buffer.recovered));
        hud_text[5].setString(std::to_string((long long)buffer.dead));

        if (!image_buffer.loadFromFile(std::string(ASSETS_THUMBNAILS) + SEP + hud_text[0].getString() + ".jpg"))
            image_buffer.loadFromFile(PTH_HUD_MISSING);

    }
    for (int i = 0; i < CNT_HUD_STRINGS; i++) {
        if (i < 2)
            hud_text[i].setOrigin(hud_text[i].getGlobalBounds().width / 2,
                                  hud_text[i].getGlobalBounds().height / 2);
        else hud_text[i].setOrigin(hud_text[i].getGlobalBounds().width, hud_text[i].getGlobalBounds().height / 2);
    }
    thumbnail.loadFromImage(image_buffer);
    thumbnail_s.setTexture(thumbnail);
    currentCountry = selectedCountry;
}

void Game::loadThumbnail(std::string path) {
    if(!image_buffer.loadFromFile(std::string(ASSETS_THUMBNAILS) + SEP + "brazil" + ".jpg"))
        image_buffer.loadFromFile(PTH_HUD_MISSING);
    thumbnail.loadFromImage(image_buffer);
    thumbnail_s.setTexture(thumbnail);
    thumbnail_s.setOrigin(thumbnail_s.getTextureRect().width/2, thumbnail_s.getTextureRect().height/2);
    thumbnail_s.setScale((double)SZ_HUD_THUMBNAIL / thumbnail_s.getTextureRect().width, (double)SZ_HUD_THUMBNAIL / thumbnail_s.getTextureRect().height);
    thumbnail_s.setPosition((hudRight[1].position.x + hudRight[2].position.x)/2, hudRight[1].position.y + (hudRight[0].position.y - hudRight[1].position.y)*SZ_HUD_THUMBNAIL_INIT);
    frame_s.setPosition(thumbnail_s.getPosition());
}

void Game::moveHUD(bool status) {
    for(int i = 0; i < CNT_HUD_VERTICES; i++)
        hudRight[i].position.x -= (status?SZ_HUD_WIDTH:-SZ_HUD_WIDTH);
    thumbnail_s.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    frame_s.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    suspected_hud.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    infected_hud.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    recovered_hud.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    dead_hud.move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    for(int i = 0; i < CNT_HUD_STRINGS; i++)
        hud_text[i].move(status?-SZ_HUD_WIDTH:SZ_HUD_WIDTH,0);
    hudPolySynchronize();
}

void Game::hudPolySynchronize() {
    std::vector<point> output;
    output.resize(4);
    for(int i = 0; i < 4; i++)
        output[i] = point(hudRight[i+4].position.x, hudRight[i+4].position.y);

    hudPoly = output;
}

void Game::HUDInitialize(RenderWindow &target) {
    hudRightState = false;
    hudRight.resize(CNT_HUD_VERTICES);
    hudLeft.resize(CNT_HUD_VERTICES);

    hudRight.setPrimitiveType(Quads);
    hudLeft.setPrimitiveType(Quads);

    for(int i = 0; i < CNT_HUD_VERTICES;i++){
        hudLeft[i].color = Color::Black;
        hudRight[i].color = Color::Black;
    }

    hudRight[0].position = Vector2f(target.getSize().x, (target.getSize().y+SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);
    hudLeft[0].position = Vector2f(0, (target.getSize().y+SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);

    hudRight[1].position = Vector2f(target.getSize().x, (target.getSize().y-SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);
    hudLeft[1].position = Vector2f(0, (target.getSize().y-SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);

    hudRight[2].position = Vector2f(target.getSize().x - SZ_HUD_WIDTH, (target.getSize().y-SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);
    hudLeft[2].position = Vector2f(SZ_HUD_WIDTH, (target.getSize().y-SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);

    hudRight[3].position = Vector2f(target.getSize().x - SZ_HUD_WIDTH, (target.getSize().y+SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);
    hudLeft[3].position = Vector2f(SZ_HUD_WIDTH, (target.getSize().y+SZ_HUD_HEIGHT)/2 + SZ_HUD_OFFSET_Y);


    for(int i = 0; i < CNT_HUD_VERTICES/2; i++){
        hudLeft[i].color = Color(50,50,50,130);
        hudRight[i].color = Color(50,50,50,130);
    }

    hudRight[4].position = hudRight[3].position;
    hudLeft[4].position = hudLeft[3].position;

    hudRight[5].position = hudRight[2].position;
    hudLeft[5].position = hudLeft[2].position;

    hudRight[6].position = Vector2f(hudRight[5].position.x - SZ_HUD_BUTTON, hudRight[5].position.y + SZ_HUD_BUTTON);
    hudLeft[6].position = Vector2f(hudLeft[5].position.x + SZ_HUD_BUTTON, hudLeft[5].position.y + SZ_HUD_BUTTON);

    hudRight[7].position = Vector2f(hudRight[4].position.x - SZ_HUD_BUTTON, hudRight[4].position.y - SZ_HUD_BUTTON);
    hudLeft[7].position = Vector2f(hudLeft[4].position.x + SZ_HUD_BUTTON, hudLeft[4].position.y - SZ_HUD_BUTTON);

    for(int i = CNT_HUD_VERTICES/2; i < CNT_HUD_VERTICES; i++){
        hudLeft[i].color = Color(50,50,50,180);
        hudRight[i].color = Color(50,50,50,180);
    }

    if(!hud_font.loadFromFile(PTH_FONT_MAIN))
        throw(PTH_FONT_MAIN);


    loadThumbnail("world");

    hud_text.resize(CNT_HUD_STRINGS);
    for(int i = 0; i < CNT_HUD_STRINGS; i++){
        hud_text[i].setFont(hud_font);
        hud_text[i].setCharacterSize(19);
        hud_text[i].setString("N/A");
        if(i<2)hud_text[i].setOrigin(hud_text[0].getGlobalBounds().width/2, hud_text[0].getGlobalBounds().height/2);
        else hud_text[i].setOrigin(hud_text[0].getGlobalBounds().width, hud_text[0].getGlobalBounds().height/2);
    }
    hud_text[0].setPosition((hudRight[1].position.x + hudRight[2].position.x)/2,
                            hudRight[1].position.y + (hudRight[0].position.y - hudRight[1].position.y)*SZ_HUD_THUMBNAIL_INIT + SZ_HUD_TEXT_INIT_Y);
    hud_text[1].setPosition(hud_text[0].getPosition().x, hud_text[0].getPosition().y + SZ_HUD_TEXT_OFFSET_Y);

    suspected_hud.setPosition(target.getSize().x + SZ_HUD_ICN_OFFSET_X, hud_text[1].getPosition().y + SZ_HUD_ICN_Y);
    infected_hud.setPosition(suspected_hud.getPosition().x, suspected_hud.getPosition().y + SZ_HUD_ICN_Y);
    recovered_hud.setPosition(infected_hud.getPosition().x, infected_hud.getPosition().y + SZ_HUD_ICN_Y);
    dead_hud.setPosition(recovered_hud.getPosition().x, recovered_hud.getPosition().y + SZ_HUD_ICN_Y);

    hud_text[2].setPosition(suspected_hud.getPosition().x - SZ_HUD_ICN_TEXT_OFFSET_X, suspected_hud.getPosition().y);
    hud_text[3].setPosition(infected_hud.getPosition().x - SZ_HUD_ICN_TEXT_OFFSET_X, infected_hud.getPosition().y);
    hud_text[4].setPosition(recovered_hud.getPosition().x - SZ_HUD_ICN_TEXT_OFFSET_X, recovered_hud.getPosition().y);
    hud_text[5].setPosition(dead_hud.getPosition().x - SZ_HUD_ICN_TEXT_OFFSET_X, dead_hud.getPosition().y);

    if(!image_buffer.loadFromFile(PTH_HUD_FRAME))
        throw(PTH_HUD_FRAME);
    frame.loadFromImage(image_buffer);
    frame_s.setTexture(frame);
    frame_s.setOrigin(frame_s.getTextureRect().width/2, frame_s.getTextureRect().height/2);
    frame_s.setScale((double)SZ_HUD_THUMBNAIL / frame_s.getTextureRect().width, (double)SZ_HUD_THUMBNAIL / frame_s.getTextureRect().height);

    moveHUD(hudRightState);
}
