#include "Graphics.h"

Graphics::Graphics(int x, int y,std::string title) : windows(nullptr,SDL_DestroyWindow), 
                                                        renderer(nullptr,SDL_DestroyRenderer) {
    std::cout << "Init graphics... " << std::endl;
    int imgFlags = IMG_INIT_PNG;
    this->title = title;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error(SDL_GetError());        
    }
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        throw std::runtime_error(IMG_GetError());                
    }    
    windows.reset(SDL_CreateWindow( this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN ));
    renderer.reset(SDL_CreateRenderer(windows.get(),-1,SDL_RENDERER_ACCELERATED));
    SDL_RenderSetLogicalSize(renderer.get(),x,y);
    SDL_SetRenderDrawBlendMode(renderer.get(),SDL_BLENDMODE_NONE);    
    clear();
    update();    
}

SDL_Texture * Graphics::load_image(std::string &path) {    
    SDL_Texture * optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cerr << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;        
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_CreateTextureFromSurface(renderer.get(),loadedSurface);
        if( optimizedSurface == NULL )
        {
            std::cerr << "Unable to optimize image " << path << " SDL Error: " << SDL_GetError() << std::endl;            
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }    
    return optimizedSurface;
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer.get(),0,0,0,255);
    SDL_RenderClear(renderer.get());    
}

void Graphics::drawRect(SDL_Rect &clip,int r,int g, int b) {
    SDL_SetRenderDrawColor(renderer.get(),r,g,b,255);
    SDL_RenderFillRect(renderer.get(),&clip);    
}

void Graphics::draw(SDL_Texture * src,SDL_Rect &clip, SDL_Rect &dest) {
    SDL_RenderCopy(renderer.get(),src,&clip,&dest);    
}

void Graphics::update() {
    SDL_RenderPresent(renderer.get());
}

Graphics::~Graphics() {    
    SDL_Quit();
}

