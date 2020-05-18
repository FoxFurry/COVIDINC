//
// Created by foxfurry on 5/1/20.
//

#ifndef PLAGUEINC_MENU_HPP
#define PLAGUEINC_MENU_HPP

#include "GraphicsDependicies.h"




struct ButtonData{
    String text_str;
    Text text_obj;
};

class Menu {
private:
    Image image_buffer;
    Texture fox_texture, title_texture[80], biohard_texture[80], logo_texture[80];
    Sprite fox_sprite, title_sprite, biohard_sprite, logo_sprite;

    RectangleShape fader;

    VertexArray buttons_array;
    std::vector<ButtonData> buttons_data;
    std::vector<std::vector<point>> buttons_poly;
    Color buttonIdleColor_1, buttonIdleColor_2, buttonActiveColor_1, buttonActiveColor_2;

    Font buttonsFont;

    int fadeCoef, phase, numOfButtons, pressedButton, gameStart;
    double frameCounter, phase2StartTime, timeBuffer = 0;
    bool animationComplete;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PRIVATE FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Draw sprites
    void Draw(RenderWindow &target) {
        if (phase == 0) {
            target.draw(title_sprite);
            target.draw(fox_sprite);
        } else if (phase == 1) {
            target.draw(logo_sprite);
            target.draw(biohard_sprite);
            target.draw(buttons_array);
            for(int i = 0; i < numOfButtons; i++)
                target.draw(buttons_data[i].text_obj);
        }
        target.draw(fader);
    }

    // Convert button *buttonID* to vector of points
    std::vector<point> buttonToPointVec(int buttonID);

    // Create a button array with specified parameters
    void buttonEngage(int _numOfButtons, std::string _buttonText[], RenderWindow &target, bool startPos);

    // Animated appear
    void appear(double timePerFrame);

    // Animated disappear
    void disappear(double timePerFrame);

    // Synchronize button and text positions
    void buttonTextSynch(int buttonID);

    //
    void buttonPolygonSynch(int buttonID);

    // Initialize all variables related to menu
    void menuInitialize(RenderWindow &target);

    // Initialize all variables related to buttons
    void buttonInitialize(RenderWindow &target);

    //
    void buttonPress(std::string command, RenderWindow &target);

public:
    Menu(RenderWindow &target) {
        menuInitialize(target);
        buttonInitialize(target);
    }

    // Animation + event tracking
    int Update(RenderWindow &target, double timePerFrame, double timeElapsed) {
        // LOGO AND
        if (phase == 0) {
            if (tm_interval(timeElapsed, -1, TM_LOGO_FO) && fadeCoef != 255) {
                fadeCoef += timePerFrame * SP_FADE;
                if (fadeCoef > 255)fadeCoef = 255;
            }
            else if (tm_interval(timeElapsed, -1, TM_LOGO_GLITCH)) {
                int tempFrame = frameCounter;
                frameCounter+=timePerFrame*SP_TITLE_GLICTH;
                frameCounter >= CNT_FRAMES - 1 ? frameCounter = 0 : 0;
                if(tempFrame!=(int)frameCounter)title_sprite.setTexture(title_texture[int(frameCounter)]);

            }
            else if (tm_interval(timeElapsed, -1, TM_LOGO_FI) && fadeCoef != 0) {
                frameCounter = 0;
                title_sprite.setTexture(title_texture[int(frameCounter)]);
                fadeCoef -= timePerFrame * SP_FADE;
                if (fadeCoef < 0)fadeCoef = 0;
            }
            else {
                phase = 1;
                phase2StartTime = timeElapsed;
            }
        } else if (phase == 1 && !gameStart) {
            point mousePos = point(Mouse::getPosition(target).x, Mouse::getPosition(target).y);
            double timeElapsed_ph2 = timeElapsed - phase2StartTime;
            int activatedButton;

            int tempFrame = frameCounter;
            frameCounter+=timePerFrame*SP_LOGO_GLITCH;
            frameCounter >= CNT_FRAMES - 1 ? frameCounter = 0 : 0;
            if(tempFrame!=(int)frameCounter) {
                logo_sprite.setTexture(logo_texture[int(frameCounter)]);
                biohard_sprite.setTexture(biohard_texture[int(frameCounter)]);
            }
            if (tm_interval(timeElapsed_ph2, -1, TM_FADE_STOP) && fadeCoef != 255) {
                fadeCoef += timePerFrame * SP_FADE;
                if (fadeCoef > 255)fadeCoef = 255;
            }

            if(tm_interval(timeElapsed_ph2, 1, TM_BUTTON_FIRST_APPEAR))
                appear(timePerFrame);

//            if(Mouse::isButtonPressed(Mouse::Button::Left) && animationComplete) {
//                for(int i = 0; i < numOfButtons; i++)
//                    if(inPolygon(mousePos, buttons_poly[i])) {
//                        pressedButton = i;
//                        timeBuffer = timeElapsed_ph2;
//                        break;
//                    }
//            }
            for(int i = 0; i < numOfButtons; i++){
                if(inPolygon(mousePos, buttons_poly[i])) {
                    activatedButton = i;
                    buttons_array[i * 4].color = buttonActiveColor_1;
                    buttons_array[i * 4 + 1].color = buttonActiveColor_1;
                    buttons_array[i * 4 + 2].color = buttonActiveColor_2;
                    buttons_array[i * 4 + 3].color = buttonActiveColor_2;
                    break;
                }
                else {
                    activatedButton = -1;
                    buttons_array[i * 4].color = buttonIdleColor_1;
                    buttons_array[i * 4 + 1].color = buttonIdleColor_1;
                    buttons_array[i * 4 + 2].color = buttonIdleColor_2;
                    buttons_array[i * 4 + 3].color = buttonIdleColor_2;
                }
            }
            if(Mouse::isButtonPressed(Mouse::Button::Left) && animationComplete && activatedButton!=-1){
                pressedButton = activatedButton;
                timeBuffer = timeElapsed_ph2;
            }
            if(pressedButton!=-1){
                double tm_button = timeElapsed_ph2 - timeBuffer;
                if(tm_interval(tm_button, -1, TM_BUTTON_DISAPP))disappear(timePerFrame);
                else if(tm_interval(tm_button, -1, TM_BUTTON_INIT))buttonPress(buttons_data[pressedButton].text_str, target);
                else if(tm_interval(tm_button, -1,TM_BUTTON_APPEAR))appear(timePerFrame);
                else pressedButton=-1;
            }
        }
        else if(gameStart){
            fadeCoef -= timePerFrame * SP_FADE;
            if (fadeCoef < 0) { fadeCoef = 0; return phase + gameStart;}
        }
        fader.setFillColor(Color(0, 0, 0, 255 - fadeCoef));
        Draw(target);
        return phase;
    }
    void loadResources();
};




#endif //PLAGUEINC_MENU_HPP
