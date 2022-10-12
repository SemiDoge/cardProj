#include "../inc/cardproj.h"
#include "../inc/defines.h"

CPWindow::CPWindow(int iWindowWidth, int iWindowHeight) {
    this->iWindowWidth = iWindowWidth;
    this->iWindowHeight = iWindowHeight;
}

int CPWindow::OnExecute() {
    if(OnInit() == false) {
        return EXIT_FAILURE;
    }

    //Load texture atlas into memory

    sdlTextureCardAtlas = TextureManager::LoadTexture("res/cardsTextureAtlas.png", sdlRenderer);
    
    //Initial entities drawn to screen

    SDL_Rect stackAtlasPos = {x: 63, y: 120};
    SDL_Rect stackBlankPos = {x: 42, y: 120};

    vecEntities.push_back(
        std::make_shared<Entity>("entyCardStack", sdlTextureCardAtlas, &stackAtlasPos, 
            SRC_CARD_STACK_WIDTH, SRC_CARD_HEIGHT, 32 + 12, 32 + 42, GLOBAL_SCALE, true)
    );

    vecEntities.push_back(
        std::make_shared<Entity>("entyFirstCard", sdlTextureCardAtlas, &stackBlankPos,
            SRC_CARD_WIDTH, SRC_CARD_HEIGHT, 32 + (12 * 38), 32 + 42, GLOBAL_SCALE, false)
    );
    
    vecEntities.push_back(
        std::make_shared<Entity>("entySecondCard", sdlTextureCardAtlas, &stackBlankPos,
            SRC_CARD_WIDTH, SRC_CARD_HEIGHT, 32 + (12 * 68), 32 + 42, GLOBAL_SCALE, false)
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

    Logger::log("Successful SDL_Image Initialization!", logSeverity::INFO);

    if ((sdlWindow = SDL_CreateWindow("Card Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWindowWidth, iWindowHeight, SDL_WINDOW_OPENGL)) == NULL) {
        return false;
    }

    Logger::log(fmt::format("Created a {}x{} SDL_Window", iWindowWidth, iWindowHeight), logSeverity::INFO);

    if ((sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0)) == NULL) {
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
        SDL_RenderCopy(sdlRenderer, sdlTextureCardAtlas, itr->GetSrcRect(), itr->GetDestRect());
    }

    //present new frame
    SDL_RenderPresent(sdlRenderer);
}

void CPWindow::OnCleanup() {
    Logger::log("Starting SDL cleanup...", logSeverity::INFO);
    SDL_DestroyTexture(sdlTextureCardAtlas);
    Logger::log("Destroyed Atlas Texture.", logSeverity::INFO);
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

    card2.face = (faces) faceDist(gen);
    card2.suit = (suits) suitDist(gen);

    //Generate the rect corresponding to the location of the card face in the texture atlas
    SDL_Rect rec1 = GenerateSubTexture(card1.face, card1.suit);
    SDL_Rect rec2 = GenerateSubTexture(card2.face, card2.suit);

    vecEntities.push_back(
        std::make_shared<Entity>(fmt::format("entyCard{}{}", (int)card1.face, (int)card1.suit), sdlTextureCardAtlas, &rec1,
            SRC_CARD_WIDTH, SRC_CARD_HEIGHT, 32 + (12 * 38), 32 + 42, GLOBAL_SCALE, false)
    );
    
    vecEntities.push_back(
        std::make_shared<Entity>(fmt::format("entyCard{}{}", (int)card2.face, (int)card2.suit), sdlTextureCardAtlas, &rec2,
            SRC_CARD_WIDTH, SRC_CARD_HEIGHT, 32 + (12 * 68), 32 + 42, GLOBAL_SCALE, false)
    );
}

SDL_Rect CPWindow::GenerateSubTexture(faces face, suits suit) {
   int topLeftX = 0; 
   int topLeftY = 0; 

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

    SDL_Rect r = {x: topLeftX, y: topLeftY};
    return r;

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

    switch (card.face) {
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
    Logger::log(fmt::format("New card uri {}", ret), logSeverity::INFO);

    return ret;
}
