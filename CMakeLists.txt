cmake_minimum_required(VERSION 3.16)
project(plagueInc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(plagueInc main.cpp SIR_model.cpp SIR_model.h DataFrame.cpp DataFrame.h ErrorFox.cpp ErrorFox.h GraphicsDependicies.h Trigonometry.cpp Trigonometry.h Menu.hpp MenuInit.cpp ButtonInit.cpp Game.hpp MapInit.cpp GUI.cpp HUD.cpp Simulation.hpp SEIRD.h)
target_link_libraries(plagueInc sfml-graphics sfml-audio)
