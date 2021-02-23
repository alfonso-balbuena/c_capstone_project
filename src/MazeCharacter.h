#ifndef MAZE_CHARACTER_H
#define MAZE_CHARACTER_H

#include <string>
#include <memory>
#include <tuple>
#include <set>
#include <random>
#include <fstream>
#include <chrono>

#include "Character.h"
#include "Utils.h"

using namespace PacmanUtils;

class MazeCharacter : public Character {
    public:
        MazeCharacter(std::string path,std::shared_ptr<Graphics> graphics);
        MazeCharacter(std::ifstream &file,std::shared_ptr<Graphics> graphics);
        // Y,X
        inline std::tuple<int,int> getMazeCoordinates() { return std::make_tuple(mazeY,mazeX); }
        void update(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) override;
        void update(std::set<int> input,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) override;
        void setState(State newState) override;
        void restoreState();
        void restart();
    protected:
        int mazeX{10};
        int mazeY{10};        
        int steps{0};
        int stepsToExit{2};
        PacmanUtils::State direction;
        void init();
        bool isStart{true};
        bool isValid(State newDirection);
        inline bool finishStep() { return x % FRAMEW == 0 && y % FRAMEH == 0; }
        void move(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w);
        void cycle(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w);
        virtual void searchTarget(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood) = 0;                                                        
};

#endif