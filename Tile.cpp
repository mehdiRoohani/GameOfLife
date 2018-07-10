#include"Tile.h"

Tile::Tile(){
    this->image = image;
    position.x = 0;
    position.y = 0;

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 20;
    srcrect.h = 20;

    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 20;
    dstrect.h = 20;
}

Tile::~Tile(){

}

void Tile::SetPosition(int x, int y){
    position.x = x;
    position.y = y;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = 20;
    dstrect.h = 20;
}

void Tile::Draw(SDL_Surface* gScreenSurface){
    SDL_BlitSurface(image, &srcrect, gScreenSurface, &dstrect);
}

void Tile::SetImage(SDL_Surface* image){
    this->image = image;
}

int Tile::getX(){
    return position.x;
}

int Tile::getY(){
    return position.y;
}
