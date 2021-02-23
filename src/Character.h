#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <memory>
#include <set>
#include <vector>
#include <SDL2/SDL.h>

#include "SpriteAnimation.h"
#include "Utils.h"
#include "Graphics.h"

using std::string;
using namespace PacmanUtils;

class Character {
    public:
        Character(string path,std::shared_ptr<Graphics> graphics);
        Character(std::ifstream &file,std::shared_ptr<Graphics> graphics);
        virtual inline void setState(State newState) { currentFrame = 0; currentAnimation = newState;}
        inline const State getState() {return currentAnimation;}
        void draw(std::shared_ptr<Graphics> graphics);
        virtual void update(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) = 0;
        virtual void update(std::set<int> input,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) = 0;
        SDL_Rect getFrame();        
    protected:
        void init(std::ifstream &file,std::shared_ptr<Graphics> graphics);
        void addAnimation(std::ifstream &file,State animationCode);
        int x{250};
        int y{250};        
        int speedx{0};
        int speedy{0};
        SpriteAnimation animations;
        State currentAnimation{State::EAST};
        int currentFrame{0};        
};

#endif