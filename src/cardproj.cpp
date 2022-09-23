#include "../inc/cardproj.h"

CPWindow::CPWindow(int iWindowWidth, int iWindowHeight) {
    sdlWindow = nullptr;
    sdlRenderer = nullptr;

    this->iWindowWidth = iWindowWidth;
    this->iWindowHeight = iWindowHeight;
}

CPWindow::~CPWindow() {
    for (auto itr : vecEntities) {
        delete itr;
    }
}

int CPWindow::OnExecute() {
    if(OnInit() == false) {
        return EXIT_FAILURE;
    }
    
    //TODO: Maybe temporary staging ground for entities?

    vecEntities.push_back(
        new Entity(TextureManager::LoadTexture("res/cardStack.png", sdlRenderer), 
            32, 32, 32 - 12, 32 + 42, 14)
    );

    vecEntities.push_back(
        new Entity(TextureManager::LoadTexture("res/cardFront.png", sdlRenderer),
            32, 32, 32 + (12 * 35), 32 + 42, 14)
    );
    
    vecEntities.push_back(
        new Entity(TextureManager::LoadTexture("res/cardFront.png", sdlRenderer),
            32, 32, 32 + (12 * 65), 32 + 42, 14)
    );

    SDL_Event Event;

    while(bRunning) {

        iFrameStart = SDL_GetTicks();

        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    
        iFrameTime = SDL_GetTicks() - iFrameStart;
    
        if (iFrameDelay > iFrameTime) {
            SDL_Delay(iFrameDelay - iFrameTime);
        }
    }

    OnCleanup();

    return 0;
}

bool CPWindow::OnInit() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
       return false; 
    }

    log("Successful SDL_Image Initialization!", logSeverity::INFO);

    if ((sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWindowWidth, iWindowHeight, SDL_WINDOW_OPENGL)) == NULL) {
        return false;
    }

    log(fmt::format("Created a {}x{} SDL_Window", iWindowWidth, iWindowHeight), logSeverity::INFO);

    if ((sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0)) == NULL) {
        return false;
    }

    if (SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255) != 0) {
        return false;
    }
    
    bRunning = true;

    log("Successful SDL Initialization!", logSeverity::INFO);
    return true;
}

void CPWindow::OnEvent(SDL_Event * event) {  

    //log("SDL_Event seen!", logSeverity::INFO);
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
    iFrame++;
}

void CPWindow::OnRender() {
    SDL_RenderClear(sdlRenderer); //clear the previous frame

    //prepare next frame
    for(auto itr : vecEntities) {
        SDL_RenderCopy(sdlRenderer, itr->GetTexture(), NULL, itr->GetDestRect());
    }

    //present new frame
    SDL_RenderPresent(sdlRenderer);
}

void CPWindow::OnCleanup() {
    log("Starting SDL cleanup...", logSeverity::INFO);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}