#include "../inc/entity.h"

Entity::Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, int w, int h, int xPos, int yPos, int iScale, bool bIsClickable) {
    iEntityScale = iScale;
    bEntityIsClickable = bIsClickable;

    sdlDestRect.w = w * iEntityScale;
    sdlDestRect.h = h * iEntityScale;
    sdlDestRect.x = xPos;
    sdlDestRect.y = yPos;

    this->sdlTexture = sdlTexture;
    this->strEntityLabel = strEntityLabel;
    log(fmt::format("Creating Entity '{}' @ ({}, {}), scale: {}", this->strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

Entity::~Entity() {
   SDL_DestroyTexture(sdlTexture);
   log(fmt::format("Destroying texture and Entity '{}' @ ({}, {}), scale: {}", strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

bool Entity::GetIsClickable() {
    return bEntityIsClickable;
}

bool Entity::WasClicked(SDL_Point pointClicked) {
    if(SDL_PointInRect(&pointClicked, &sdlDestRect) == SDL_TRUE) {
        log(fmt::format("Entity '{}' clicked @ ({},{})", strEntityLabel, pointClicked.x, pointClicked.y), logSeverity::INFO);
        return true;
    }

    return false;
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