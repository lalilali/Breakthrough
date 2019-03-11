#include <string>
#include <stdlib.h>
#include <time.h>
#include "gametool.h"
#include "load&free.h"
void setTitle(float t)
{
    char a[100] ;
    snprintf(a,sizeof(a),"%f",t);
    SDL_WM_SetCaption( a, NULL );
}
void loadFiles(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music **music,Mix_Chunk *effects[])
{
    images[image_board]=load_image("images/board.png",0,0,0);
    images[image_blackpawn]=load_image("images/blackpawn.png",255,255,255);
    images[image_whitepawn]=load_image("images/whitepawn.png",255,255,255);
    images[image_start]=load_image("images/start.png",255,255,255);
    images[image_select]=load_image("images/select.png",255,255,255);
    images[image_select2]=load_image("images/select2.png",255,255,255);
    images[image_blackwin]=load_image("images/blackwin.jpg",0,0,0);
    images[image_whitewin]=load_image("images/whitewin.jpg",0,0,0);
    images[image_chose1]=load_image("images/chose1.png",255,255,255);
    images[image_chose2]=load_image("images/chose2.png",255,255,255);
    images[image_background]=load_image("images/background.png",0,0,0);
    images[image_chess]=load_image("images/chess.png",255,255,255);

    fonts[0] = TTF_OpenFont("font/wt064.ttf",36);
    fonts[1] = TTF_OpenFont("font/wt064.ttf",24);
    fonts[2] = TTF_OpenFont("font/wt064.ttf",72);



    music[0] = Mix_LoadMUS( "music/start.mp3" );
    music[1] = Mix_LoadMUS( "music/stage.mp3" );

}
void freeAll(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music *music,Mix_Chunk *effects[])
{
    for(int i= 0;i<sizeof(images)/sizeof(images[0]);i++){
        SDL_FreeSurface(images[i]);
    }

    for(int i= 0;i<sizeof(fonts)/sizeof(fonts[0]);i++){
        TTF_CloseFont(fonts[i]);
    }

    Mix_FreeMusic( music );
    for(int i= 0;i<sizeof(effects)/sizeof(effects[0]);i++){
        Mix_FreeChunk(effects[i]);
    }

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

