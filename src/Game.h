#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <set>
#include <SDL2/SDL.h>

#include "Maze.h"
#include "Graphics.h"
#include "Utils.h"
#include "MazeCharacter.h"
#include "Pacman.h"
#include "Blinky.h"

using namespace PacmanUtils;

class Game {
    public:
        Game(std::string file);
        void run();
    private:
        void collision();
        void update(std::set<int> input);
        void draw();
        void initEnemy(string path);
        void initHero(string path);
        MazeCharacter * getEnemy(string type,std::ifstream &file,std::shared_ptr<Graphics> graphics);        
        std::set<int> eventInput();
        std::unique_ptr<Maze> map;        
        std::shared_ptr<Graphics> graphics;
        std::unique_ptr<Pacman> hero;
        std::vector<std::shared_ptr<MazeCharacter>> enemies;
        bool finish{false};
};

#endif