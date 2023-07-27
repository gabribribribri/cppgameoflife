#pragma once
#include "grid.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include "parameters.hpp"


class SDL_GameOfLifeHandler {

private:

    SDL_Window*   m_Window;
    SDL_Renderer* m_Renderer;
    GameOfLife&   m_Game;

    void ScreenGrid() {
        for (int y = 0; y < HEIGHT_Y; y++) {
            for (int x = 0; x < WIDTH_X; x++) {
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
        SDL_SetRenderDrawColor(m_Renderer, PIXEL_RED_VALUE, PIXEL_GREEN_VALUE, PIXEL_BLUE_VALUE, 255);
        ScreenGrid();
        SDL_RenderPresent(m_Renderer);
    }

    void GameIteration() {
        GameRender();
        m_Game.GameIteration();
    }

public:

    void GameLoop() {
        SDL_Event events;
        bool      running           = true;
        bool      isPaused          = false;
        uint      framesSinceUpdate = 0;
        uint      updateRate        = UPDATE_RATE;


        while (running) {
            while (SDL_PollEvent(&events)) {
                switch (events.type) {
                    case SDL_QUIT:
                        running = false;
                        break;

                    case SDL_KEYDOWN:
                        if (events.key.keysym.sym == SDLK_SPACE)
                            isPaused = !isPaused;
                        if (events.key.keysym.sym == SDLK_c)
                            updateRate -= 5;
                        if (events.key.keysym.sym == SDLK_v)
                            updateRate += 5;
                        break;
                    
                    case SDL_MOUSEBUTTONDOWN:
                        if(events.button.button == SDL_BUTTON_LEFT) {
                            bool& cell = m_Game[events.motion.y/15][events.motion.x/15];
                            cell = !cell;
                        }
                        break;
                }
            }

            if (framesSinceUpdate >= updateRate) {
                if (!isPaused) m_Game.GameIteration();
                framesSinceUpdate = 0;
            }

            GameRender();
            framesSinceUpdate++;
            SDL_Delay(static_cast<uint>(1.0/FRAME_RATE*1000+0.5));
        }
    }

    SDL_GameOfLifeHandler(GameOfLife& gameArg) //No I won't do error management
        : m_Game(gameArg) 
    {
        SDL_Init(SDL_INIT_VIDEO);
        
        m_Window = SDL_CreateWindow(
            "Game Of Life", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            WIDTH_X * PIXEL_SIZE, 
            HEIGHT_Y * PIXEL_SIZE, 
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