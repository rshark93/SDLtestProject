#include "STexture.h"
#include <iostream>

STexture::STexture() {
	std::cout << "STexture()" << std::endl;
}

STexture::~STexture() {
	std::cout << "~STexture()" << std::endl;
	free();
}

bool STexture::load_from_file(const std::string path, SDL_Renderer* gRenderer) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != nullptr) {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture != nullptr) {
			//Get image dimensions
			m_width_ = loadedSurface->w;
			m_height_ = loadedSurface->h;
		} else std::cout << "Unable to create texture from: " << path.c_str() <<
			"SDL Error: " << SDL_GetError() << std::endl;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	} else std::cout << "Unable to load image %s! SDL_image Error: " << path << std::endl;

	//Return success
	sdlTexture = newTexture;
	return sdlTexture != nullptr;
}

void STexture::free() {
	//Free texture if it exists
	if (sdlTexture != nullptr) {
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = nullptr;
	}

	m_width_ = 0;
	m_height_ = 0;
}

void STexture::set_color(const Uint8 red, const Uint8 green, const Uint8 blue) const {
	//Modulate texture rgb
	SDL_SetTextureColorMod(sdlTexture, red, green, blue);
}

void STexture::set_blend_mode(SDL_BlendMode blending) const {
	//Set blending function
	SDL_SetTextureBlendMode(sdlTexture, blending);
}

void STexture::set_alpha(Uint8 alpha) const {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(sdlTexture, alpha);
}

void STexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,
	SDL_Renderer* gRenderer) const {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width_, m_height_ };

	//Set clip rendering dimensions
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, sdlTexture, clip, &renderQuad, angle, center, flip);
}

int STexture::get_width() const {
	return m_width_;
}

int STexture::get_height() const {
	return m_height_;
}
