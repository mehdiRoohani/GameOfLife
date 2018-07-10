/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Tile.h"
#include "Menu.h"
#include <iostream>
#include <unistd.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

bool init();                            //Starts up SDL and creates window
bool loadMedia();                       //Loads media
void close();                           //Frees media and shuts down SDL

SDL_Window* gWindow = NULL;             //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;     //The surface contained by the window
SDL_Surface* grey = NULL;
SDL_Surface* blue = NULL;
SDL_Surface* menuInit1 = NULL;
SDL_Surface* menuInit2 = NULL;
SDL_Surface* menuInit3 = NULL;
SDL_Surface* menuInit4 = NULL;
SDL_Surface* menuInit5 = NULL;
SDL_Surface* menuInit6 = NULL;
SDL_Surface* menuInit7 = NULL;
SDL_Surface* menuStrtDis = NULL;
SDL_Surface* shortGuide = NULL;
SDL_Surface* highSpeed = NULL;
SDL_Surface* lowSpeed = NULL;

//Game Loop
void gameLoopCounter(bool toggled[],int toggleCount[],int w,int hei){
    for (int i=0; i<hei; i++){
        for (int j=0; j<w; j++){
            toggleCount[j+(w*i)] = 0;

            //Center
            if(i>0 && (j+(w*i))>(i*w) && (j+(w*i))<(((i+1)*w)-1) && i<29){
                if(toggled[j+(w*i)-w]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+w]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-1]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+1]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-41]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-39]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+39]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+41]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

            //firstColumn
            else if(i>0 && j==0 && i<29){
                if(toggled[(w*i)-w]==true)    //up
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*i)+w]==true)    //down
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*(i+1))-1]==true) //left
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*i)+1]==true)     //right
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*(i+1))-41]==true)//upLeft
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*i)-39]==true)    //upRight
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*(i+1))+39]==true)//downLeft
                    toggleCount[(w*i)]+=1;
                if(toggled[(w*i)+41]==true)    //downRight
                    toggleCount[(w*i)]+=1;
            }

            //lastColumn
            else if(i>0 && j==39 && i<29){
                if(toggled[j+(w*i)-w]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+w]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-1]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*(i-1))+1]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-41]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*(i-1))-39]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+39]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*(i-1))+41]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

            //firstRow
            else if(i==0 && (j+(w*i))>(i*w) && (j+(w*i))<(((i+1)*w)-1)){
                if(toggled[j+(w*29)]==true)    //up
                    toggleCount[j]+=1;
                if(toggled[j+w]==true)         //down
                    toggleCount[j]+=1;
                if(toggled[j-1]==true)          //left
                    toggleCount[j]+=1;
                if(toggled[j+1]==true)          //right
                    toggleCount[j]+=1;
                if(toggled[j+(w*29)-1]==true)  //upLeft
                    toggleCount[j]+=1;
                if(toggled[j+(w*29)+1]==true)  //upRight
                    toggleCount[j]+=1;
                if(toggled[j+39]==true)         //downLeft
                    toggleCount[j]+=1;
                if(toggled[j+41]==true)         //downRight
                    toggleCount[j]+=1;
            }

            //lastRow
            else if(i==29 && (j+(w*i))>(i*w) && (j+(w*i))<(((i+1)*w)-1)){
                if(toggled[j+(w*i)-w]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-1]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+1]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-41]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-39]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j-1]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+1]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

            //topLeft
            else if(i==0 && j==0){
                if(toggled[(w*29)]==true)  //up
                    toggleCount[0]+=1;
                if(toggled[w*(i+1)]==true)  //down
                    toggleCount[0]+=1;
                if(toggled[(w*(i+1))-1]==true)   //left
                    toggleCount[0]+=1;
                if(toggled[j+1]==true)   //right
                    toggleCount[0]+=1;
                if(toggled[(w*hei)-1]==true)  //upLeft
                    toggleCount[0]+=1;
                if(toggled[(w*29)+1]==true)  //upRight
                    toggleCount[0]+=1;
                if(toggled[(w*(i+2))-1]==true)  //downLeft
                    toggleCount[0]+=1;
                if(toggled[41]==true)  //downRight
                    toggleCount[0]+=1;
            }

            //topRight
            else if(i==0 && j==39){
                if(toggled[1199]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+w]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-1]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[0]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1198]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1160]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+39]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[w]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

            //bottomLeft
            else if(i==29 && j==0){
                if(toggled[j+(w*i)-w]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[0]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1199]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)+1]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1159]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-39]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[39]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

            //bottomRight
            else if(i==29 && j==39){
                if(toggled[j+(w*i)-w]==true)  //up
                    toggleCount[j+(w*i)]+=1;
                if(toggled[39]==true)  //down
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-1]==true)   //left
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1160]==true)   //right
                    toggleCount[j+(w*i)]+=1;
                if(toggled[j+(w*i)-41]==true)  //upLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[1120]==true)  //upRight
                    toggleCount[j+(w*i)]+=1;
                if(toggled[38]==true)  //downLeft
                    toggleCount[j+(w*i)]+=1;
                if(toggled[0]==true)  //downRight
                    toggleCount[j+(w*i)]+=1;
            }

        }
    }
}
void gameLoopUpdateImage(bool toggled[],int togglecount[],Tile tile[],int w, int hei){

    for (int i=0; i<hei; i++){
        for (int j=0; j<w; j++){
            if(toggled[j+(w*i)]==true && (togglecount[j+(w*i)]==2 || togglecount[j+(w*i)]==3)){
            }
            else{
                toggled[j+(w*i)]=false;
                tile[j+(w*i)].SetImage(grey);
                tile[j+(w*i)].Draw(gScreenSurface);
            }
            if(toggled[j+(w*i)]==false && togglecount[j+(w*i)]==3){
                toggled[j+(w*i)]=true;
                tile[j+(w*i)].SetImage(blue);
                tile[j+(w*i)].Draw(gScreenSurface);
            }
        }
    }

    SDL_UpdateWindowSurface( gWindow );
}
void gameLoopInitial(bool toggled[],int togglecount[],Tile tile[],int choice,int w, int hei){
    for (int i=0; i<hei; i++){
        for (int j=0; j<w; j++){
            togglecount[j+(w*i)] = 0;
            tile[j+(w*i)].SetPosition(20*j,20*i);
            switch(choice){

                //Clear
                case 1:{
                    tile[j+(w*i)].SetImage(grey);
                    toggled[j+(w*i)]=false;
                    break;
                }

                //10CellRow
                case 2:{
                    if(i==14 && j>14 && j<25){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(40*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

                //SmallExploder
                case 3:{
                    if((i==13 || i==16) && j==19){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==14 && j>=18 && j<=20){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==15 && (j==18 || j==20)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(w*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

                //Exploder
                case 4:{
                    if(i>=12 && i<=16 && (j==17 || j==21)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if((i==12 || i==16) && j==19){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(w*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

                //Tumbler
                case 5:{
                    if((i==12 || i==13)  && j>=17 && j<=21 && j!=19){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==14 && (j==18 || j==20)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if((i==15 || i==16) && (j==16 || j==18 || j==20 || j==22)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==17 && (j==16 || j==17 || j==21 || j==22)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(w*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

                //Glider
                case 6:{
                    if(i==13 && j==19){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==14 && j==20){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==15 && j>=18 && j<=20){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(w*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

                //SpaceShips
                case 7:{
                    if(i==13 && j>=18 && j<=21){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if((i==14 && (j==17 || j==21)) || (i==15 && j==21)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else if(i==16 && (j==17 || j==20)){
                        tile[j+(w*i)].SetImage(blue);
                        toggled[j+(w*i)]=true;
                    }
                    else{
                        tile[j+(w*i)].SetImage(grey);
                        toggled[j+(w*i)]=false;
                    }
                    break;
                }

            }

            tile[j+(w*i)].Draw(gScreenSurface);
        }
    }
}
void indGridToggling(bool toggled[],Tile tile[],int x,int y,int w, int hei){
    for (int i=0; i<hei; i++){
        for (int j=0; j<w; j++){
            if(x>(tile[j+(w*i)].getX()) && x<(tile[j+(w*i)].getX()+20) && y>(tile[j+(w*i)].getY()) && y<(tile[j+(w*i)].getY()+20)){
                if(toggled[j+(w*i)]==false){
                    toggled[j+(w*i)]=true;
                    tile[j+(w*i)].SetImage(blue);
                }
                else{
                    toggled[j+(w*i)]=false;
                    tile[j+(w*i)].SetImage(grey);
                }
                tile[j+(w*i)].Draw(gScreenSurface);
            }
        }
    }
    SDL_UpdateWindowSurface( gWindow );
}

int main( int argc, char* args[] )
{
    Tile tile[1200];
    Menu men;
    Menu men1;
    Menu shortG;
    Menu speed;
    bool toggled[1200];
    int togglecount[1200];


	if( !init() )   //Start up SDL and create window
	{
		printf( "Failed to initialize!\n" );
		return 0;
	}
	else
	{
		if( !loadMedia() )  //Load media
		{
			printf( "Failed to load media!\n" );
			return 0;
		}
		else
		{
		    bool quit = false,loop=false;
		    bool shortGui=false;
		    bool lowSpeedF=true;
		    bool mouseClicked = false,mouseClicked1 = false;
		    SDL_Event e;
		    const Uint8* currentKeyStates;
		    int x, y;

            shortG.SetPosition(0,0);
            shortG.crop(0,0,1000,600);
            shortG.SetImage(shortGuide);
            shortG.Draw(gScreenSurface);

            men.SetPosition(800,475);
            men.crop(0,475,200,125);

            men1.SetPosition(800,0);
            men1.crop(0,0,200,450);

            speed.SetPosition(800,450);
            speed.crop(0,0,200,25);

            SDL_UpdateWindowSurface( gWindow );


            //Shift from ShortGuide
            while(!shortGui){

                while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                        shortGui=true;
                    }
                    SDL_GetMouseState( &x, &y );
                    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                        if(x>373 && x<430 && y>460 && y<475){
                            men.SetImage(menuInit1);
                            men.Draw(gScreenSurface);

                            men1.SetImage(menuInit1);
                            men1.Draw(gScreenSurface);

                            speed.SetImage(highSpeed);
                            speed.Draw(gScreenSurface);

                            gameLoopInitial(toggled,togglecount,tile,1,40,30);
                            shortGui=true;
                        }
                    }
                }
            }

            SDL_UpdateWindowSurface( gWindow );
            int delay=300;

		    while( !quit )                          //While application is running
			{

                while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
                {
                    currentKeyStates = SDL_GetKeyboardState( NULL );

                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    //Design patterns on their respective keys.
                    if(currentKeyStates[ SDL_SCANCODE_1 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,1,40,30);
                        men1.SetImage(menuInit1);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );

                    }
                    if(currentKeyStates[ SDL_SCANCODE_2 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,2,40,30);
                        men1.SetImage(menuInit2);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }
                    if(currentKeyStates[ SDL_SCANCODE_3 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,3,40,30);
                        men1.SetImage(menuInit3);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }
                    if(currentKeyStates[ SDL_SCANCODE_4 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,4,40,30);
                        men1.SetImage(menuInit4);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }
                    if(currentKeyStates[ SDL_SCANCODE_5 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,5,40,30);
                        men1.SetImage(menuInit5);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }
                    if(currentKeyStates[ SDL_SCANCODE_6 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,6,40,30);
                        men1.SetImage(menuInit6);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }
                    if(currentKeyStates[ SDL_SCANCODE_7 ])
                    {
                        gameLoopInitial(toggled,togglecount,tile,7,40,30);
                        men1.SetImage(menuInit7);
                        men1.Draw(gScreenSurface);
                        SDL_UpdateWindowSurface( gWindow );
                    }


                    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                    {
                        //Get mouse position
                        SDL_GetMouseState( &x, &y );

                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT && mouseClicked == false){

                                mouseClicked = true;

                                //Design Patterns on their click
                                if(x>885 && x<915 && y>282 && y<295){
                                    gameLoopInitial(toggled,togglecount,tile,1,40,30);
                                    men1.SetImage(menuInit1);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>870 && x<930 && y>298 && y<310){
                                    gameLoopInitial(toggled,togglecount,tile,2,40,30);
                                    men1.SetImage(menuInit2);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>860 && x<940 && y>315 && y<327){
                                    gameLoopInitial(toggled,togglecount,tile,3,40,30);
                                    men1.SetImage(menuInit3);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>875 && x<925 && y>330 && y<342){
                                    gameLoopInitial(toggled,togglecount,tile,4,40,30);
                                    men1.SetImage(menuInit4);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>875 && x<925 && y>345 && y<357){
                                    gameLoopInitial(toggled,togglecount,tile,5,40,30);
                                    men1.SetImage(menuInit5);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>885 && x<915 && y>360 && y<372){
                                    gameLoopInitial(toggled,togglecount,tile,6,40,30);
                                    men1.SetImage(menuInit6);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>870 && x<930 && y>375 && y<387){
                                    gameLoopInitial(toggled,togglecount,tile,7,40,30);
                                    men1.SetImage(menuInit7);
                                    men1.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }

                                if(x>845 && x<955 && y>450 && y<475){
                                    if(lowSpeedF){
                                        speed.SetImage(lowSpeed);
                                        lowSpeedF=false;
                                        delay=100;
                                    }
                                    else{
                                        speed.SetImage(highSpeed);
                                        lowSpeedF=true;
                                        delay=300;
                                    }
                                    speed.Draw(gScreenSurface);
                                    SDL_UpdateWindowSurface( gWindow );
                                }


                                // Start Button
                                if(x>850 && x<950 && y>514 && y<536 && loop == false){

                                    men.SetImage(menuStrtDis);
                                    men.Draw(gScreenSurface);
                                    loop=true;
                                    while(loop){

                                        gameLoopCounter(toggled,togglecount,40,30);
                                        gameLoopUpdateImage(toggled,togglecount,tile,40,30);
                                        SDL_UpdateWindowSurface( gWindow );

                                        while( SDL_PollEvent( &e ) != 0 ){

                                            if( e.type == SDL_QUIT )
                                            {
                                                quit = true;
                                                loop=false;
                                            }
                                            SDL_GetMouseState( &x, &y );

                                            if(e.type == SDL_MOUSEBUTTONDOWN){

                                                // Stop Button
                                                if(e.button.button == SDL_BUTTON_LEFT && loop==true && x>850 && x<950 && y>541 && y<563)
                                                {
                                                    loop=false;
                                                    men.SetImage(menuInit1);
                                                    men.Draw(gScreenSurface);
                                                    SDL_UpdateWindowSurface( gWindow );
                                                }

                                                // Individual grid toggling with mouse
                                                indGridToggling(toggled,tile,x,y,40,30);

                                                // Change Speed
                                                if(x>845 && x<955 && y>450 && y<475){
                                                    if(lowSpeedF){
                                                        speed.SetImage(lowSpeed);
                                                        lowSpeedF=false;
                                                        delay=100;
                                                    }
                                                    else{
                                                        speed.SetImage(highSpeed);
                                                        lowSpeedF=true;
                                                        delay=300;
                                                    }
                                                    speed.Draw(gScreenSurface);
                                                    SDL_UpdateWindowSurface( gWindow );
                                                }

                                            }

                                        }
                                        SDL_Delay(delay);
                                    }
                                        loop=false;
                                }

                                // Individual grid toggling with mouse
                                indGridToggling(toggled,tile,x,y,40,30);

                                //Next Button
                                if(e.button.button == SDL_BUTTON_LEFT && x>850 && x<950 && y>487 && y<509){
                                    gameLoopCounter(toggled,togglecount,40,30);
                                    gameLoopUpdateImage(toggled,togglecount,tile,40,30);
                                }

                            }

                        }

                        if(e.type == SDL_MOUSEBUTTONUP && mouseClicked == true)
                        {
                                mouseClicked = false;
                        }
                    }
                }
            }
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	grey = SDL_LoadBMP( "Images/redSquare.bmp" );
	blue = SDL_LoadBMP( "Images/blueSquare.bmp" );
	menuInit1 = SDL_LoadBMP( "Images/gameMenuInit1.bmp" );
	menuInit2 = SDL_LoadBMP( "Images/gameMenuInit2.bmp" );
	menuInit3 = SDL_LoadBMP( "Images/gameMenuInit3.bmp" );
	menuInit4 = SDL_LoadBMP( "Images/gameMenuInit4.bmp" );
	menuInit5 = SDL_LoadBMP( "Images/gameMenuInit5.bmp" );
	menuInit6 = SDL_LoadBMP( "Images/gameMenuInit6.bmp" );
	menuInit7 = SDL_LoadBMP( "Images/gameMenuInit7.bmp" );
	menuStrtDis = SDL_LoadBMP( "Images/gameMenuStartDis.bmp" );
	shortGuide = SDL_LoadBMP( "Images/shortGuide.bmp" );
	highSpeed = SDL_LoadBMP( "Images/highSpeed.bmp" );
	lowSpeed = SDL_LoadBMP( "Images/lowSpeed.bmp" );
	if( grey == NULL || blue == NULL || menuInit1==NULL || menuInit2==NULL || menuInit3==NULL || menuInit4==NULL || menuInit5==NULL || menuInit6==NULL || menuInit7==NULL || menuStrtDis==NULL || shortGuide==NULL || highSpeed==NULL || lowSpeed==NULL)
	{
		printf( "Unable to load all the images %s! SDL Error: %s\n", "", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( grey );
	grey = NULL;

	SDL_FreeSurface( blue );
	blue = NULL;
	SDL_FreeSurface( menuInit1);
	menuInit1 = NULL;
	SDL_FreeSurface( menuInit2);
	menuInit2 = NULL;
	SDL_FreeSurface( menuInit3);
	menuInit3 = NULL;
	SDL_FreeSurface( menuInit4);
	menuInit4 = NULL;
	SDL_FreeSurface( menuInit5);
	menuInit5 = NULL;
	SDL_FreeSurface( menuInit6);
	menuInit6 = NULL;
	SDL_FreeSurface( menuInit7);
	menuInit7 = NULL;
	SDL_FreeSurface(menuStrtDis);
	menuStrtDis = NULL;
	SDL_FreeSurface(shortGuide);
	shortGuide = NULL;
	SDL_FreeSurface(highSpeed);
	highSpeed = NULL;
	SDL_FreeSurface(lowSpeed);
	lowSpeed = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
