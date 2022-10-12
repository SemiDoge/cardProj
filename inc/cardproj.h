#ifndef CARDPROJ_H
#define CARDPROJ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <random>

#include "../inc/textureManager.h"
#include "../inc/entity.h"

enum faces {
    Ace = 1, Two, Three, 
    Four, Five, Six,
    Seven, Eight, Nine, 
    Ten, Jack, Queen,
    King
};

enum suits {
    Club = 1, Diamond,
    Heart, Spade 
};

struct playingCard {
    faces face;
    suits suit;
    SDL_Rect * sdlSrcRect = nullptr;
};

class CPWindow {
private:
    bool bRunning;

    int iWindowWidth = 0;
    int iWindowHeight = 0;
    int iFrameTime = 0;
    const int iTargetFPS = 60;
    const int iFrameDelay = 1000 / iTargetFPS;
    
    Uint32 iFrameStart = 0;

    SDL_Window * sdlWindow = nullptr;
    SDL_Renderer * sdlRenderer = nullptr;
    SDL_Texture * sdlTextureCardAtlas = nullptr;

    std::vector<std::shared_ptr<Entity>> vecEntities;
    

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
    SDL_Rect GenerateSubTexture(faces face, suits suit);
};

#endif