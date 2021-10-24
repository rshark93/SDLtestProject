#include "Widget.h"
#include <SDL.h>

Widget::Widget() { 
    std::cout << "Widget()" << std::endl;

    // ������ SDL
    auto init_status = SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "init status: " << init_status << std::endl;
    
    // �������� ����
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    // �������� ���������
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    
    // �������� BMP �����������
    SDL_Surface* bmp = SDL_LoadBMP("C:/Users/Shark/Pictures/8-Bit_Inc.bmp");
    if (bmp == nullptr)
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

    if (bmp != nullptr) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
        SDL_FreeSurface(bmp);
        if (tex == nullptr)
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;

        // ��������� ��������
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);

        SDL_Delay(2000);

        // ������ ������
        SDL_DestroyTexture(tex);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

Widget::~Widget() { 
    std::cout << "~Widget()" << std::endl;
}