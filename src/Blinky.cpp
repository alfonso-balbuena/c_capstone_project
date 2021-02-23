#include "Blinky.h"

Blinky::Blinky(std::string path,std::shared_ptr<Graphics> graphics) : MazeCharacter(path,graphics) {
    
}

Blinky::Blinky(std::ifstream &file,std::shared_ptr<Graphics> graphics) : MazeCharacter(file,graphics) {
    
}

std::vector<int> Blinky::filter(std::vector<std::tuple<int,int,TypeItem> > neighborhood,std::vector<State> possibleDirection) {
    std::vector<int> index;
    for(int i = 0; i < neighborhood.size(); i++) {
        if(isValid(possibleDirection[i]) && std::get<2>(neighborhood[i]) != TypeItem::BLOCK
            && !(std::get<0>(neighborhood[i]) == 9 && std::get<1>(neighborhood[i]) ==10)) {            
            index.push_back(i);
        }
    }
    return index;
}

void Blinky::searchTarget(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood) {    
    std::vector<State> possibleDirection = {State::NORTH,State::EAST,State::SOUTH,State::WEST};
    std::vector<int> index = filter(neighborhood,possibleDirection);    
    std::vector<int> differences;       
    differences.resize(index.size());
    std::transform(index.begin(),index.end(),differences.begin(),[&neighborhood,&target](int i){
        int newDistanceX = std::abs(std::get<1>(neighborhood[i]) - std::get<1>(target));
        int newDistanceY = std::abs(std::get<0>(neighborhood[i]) - std::get<0>(target));
        return newDistanceX + newDistanceY;
    });    
    auto min = std::min_element(differences.begin(),differences.end());    
    int i = index[min - differences.begin()];    
    direction = possibleDirection[i];
    if(currentAnimation != State::VULNERABLE) {
        setState(possibleDirection[i]);
    }    
}
