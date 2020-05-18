//
// Created by foxfurry on 5/2/20.
//

#include "Menu.hpp"

std::string startmenu[4] = {"New game", "Load game", "Settings", "Exit game"};
std::string settingsmenu[2] = {"Coming soon", "Main menu"};


std::vector<point> Menu::buttonToPointVec(int buttonID){
    if(buttonID >= numOfButtons)throw(0);
    std::vector<point> output;
    output.resize(4);
    for(int i = 0; i < 4; i++)
        output[i] = point(buttons_array[(buttonID * 4) + i].position.x, buttons_array[(buttonID * 4) + i].position.y);
    return output;
}

void Menu::buttonPolygonSynch(int buttonID) {
    if(buttonID >= numOfButtons)throw(0);
    buttons_poly[buttonID] = buttonToPointVec(buttonID);
}

void Menu::buttonPress(std::string command, RenderWindow &target) {
        if(command=="Exit game")std::exit(0);
        else if(command == "New game")gameStart = 1;
        else if(command == "Settings")buttonEngage(2, settingsmenu, target, 0);
        else if(command=="Main menu")buttonEngage(4, startmenu, target, 0);
    }

void Menu::buttonTextSynch(int buttonID) {
    if(buttonID>= numOfButtons)throw(0);
    buttons_data[buttonID].text_obj.setPosition(
            buttons_array[4 * buttonID + 3].position.x + abs((buttons_array[4 * buttonID + 2].position.x + buttons_array[4 * buttonID + 3].position.x) / 5.f),
            (buttons_array[4 * buttonID + 3].position.y + buttons_array[4 * buttonID].position.y) / 2);
}

void Menu::buttonInitialize(RenderWindow &target){
    buttonIdleColor_1 = Color(125, 154, 151, 30);
    buttonIdleColor_2 = Color(133, 154, 152, 60);
    buttonActiveColor_1 = Color(40, 53, 51, 200);
    buttonActiveColor_2 = Color(13, 34, 32, 200);
    if(!buttonsFont.loadFromFile("source/fonts/neuropol.ttf"))throw("neuropol.ttf");
    buttonEngage(4, startmenu, target, 0);
    pressedButton = -1;

}

void Menu::buttonEngage(int _numOfButtons, std::string _buttonText[], RenderWindow &target, bool startPos){
    numOfButtons = _numOfButtons;

    buttons_array.resize(4 * numOfButtons);
    buttons_array.setPrimitiveType(Quads);
    for (int i = 0; i < 4 * numOfButtons; i++)
        if(i%4==0 || (i-1)%4==0)buttons_array[i].color = buttonIdleColor_1;
        else buttons_array[i].color = buttonIdleColor_2;

    buttons_data.resize(numOfButtons);
    buttons_poly.resize(numOfButtons);

    for (int i = 0; i < numOfButtons; i++) {
        buttons_data[i].text_str = _buttonText[i];
        buttons_data[i].text_obj.setFont(buttonsFont);
        buttons_data[i].text_obj.setCharacterSize(50);
        buttons_data[i].text_obj.setString(buttons_data[i].text_str);
        buttons_data[i].text_obj.setFillColor(Color::White);

        if (i == 0) {
            if(startPos) {
                buttons_array[0].position = Vector2f(0, target.getSize().y
                                                        * PT_BUTTONS_INIT);
                buttons_array[1].position = Vector2f(SZ_BUTTONS_ALPHA, target.getSize().y
                                                                       * PT_BUTTONS_INIT);
                buttons_array[2].position = Vector2f(SZ_BUTTONS_BETA, target.getSize().y
                                                                      * PT_BUTTONS_INIT + SZ_BUTTONS_GAMMA);
                buttons_array[3].position = Vector2f(0, target.getSize().y
                                                        * PT_BUTTONS_INIT + SZ_BUTTONS_GAMMA);
            }
            else{
                buttons_array[0].position = Vector2f(-SZ_BUTTONS_BETA, target.getSize().y
                                                                       * PT_BUTTONS_INIT);
                buttons_array[1].position = Vector2f(SZ_BUTTONS_ALPHA - SZ_BUTTONS_BETA, target.getSize().y
                                                                                         * PT_BUTTONS_INIT);
                buttons_array[2].position = Vector2f(0, target.getSize().y
                                                        * PT_BUTTONS_INIT + SZ_BUTTONS_GAMMA);
                buttons_array[3].position = Vector2f(-SZ_BUTTONS_BETA, target.getSize().y
                                                                       * PT_BUTTONS_INIT + SZ_BUTTONS_GAMMA);
            }
        } else {
            buttons_array[4 * i + 0].position = Vector2f(buttons_array[4 * i - 4].position.x,
                                                         buttons_array[4 * i - 4].position.y + SZ_BUTTONS_OFFSET);
            buttons_array[4 * i + 1].position = Vector2f(buttons_array[4 * i - 3].position.x,
                                                         buttons_array[4 * i - 3].position.y + SZ_BUTTONS_OFFSET);
            buttons_array[4 * i + 2].position = Vector2f(buttons_array[4 * i - 2].position.x,
                                                         buttons_array[4 * i - 2].position.y + SZ_BUTTONS_OFFSET);
            buttons_array[4 * i + 3].position = Vector2f(buttons_array[4 * i - 1].position.x,
                                                         buttons_array[4 * i - 1].position.y + SZ_BUTTONS_OFFSET);
        }

        buttons_data[i].text_obj.setOrigin(0, buttons_data[i].text_obj.getGlobalBounds().height / 1.5f);
        buttons_poly[i] = buttonToPointVec(i);
        buttonTextSynch(i);
    }

    animationComplete = 0;
}

