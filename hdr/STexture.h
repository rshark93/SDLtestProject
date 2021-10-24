#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class STexture {
private:
	//The actual hardware texture
	///std::shared_ptr<SDL_Texture*> sdlTexture = std::make_shared<SDL_Texture*>();
	SDL_Texture* sdlTexture = nullptr;
	//Image dimensions
	int mWidth = 0;
	int mHeight = 0;
public:
	//Initializes variables
	STexture();

	//Deallocates memory
	~STexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	//Creates image from font string
	//bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip, double , SDL_Point* center, SDL_RendererFlip flip,
		SDL_Renderer* gRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();

};