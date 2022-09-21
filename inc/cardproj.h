#ifndef CARDPROJ_H
#define CARDPROJ_H

#include <SDL2/SDL.h>

class CPWindow {
    private:
        bool bRunning;
        SDL_Window * sdlWindow;
        int iWindowWidth = 0; // 620x480 shall be the default will get overridden
        int iWindowHeight = 0;

    public:
        CPWindow(int iWindowWidth, int iWindowHeight);
        int OnExecute();

    public:
        bool OnInit();
        void OnEvent(SDL_Event * event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

#endif