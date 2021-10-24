#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <Image.h>
#include <thread>
#include <chrono>

class MCore {
private:
	const int SCREEN_WIDTH = 860;
	const int SCREEN_HEIGHT = 640;
	std::string button_img_path = "../../img/button.png";
	std::string image_path = "../../img/BTaropdpc1.gif";
	std::string image_path_2 = "../../img/BTaropdpc2.gif";
	//The window we'll be rendering to
	SDL_Window* gWindow = nullptr;

	//The surface contained by the window
	//SDL_Surface* gScreenSurface = nullptr;

	//The image we will load and show on the screen
	//SDL_Surface* gXOut = nullptr;
	std::shared_ptr<STexture> sTexture = std::make_shared<STexture>();

	//The window renderer
	SDL_Renderer* gRenderer = nullptr;
	Button* gButtons = new Button[TOTAL_BUTTONS];
	Image* gImages = new Image[TOTAL_BUTTONS];

    //std::thread buttonThread;

	std::atomic_bool quit = false;
    std::shared_ptr<std::thread> buttonThread = nullptr;
    //std::shared_ptr<std::thread> imageThread = nullptr;
public:

	MCore();
	~MCore();

	bool init();

	bool loadMedia();

	void close();

	int run();

	static bool quitGame;

    void buttonRun();
	//void mainLoop();

	//void Update();
	//void Draw();

	//void reset();

	static bool mouseLeftPressed;
	static int mouseX, mouseY;
};