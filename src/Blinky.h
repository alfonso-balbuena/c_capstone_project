#ifndef BLINKY_H
#define BLINKY_H

#include <string>
#include <memory>
#include <tuple>
#include <set>
#include <random>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "MazeCharacter.h"
#include "Graphics.h"
#include "Utils.h"

class Blinky : public MazeCharacter {
    public:
        Blinky(std::string path,std::shared_ptr<Graphics> graphics);
        Blinky(std::ifstream &file,std::shared_ptr<Graphics> graphics);        
    protected: 
        void searchTarget(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood) override;
        std::vector<int> filter(std::vector<std::tuple<int,int,TypeItem> > neighborhood,std::vector<State> possibleDirection);
};

#endif
