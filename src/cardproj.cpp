#include "../inc/cardproj.h"

CPWindow::CPWindow(int iWindowWidth = 620, int iWindowHeight = 480) {
    sdlWindow = nullptr;
    sdlRenderer = nullptr;

    this->iWindowWidth = iWindowWidth;
    this->iWindowHeight = iWindowHeight;
}

CPWindow::~CPWindow() {

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

    if ((sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWindowWidth, iWindowHeight, SDL_WINDOW_OPENGL)) == NULL) {
        return false;
    }

    if ((sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0)) == NULL) {
        return false;
    }

    if (SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255) != 0) {
        return false;
    }
    
    bRunning = true;

    fmt::print("[INFO] Successful SDL Initialization\n");
    return true;
}

void CPWindow::OnEvent(SDL_Event * event) {  

    //fmt::print("SDL_Event seen!\n");
    switch(event->type) {
        case SDL_QUIT:
            bRunning = false;
        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                bRunning = false;
                break;
            
            default:
                //keyboard sym default
                break;
            }
        break;
        default:
            //event->type default
        break;
    }
}

void CPWindow::OnLoop() {
    //SDL_Delay(9000);
}

void CPWindow::OnRender() {
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
}

void CPWindow::OnCleanup() {
    fmt::print("[INFO] Starting SDL cleanup\n");
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}