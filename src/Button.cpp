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
        auto x = 0, y = 0;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        //Mouse is left of the button
        auto inside = x < mPosition.x ? false :
            //Mouse is right of the button
            x > mPosition.x + BUTTON_WIDTH ? false :
            //Mouse above the button
            y < mPosition.y ? false :
            //Mouse below the button
            y > mPosition.y + BUTTON_HEIGHT ? false : true;
    	
        std::cout << "inside: "<< (inside ? "true" : "false") << std::endl;
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
