//
// Created by foxfurry on 5/2/20.
//


#include "Menu.hpp"

void Menu::menuInitialize(RenderWindow &target){
    fader.setSize(Vector2f(target.getSize().x, target.getSize().y));
    fader.setFillColor(Color(0, 0, 0, 0));

    fox_sprite.setPosition(target.getSize().x / 2, target.getSize().y * 0.4);
    biohard_sprite.setPosition(target.getSize().x * 0.8, target.getSize().y / 2);

    phase2StartTime = 0;
    fadeCoef = 0;
    frameCounter = 0, phase = 0;
    gameStart=0;
}

void Menu::loadResources() {
    image_buffer.loadFromFile(PTH_MENU_FOX);
    fox_texture.loadFromImage(image_buffer);
    fox_sprite.setTexture(fox_texture);
    fox_sprite.setOrigin(fox_sprite.getTextureRect().width / 2, fox_sprite.getTextureRect().height / 2);

    for (int i = 0; i < CNT_FRAMES; i++) {

        std::string texture_name = std::string(PTH_MENU_TITLE_1) + (i < 10 ? std::string("0") : "") + std::to_string(i) + PTH_MENU_PATH_END;
        if (!image_buffer.loadFromFile(texture_name))
            throw (texture_name);

        title_texture[i].loadFromImage(image_buffer);
        texture_name = std::string(PTH_MENU_LOGO_1) + (i < 10 ? std::string("0") : "") + std::to_string(i) + PTH_MENU_PATH_END;

        if (!image_buffer.loadFromFile(texture_name))
            throw (texture_name);

        logo_texture[i].loadFromImage(image_buffer);
        texture_name = PTH_MENU_BIOHAZARD + (i < 10 ? std::string("0") : "") + std::to_string(i) + PTH_MENU_PATH_END;

        if (!image_buffer.loadFromFile(texture_name))
            throw (texture_name);

        biohard_texture[i].loadFromImage(image_buffer);
        biohard_texture[i].setSmooth(1);
    }
    title_sprite.setTexture(title_texture[0]);
    title_sprite.setOrigin(title_sprite.getTextureRect().width / 2, title_sprite.getTextureRect().height / 2);
    title_sprite.setPosition(fox_sprite.getPosition());
    title_sprite.move(0, 350);

    logo_sprite.setTexture(logo_texture[0]);
    logo_sprite.move(100, 50);

    biohard_sprite.setTexture(biohard_texture[0]);
    biohard_sprite.setOrigin(biohard_sprite.getTextureRect().width / 2, biohard_sprite.getTextureRect().height / 2);
    biohard_sprite.setScale(1.5f, 1.5f);
    biohard_sprite.getGlobalBounds().contains(Vector2f(4,4));
}


