#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation() : _image(nullptr,SDL_DestroyTexture) {}

SpriteAnimation::SpriteAnimation(const SpriteAnimation& other) : _image(nullptr) {
    _animations = other._animations;
    _image = other._image;
}

SpriteAnimation::SpriteAnimation(SpriteAnimation&& other) : _image(nullptr) {
    _animations = other._animations;
    _image = other._image;
}

SpriteAnimation& SpriteAnimation::operator=(const SpriteAnimation& other) {
    _animations = other._animations;
    _image = other._image;
}

SpriteAnimation& SpriteAnimation::operator=(SpriteAnimation&& other) {
    _animations = other._animations;
    _image = other._image;
}

void SpriteAnimation::setImage(SDL_Texture * image) {
    
    _image.reset(image,SDL_DestroyTexture);
}
        
void SpriteAnimation::addAnimation(int animationCode) {    
    _animations.insert(std::pair<int,std::vector<SDL_Rect>>(animationCode,std::vector<SDL_Rect>()));
}
        
void SpriteAnimation::addFrameToAnimation(int animationCode,SDL_Rect frame) {    
    _animations[animationCode].push_back(frame);
}
        
SDL_Texture * SpriteAnimation::getImage() {
    return _image.get();    
}

SDL_Rect SpriteAnimation::getFrame(int animationCode,int frame) {
    return _animations[animationCode].at(frame);
}

size_t SpriteAnimation::size(int animationCode) {
    return _animations[animationCode].size();
}