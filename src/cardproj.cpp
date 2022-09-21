#include "../inc/cardproj.h"

CPWindow::CPWindow(int iWindowWidth = 620, int iWindowHeight = 480) {
    sdlWindow = nullptr;
    bRunning = true;

    this->iWindowWidth = iWindowWidth;
    this->iWindowHeight = iWindowHeight;
}

int CPWindow::OnExecute() {
    if(OnInit() == false) {
        return EXIT_FAILURE;
    }

    SDL_Event Event;

    while(bRunning) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

bool CPWindow::OnInit() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    if ((sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWindowHeight, iWindowWidth, SDL_WINDOW_OPENGL)) == NULL) {
        return false;
    }


    return true;
}

void CPWindow::OnEvent(SDL_Event * event) {
    if(event->type == SDL_QUIT) {
        bRunning = false;
    }
}

void CPWindow::OnLoop() {
    SDL_Delay(9000);
}

void CPWindow::OnRender() {

}

void CPWindow::OnCleanup() {
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}