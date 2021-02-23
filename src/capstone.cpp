#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL2/SDL_image.h>

#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void init_hero(std::string &file) {
    std::cout << "Init hero... " << file << std::endl;
}

void init_map(std::string &file) {
    std::cout << "Init map... " << file << std::endl;
}

void init_enemy(std::string &file) {
    std::cout << "Init enemy... " << file << std::endl;
}


int main() {    
    Game game("./assets/game.data");        
    game.run();
    return 0;
}