//
// Created by fox on 3/22/20.
//

#include "ErrorFox.h"


ErrorFox::ErrorFox(){
    errors_list[0] = "UNABLE TO LOAD FILE:";
    errors_list[1] = "UNABLE TO START DATAFRAME:";
    errors_list[2] = "UNABLE TO CREATE GRAPHICAL OBJECT:";
    errorMessage.setFont(errorFont);

}

void ErrorFox::errorFoxReport(int errorID) {
    errorMessage.setCharacterSize(30);
    errorMessage.setString("ERROR: " + (errorID<ERROR_COUNT ? errors_list[errorID]:("You freak, there is no error #" + std::to_string(errorID))));
    errorMessage.setOrigin(errorMessage.getGlobalBounds().width/2, errorMessage.getGlobalBounds().height/2);
}

void ErrorFox::errorFoxReport(int errorID, std::string errorDetails) {
    RenderWindow errorWindow(VideoMode(450, 100), "ERROR");

    errorWindow.setActive(1);
    errorWindow.setVisible(1);

    errorFont.loadFromFile("source/fonts/consola.ttf");
    errorMessage.setFont(errorFont);
    errorMessage.setCharacterSize(20);
    errorMessage.setString("ERROR: " + (errorID<ERROR_COUNT ? errors_list[errorID]:("You freak, there is no error #" + std::to_string(errorID))) + " " + errorDetails);
    errorMessage.setOrigin(errorMessage.getGlobalBounds().width/2, errorMessage.getGlobalBounds().height/2);
    errorMessage.setPosition(errorWindow.getSize().x/2, errorWindow.getSize().y/2);
    errorMessage.setFillColor(Color::Black);
    while(errorWindow.isOpen()) {
        Event event;

        while(errorWindow.pollEvent(event))
            if (event.type == Event::Closed||event.type == Event::KeyPressed||event.type == Event::MouseButtonPressed)
                errorWindow.close();

        errorWindow.clear(Color(230,230,230));
        errorWindow.draw(errorMessage);
        errorWindow.display();
    }
}

