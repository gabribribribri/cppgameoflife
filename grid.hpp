#pragma once
#include <array>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std::chrono_literals;


class GameOfLife {

public:
    //some boring constant shit
    static constexpr size_t HEIGHT_Y                      = 30;
    static constexpr size_t WIDTH_X                       = 100;
    static constexpr int    POURCENT                      = 30;
    static constexpr int INTERVALLE                       = 100;
    using GridType = std::array<std::array<bool, WIDTH_X>, HEIGHT_Y>;

    GameOfLife() {
        m_CurrentGrid = new GridType;
        m_NextGrid    = new GridType;
        
        srand(time(nullptr));
        for (size_t y = 0; y < HEIGHT_Y; y++)
            for (size_t x = 0; x < WIDTH_X; x++) 
                (*m_CurrentGrid)[y][x] = ((rand()%100) < POURCENT);
        
    }

    ~GameOfLife() {
        delete m_CurrentGrid;
        delete m_NextGrid;
    }

    void GameIteration() {
        Next();
        SwitchGridsPtr();
    }

    void GameIterationAndPrint() {
        PrintGrid();
        Next();
        SwitchGridsPtr();
    }

    void GameLoop() {
        for(;;) {
            GameIterationAndPrint();
            std::this_thread::sleep_for(std::chrono::milliseconds(INTERVALLE));
        }        
    }

    std::array<bool, WIDTH_X>& operator[](size_t index) {
        if (index > WIDTH_X or index < 0)
            throw std::length_error("index > WIDTH_X");
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

    void PrintGrid() {
        system("clear");
        for (auto& line : *m_CurrentGrid) {
            for(bool cell : line)
                std::cout << (cell ? "#" : " ");
            std::cout << "\n";
        }
    }

    void PrintVoisins() {
        system("clear");
        for (size_t y = 0; y < HEIGHT_Y; y++) {
            for (size_t x = 0; x < WIDTH_X; x++)
                std::cout << (int)CountVoisins(x, y);
            std::cout << "\n";
        }
    }
};