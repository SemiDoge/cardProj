#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <fmt/format.h>

#include "../inc/logging.hpp"

class Entity {
private:
    int iEntityScale = 1;
    Uint8 zidx = 0;
    bool bEntityIsClickable = false;
    bool bEntityIsDraggable = false;
    std::string strEntityLabel;
    SDL_Rect sdlSrcRect{};
    SDL_Rect sdlDestRect{};
    SDL_Texture * sdlTexture = nullptr;

public:
    Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, SDL_Rect loc, int iScale, bool bIsClickable, bool isDraggable, Uint8 zidx);
    ~Entity();

public:
    [[nodiscard]] bool GetIsClickable() const;
    [[nodiscard]] bool GetIsDraggable() const;
    bool WasClicked(SDL_Point pointClicked);

    Uint8 GetZIndex() const;

    [[maybe_unused]] std::string GetEntityLabel();
    SDL_Rect * GetSrcRect();
    SDL_Rect * GetDestRect();
    [[nodiscard]] SDL_Texture * GetTexture() const;

    [[maybe_unused]] std::string DisplayString();

    void SetDestRect(SDL_Rect destRect);
    void SetDestRectXY(int x, int y);
    void SetZIndex(Uint8 z);
};

#endif