void Menu::appear(double timePerFrame) {
    for(int i = 0; i < numOfButtons; i++){
        if(i!=0 && buttons_array[4 * (i - 1) + 2].position.x < SZ_BUTTONS_BETA / 2)continue;
        if(buttons_array[4 * i + 2].position.x < SZ_BUTTONS_BETA) {
            for (int j = 0; j < 4; j++)
                buttons_array[4 * i + j].position.x += SP_BUTTON_TRANSLATION * timePerFrame;
            buttons_data[i].text_obj.move(SP_BUTTON_TRANSLATION * timePerFrame, 0);
        }if(buttons_array[4 * i + 2].position.x > SZ_BUTTONS_BETA){
            buttons_array[4 * i + 0].position.x = 0;
            buttons_array[4 * i + 1].position.x = SZ_BUTTONS_ALPHA;
            buttons_array[4 * i + 2].position.x=SZ_BUTTONS_BETA;
            buttons_array[4 * i + 3].position.x = 0;
            buttonTextSynch(i);
            buttonPolygonSynch(i);
            animationComplete = 1;
        }
    }

}

void Menu::disappear(double timePerFrame) {
    animationComplete = 0;
    for(int i = 0; i < numOfButtons; i++){
        if(i!=0 && buttons_array[4 * (i - 1) + 2].position.x > SZ_BUTTONS_BETA / 2)continue;
        if(buttons_array[4 * i + 2].position.x > 0) {
            for (int j = 0; j < 4; j++)
                buttons_array[4 * i + j].position.x -= SP_BUTTON_TRANSLATION * timePerFrame;
            buttons_data[i].text_obj.move(-SP_BUTTON_TRANSLATION * timePerFrame, 0);
        }if(buttons_array[4 * i + 2].position.x < 0){
            buttons_array[4 * i + 0].position.x = -SZ_BUTTONS_BETA;
            buttons_array[4 * i + 1].position.x = SZ_BUTTONS_ALPHA - SZ_BUTTONS_BETA;
            buttons_array[4 * i + 2].position.x=0;
            buttons_array[4 * i + 3].position.x = -SZ_BUTTONS_BETA;
            buttonTextSynch(i);
            buttonPolygonSynch(i);
        }
    }
}
