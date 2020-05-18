//
// Created by fox on 3/22/20.
//

#ifndef PLAGUEINC_ERRORFOX_H
#define PLAGUEINC_ERRORFOX_H

#include <SFML/Graphics.hpp>
#include <string>

#define ERROR_COUNT 3

using namespace sf;

class ErrorFox {
private:
    Text errorMessage;
    Font errorFont;

    std::string errors_list[ERROR_COUNT];
public:
    ErrorFox();

    void errorFoxReport(int errorID);
    void errorFoxReport(int errorID, std::string errorDetails);
};
#endif //PLAGUEINC_ERRORFOX_H
