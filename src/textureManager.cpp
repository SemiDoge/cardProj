#include "../inc/textureManager.hpp"

SDL_Texture * TextureManager::LoadTexture(const char * strFileName, SDL_Renderer * sdlRenderer) {

    SDL_Surface * tmpSurface;
    SDL_Texture * texture;

    if ((tmpSurface = IMG_Load(strFileName)) == nullptr) {
        Logger::log(fmt::format("Failed to create surface, reason: {}", IMG_GetError()), logSeverity::ERROR);
        return nullptr;
    }

    if((texture = SDL_CreateTextureFromSurface(sdlRenderer, tmpSurface)) == nullptr) {
        Logger::log(fmt::format("Failed to create texture from: {}", strFileName), logSeverity::ERROR);
        SDL_FreeSurface(tmpSurface);

        return nullptr;
    }

    SDL_FreeSurface(tmpSurface);
    return texture;
}