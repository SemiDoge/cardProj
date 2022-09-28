#include "../inc/textureManager.h"

SDL_Texture * TextureManager::LoadTexture(const char * strFileName, SDL_Renderer * sdlRenderer) {

    SDL_Surface * tmpSurface = nullptr;
    SDL_Texture * texture = nullptr;


    if ((tmpSurface = IMG_Load(strFileName)) == NULL) {
        Logger::log(fmt::format("Failed to create surface, reason: {}", IMG_GetError()), logSeverity::ERROR);
        return NULL;
    }

    if((texture = SDL_CreateTextureFromSurface(sdlRenderer, tmpSurface)) == NULL) {
        Logger::log(fmt::format("Failed to create texture from: {}", strFileName), logSeverity::ERROR);
        SDL_FreeSurface(tmpSurface);

        return NULL;
    }

    SDL_FreeSurface(tmpSurface);

    return texture;
}