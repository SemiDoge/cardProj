#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../inc/logging.h"

class TextureManager {
public:
    static SDL_Texture * LoadTexture(const char * strFileName, SDL_Renderer * sdlRenderer);
};