#pragma once

#include <SDL.h>
#include "Tile.h"

class Menu:public Tile
{
public:
    Menu();
    ~Menu();
    void SetPosition(int, int);
    void crop(int,int,int,int);
};
