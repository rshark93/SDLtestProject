#include "MCore.h"
#include "iostream"

// Run SDL
bool MCore::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
           std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow != nullptr) {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                auto img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
        else {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
    }

    return success;
}

bool MCore::loadMedia() const
{
    //Loading success flag
    bool success = true;

    //Load sprites
    if (!sTexture->load_from_file(button_img_path, gRenderer) &&
        !sTexture->load_from_file(image_path, gRenderer)) {
        std::cout << "Failed to load button or image sprite texture!" << std::endl;
        success = false;
    } else {
        //Set sprites
        for (auto i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            gImages->iSpriteClips[i].x = 0;
            gImages->iSpriteClips[i].y = i * 200;
            gImages->iSpriteClips[i].w = IMAGE_WIDTH;
            gImages->iSpriteClips[i].h = IMAGE_HEIGHT;

            gButtons->gSpriteClips[i].x = 0;
            gButtons->gSpriteClips[i].y = i * 200;
            gButtons->gSpriteClips[i].w = BUTTON_WIDTH;
            gButtons->gSpriteClips[i].h = BUTTON_HEIGHT;
        }

        //Set buttons in corners
        gImages->setPosition(0, 0);
        gButtons->setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
        
        //gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
        //gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
        //gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    }

    return success;
}

void MCore::close() {
    //Free loaded images
    if (sTexture != nullptr)
        sTexture->free();

    //Destroy window	
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

MCore::MCore() {
	std::cout << "MCore()" << std::endl;
    init();
}

MCore::~MCore() {
	std::cout << "~MCore()" << std::endl;
    close();
}

int MCore::run() {

    //buttonThread = std::shared_ptr<std::thread>(new std::thread( [this] { buttonRun(); }));
    //buttonRun();
    
    if (!init())
        std::cout << "Failed to initialize!" << std::endl;
    else {
        //Load media
        if (!loadMedia())
            std::cout << "Failed to load media!" << std::endl;
        else {
            buttonRun();
            //buttonThread = std::thread(&MCore::buttonRun, this);
            //buttonThread = std::shared_ptr<std::thread>(new std::thread([this] { buttonRun(); }));
        }
    }

    //SDL_Thread* threadID = SDL_CreateThread(buttonRun, "LazyThread", (void*)data);

    if (buttonThread->joinable())
        buttonThread->join();
   
    return 0;
}

void MCore::buttonRun() {
            //Event handler
            SDL_Event e;
            SDL_Event ei;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0 || SDL_PollEvent(&ei) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT || ei.type == SDL_QUIT)
                        quit = true;

                    // Handle button & image events
                    //if (SDL_PollEvent(&e) != 0)
                    gButtons->handleEvent(&e);
                    //if (SDL_PollEvent(&ei) != 0)
                    gImages->ihandleEvent(&ei);
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render buttons
                sTexture->load_from_file(button_img_path, gRenderer);
                gButtons->render(gRenderer, *sTexture);

                std::cout << "ei.type: " << ei.type << std::endl;
                std::cout << "gImages->imCurrentSprite: " << gImages->imCurrentSprite << std::endl;
                std::cout << "gButtons->gSpriteClips: " << gButtons->mCurrentSprite << std::endl;
                //Render images
                if (gImages->imCurrentSprite)
                    sTexture->load_from_file(image_path_2, gRenderer);
                else
                    sTexture->load_from_file(image_path, gRenderer);
                gImages->render(gRenderer, *sTexture);

                if (gButtons->mCurrentSprite && e.type == SDL_MOUSEBUTTONDOWN) {
                    if (click_flag) {
                        click_flag = false;
                        run();
                    } else {
                        click_flag = true;
                        close();
                    }
                }

                //Update screen
                SDL_RenderPresent(gRenderer);
    }
}
