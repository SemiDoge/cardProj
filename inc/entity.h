#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <fmt/format.h>

#include "../inc/logging.h"

class Entity {
private:
    int iEntityScale = 1;
    bool bIsClickable = false;
    SDL_Rect sdlDestRect;
    SDL_Texture * sdlTexture = nullptr;

public:
    Entity(SDL_Texture * sdlTexture, int w, int h, int xPos, int yPos, int iScale);
    ~Entity();

public:
    bool GetIsClickable();
    SDL_Rect * GetDestRect();
    SDL_Texture * GetTexture();

    void SetDestRect(SDL_Rect destRect);
};

#endif