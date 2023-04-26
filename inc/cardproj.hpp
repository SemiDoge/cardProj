#ifndef CARDPROJ_H
#define CARDPROJ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <random>

#include "../inc/textureManager.hpp"
#include "../inc/entity.hpp"
#include "../inc/playingCard.hpp"

struct mouseMeta {
    bool lmbDown = false;
    bool rmbDown = false;
    SDL_Point pos{};
    SDL_Point clickOffset{};

    void ResetMouse() {
        lmbDown = false;
        rmbDown = false;
        clickOffset.x = 0;
        clickOffset.y = 0;
    }
};

class CPWindow {
private:
    bool bRunning{};

    int iWindowWidth = 0;
    int iWindowHeight = 0;
    unsigned int iFrameTime = 0;
    const int iTargetFPS = 60;
    const int iFrameDelay = 1000 / iTargetFPS;
    
    Uint32 iFrameStart = 0;

    SDL_Window * sdlWindow = nullptr;
    SDL_Renderer * sdlRenderer = nullptr;
    SDL_Texture * sdlTextureCardAtlas = nullptr;
    mouseMeta mouse;

    std::vector<std::shared_ptr<Entity>> vecEntities;
    std::shared_ptr<Entity> selectedEntity = nullptr;
    Uint8 selectedEntityOldZ{};
    SDL_Rect * priorDragPos = nullptr;
    

public:
    Uint32 iFrame = 0;

public:
    CPWindow(int iWindowWidth, int iWindowHeight);
    ~CPWindow() = default;
    int OnExecute();

public:
    bool OnInit();
    void OnEvent(SDL_Event * event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

public:
    void DrawRandomCards();
    static SDL_Rect GenerateSubTexture(faces face, suits suit);
};

#endif