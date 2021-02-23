#include "Game.h"

Game::Game(std::string file) : map(nullptr), graphics(nullptr), hero(nullptr) {
    std::ifstream gameFile(file);
    std::string line;
    std::string type;
    std::string separator;
    std::string fileInit;
    while(std::getline(gameFile,line)) {
        std::istringstream stringStream(line);
        stringStream >> type >> separator >> fileInit;        
        if(type.compare(HERO) == 0) {
            initHero(fileInit);
        } else if(type.compare(MAP) == 0) {            
            map.reset(new Maze(fileInit,graphics));
        }else if(type.compare(ENEMY) == 0) {
            initEnemy(fileInit);
        } else if(type.compare(SIZE) == 0) {            
            graphics.reset(new Graphics(std::stoi(fileInit),std::stoi(separator),"Pacman"));
        }

    }
}

void Game::initHero(string path) {
    string line;
    std::ifstream file(path);
    std::getline(file,line);
    hero.reset(new Pacman(file,graphics));
}

void Game::initEnemy(string path) {
    string line;    
    std::ifstream file(path);
    std::getline(file,line);
    auto data = readLine(line);
    MazeCharacter *enemy = getEnemy(std::get<2>(data),file,graphics);
    if(enemy != nullptr) {
        enemies.emplace_back(enemy);
    }    
}

MazeCharacter * Game::getEnemy(string type,std::ifstream &file,std::shared_ptr<Graphics> graphics) {
    MazeCharacter * enemy = nullptr;
    if(type.compare(BLINKY) == 0) {        
        enemy = dynamic_cast<MazeCharacter *>(new Blinky(file,graphics));
    }
    return enemy;
}

void Game::run() {
    bool pause = false;
    while(!finish) {                
        auto input = eventInput();        
        auto it = input.find(SDLK_q);
        if(it != input.end()) {            
            std::cout << "Exit... "  << std::endl;
            break;
        }        
        it = input.find(SDLK_p);
        if(it != input.end()) {            
            pause = !pause;
        }        
        if(!pause) {
            if(map->hasElements()) {
            draw();
            update(input);  
            collision();
            } else {
                std::cout << "Finish..." << std::endl;
            }    
            SDL_Delay(50);
        } else {
            SDL_Delay(20);
        }
        
    }
    
}

void Game::collision(){
    auto heroFrame = hero->getFrame();
    auto mazeCoordinates = hero->getMazeCoordinates();
    auto element = map->getElement(std::get<1>(mazeCoordinates),std::get<0>(mazeCoordinates));
    if(std::get<0>(element) != TypeItem::SPACE && PacmanUtils::collision(heroFrame,std::get<1>(element))) {
        if(std::get<0>(element) == TypeItem::SPECIAL) {
            for(auto enemy : enemies) {
                enemy->setState(State::VULNERABLE);
            }
        }
        map->clearElement(std::get<1>(mazeCoordinates),std::get<0>(mazeCoordinates));
    }
    for(auto enemy : enemies) {
        if(PacmanUtils::collision(heroFrame,enemy->getFrame())) {
            if(enemy->getState() != State::VULNERABLE) {
                finish = true;
                break;
            } else {                
                enemy->restart();
            }
        }
        
    }
}

std::set<int> Game::eventInput() {
    std::set<int> input;
    SDL_Event event;    
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                case SDLK_RIGHT:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_q:   
                case SDLK_p:                 
                    input.insert(event.key.keysym.sym);
                    break;
            }
            
        }
    }    
    return input;
}

void Game::update(std::set<int> input) {    
    auto coordinates = hero->getMazeCoordinates();
    hero->update(input,map->getNeighborhood(std::get<1>(coordinates),std::get<0>(coordinates)),map->getHeight(),map->getWidth());
    for(int i = 0; i < enemies.size(); i++) {
        auto enemyCoordinates = enemies[i]->getMazeCoordinates();        
        enemies[i]->update(hero->getMazeCoordinates(),map->getNeighborhood(std::get<1>(enemyCoordinates),std::get<0>(enemyCoordinates)),map->getHeight(),map->getWidth());
    }    
}

void Game::draw() {
    graphics->clear();
    map->draw(graphics);    
    hero->draw(graphics);
    for(int i = 0; i < enemies.size(); i++) {
        enemies[i]->draw(graphics);
    }    
    graphics->update();
}