#include "Utils.h"

using namespace PacmanUtils;


TypeItem PacmanUtils::stringToTypeItem(string type) {
    if(type.compare(SPECIAL) == 0) {
        return TypeItem::SPECIAL;        
    } else if(type.compare(FOOD) == 0) {
        return TypeItem::FOOD;        
    } else if(type.compare(CHERRY) == 0) {
        return TypeItem::CHERRY;
    } else if(type.compare(STRAWBERRY) == 0) {
        return TypeItem::STRAWBERRY;    
    } else if(type.compare(PEACH)  == 0) {
        return TypeItem::PEACH;
    } else if(type.compare(APPLE) == 0) {
        return TypeItem::APPLE;        
    }
    return TypeItem::ERROR;
}

const string PacmanUtils::typeItemToString(TypeItem type) {
    switch (type)
    {
    case TypeItem::SPECIAL:
        return SPECIAL;
    case TypeItem::FOOD:
        return FOOD;
    case TypeItem::CHERRY:
        return CHERRY;
    case TypeItem::STRAWBERRY:
        return STRAWBERRY;
    case TypeItem::PEACH:
        return PEACH;
    case TypeItem::APPLE:
        return APPLE;
    case TypeItem::BLOCK:
        return BLOCK;
    case TypeItem::SPACE:
        return SPACE;
    default:
        return "";
    }
}

State PacmanUtils::sdlToState(int input) {    
    switch (input)
    {
        case SDLK_UP:
            return State::NORTH;
        case SDLK_RIGHT:
            return State::EAST;
        case SDLK_DOWN:
            return State::SOUTH;
        case SDLK_LEFT:    
            return State::WEST;
        default:
            return State::ERROR;
    }
}

std::tuple<string,string,string> PacmanUtils::readLine(string line) {    
    string title;
    string separator;
    string value;    
    std::istringstream stringStream(line);
    stringStream >> title >> separator  >> value;
    return std::make_tuple(title,separator,value);
}

State PacmanUtils::stringToState(string type) {
    if(type.compare(NORTH) == 0) {
        return State::NORTH;        
    } else if(type.compare(SOUTH) == 0) {
        return State::SOUTH;
    } else if(type.compare(EAST) == 0) {
        return State::EAST;
    } else if(type.compare(WEST) == 0) {
        return State::WEST;    
    } else if(type.compare(DEAD) == 0) {
        return State::DEAD;
    } else if(type.compare(VULNERABLE) == 0) {
        return State::VULNERABLE;
    }
    return State::ERROR;
}

const string PacmanUtils::stateToString(State state) {
    switch (state)
    {
    case State::NORTH:
        return NORTH;
    case State::SOUTH:
        return SOUTH;
    case State::EAST:
        return EAST;
    case State::WEST:
        return WEST;
    case State::DEAD:
        return DEAD;
    case State::VULNERABLE:
        return VULNERABLE;
    default:
        return "";
    }
}

std::tuple<TypeItem,int,SDL_Rect> PacmanUtils::readMapElement(std::ifstream &file) {
    SDL_Rect frame;
    TypeItem type;
    string line;
    string title;
    std::getline(file,line);
    auto values = PacmanUtils::readLine(line);
    type = stringToTypeItem(std::get<2>(values));
    std::getline(file,line);
    values = PacmanUtils::readLine(line);
    int val = std::stoi(std::get<2>(values));        
    std::getline(file,line);
    std::istringstream stringStream(line);    
    stringStream >> title >> frame.y >> frame.x >> frame.h >> frame.w;
    return std::make_tuple(type,val,frame);    
}

bool PacmanUtils::collision(SDL_Rect src1,SDL_Rect src2) {
    if (src1.x < src2.x + src2.w && src1.x + src1.w > src2.x &&
        src1.y < src2.y + src2.h && src1.h + src1.y > src2.y) 
        return true;
    return false;
}