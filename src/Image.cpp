#include "Image.h"
#include <iostream>

Image::Image() {
	std::cout << "Image()" << std::endl;

    iPosition.x = 0;
    iPosition.y = 0;

    imCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

Image::~Image() {
	std::cout << "~Image()" << std::endl;
    if (center != nullptr)
        delete[] center;
}

void Image::setPosition(int x, int y) {
    iPosition.x = x;
    iPosition.y = y;
}
//typedef void (Button::* CallbackType)(SDL_Event* e);
void Image::ihandleEvent(SDL_Event* ei) {
    //If mouse event happened
    if (ei->type == SDL_MOUSEMOTION || ei->type == SDL_MOUSEBUTTONDOWN || ei->type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Mouse is left of the button
        auto inside = x < iPosition.x ?  false :
        //Mouse is right of the button
        x > iPosition.x + IMAGE_WIDTH ? false :
        //Mouse above the button
        y < iPosition.y ? false :
        //Mouse below the button
        y > iPosition.y + IMAGE_HEIGHT ? false : true;

        std::cout << "inside: " << (inside ? "true" : "false") << std::endl;
        //Mouse is outside button
        if (!inside)
            imCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        //Mouse is inside button
        else {
            //Set mouse over sprite
            //change picture
            switch (ei->type) {
            case SDL_MOUSEMOTION:
                imCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                imCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                imCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }

        std::cout << "Image imCurrentSprite: " << imCurrentSprite << std::endl;
    }
}

void Image::render(SDL_Renderer* gRenderer, STexture & sTexture) {
    //Show current button sprite
    sTexture.render(iPosition.x, iPosition.y, iSpriteClips,
        0, center, SDL_FLIP_NONE, gRenderer);
}