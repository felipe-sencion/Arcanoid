#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class ScoreDisplay
{
private:
    TTF_Font *font;
    SDL_Texture *scoreTexture;
    SDL_Rect messageRect;
    SDL_Color messageColor;
    string text;
public:
    ScoreDisplay();
    void render(unsigned int x, unsigned int y, unsigned int w, unsigned int h, SDL_Renderer *renderer);
    void clean();
    void setText(const string &value);
    SDL_Texture *getScoreTexture() const;
    void setScoreTexture(SDL_Texture *value);
    string getText() const;
};

#endif // SCOREDISPLAY_H
