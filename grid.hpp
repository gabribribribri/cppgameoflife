#pragma once
#include <array>
#include <chrono>
#include <thread>
#include <iostream>
#include "parameters.hpp"
using namespace std::chrono_literals;


class GameOfLife {

public:
    using GridType = std::array<std::array<bool, WIDTH_X>, HEIGHT_Y>;

    GameOfLife() {
        m_CurrentGrid = new GridType;
        m_NextGrid    = new GridType;
        
        srand(time(nullptr));
        for (size_t y = 0; y < HEIGHT_Y; y++)
            for (size_t x = 0; x < WIDTH_X; x++) 
                (*m_CurrentGrid)[y][x] = ((rand()%100) < POURCENT_PIXEL_START);
        
    }

    ~GameOfLife() {
        delete m_CurrentGrid;
        delete m_NextGrid;
    }

    void GameIteration() {
        Next();
        SwitchGridsPtr();
    }

    std::array<bool, WIDTH_X>& operator[](size_t index) {
        if (index > HEIGHT_Y or index < 0)
            throw std::length_error("index > HEIGHT_Y");
        else
            return m_CurrentGrid->at(index);
    } 

private:
    GridType* m_CurrentGrid; //the actual grid
    GridType* m_NextGrid; //future grid

    void Next() {
        for(size_t y = 0; y < HEIGHT_Y; y++) {
            for(size_t x = 0; x < WIDTH_X; x++) {
                uint8_t voisins = CountVoisins(x, y);
                (*m_NextGrid)[y][x] = SurviveRules(voisins, (*m_CurrentGrid)[y][x]);
            }
        }
    }

    bool SurviveRules(uint8_t voisins, bool alive) {
        if (alive)
            return voisins >= 2 and voisins <= 3;
        else
            return voisins == 3;
    }

    uint8_t CountVoisins(size_t x, size_t y) {
        uint8_t voisins = 0;
        for (int8_t i = -1; i <= 1; i++) {
            for (int8_t j = -1; j <= 1; j++) {
                if (i == 0 and j == 0 ) continue;
                if (y+j < 0 or x+i < 0) continue;
                voisins += (*m_CurrentGrid)[y+j][x+i];
            }
        }
        return voisins;
    }

    void SwitchGridsPtr() { 
        GridType* temp = m_CurrentGrid;
        m_CurrentGrid = m_NextGrid;
        m_NextGrid = temp;
    }
};