#include "../inc/cardproj.hpp"
#include "../inc/defines.hpp"
#include "../inc/zsorting.hpp"

CPWindow::CPWindow(int iWindowWidth, int iWindowHeight) {
    this->iWindowWidth = iWindowWidth;
    this->iWindowHeight = iWindowHeight;
}

int CPWindow::OnExecute() {
    if(!OnInit()) {
        return EXIT_FAILURE;
    }

    //Load texture atlas into memory

    sdlTextureCardAtlas = TextureManager::LoadTexture("res/cardsTextureAtlas.png", sdlRenderer);
    
    //Initial entities drawn to screen

    SDL_Rect stackAtlasPos = {.x = 84, .y = 120, .w = 0, .h = 0};
    SDL_Rect stackBlankPos = {.x = 42, .y = 120, .w = 0, .h = 0};

    vecEntities.push_back(
        std::make_shared<Entity>("entyCardStack", sdlTextureCardAtlas, &stackAtlasPos,
            SDL_Rect{.x = 32 + 12, .y = 32 + 42, .w = SRC_CARD_STACK_WIDTH, .h = SRC_CARD_HEIGHT}, GLOBAL_SCALE, true, false, 0)
    );

    vecEntities.push_back(
        std::make_shared<Entity>("entyFirstBlankCard", sdlTextureCardAtlas, &stackBlankPos,
            SDL_Rect{.x = 32 + (12 * 38), .y = 32 + 42, .w = SRC_CARD_WIDTH, .h = SRC_CARD_HEIGHT}, GLOBAL_SCALE, false, true, 1)
    );

    vecEntities.push_back(
        std::make_shared<Entity>("entySecondBlankCard", sdlTextureCardAtlas, &stackBlankPos,
            SDL_Rect{.x = 32 + (12 * 68), .y = 32 + 42, .w = SRC_CARD_WIDTH, .h = SRC_CARD_HEIGHT}, GLOBAL_SCALE, false, true, 1)
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
    
        if (iFrameDelay > (int) iFrameTime) {
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

    Logger::log("Successful SDL_Image Initialization!", logSeverity::INFO);

    if ((sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      iWindowWidth, iWindowHeight, SDL_WINDOW_OPENGL)) == nullptr) {
        return false;
    }

    Logger::log(fmt::format("Created a {}x{} SDL_Window", iWindowWidth, iWindowHeight), logSeverity::INFO);

    if ((sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0)) == nullptr) {
        return false;
    }

    if (SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255) != 0) {
        return false;
    }
    
    bRunning = true;

    Logger::log("Successful SDL Initialization!", logSeverity::INFO);
    return true;
}

