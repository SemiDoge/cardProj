#ifndef CARDPROJ_H
#define CARDPROJ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../inc/logging.h"

class CPWindow {
private:
    bool bRunning;
    int iWindowWidth = 0;
    int iWindowHeight = 0;

    SDL_Window * sdlWindow;
    SDL_Renderer * sdlRenderer;

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