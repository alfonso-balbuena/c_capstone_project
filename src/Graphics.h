#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <iostream>
#include <exception>
#include <string>

class Graphics {

    public: 
        Graphics(int x, int y,std::string title);
        ~Graphics();
        SDL_Texture *load_image(std::string &path);
        void draw(SDL_Texture *src,SDL_Rect &clip, SDL_Rect &dest);
        void drawRect(SDL_Rect &clip,int r,int g, int b);
        void update();
        void clear();
    private:
        std::string title;
        std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> renderer;
        std::unique_ptr<SDL_Window,decltype(&SDL_DestroyWindow)> windows;        
};

#endif