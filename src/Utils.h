#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <tuple>
#include <sstream>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include "Graphics.h"

using std::string;

namespace PacmanUtils {
    const int FRAMEW = 24;
    const int FRAMEH = 24;

    const string SPRITESHEET = "Spritesheet";
    const string ELEMENTS = "Elements";
    const string TYPE = "Type";
    const string VALUE = "Value";
    const string SIZE = "Size";
    const string SIZEX = "Sizex";
    const string SIZEY = "Sizey";
    const string DATA = "Data";
    const string HERO = "Hero";
    const string MAP = "Map";
    const string ENEMY = "Enemy";        
    
    const string SPECIAL = "Special";
    const string FOOD = "Food";
    const string CHERRY = "Cheery";
    const string STRAWBERRY = "Strawberry";
    const string PEACH = "Peach";
    const string APPLE = "Apple";
    const string BLOCK = "Block";
    const string SPACE = "Space";
    const string NORTH = "North";
    const string SOUTH = "South";
    const string EAST = "East";
    const string WEST = "West";
    const string DEAD = "Dead";
    const string VULNERABLE = "Vulnerable";
    const string SPEEDX = "SpeedX";
    const string SPEEDY = "SpeedY";
    const string ANIMATION = "Animation";
    const string FRAMES = "Frames";    
    const string BLINKY = "Blinky";
    const string CLYDE = "Clyde";
    const string INKY = "Inky";
    const string PINKY = "Pinky";

    enum class TypeItem : int { BLOCK, FOOD, SPECIAL, CHERRY, STRAWBERRY, PEACH, APPLE, SPACE = 8, ERROR = -1 };
    enum class State : int {NORTH, SOUTH,EAST,WEST,DEAD,VULNERABLE,ERROR = -1};

    TypeItem stringToTypeItem(string type);
    const string typeItemToString(TypeItem type);
    State stringToState(string type);
    const string stateToString(State state);
    State sdlToState(int input);

    std::tuple<string,string,string> readLine(string line);
    std::tuple<TypeItem,int,SDL_Rect> readMapElement(std::ifstream &file);
    bool collision(SDL_Rect src1,SDL_Rect src2);    
}

#endif