#include "sdlhandler.hpp"

int main(int argc, char** argv) {
    GameOfLife game;
    SDL_GameOfLifeHandler handler(game);
    handler.GameLoop();
}