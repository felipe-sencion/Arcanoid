#include "game.h"

bool Game::getIsRunning() const
{
    return isRunning;
}

void Game::setIsRunning(bool value)
{
    isRunning = value;
}

SDL_Renderer *Game::getRenderer() const
{
    return renderer;
}

void Game::setRenderer(SDL_Renderer *value)
{
    renderer = value;
}

SDL_Window *Game::getWindow() const
{
    return window;
}

void Game::setWindow(SDL_Window *value)
{
    window = value;
}

int Game::getScreenWidth() const
{
    return screenWidth;
}

void Game::setScreenWidth(int value)
{
    screenWidth = value;
}

int Game::getScreenHeight() const
{
    return screenHeight;
}

void Game::setScreenHeight(int value)
{
    screenHeight = value;
}

Game::Game()
{
    isRunning = false;
}

void Game::init(const char *title, int w, int h, bool fullScreen)
{
    int flags = 0;
    screenWidth = w;
    screenHeight = h;

    if (fullScreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screenWidth,
                                  screenHeight,
                                  flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        else
            cout <<"Couldn't initializa renderer " <<SDL_GetError() <<endl;

        isRunning = true;
    }
}
