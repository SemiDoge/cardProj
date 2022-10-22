#include <utility>

#include "../inc/entity.hpp"

Entity::Entity(std::string strEntityLabel, SDL_Texture * sdlTexture, SDL_Rect * atlasLocRect, SDL_Rect loc, int iScale, bool isClickable, bool isDragable) {
    iEntityScale = iScale;
    bEntityIsClickable = isClickable;
    bEntityIsDragable = isDragable;

    sdlDestRect.w = loc.w * iEntityScale;
    sdlDestRect.h = loc.h * iEntityScale;
    sdlDestRect.x = loc.x;
    sdlDestRect.y = loc.y;

    sdlSrcRect.w = loc.w;
    sdlSrcRect.h = loc.h;
    sdlSrcRect.x = atlasLocRect->x; 
    sdlSrcRect.y = atlasLocRect->y;

    this->sdlTexture = sdlTexture;
    this->strEntityLabel = std::move(strEntityLabel);

    Logger::log(fmt::format("Creating Entity '{}' @ ({}, {}), scale: {}", this->strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

Entity::~Entity() {
    Logger::log(fmt::format("Destroying Entity '{}' @ ({}, {}), scale: {}", strEntityLabel, sdlDestRect.x, sdlDestRect.y, iEntityScale), logSeverity::INFO);
}

bool Entity::GetIsClickable() const {
    return bEntityIsClickable;
}


bool Entity::GetIsDragable() const {
    return bEntityIsDragable;
}

bool Entity::WasClicked(SDL_Point pointClicked) {
    //TODO: Investigate, the clickable area seems to be larger than it should be.
    if(SDL_PointInRect(&pointClicked, &sdlDestRect) == SDL_TRUE) {
        Logger::log(fmt::format("Entity '{}' clicked @ ({},{})", strEntityLabel, pointClicked.x, pointClicked.y), logSeverity::INFO);
        return true;
    }

    return false;
}

[[maybe_unused]] std::string Entity::GetEntityLabel() {
    return strEntityLabel;
}

SDL_Rect * Entity::GetDestRect() {
    return &sdlDestRect;
}

SDL_Rect * Entity::GetSrcRect() {
    return &sdlSrcRect;
}

SDL_Texture * Entity::GetTexture() const {
    return sdlTexture;
}

[[maybe_unused]] std::string Entity::DisplayString() {
    std::string retString;

    return fmt::format(
        "{} {{\n\t\tEntityScale: {}\n\t\tIsClickable: {}\n\t\tIsDragable: {}\n\t\tsdlDestRect {{\n\t\t\tx: {}, y: {}\n\t\t\tw: {}, h: {}\n\t\t}}", strEntityLabel, 
                iEntityScale, bEntityIsClickable, bEntityIsDragable,
                sdlDestRect.x, sdlDestRect.y, sdlDestRect.w, sdlDestRect.h
    );
}

void Entity::SetDestRect(SDL_Rect destRect) {
    sdlDestRect.w = destRect.w;
    sdlDestRect.h = destRect.h;
    sdlDestRect.x = destRect.x;
    sdlDestRect.y = destRect.y;
}

void Entity::SetDestRectXY(int x, int y)  {
    sdlDestRect.x = x;
    sdlDestRect.y = y;
}