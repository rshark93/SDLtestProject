#include "Widget.h"
#include <SDL.h>

Widget::Widget() { 
    std::cout << "Widget()" << std::endl;

    // Run SDL
    const auto init_status = SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "init status: " << init_status << std::endl;
    
    // Close window
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    // Create render
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    
    // Laod image
    const auto* img_path = "C:/Users/Shark/Pictures/8-Bit_Inc.bmp";
    SDL_Surface* bmp = SDL_LoadBMP(img_path);

    if (bmp != nullptr) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
        SDL_FreeSurface(bmp);
        if (tex == nullptr)
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;

        // Draw texture
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderPresent(ren);

        SDL_Delay(20);

    	// Destroy texture
        SDL_DestroyTexture(tex);
    } else
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

Widget::~Widget() { 
    std::cout << "~Widget()" << std::endl;
}