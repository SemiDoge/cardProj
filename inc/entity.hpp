#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <fmt/format.h>

#include "../inc/logging.hpp"

class Entity {
private:
    int iEntityScale = 1;
    bool bEntityIsClickable = false;
    bool bEntityIsDragable = false;
    std::string strEntityLabel;
    SDL_Rect sdlSrcRect{};
    SDL_Rect sdlDestRect{};
    SDL_Texture * sdlTexture = nullptr;

public:
    Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, SDL_Rect loc, int iScale, bool bIsClickable, bool isDragable);
    ~Entity();

public:
    [[nodiscard]] bool GetIsClickable() const;
    [[nodiscard]] bool GetIsDragable() const;
    bool WasClicked(SDL_Point pointClicked);

    [[maybe_unused]] std::string GetEntityLabel();
    SDL_Rect * GetSrcRect();
    SDL_Rect * GetDestRect();
    [[nodiscard]] SDL_Texture * GetTexture() const;

    [[maybe_unused]] std::string DisplayString();

    void SetDestRect(SDL_Rect destRect);
    void SetDestRectXY(int x, int y);
};

#endif