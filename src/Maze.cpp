#include "Maze.h"

Maze::Maze(std::string &file,std::shared_ptr<Graphics> graphics) {        
    std::ifstream mapFile(file);
    string line;
    string type;
    string separator;
    string value;    
    
    while(std::getline(mapFile,line)) {        
        std::istringstream stringStream(line);
        stringStream >> type >> separator >> value;           
        if(type.compare(SPRITESHEET) == 0) {            
            animations.setImage(graphics->load_image(value));
        } else if(type.compare(ELEMENTS) == 0) {
            int it = std::stoi(value);
            for(int i = 0; i < it; i++) {            
                initElement(PacmanUtils::readMapElement(mapFile));                
            }
        }else if(type.compare(SIZEX) == 0) {            
            size_x = std::stoi(value);            
        } else if(type.compare(SIZEY) == 0) {            
            size_y = std::stoi(value);            
        }
        else if(type.compare(DATA) == 0) {            
            initMazeData(mapFile,size_x,size_y);
        }

    }    
}

void Maze::initMazeData(std::ifstream &file, int x, int y) {
    string line;
    int type;
    for(int i = 0; i < y; i++) {
        std::getline(file,line);
        std::istringstream stringStream(line);
        vector< std::tuple<TypeItem,SDL_Rect>> row;
        for(int j = 0; j < x; j++) {            
            stringStream >> type;
            TypeItem item = static_cast<TypeItem>(type);
            //std::cout << typeItemToString(item) << std::endl;
            //SDL_Rect aux = animations.getFrame(type,0);
            if(item == TypeItem::BLOCK || item == TypeItem::SPACE) {
                row.emplace_back(item, getPosition(item,j,i,FRAMEW,FRAMEH));
            } else {
                numberElements++;
                SDL_Rect aux = animations.getFrame(type,0);
                row.emplace_back(item, getPosition(item,j,i,aux.w,aux.h));
            }
                
        }
        data.push_back(row);
    }    
}

SDL_Rect Maze::getPosition(TypeItem type,int x, int y,int w,int h) {
    SDL_Rect pos;
    pos.h = h;
    pos.w = w;
    pos.x = x * FRAMEW;
    pos.y = y * FRAMEH;
    if(type == TypeItem::FOOD) {
        pos.x += 7;
        pos.y += 7;
    }
    return pos;
}


void Maze::initElement(std::tuple<TypeItem,int,SDL_Rect> values) {
    int intType = static_cast<int>(std::get<0>(values));    
    valueElements.insert(std::pair<int,int>(intType,std::get<1>(values)));    
    animations.addAnimation(intType);
    animations.addFrameToAnimation(intType,std::get<2>(values));
}

vector<std::tuple<int,int,TypeItem> > Maze::getNeighborhood(int x,int y) {    
    vector<int> offsetX = {0,1,0,-1};
    vector<int> offsetY = {-1,0,1,0};
    vector<std::tuple<int,int,TypeItem> > neighborhood;
    for(int i = 0; i < offsetX.size(); i++) {
        int neighborX = (x + offsetX[i] < 0) ? (data[y].size() - 1) : 
                        ((x + offsetX[i] >= data[y].size()) ? 0 : x + offsetX[i]);

        int neighborY = (y + offsetY[i] < 0) ? (data.size() - 1) : 
                        ((y + offsetY[i] >= data.size()) ? 0 : y + offsetY[i]);
        neighborhood.push_back(std::make_tuple(neighborY,neighborX,std::get<0>(data[neighborY][neighborX])));
    }
    return neighborhood;
}

void Maze::draw(std::shared_ptr<Graphics> graphics) {
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size(); j++) {
            TypeItem item = std::get<0>(data[i][j]);
            SDL_Rect pos = std::get<1>(data[i][j]);            

            if(item == TypeItem::BLOCK) {
                graphics->drawRect(pos,37,36,64);
            } else if(item == TypeItem::SPACE) {
                graphics->drawRect(pos,0,0,0);
            } else {                 
                SDL_Rect aux = animations.getFrame(static_cast<int>(item),0);                
                graphics->draw(animations.getImage(),aux,pos);
            }
        }
    }
}

int Maze::getValueElement(TypeItem type) {
    return valueElements[static_cast<int>(type)];
}

std::tuple<TypeItem,SDL_Rect> Maze::getElement(int x,int y) {
    return data[y][x];
}

void Maze::clearElement(int x,int y) {
    numberElements--;
    SDL_Rect rect;
    data[y][x] = std::make_tuple(TypeItem::SPACE,rect);
}