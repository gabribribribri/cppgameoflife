#pragma once
#include <cstddef>
#include <cstdint>

//Le pourcentage de pixel au départ
constexpr uint8_t POURCENT_PIXEL_START = 30;

//Hauteur et Largeur en pixel de la grille
constexpr size_t WIDTH_X               = 50;
constexpr size_t HEIGHT_Y              = 30;

//La taille d'un pixel... en pixels...
constexpr uint8_t PIXEL_SIZE           = 15;

//La couleur du pixel
constexpr uint8_t PIXEL_RED_VALUE      = 255;
constexpr uint8_t PIXEL_GREEN_VALUE    = 255;
constexpr uint8_t PIXEL_BLUE_VALUE     = 0;

//Time things
constexpr uint8_t FRAME_RATE = 120; //Le nombre d'images affichées par seconde
constexpr uint8_t UPDATE_RATE = 100; //Le nombre d'image affiché qu'il doit s'écoulé avant la mise à jour de la grille.

