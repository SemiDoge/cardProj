#include "../inc/entity.h"

Entity::Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, SDL_Rect loc, int iScale, bool bIsClickable) {
    iEntityScale = iScale;
    bEntityIsClickable = bIsClickable;

    sdlDestRect.w = loc.w * iEntityScale;
    sdlDestRect.h = loc.h * iEntityScale;
    sdlDestRect.x = loc.x;
    sdlDestRect.y = loc.y;

    sdlSrcRect.w = loc.w;
    sdlSrcRect.h = loc.h;
    sdlSrcRect.x = atlasLocRect->x; 
    sdlSrcRect.y = atlasLocRect->y;

    this->sdlTexture = sdlTexture;
    this->strEntityLabel = strEntityLabel;

    Logger::log(fmt::format("Creating Entity '{}' @ ({}, {}), scale: {}", this->strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

Entity::~Entity() {
    Logger::log(fmt::format("Destroying Entity '{}' @ ({}, {}), scale: {}", strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

bool Entity::GetIsClickable() {
    return bEntityIsClickable;
}

bool Entity::WasClicked(SDL_Point pointClicked) {
    //TODO: Investigate, the clickable area seems to be larger than it should be.
    if(SDL_PointInRect(&pointClicked, &sdlDestRect) == SDL_TRUE) {
        Logger::log(fmt::format("Entity '{}' clicked @ ({},{})", strEntityLabel, pointClicked.x, pointClicked.y), logSeverity::INFO);
        return true;
    }

    return false;
}

std::string Entity::GetEntityLabel() {
    return strEntityLabel;
}

SDL_Rect * Entity::GetDestRect() {
    return &sdlDestRect;
}

SDL_Rect * Entity::GetSrcRect() {
    return &sdlSrcRect;
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