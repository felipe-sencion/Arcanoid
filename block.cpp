#include "block.h"

SDL_Rect &Block::getRect()
{
    return rect;
}

void Block::setRect(const SDL_Rect &value)
{
    rect = value;
}

SDL_Color Block::getColor() const
{
    return color;
}

void Block::setColor(const SDL_Color &value)
{
    color = value;
}

Block::Block()
{

}

void Block::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
