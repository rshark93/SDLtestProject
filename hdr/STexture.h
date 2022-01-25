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
	int m_width_ = 0;
	int m_height_ = 0;
public:
	//Initializes variables
	STexture();

	//Deallocate memory
	~STexture();

	//Loads image at specified path
	bool load_from_file(std::string path, SDL_Renderer* gRenderer);

	//Creates image from font string
	//bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocate texture
	void free();

	//Set color modulation
	void set_color(Uint8 red, Uint8 green, Uint8 blue) const;

	//Set blending
	void set_blend_mode(SDL_BlendMode blending) const;

	//Set alpha modulation
	void set_alpha(Uint8 alpha) const;

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip, double , SDL_Point* center, SDL_RendererFlip flip,
		SDL_Renderer* gRenderer) const;

	//Gets image dimensions
	[[nodiscard]] int get_width() const;
	[[nodiscard]] int get_height() const;

};