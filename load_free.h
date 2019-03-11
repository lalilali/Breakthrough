#ifndef LOADFREE_H_INCLUDED
#define LOADFREE_H_INCLUDED
#include "gametool.h"
void setTitle(float t);
enum image_name{image_board,image_blackpawn,image_whitepawn,image_start,image_select,image_select2,image_blackwin,image_whitewin,
                image_chose1,image_chose2,image_background,image_chess};
void loadFiles(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music **music,Mix_Chunk *effects[]);
void freeAll(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music *music,Mix_Chunk *effects[]);
#endif // LOAD&FRE
