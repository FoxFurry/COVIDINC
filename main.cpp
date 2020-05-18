
#include <thread>
#include <fstream>

#include "Menu.hpp"
#include "Game.hpp"
#include "ErrorFox.h"
#include "SEIRD.h"

#define MOUSE_ROTATION_SPEED 0.1

int main(int argc, char **argv) {


//    std::ofstream mycsv("example.csv");
//    mycsv << "date;confirmed;recovered;dead\n";
//    countryPeople start(144500000, 144500000 - 1641 - 3248 - 64, 1641, 3248, 64,8);
//
//    for(int i = 0; i < 105; i++){
//        countryPeople dx = SEIRDDX(start, BETA, PSI, KAPPA, GAMMA, MU, PhiPolynomial);
//        mycsv << std::to_string(i) << ";" << std::to_string(start.infected + start.exposed) << ";" << std::to_string(start.recovered) << ";" << std::to_string(start.dead) << "\n";
//        start += dx;
//    }

    ContextSettings windowSettings;
    windowSettings.antialiasingLevel = 4;
    RenderWindow mainWindow(VideoMode::getDesktopMode(), "PlagueInc by UTM", Style::Titlebar | Style::Close | Style::Resize | Style::Fullscreen, windowSettings);
    mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setFramerateLimit(60);
    mainWindow.setMouseCursorVisible(false);
    int n = 10000;

    Image mouse_i;
    mouse_i.loadFromFile("source/sprites/mouse_icon.png");
    Texture mouse_t;
    mouse_t.loadFromImage(mouse_i);
    Sprite mouse_s;
    mouse_s.setTexture(mouse_t);
    mouse_s.setOrigin(mouse_s.getGlobalBounds().width/2, mouse_s.getGlobalBounds().height/2);

    Clock animationDelayClock, nonStopClock;

    Menu mainMenu(mainWindow);
    std::thread menuLoad(&Menu::loadResources, &mainMenu);
    menuLoad.join();

    Game mainGame(mainWindow);
    std::thread gameLoad(&Game::loadResources, &mainGame);
    gameLoad.detach();

    ErrorFox mainErrorHunter;

    std::string buffer;

    bool mouseVisible = true;
    int menuStatus = 0;

    while (mainWindow.isOpen()) {
        if(!mainWindow.hasFocus())continue;
        Event event{};
        while (mainWindow.pollEvent(event)) {
            if (event.type == Event::Closed)
                mainWindow.close();
            if(event.type == Event::KeyPressed){
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                    std::exit(0);
            }
        }

        //Estimated time to draw a frame
        double timePerFrame = animationDelayClock.getElapsedTime().asMicroseconds();
        timePerFrame /= 800;

        //Elapsed time since launch
        double timeElapsed = nonStopClock.getElapsedTime().asMicroseconds();

        mouse_s.setPosition(Vector2f(Mouse::getPosition(mainWindow)));
        mouse_s.rotate(-MOUSE_ROTATION_SPEED*timePerFrame);

        animationDelayClock.restart();
        mainWindow.clear(Color::Black);

        if (menuStatus!=2) {
            menuStatus = mainMenu.Update(mainWindow, timePerFrame, timeElapsed);
            if (menuStatus == 1)mouseVisible = 1;
        }
        else{
            if(mainGame.getLoadStatus())mainGame.update(mainWindow, timePerFrame, timeElapsed, event);
        }
        if(mouseVisible)mainWindow.draw(mouse_s);
        mainWindow.display();
    }
    return 0;
}
