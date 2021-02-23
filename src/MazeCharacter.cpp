#include "MazeCharacter.h"

MazeCharacter::MazeCharacter(std::string path,std::shared_ptr<Graphics> graphics) : Character(path,graphics) {
    init();
}

MazeCharacter::MazeCharacter(std::ifstream &file,std::shared_ptr<Graphics> graphics) : Character(file,graphics) {
    init();
}

void MazeCharacter::setState(State newState) {
    if(newState != State::VULNERABLE)
        direction = newState;
    Character::setState(newState);
}


void MazeCharacter::restart() {
    mazeX = 10;
    mazeY = 10;
    currentAnimation = State::EAST;
    currentFrame = 0;
    steps = 0;
    isStart = true;
    init();    
}

void MazeCharacter::restoreState() {
    Character::setState(direction);
}

void MazeCharacter::init() {
    x = mazeX * FRAMEW;
    y = mazeY * FRAMEH;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1,10);
    stepsToExit = distribution(generator) * 2;    
    direction = currentAnimation;
}

void MazeCharacter::update(std::tuple<int,int> target,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w)  {
    if(finishStep()) {          
        if(isStart) {        
            if(steps >= stepsToExit && mazeY == 10 && mazeX == 10) {        
                setState(State::NORTH);                
                isStart = false;
            } else {        
                steps++;
                if(direction == State::EAST && std::get<2>(neighborhood[1]) == TypeItem::BLOCK) {
                    setState(State::WEST);                    
                } else if(direction == State::WEST && std::get<2>(neighborhood[3]) == TypeItem::BLOCK) {                    
                    setState(State::EAST);
                }
            }
        } else {            
            searchTarget(target,neighborhood);
        }
    }
    move(neighborhood,h,w);    
}

void MazeCharacter::move(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) {
    
        switch (direction)
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
        
    
    cycle(neighborhood,h,w);
}

void MazeCharacter::cycle(std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) {    

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


bool MazeCharacter::isValid(State newDirection) {    
    if(direction == State::NORTH && newDirection == State::SOUTH ||
        direction == State::SOUTH && newDirection == State::NORTH ||
        direction == State::WEST && newDirection == State::EAST ||
        direction == State::EAST && newDirection == State::WEST){
        return false;
        }        
    return true;
}

void MazeCharacter::update(std::set<int> input,std::vector<std::tuple<int,int,TypeItem> > neighborhood,int h,int w) {    
   
}