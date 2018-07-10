#pragma once

#include <SDL.h>
#include"Point.h"

class Tile
{
protected:
    Point position;
    SDL_Surface* image;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
public:
    Tile();
    ~Tile();
    void SetPosition(int x, int y);
    void Draw(SDL_Surface* gScreenSurface);
    void SetImage(SDL_Surface* image);
    int getX();
    int getY();
};
