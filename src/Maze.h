#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <map>
#include <tuple>

#include "Utils.h"
#include "Graphics.h"
#include "SpriteAnimation.h"

using std::vector;
using std::string;
using namespace PacmanUtils;

class Maze {
    public:
        Maze(string &file,std::shared_ptr<Graphics> graphics);
        void draw(std::shared_ptr<Graphics> graphics);
         /***
         * Return y,x in the next order N,E,S,W
        */
        vector<std::tuple<int,int,TypeItem> > getNeighborhood(int x,int y);
        int getValueElement(TypeItem type);
        std::tuple<TypeItem,SDL_Rect> getElement(int x,int y);
        void clearElement(int x,int y);
        inline bool hasElements() { return numberElements > 0;}
        inline const unsigned int getWidth() {return size_x;}
        inline const unsigned int getHeight() {return size_y;}
    private:
        int numberElements{0};
        void initElement(std::tuple<TypeItem,int,SDL_Rect> values);
        void initMazeData(std::ifstream &file, int x, int y);
        SDL_Rect getPosition(TypeItem type,int x, int y,int w,int h);
        vector< vector< std::tuple<TypeItem,SDL_Rect> > > data;
        std::map<int,int> valueElements;
        SpriteAnimation animations;
        unsigned int size_x;
        unsigned int size_y;
};

#endif