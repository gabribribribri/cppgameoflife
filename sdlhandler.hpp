#pragma once
#include "grid.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class SDLGameOfLifeHandler {

private:
    SDL_Window*   m_Window;
    SDL_Renderer* m_Renderer;
    GameOfLife&   m_Game;

    

public:
    static const int PIXEL_SIZE = 15;

    SDLGameOfLifeHandler(GameOfLife& gameArg) //No I won't do error management
        : m_Game(gameArg) 
    {
        SDL_Init(SDL_INIT_VIDEO);
        
        m_Window = SDL_CreateWindow(
            "Game Of Life", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED,
            GameOfLife::WIDTH_X * PIXEL_SIZE, 
            GameOfLife::HEIGHT_Y * PIXEL_SIZE, 
            SDL_WINDOW_SHOWN
        );

        m_Renderer = SDL_CreateRenderer(
            m_Window, 
            -1, 
            SDL_RENDERER_ACCELERATED
        );
    }

    ~SDLGameOfLifeHandler() {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
};