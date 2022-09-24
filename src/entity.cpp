#include "../inc/entity.h"

Entity::Entity(SDL_Texture * sdlTexture, int w, int h, int xPos, int yPos, int iScale) {
    iEntityScale = iScale;

    sdlDestRect.w = w * iEntityScale;
    sdlDestRect.h = h * iEntityScale;
    sdlDestRect.x = xPos;
    sdlDestRect.y = yPos;

    this->sdlTexture = sdlTexture;

    log(fmt::format("Creating entity at x: {}, y: {}, scale: {}", sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

Entity::~Entity() {
   SDL_DestroyTexture(sdlTexture);
   log(fmt::format("Destroying texture and Entity at x: {}, y: {}, scale: {}", sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

bool Entity::GetIsClickable() {
    return bIsClickable;
}

SDL_Rect * Entity::GetDestRect() {
    return &sdlDestRect;
}

SDL_Texture * Entity::GetTexture() {
    return sdlTexture;
}

void Entity::SetDestRect(SDL_Rect destRect) {
    sdlDestRect.w = destRect.w;
    sdlDestRect.h = destRect.h;
    sdlDestRect.x = destRect.x;
    sdlDestRect.y = destRect.y;
}