#include "sdlhandler.hpp"

int main() {
    GameOfLife game;
    SDL_GameOfLifeHandler handler(game);
    handler.PrimitiveGameLoop();
}