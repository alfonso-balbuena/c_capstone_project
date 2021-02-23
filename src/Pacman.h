#ifndef PACMAN_H
#define PACMAN_H

#include <string>
#include <memory>
#include <tuple>
#include <set>

#include "Character.h"
#include "Graphics.h"
#include "Utils.h"

class Pacman : public Character {    
    public:
        Pacman(string path,std::shared_ptr<Graphics> graphics);
        Pacman(std::ifstream &file,std::shared_ptr<Graphics> graphics);        
        void update(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) override;
        void update(std::set<int> input,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) override;
        /***
         * Return y,x
        */
        std::tuple<int,int> getMazeCoordinates();
    private:
        bool isMoving{true};        
        int mazeX;
        int mazeY;
        std::set<int> nextMoves;
        void reset(State newState);
        void cycle(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w);
        void init();
        bool finishStep();
        bool isValidInput(int input);
        void move(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w);
        State nextState(std::vector<std::tuple<int,int,TypeItem> > neighborhood,State newState);
        int getIndexMove(State state);
};

#endif