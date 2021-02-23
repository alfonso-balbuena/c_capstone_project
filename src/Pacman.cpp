#include "Pacman.h"

Pacman::Pacman(string path,std::shared_ptr<Graphics> graphics) : Character(path,graphics) {
    init();
}

Pacman::Pacman(std::ifstream &file,std::shared_ptr<Graphics> graphics) : Character(file,graphics) {
    init();
}

void Pacman::init() {
    mazeX = 10;
    mazeY = 12;
    x = mazeX * FRAMEW;
    y = mazeY * FRAMEH;    
}

void Pacman::update(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w)  {

}

void Pacman::reset(State newState) {
    if(currentAnimation != newState) {        
        isMoving = true;
        currentFrame = 0;
    }
}

void Pacman::update(std::set<int> input,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w){    
    bool hasInput = false;    
    for(auto it : input) {
        nextMoves.insert(it);
    }    
    if(finishStep()) {        
        for(auto it : nextMoves) {
            if(isValidInput(it)) {                
                hasInput = true;
                PacmanUtils::State newState = nextState(neighborhood,PacmanUtils::sdlToState(it));                   
                reset(newState);                
                currentAnimation = newState;
                break;
            }
        }
        nextMoves.clear();
    }     
    if(!hasInput) {         
        int indexDirection = getIndexMove(currentAnimation);        
        isMoving = std::get<2>(neighborhood[indexDirection]) != TypeItem::BLOCK;        
    }    
    move(neighborhood,h,w);
}

bool Pacman::finishStep() {
    return x % FRAMEW == 0 && y % FRAMEH == 0;
}

void Pacman::move(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) {
     
    if(isMoving) {
        switch (currentAnimation)
        {
            case State::NORTH:
                y -= speedy;
                if(finishStep()) {
                    mazeY--;
                }
                break;
            case State::SOUTH:
                y += speedy;
                if(finishStep()) {
                    mazeY++;
                }
                break;
            case State::EAST:
                x += speedx;
                if(finishStep()) {
                    mazeX++;
                }
                break;
            case State::WEST:            
                x -= speedx;
                if(finishStep()) {
                    mazeX--;
                }
                break;
        }
        
    }
    cycle(neighborhood,h,w);
}

void Pacman::cycle(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) {    

    if(mazeY < 0) {
        mazeY = std::get<0>(neighborhood[0]);
        y = mazeY * FRAMEH;
    } else if(mazeX < 0) {
        mazeX = std::get<1>(neighborhood[3]);
        x = mazeX * FRAMEW;
    } else if(mazeX >= w) {
        mazeX = std::get<1>(neighborhood[1]);
        x = mazeX * FRAMEW;
    } else if(mazeY >= h) {
        mazeY = std::get<0>(neighborhood[2]);
        y = mazeY * FRAMEH;
    }
}

State Pacman::nextState(std::vector<std::tuple<int,int,TypeItem> > neighborhood,State newState) {
    int indexDirection = getIndexMove(newState);    
    if(currentAnimation != newState) {        
        if(std::get<2>(neighborhood[indexDirection]) == TypeItem::BLOCK) {
            newState = currentAnimation;            
        }
    }
    return newState;
}

int Pacman::getIndexMove(State state) {
    int index{0};
    switch (state)
    {
        case State::NORTH:
            index = 0;
            break;
        case State::EAST:
            index = 1;
            break;
        case State::SOUTH:
            index = 2;
            break;
        case State::WEST:
            index = 3;
            break;
    }
    return index;
}

bool Pacman::isValidInput(int input) {
    bool flag{true};
    State aux = sdlToState(input);
    if(aux == currentAnimation) {
        return false;
    }        
    return flag;
}

std::tuple<int,int> Pacman::getMazeCoordinates() {    
    return std::make_tuple(mazeY,mazeX);
}