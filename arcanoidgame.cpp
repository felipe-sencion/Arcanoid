#include "arcanoidgame.h"
#include <math.h>
#include <sstream>
#include <iomanip>

bool ArcanoidGame::getStarted() const
{
    return started;
}

void ArcanoidGame::setStarted(bool value)
{
    started = value;
}

void ArcanoidGame::createBlocks(unsigned int sw, unsigned int sh, unsigned int rows, unsigned int cols)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255);
    unsigned int w = sw/(cols+1);
    unsigned int h = sh/((rows+1)*3);
    for (unsigned int r(0); r < rows; ++r)
    {
        for (unsigned int c(0); c < cols; ++c)
        {
            Block b;
            SDL_Color color;
            SDL_Rect rect;
            color.r = dist(gen);
            color.g = dist(gen);
            color.b = dist(gen);
            color.a = 255;
            rect.x = c * w + (w/cols) * c + (w/cols)/2;
            rect.y = (r+1) * h + r*3;
            rect.w = w;
            rect.h = h;
            b.setColor(color);
            b.setRect(rect);
            blocks.push_back(b);
        }
    }
}

void ArcanoidGame::updateBall()
{
    if (ballRect.x + ballRect.w + ballXSpeed >= getScreenWidth() || ballRect.x + ballXSpeed <= 0)
        ballXSpeed *= -1;
    if (ballRect.y + ballYSpeed <= 0)
        ballYSpeed *= -1;

    ballRect.x += ballXSpeed;
    ballRect.y += ballYSpeed;

    if (ballRect.y + ballRect.h/2 > arcanoid.getRect().y)
        setIsRunning(false);

}

void ArcanoidGame::detectCollisions()
{
    SDL_bool arcanCollision = SDL_HasIntersection(&arcanoid.getRect(), &ballRect);
    if (arcanCollision)
    {
        ballYSpeed *= -1;
        if (ballRect.x + ballRect.w/2 > arcanoid.getRect().x + arcanoid.getRect().w/2)
            ballXSpeed++;
        else
            ballXSpeed--;

    }
    list<Block>::iterator it = blocks.begin();
    while(it != blocks.end())
    {
        SDL_Rect *rect = &(*it).getRect();
        SDL_bool blockCollision = SDL_HasIntersection(&*rect, &ballRect);
        int ballXCenter = (ballRect.x *2 + ballRect.w)/2;
        int ballYCenter = (ballRect.y *2 + ballRect.h)/2;
        if (blockCollision)
        {
            if (ballXCenter >= rect->x && ballXCenter <= rect->x + rect->w)
            {
                if(ballYCenter >= rect->y && ballYCenter <= rect->y + rect->h)
                    ballXSpeed *= -1;
                else
                    ballYSpeed *= -1;
            }
            else if(ballYCenter >= rect->y && ballYCenter <= rect->y + rect->h)
                ballXSpeed *= -1;
            else
            {
                if (abs(ballXSpeed) > abs(ballYSpeed))
                    ballXSpeed *= -1;
                else
                    ballYSpeed *= -1;
            }

            blocks.erase(it);
            --it;
            stringstream ss;
            score += 10;
            ss <<setw(4) <<score;
            string scoreString = "Score: " + ss.str();
            scoreDisplay->setText(scoreString);
            break;
        }
        ++it;
    }

}

ArcanoidGame::ArcanoidGame()
{
    SDL_Rect rect;
    SDL_Color color;
    int screenWidth = 300;
    int screenHeight = 400;
    int arcanoidWidth = screenWidth / 4;
    int arcanoidHeight = screenHeight / 20;

    init("Arcanoid", screenWidth, screenHeight, false);
    TTF_Init();
    createBlocks(300, 400, 7, 5);

    color.r = 175;
    color.g = 150;
    color.b = 50;
    color.a = 255;
    rect.w = arcanoidWidth;
    rect.h = arcanoidHeight;
    rect.x = screenWidth/2-arcanoidWidth/2;
    rect.y = (screenHeight/8)*7;
    arcanoid.setColor(color);
    arcanoid.setRect(rect);

    SDL_Surface *tempSurface;
    tempSurface = IMG_Load("ball.png");
    ballTexture = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    ballRect.w = 12;
    ballRect.h = 12;
    ballRect.x = screenWidth/2-ballRect.w/2;
    ballRect.y = rect.y-ballRect.h;
    setStarted(false);
    ballXSpeed = 0;
    ballYSpeed = 0;

    scoreDisplay = new ScoreDisplay();
    score = 0;
    scoreDisplay->setText("Score:    0");

    run();
}

void ArcanoidGame::run()
{
    const int FPS = 12;//24;
    const int FRAME_DELAY = 1000/FPS;
    unsigned int frameStart;
    unsigned int frameTime;
    while(getIsRunning())
    {
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);
    }
    clean();
}

void ArcanoidGame::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
    case SDL_QUIT:
        setIsRunning(false);
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            SDL_Rect rect = arcanoid.getRect();
            if (rect.x - ARCAN_SPEED > 0)
            {
                rect.x -= ARCAN_SPEED;
                arcanoid.setRect(rect);
                if (!started)
                    ballRect.x -= ARCAN_SPEED;
            }
            break;
        }
        case SDLK_RIGHT:
        {
            SDL_Rect rect = arcanoid.getRect();
            if (rect.x + rect.w + ARCAN_SPEED < getScreenWidth())
            {
                rect.x += ARCAN_SPEED;
                arcanoid.setRect(rect);
                if (!started)
                    ballRect.x += ARCAN_SPEED;
            }
            break;
        }
        case SDLK_SPACE:
            if (!started)
            {
                if (ballRect.x >= getScreenWidth() / 2 - ballRect.w / 2)
                    ballXSpeed = 5;
                else
                    ballXSpeed = -5;
                ballYSpeed = -5;
            }
            started = true;
        }
        break;
    default:
        break;
    }
}

void ArcanoidGame::update()
{
    updateBall();
    detectCollisions();
}

void ArcanoidGame::render()
{
    SDL_RenderClear(getRenderer());

    for (Block b: blocks)
        b.render(getRenderer());
    arcanoid.render(getRenderer());
    SDL_RenderCopy(getRenderer(), ballTexture, nullptr, &ballRect);

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(scoreDisplay->getScoreTexture(), NULL, NULL, &textW, &textH);
    scoreDisplay->render(getScreenWidth() - textW, getScreenHeight() - textH, textW, textH, getRenderer());

    SDL_SetRenderDrawColor(getRenderer(), 0,0,0,255);
    SDL_RenderPresent(getRenderer());
}

void ArcanoidGame::clean()
{
    SDL_DestroyWindow(getWindow());
    SDL_DestroyRenderer(getRenderer());
    SDL_DestroyTexture(ballTexture);
    scoreDisplay->clean();
    TTF_Quit();
    SDL_Quit();
}
