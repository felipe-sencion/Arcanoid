#include "scoredisplay.h"

SDL_Texture *ScoreDisplay::getScoreTexture() const
{
    return scoreTexture;
}

void ScoreDisplay::setScoreTexture(SDL_Texture *value)
{
    scoreTexture = value;
}

string ScoreDisplay::getText() const
{
    return text;
}

ScoreDisplay::ScoreDisplay()
{
    messageColor.r = 255;
    messageColor.g = 255;
    messageColor.b = 255;
    messageColor.a = 255;
    font = TTF_OpenFont("tarzeau_ocr_a.ttf", 24);
}

void ScoreDisplay::render(unsigned int x, unsigned int y, unsigned int w, unsigned int h, SDL_Renderer *renderer)
{
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = w;
    messageRect.h = h;

    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, text.c_str(), messageColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, messageSurface); //now you can convert it into a texture
    SDL_FreeSurface(messageSurface);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &messageRect);
}

void ScoreDisplay::clean()
{
    SDL_DestroyTexture(scoreTexture);
    TTF_CloseFont(font);
}

void ScoreDisplay::setText(const string &value)
{
    text = value;
}
