#include "Character.h"

Character::Character(string path,std::shared_ptr<Graphics> graphics) {
    std::ifstream file(path);
    init(file,graphics);
}


Character::Character(std::ifstream &file,std::shared_ptr<Graphics> graphics) {
    init(file,graphics);
}

void Character::init(std::ifstream &file,std::shared_ptr<Graphics> graphics) {
    string line;    
    while(std::getline(file,line)) {     
        auto data = PacmanUtils::readLine(line);
        string key = std::get<0>(data);        
        if(key.compare(SPRITESHEET) == 0) {            
            animations.setImage(graphics->load_image(std::get<2>(data)));
        } else if(key.compare(SPEEDX) == 0) {
            speedx = std::stof(std::get<2>(data));
        } else if(key.compare(SPEEDY) == 0) {
            speedy = std::stof(std::get<2>(data));
        } else if (key.compare(ANIMATION) == 0) {
            addAnimation(file,stringToState(std::get<2>(data)));
        }
    }
}

void Character::draw(std::shared_ptr<Graphics> graphics) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.h = FRAMEH;
    dest.w = FRAMEW;    
    SDL_Rect clip = animations.getFrame(static_cast<int>(currentAnimation),currentFrame);
    graphics->draw(animations.getImage(),clip,dest);    
    currentFrame = (currentFrame + 1 < animations.size(static_cast<int>(currentAnimation))) ? currentFrame + 1 : 0;
}

SDL_Rect Character::getFrame() {
    SDL_Rect frame;
    frame.x = x;
    frame.y = y;
    auto f = animations.getFrame(static_cast<int>(currentAnimation),currentFrame);
    frame.h = f.h;
    frame.w = f.w;
    return frame;
}

void Character::addAnimation(std::ifstream &file,State animationCode) {
    string line;    
    animations.addAnimation(static_cast<int>(animationCode));
    std::getline(file,line);
    auto frames = PacmanUtils::readLine(line);
    int nFrames = std::stoi(std::get<2>(frames));    
    for(int i = 0; i < nFrames; i++) {
        SDL_Rect clip;
        std::getline(file,line);
        std::istringstream stringStream(line);    
        stringStream >> clip.y >> clip.x >> clip.h >> clip.w;
        animations.addFrameToAnimation(static_cast<int>(animationCode),clip);
    }
}