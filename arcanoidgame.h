#ifndef ARCANOIDGAME_H
#define ARCANOIDGAME_H
#include <iostream>
#include <list>
#include "game.h"
#include "block.h"
#include <random>
#include <SDL2/SDL_ttf.h>
#include "scoredisplay.h"

using namespace std;

class ArcanoidGame : public Game
{
private:
    const int ARCAN_SPEED = 10;

    list<Block> blocks;
    Block arcanoid;
    SDL_Texture *ballTexture;
    SDL_Rect ballRect;
    bool started;
    int ballXSpeed;
    int ballYSpeed;
    ScoreDisplay *scoreDisplay;
    int score;

    void createBlocks(unsigned int sw, unsigned int sh, unsigned int rows, unsigned int cols);
    void updateBall();
    void detectCollisions();

public:
    ArcanoidGame();

    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool getStarted() const;
    void setStarted(bool value);
};

#endif // ARCANOIDGAME_H
