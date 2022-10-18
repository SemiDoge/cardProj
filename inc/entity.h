#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <fmt/format.h>

#include "../inc/logging.h"

class Entity {
private:
    int iEntityScale = 1;
    bool bEntityIsClickable = false;
    bool bEntityIsDragable = false;
    std::string strEntityLabel = "";
    SDL_Rect sdlSrcRect;
    SDL_Rect sdlDestRect;
    SDL_Texture * sdlTexture = nullptr;

public:
    Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, SDL_Rect loc, int iScale, bool bIsClickable, bool isDragable);
    ~Entity();

public:
    bool GetIsClickable();
    bool GetIsDragable();
    bool WasClicked(SDL_Point pointClicked);
    std::string GetEntityLabel();
    SDL_Rect * GetSrcRect();
    SDL_Rect * GetDestRect();
    SDL_Texture * GetTexture();
    std::string DisplayString();


    void SetDestRect(SDL_Rect destRect);
    void SetDestRectXY(int x, int y);
};

#endif