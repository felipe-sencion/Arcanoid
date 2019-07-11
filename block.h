#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Block
{
private:
    SDL_Rect rect;
    SDL_Color color;
public:
    Block();
    void render(SDL_Renderer *renderer);
    SDL_Rect &getRect();
    void setRect(const SDL_Rect &value);
    SDL_Color getColor() const;
    void setColor(const SDL_Color &value);
};

#endif // BLOCK_H
