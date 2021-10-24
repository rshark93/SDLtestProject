#pragma once

#include "Button.h"
#include <atomic>

//typedef void (Button::* CallbackType)(SDL_Event* e);
// typedef std::function<void (const GameCharacter&)> HealthCalcFunc;

//Button constants
constexpr int IMAGE_WIDTH = 365;
constexpr int IMAGE_HEIGHT = 360;
constexpr int TOTAL_IMAGES = 1;

class Image : public Button{

private:
	//Check if mouse is in button
	//Top left position 
	SDL_Point iPosition;

	//Currently used global sprite
	//LButtonSprite imCurrentSprite;

	SDL_Point* center = new SDL_Point{ 0, 0 };
public:
	//STexture gImageSpriteSheetTexture;
	SDL_Rect iSpriteClips[BUTTON_SPRITE_TOTAL];

	Image();
	~Image();
	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void ihandleEvent(SDL_Event* ei);

	//Shows button sprite
	void render(SDL_Renderer* gRenderer, STexture& sTexture);

	//std::atomic_bool inside = true;

	//Currently used global sprite
	LButtonSprite imCurrentSprite;
};