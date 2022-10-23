#include <fmt/format.h>
#include "../inc/cardproj.hpp"

#define FAIL fmt::print("FAIL");
#define SUCCESS fmt::print("SUCCESS");

struct SDL_Context {
    SDL_Window * sdlWindow = nullptr;
    SDL_Renderer * sdlRenderer = nullptr;
    int iWindowWidth = 0;
    int iWindowHeight = 0;
};

void testSDLInitVideo();
void testSDLInitImage();
void testSDLWindowSetupCreateWindow(SDL_Context * context);
void testSDLRendererSetup(SDL_Context * context);
void testSDLTextureAtlasLoad(SDL_Context * context);

int sdlTests(int argc, char * argv[]) {
    int defaultChoice = 1;
    int choice = defaultChoice;

    if (argc > 1) {
        if(sscanf(argv[1], "%d", &choice) != 1) {
            fmt::print("Couldn't parse input ( {} ) as number\n", argv[1]);
            return -1;
        }
    }

    SDL_Context context;
    context.iWindowWidth = 1240;
    context.iWindowHeight = 600;

    switch(choice) {
        case 1:
            testSDLInitVideo();
        break; 
        case 2:
            testSDLInitImage();
        break;
        case 3:
            testSDLWindowSetupCreateWindow(&context);
        break;
        case 4:
            testSDLRendererSetup(&context);
        break;
        case 5:
            //testSDLTextureAtlasLoad(&context);
        break;
        default:
        fmt::print("Test #{} does not exist in sdlTest.", choice);
        return -1;
    }

    return 0;
}

void testSDLInitVideo() {
    fmt::print("testSDLInitVideo\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        FAIL
    }
}

void testSDLInitImage() {
    fmt::print("testSDLInitImage\n");
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        FAIL
    }
}

void testSDLWindowSetupCreateWindow(SDL_Context * context) {
    fmt::print("testSDLCreateWindow\n");

    if ((context->sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      context->iWindowWidth, context->iWindowHeight, SDL_WINDOW_OPENGL)) == nullptr) {
        FAIL
    }
}

void testSDLRendererSetup(SDL_Context * context) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        FAIL
    }

    if ((context->sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      context->iWindowWidth, context->iWindowHeight, SDL_WINDOW_OPENGL)) == nullptr) {
        FAIL
    }

    if ((context->sdlRenderer = SDL_CreateRenderer(context->sdlWindow, -1, 0)) == nullptr) {
        FAIL
    }
}

void testSDLTextureAtlasLoad(SDL_Context * context) {
    SDL_Texture * cardAtlasTexture = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        FAIL
        fmt::print("@SDL_Init");
    }

    if ((context->sdlWindow = SDL_CreateWindow("TextureAtlasLoad", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      context->iWindowWidth, context->iWindowHeight, SDL_WINDOW_OPENGL)) == nullptr) {
        FAIL
        fmt::print("@SDL_CreateWindow");
    }

    if ((context->sdlRenderer = SDL_CreateRenderer(context->sdlWindow, -1, 0)) == nullptr) {
        FAIL
        fmt::print("@SDL_CreateRender");
    }

    //There is something fishy about this test. It fails when being run as part of the ctest suite but 
    //succeedes when run individually 
    if ((cardAtlasTexture = TextureManager::LoadTexture("res/cardsTextureAtlas.png", context->sdlRenderer)) == nullptr) {
        FAIL
        fmt::print("@pointerTest");
    } else {
        SUCCESS
    }
}

