#pragma once
#include "Menu.h"

Menu::Menu():Tile(){
    srcrect.w = 200;
    srcrect.h = 600;

    dstrect.w = 200;
    dstrect.h = 600;
}
Menu::~Menu()
{

}
void Menu::SetPosition(int x, int y){
    position.x = x;
    position.y = y;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = 200;
    dstrect.h = 600;
}

void Menu::crop(int x,int y,int w,int h){
    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = w;
    srcrect.h = h;
}
