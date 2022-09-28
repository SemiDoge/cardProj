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
    
    //Initial entities drawn to screen

    vecEntities.push_back(
        new Entity("entyCardStack", TextureManager::LoadTexture("res/cardStack.png", sdlRenderer), 
            32, 32, 32 - 12, 32 + 42, 14, true)
    );

    vecEntities.push_back(
        new Entity("entyFirstCard", TextureManager::LoadTexture("res/cardFront.png", sdlRenderer),
            32, 32, 32 + (12 * 35), 32 + 42, 14, false)
    );
    
    vecEntities.push_back(
        new Entity("entySecondCard", TextureManager::LoadTexture("res/cardFront.png", sdlRenderer),
            32, 32, 32 + (12 * 65), 32 + 42, 14, false)
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
        case SDL_MOUSEBUTTONDOWN:
            //log(fmt::format("Mouse event seen @ ({}, {})", sdlPointMouseClick.x, sdlPointMouseClick.y), logSeverity::DEBUG);
            for(auto itr : vecEntities) {
                if(itr->GetIsClickable() == true && itr->WasClicked(SDL_Point{event->button.x, event->button.y})) {
                    DrawRandomCards();
                    break;
                }
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

void CPWindow::DrawRandomCards() {
    size_t size = vecEntities.size();

    playingCard card1;
    playingCard card2;

    for (size_t i = 1; i < size; i++) {
        vecEntities.pop_back();
    }

    //set up randomiser
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> faceDist(1,13);
    std::uniform_int_distribution<> suitDist(1,4);

    card1.face = (faces) faceDist(gen);
    card1.suit = (suits) suitDist(gen);

    card2.face = (faces) faceDist(gen);
    card2.suit = (suits) suitDist(gen);

    card1.sdlTexture = TextureManager::LoadTexture(GenerateResourceLocation(card1).c_str(), sdlRenderer);
    card2.sdlTexture = TextureManager::LoadTexture(GenerateResourceLocation(card2).c_str(), sdlRenderer);

    vecEntities.push_back(
        new Entity(fmt::format("entyCard{}{}", (int)card1.face, (int)card1.suit), card1.sdlTexture,
            32, 32, 32 + (12 * 35), 32 + 42, 14, false)
    );
    
    vecEntities.push_back(
        new Entity(fmt::format("entyCard{}{}", (int)card2.face, (int)card2.suit), card2.sdlTexture,
            32, 32, 32 + (12 * 65), 32 + 42, 14, false)
    );
}

std::string CPWindow::GenerateResourceLocation(playingCard card) {
    std::string strSuit = "";
    std::string strFace = "";

    switch(card.suit) {
        case Club:
            strSuit.append("Club");
            break;
        case Diamond:
            strSuit.append("Diamond");
            break;
        case Heart:
            strSuit.append("Heart");
            break;
        case Spade:
            strSuit.append("Spade");
            break;
        default:
            strSuit.append("Err");
    }

    switch (card.face)
    {
        case Ace:
        strFace.append("Ace");
        break;

        case Two:
        strFace.append("2");
        break;

        case Three:
        strFace.append("3");
        break;

        case Four:
        strFace.append("4");
        break;

        case Five:
        strFace.append("5");
        break;

        case Six:
        strFace.append("6");
        break;

        case Seven:
        strFace.append("7");
        break;

        case Eight:
        strFace.append("8");
        break;

        case Nine:
        strFace.append("9");
        break;

        case Ten:
        strFace.append("10");
        break; 
        
        case Jack:
        strFace.append("Jack");
        break;

        case Queen:
        strFace.append("Queen");
        break;

        case King:
        strFace.append("King");
        break;

        default:
            strFace.append("Err");
    }

    //If for what ever reason there is an error, draw a Joker card
    if (strSuit == "Err" || strFace == "Err") {
        return std::string("res/cardBlackJoker.png");
    }

    std::string ret = fmt::format("res/{}Cards/card{}{}.png", strSuit, strFace, strSuit);
    log(fmt::format("New card uri {}", ret), logSeverity::INFO);

    return ret;
}