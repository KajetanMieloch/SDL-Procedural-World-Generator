#include "equipment.hpp"

Equipment::Equipment(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

Equipment::~Equipment() {
    // Clean up code...
}

void Equipment::init() {

    //Textures
    redBrickTex = LoadTexture("res/textures/red_brick.png");
    blueBrickTex = LoadTexture("res/textures/blue_brick.png");
    transparentTex = LoadTexture("res/textures/transparent.png");
    bombTex = LoadTexture("res/textures/bomb.png");
    wallTex = LoadTexture("res/textures/wall.png");
    cornerTex = LoadTexture("res/textures/corner.png");
}

SDL_Texture* Equipment::LoadTexture(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        // Handle the error appropriately
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        // Handle the error appropriately
    }

    return texture;
}

int Equipment::processClick(int mouseX, int mouseY){
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int cellWidth = 50;
    int cellHeight = 50;
    int gridWidth = 10;
    int gridHeight = 10;
    int startX = (windowWidth - gridWidth * cellWidth) / 2;
    int startY = (windowHeight - gridHeight * cellHeight) / 2;

    int clickedI = (mouseY - startY) / cellHeight;
    int clickedJ = (mouseX - startX) / cellWidth;

    // Return the texture ID based on the clicked cell
    if (clickedI == 0 && clickedJ == 0) {
        return 1;
    }
    else if (clickedI == 0 && clickedJ == 1) {
        return 2;
    }
    else if (clickedI == 0 && clickedJ == 2) {
        return 101;
    }
    else if (clickedI == 0 && clickedJ == 3) {
        return 102;
    }
    else if (clickedI == 0 && clickedJ == 4) {
        return 103;
    }
    else {
        return 0;
    }
}

void Equipment::generateEquipment() {
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int equipmentWidth = 600;
    int equipmentHeight = 600;
    int equipmentX = (windowWidth - equipmentWidth) / 2;
    int equipmentY = (windowHeight - equipmentHeight) / 2;
    SDL_Rect equipmentRect;
    equipmentRect.x = equipmentX;
    equipmentRect.y = equipmentY;
    equipmentRect.w = equipmentWidth;
    equipmentRect.h = equipmentHeight;
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &equipmentRect);

    // Generate the grid for the equipment
    int cellWidth = 50;
    int cellHeight = 50;
    int gridWidth = 10;
    int gridHeight = 10;
    int startX = (windowWidth - gridWidth * cellWidth) / 2;
    int startY = (windowHeight - gridHeight * cellHeight) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            SDL_Rect cellRect;
            cellRect.x = startX + j * cellWidth;
            cellRect.y = startY + i * cellHeight;
            cellRect.w = cellWidth;
            cellRect.h = cellHeight;
            SDL_RenderDrawRect(renderer, &cellRect);

            //For each cell, draw the appropriate texture
            if (i == 0 && j == 0) {
                SDL_RenderCopy(renderer, redBrickTex, NULL, &cellRect);
            }
            else if (i == 0 && j == 1) {
                SDL_RenderCopy(renderer, blueBrickTex, NULL, &cellRect);
            }
            else if (i == 0 && j == 2) {
                SDL_RenderCopy(renderer, bombTex, NULL, &cellRect);
            }
            else if (i == 0 && j == 3) {
                SDL_RenderCopy(renderer, wallTex, NULL, &cellRect);
            }
            else if (i == 0 && j == 4) {
                SDL_RenderCopy(renderer, cornerTex, NULL, &cellRect);
            }
        }
    }
}

void Equipment::toggleEquipment() {
    equipmentOpen = !equipmentOpen;
}

bool Equipment::isEquipmentOpen() {
    return equipmentOpen;
}