void CPWindow::OnEvent(SDL_Event * event) {  

    switch(event->type) {
        case SDL_QUIT:
            bRunning = false;
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                bRunning = false;
                break;
            case SDLK_RETURN:
                DrawRandomCards();
                break;
            
            default:
                //keyboard sym default
                break;
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if (!mouse.lmbDown && event->button.button == SDL_BUTTON_LEFT) {
                mouse.lmbDown = true;

                for (const auto& itr : vecEntities) {
                    if (itr->WasClicked(mouse.pos)) {
                        selectedEntity = itr;
                        selectedEntityOldZ = itr->GetZIndex();
                        //Logger::log(fmt::format("{}", selectedEntity->DisplayString()), logSeverity::DEBUG);

                        if(selectedEntity->GetIsClickable()) {
                            DrawRandomCards();
                        } else if (selectedEntity->GetIsDraggable()) {
                            selectedEntity->SetZIndex(Z_INDEX_MAX);
                            zidxSort(vecEntities);
                            mouse.clickOffset.x = mouse.pos.x - selectedEntity->GetDestRect()->x;
                            mouse.clickOffset.y = mouse.pos.y - selectedEntity->GetDestRect()->y;
                        } else {
                            selectedEntity = nullptr;
                            selectedEntityOldZ = 0;
                        }

                        break;
                    }
                }
            }


            break;
        case SDL_MOUSEMOTION:
            mouse.pos = {event->motion.x, event->motion.y};

            if (mouse.lmbDown && selectedEntity != nullptr && selectedEntity->GetIsDraggable()) {
                priorDragPos = selectedEntity->GetDestRect();
                selectedEntity->SetDestRectXY(mouse.pos.x - mouse.clickOffset.x, mouse.pos.y - mouse.clickOffset.y);
            }

            break;
        case SDL_MOUSEBUTTONUP:
            //Logger::log(fmt::format("{}", selectedEntity->DisplayString()), logSeverity::DEBUG);
            mouse.lmbDown = false;
            if (selectedEntity != nullptr) {
                selectedEntity->SetZIndex(selectedEntityOldZ);
                selectedEntity = nullptr;
                mouse.ResetMouse();
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
    for(const auto& itr : vecEntities) {
        SDL_RenderCopy(sdlRenderer, itr->GetTexture(), itr->GetSrcRect(), itr->GetDestRect());
    }

    //present new frame
    SDL_RenderPresent(sdlRenderer);
}

void CPWindow::OnCleanup() {
    Logger::log("Starting SDL cleanup...", logSeverity::INFO);
    SDL_DestroyTexture(sdlTextureCardAtlas);
    Logger::log("Freed Atlas Texture.", logSeverity::INFO);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

void CPWindow::DrawRandomCards() {
    playingCard card1, card2;

    //remove last set of randomised playing cards
    for (size_t i = 1; i <= vecEntities.size(); i++) {
        vecEntities.pop_back();
    }

    //set up randomiser
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> faceDist(1,13);
    std::uniform_int_distribution<> suitDist(1,4);

    card1.face = (faces) faceDist(gen);
    card1.suit = (suits) suitDist(gen);
    card1.GenerateName();

    card2.face = (faces) faceDist(gen);
    card2.suit = (suits) suitDist(gen);
    card2.GenerateName();

    //Generate the rect corresponding to the location of the card face in the texture atlas
    SDL_Rect rec1 = GenerateSubTexture(card1.face, card1.suit);
    SDL_Rect rec2 = GenerateSubTexture(card2.face, card2.suit);
    
    vecEntities.push_back(
        std::make_shared<Entity>(fmt::format("entyCard{}", card1.name), sdlTextureCardAtlas, &rec1, 
            SDL_Rect{.x = 32 + (12 * 38), .y = 32 + 42, .w = SRC_CARD_WIDTH, .h = SRC_CARD_HEIGHT}, GLOBAL_SCALE, false, true, 1)
    );
    
    vecEntities.push_back(
        std::make_shared<Entity>(fmt::format("entyCard{}", card2.name), sdlTextureCardAtlas, &rec2, 
            SDL_Rect{.x = 32 + (12 * 68), .y = 32 + 42, .w = SRC_CARD_WIDTH, .h = SRC_CARD_HEIGHT}, GLOBAL_SCALE, false, true, 1)
    );
    
}

SDL_Rect CPWindow::GenerateSubTexture(faces face, suits suit) {
   int topLeftX;
   int topLeftY;

    switch (suit) {
        case Club:
            topLeftY = 90;
            break;
        case Diamond:
            topLeftY = 60;
            break;
        case Heart:
            topLeftY = 30;
            break;
        case Spade:
            topLeftY = 0;
            break;
        default:
            topLeftY = 120;
   }

    switch (face) {
        case Ace:
            topLeftX = 0;
        break;

        case Two:
            topLeftX = 21;
        break;

        case Three:
            topLeftX = 42;
        break;

        case Four:
            topLeftX = 63;
        break;

        case Five:
            topLeftX = 84;
        break;

        case Six:
            topLeftX = 105;
        break;

        case Seven:
            topLeftX = 126;
        break;

        case Eight:
            topLeftX = 147;
        break;

        case Nine:
            topLeftX = 168;
        break;

        case Ten:
            topLeftX = 189;
        break; 
        
        case Jack:
            topLeftX = 210;
        break;

        case Queen:
            topLeftX = 231;
        break;

        case King:
            topLeftX = 252;
        break;

        default:
            topLeftX = 42;
    }

    SDL_Rect r = {.x = topLeftX, .y = topLeftY, .w = 0, .h = 0};
    return r;

}