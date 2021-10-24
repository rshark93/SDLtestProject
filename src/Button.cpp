#include "Button.h"
#include "logger.h"

INITIALIZE_LOGGER;

Button::Button() {
    _log(logger::log_trace) << "Button()" << std::endl;

    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

Button::~Button() {
	std::cout << "~Button()" << std::endl;

    if (center != nullptr)
        delete[] center;
}

void Button::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

void Button::handleEvent(SDL_Event* e) {
    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < mPosition.x)
            inside = false;
        //Mouse is right of the button
        else if (x > mPosition.x + BUTTON_WIDTH)
            inside = false;
        //Mouse above the button
        else if (y < mPosition.y)
            inside = false;
        //Mouse below the button
        else if (y > mPosition.y + BUTTON_HEIGHT)
            inside = false;

        std::string ain = inside ? "true" : "false";
        std::cout << "inside: "<< ain << std::endl;
        //Mouse is outside button
        if (!inside)
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        //Mouse is inside button
        else {
            //Set mouse over sprite
            switch (e->type) {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }

        std::cout << "mCurrentSprite: " << mCurrentSprite << std::endl;
    }
}

void Button::render(SDL_Renderer* gRenderer, STexture& sTexture) {
    //Show current button sprite
    sTexture.render(mPosition.x, mPosition.y, gSpriteClips,
        0, center, SDL_FLIP_NONE, gRenderer);
}
