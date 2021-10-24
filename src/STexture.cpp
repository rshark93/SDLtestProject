#include "STexture.h"
#include <iostream>

STexture::STexture() {
	std::cout << "STexture()" << std::endl;
}

STexture::~STexture() {
	std::cout << "~STexture()" << std::endl;
	free();
}

bool STexture::loadFromFile(std::string path, SDL_Renderer* gRenderer) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
		std::cout << "Unable to load image %s! SDL_image Error: " << path << std::endl;
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == nullptr)
			std::cout << "Unable to create texture from: " << path.c_str() <<
				"SDL Error: " << SDL_GetError() << std::endl;
		else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	sdlTexture = newTexture;
	return sdlTexture != nullptr;
}

void STexture::free() {
	//Free texture if it exists
	if (sdlTexture != nullptr) {
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void STexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(sdlTexture, red, green, blue);
}

void STexture::setBlendMode(SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(sdlTexture, blending);
}

void STexture::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(sdlTexture, alpha);
}

void STexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,
	SDL_Renderer* gRenderer) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, sdlTexture, clip, &renderQuad, angle, center, flip);
}

int STexture::getWidth() {
	return mWidth;
}

int STexture::getHeight() {
	return mHeight;
}
