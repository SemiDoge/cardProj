#ifndef CARDPROJ_H
#define CARDPROJ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../inc/textureManager.h"

class CPWindow {
private:
    bool bRunning;

    int iWindowWidth = 0;
    int iWindowHeight = 0;
    int iFrameTime = 0;
    const int iTargetFPS = 60;
    const int iFrameDelay = 1000 / iTargetFPS;
    
    Uint32 iFrameStart = 0;

    SDL_Window * sdlWindow;
    SDL_Renderer * sdlRenderer;

    std::vector<SDL_Texture *> textures;
    

public:
    Uint32 iFrame = 0;

public:
    CPWindow(int iWindowWidth, int iWindowHeight);
    ~CPWindow();
    int OnExecute();

public:
    bool OnInit();
    void OnEvent(SDL_Event * event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif