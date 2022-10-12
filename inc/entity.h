#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <fmt/format.h>

#include "../inc/logging.h"

class Entity {
private:
    int iEntityScale = 1;
    bool bEntityIsClickable = false;
    std::string strEntityLabel = "";
    SDL_Rect sdlSrcRect;
    SDL_Rect sdlDestRect;
    SDL_Texture * sdlTexture = nullptr;

public:
    Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, int w, int h, int xPos, int yPos, int iScale, bool bIsClickable);
    ~Entity();

public:
    bool GetIsClickable();
    bool WasClicked(SDL_Point pointClicked);
    std::string GetEntityLabel();
    SDL_Rect * GetSrcRect();
    SDL_Rect * GetDestRect();
    SDL_Texture * GetTexture();


    void SetDestRect(SDL_Rect destRect);
};

#endif