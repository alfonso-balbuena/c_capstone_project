#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>


class SpriteAnimation {

    public:
        SpriteAnimation();
        SpriteAnimation(const SpriteAnimation& other);
        SpriteAnimation(SpriteAnimation&& other);
        SpriteAnimation& operator=(const SpriteAnimation& other);
        SpriteAnimation& operator=(SpriteAnimation&& other);

        void setImage(SDL_Texture * image);
        void addAnimation(int animationCode);
        void addFrameToAnimation(int animationCode,SDL_Rect frame);
        SDL_Texture * getImage();
        SDL_Rect getFrame(int animationCode,int frame);
        size_t size(int animationCode);
    private:
        std::shared_ptr<SDL_Texture> _image;
        std::map<int, std::vector<SDL_Rect> > _animations;
};

#endif