//
// Created by fox on 2/24/20.
//

#include "SIR_model.h"


void sir( const state_type &x , state_type &dxdt , double t ){
    dxdt[0] = -b * x[0] * x[1];
    dxdt[1] = b * x[0] * x[1] - a * x[1];
    dxdt[2] = a * x[1];
}

void write_sir(const state_type &x , const double t ){
    printf("%f\t%.10lf\t%.10lf\t%.10lf\t", t, x[0], x[1], x[2]);
}


//GH_Menu::GH_Menu(RenderWindow &targetWindow) {
//    for (int i = 0; i < CNT_FRAMES; i++) {
//        if (!title_i.loadFromFile(
//                "source/sprites/title_glitch/frame_" + (i < 10 ? std::string("0") : "") + std::to_string(i) +
//                "_delay-0.05s.gif"))
//            throw ("source/sprites/title_glitch/frame_" + (i > 10 ? std::string("0") : "") + std::to_string(i) +
//                   "_delay-0.05s.gif");
//        title_t[i].loadFromImage(title_i);
//
//
//        if (!logo_i.loadFromFile(
//                "source/sprites/logo_glitch/frame_" + (i < 10 ? std::string("0") : "") + std::to_string(i) +
//                "_delay-0.05s.gif"))
//            throw ("source/sprites/logo_glitch/frame_" + (i > 10 ? std::string("0") : "") + std::to_string(i) +
//                   "_delay-0.05s.gif");
//        logo_t[i].loadFromImage(logo_i);
//
//
//        if (!biohazard_i.loadFromFile(
//                "source/sprites/biohazard_glitch/frame_" + (i < 10 ? std::string("0") : "") + std::to_string(i) +
//                "_delay-0.05s.gif"))
//            throw ("source/sprites/biohazard_glitch/frame_" + (i > 10 ? std::string("0") : "") + std::to_string(i) +
//                   "_delay-0.05s.gif");
//        biohazard_t[i].loadFromImage(biohazard_i);
//        biohazard_t[i].setSmooth(1);
//    }