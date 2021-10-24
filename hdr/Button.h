#pragma once
#include "Widget.h"
#include <SDL.h>
#include <STexture.h>

//Button constants
constexpr int BUTTON_WIDTH = 150;
constexpr int BUTTON_HEIGHT = 74;
constexpr int TOTAL_BUTTONS = 1;

enum LButtonSprite {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

class Button/* : public Widget */{
private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	SDL_Point *center = new SDL_Point{ 0, 0 };
public:
	SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

	Button();
	~Button();
	//Sets top left position
	virtual void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	virtual void render(SDL_Renderer* gRenderer, STexture& sTexture);
};