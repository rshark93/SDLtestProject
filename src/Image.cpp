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

        auto inside = true;

        //Mouse is left of the button
        if (x < iPosition.x)
            inside = false;
        //Mouse is right of the button
        else if (x > iPosition.x + IMAGE_WIDTH)
            inside = false;
        //Mouse above the button
        else if (y < iPosition.y)
            inside = false;
        //Mouse below the button
        else if (y > iPosition.y + IMAGE_HEIGHT)
            inside = false;

        std::string ain = inside ? "true" : "false";
        std::cout << "inside: " << ain << std::endl;
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