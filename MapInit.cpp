//
// Created by foxfurry on 5/6/20.
//

#include "Game.hpp"

void Game::moveMap(Vector2f offset) {
    double  view_x = 1920 - world_map_view.getCenter().x,
            view_y = 1080 - world_map_view.getCenter().y,
            map_size_x = world_s.getGlobalBounds().width * pow(0.8, viewScale),
            map_size_y = world_s.getGlobalBounds().height * pow(0.8, viewScale);
    world_map_view.move(offset);

    if (view_x + map_size_x / 2 > world_s.getGlobalBounds().width) {
        double offset_segment = view_x + map_size_x / 2 - world_s.getGlobalBounds().width;
        world_map_view.move(offset_segment, 0);
    } else if (view_x - map_size_x / 2 < 0) {
        double offset_segment = view_x - map_size_x / 2;
        world_map_view.move(offset_segment, 0);
    } if (view_y + map_size_y / 2 > world_s.getGlobalBounds().height) {
        double offset_segment = view_y + map_size_y / 2 - world_s.getGlobalBounds().height;
        world_map_view.move(0, offset_segment);
    } else if (view_y - map_size_y / 2 < 0) {
        double offset_segment = view_y - map_size_y / 2;
        world_map_view.move(0, offset_segment);
    }
}

void Game::mapInitialize(RenderWindow &target) {
//    int screen_x = target.getSize().x;
//    int screen_y = target.getSize().y;
//    int gcd;
//    while(gcd!=1){
//        gcd = std::__gcd(screen_x, screen_y);
//        screen_x/=gcd;
//        screen_y/=gcd;
//    }
//    std::cout << screen_x << "\t" << screen_y << "\n";
    fader.setFillColor(Color::Black);
    fader.setSize(Vector2f(target.getSize()));
    fadeCoef = 0; timeGiven = 0;

    static_map_fader.setPrimitiveType(Quads);
    static_map_fader.resize(4);
    static_map_fader[0].position = Vector2f(0, target.getSize().y*MAP_GUI_RATIO - SZ_MAP_FADER);
    static_map_fader[1].position = Vector2f(target.getSize().x, target.getSize().y*MAP_GUI_RATIO - SZ_MAP_FADER);
    static_map_fader[2].position = Vector2f(target.getSize().x, target.getSize().y*MAP_GUI_RATIO);
    static_map_fader[3].position = Vector2f(0, target.getSize().y*MAP_GUI_RATIO);
    for(int i = 0; i < 4; i++)
        static_map_fader[i].color = (i>1?Color::Black:Color::Transparent);

    world_map_view.setCenter(target.getView().getCenter());
    world_map_view.setViewport(FloatRect(0, 0, 1, MAP_GUI_RATIO));
    world_map_view.setSize(1920, 1080);

    ui_view.setCenter(target.getView().getCenter());
    ui_view.setViewport(FloatRect(0, MAP_GUI_RATIO, 1, 1));
    ui_view.setSize(1920, 1080);
    viewScale = 0;
    moveMode = 0;
    mapClicked = 0;
    selectedCountry = -1;
    currentCountry = -1;
}

void Game::loadResources() {
    if(!map_mask.loadFromFile(PTH_GAME_MASK))
        throw(PTH_GAME_MASK);

    if (!image_buffer.loadFromFile(PTH_GAME_WORLD))
        throw (PTH_GAME_WORLD);
    world_map.loadFromImage(image_buffer);
    world_map.setSmooth(1);
    world_s.setTexture(world_map);
    wind.resize(CNT_FRAMES_WIND);
    for (int i = 0; i < CNT_FRAMES_WIND; i++) {
        std::string texture_name = std::string(PTH_GAME_WIND) + (i < 100? (i<10? "00":"0") : "") + std::to_string(i) + PTH_GAME_PATH_END;
        image_buffer.loadFromFile(texture_name);
        wind[i].loadFromImage(image_buffer);
        wind[i].setSmooth(1);
    }

    wind_s.setTexture(wind[0]);
    scaleFactorX = (double) resoX / world_s.getTextureRect().width;
    scaleFactorY = (double) resoY / world_s.getTextureRect().height;

    world_s.setScale(scaleFactorX, scaleFactorY);
    wind_s.setScale((double) resoX / wind_s.getTextureRect().width, (double) resoY / wind_s.getTextureRect().height);

    loadComplete = 1;
}

void Game::activeMap(int scrollStatus, Event event) {
    if (scrollStatus == 1) {
        if (viewScale < 4) {
            viewScale++;
            world_map_view.zoom(0.8f);
            moveMap(Vector2f(0,0));
        }
    } else if (scrollStatus == -1) {
        if (viewScale > 0) {
            viewScale--;
            world_map_view.zoom(1.25f);
            if (viewScale == 0)world_map_view.setCenter(960, 540);
            else moveMap(Vector2f(0,0));
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left) && !moveMode && viewScale != 0) {
        moveMode = 1;
        mouseBuffer = Mouse::getPosition();
        mouseBufferStatic = mouseBuffer;

    }
    else if (moveMode && Mouse::isButtonPressed(Mouse::Left)) {
            Vector2f offset = Vector2f((mouseBuffer.x - Mouse::getPosition().x),
                                       (mouseBuffer.y - Mouse::getPosition().y));
            moveMap(offset);
            mouseBuffer = Mouse::getPosition();
    }
    else moveMode = false;

    if(event.type == Event::MouseButtonReleased)
        if(event.mouseButton.button == Mouse::Left && mouseBufferStatic==mouseBuffer){
            mapClicked = 1;
        }

}

void Game::activeGUI(int scrollStatus) {
    return;
}
