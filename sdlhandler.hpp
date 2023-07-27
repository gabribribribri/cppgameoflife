#pragma once
#include "grid.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>


class SDL_GameOfLifeHandler {

private:

    static const int PIXEL_SIZE = 15;
    static const uint FRAME_RATE = 120;
    static const uint UPDATE_RATE = FRAME_RATE*0.7;
    SDL_Window*   m_Window;
    SDL_Renderer* m_Renderer;
    GameOfLife&   m_Game;

    void ScreenGrid() {
        for (int y = 0; y < GameOfLife::HEIGHT_Y; y++) {
            for (int x = 0; x < GameOfLife::WIDTH_X; x++) {
                if (!m_Game[y][x]) continue;
                
                SDL_Rect pixel {
                    x*PIXEL_SIZE,
                    y*PIXEL_SIZE,
                    PIXEL_SIZE,
                    PIXEL_SIZE
                };
                SDL_RenderFillRect(m_Renderer, &pixel);
            }
        }
    }

    void GameRender() {
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_Renderer);
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 0, 255);
        ScreenGrid();
        SDL_RenderPresent(m_Renderer);
    }

    void GameIteration() {
        GameRender();
        m_Game.GameIteration();
    }

public:
    
    void EventHandlingGameLoop() {
        SDL_Event events;
        bool running = true;
        uint framesSinceUpdate = 0;
        while (running) {
            while (SDL_PollEvent(&events)) {
                switch (events.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            }
            if (framesSinceUpdate >= UPDATE_RATE) {
                m_Game.GameIteration();
                framesSinceUpdate = 0;
            }
            GameRender();
            framesSinceUpdate++;
            SDL_Delay(static_cast<uint>(1.0/FRAME_RATE*1000+0.5));
        }
    }

    void PrimitiveGameLoop() {
        for(;;) {
            GameIteration();
            SDL_Delay(GameOfLife::INTERVALLE);
        }
    }


    SDL_GameOfLifeHandler(GameOfLife& gameArg) //No I won't do error management
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

    ~SDL_GameOfLifeHandler() {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
};