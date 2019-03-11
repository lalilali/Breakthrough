#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<iostream>

#include "gametool.h"
#include "load&free.h"

using namespace std;
struct Blackpawn
{
    int x=0;
    int y=0;
    bool dead=false;
    int initx=135,inity=20;
};
struct Whitepawn
{
    int x=0;
    int y=0;
    bool dead=false;
    int initx=135,inity=431;
};
void set_pawns(Blackpawn *bp,Whitepawn *wp,SDL_Surface *screen,SDL_Surface *images[])
{
    ////////////////////////////黑色棋子
    int dy=0;
    int count=0;
    for(int i=0; i<2; i++)
    {
        int dx=0;
        for(int j=0; j<8; j++)
        {
            bp[count].x=bp[count].initx+dx;
            bp[count].y=bp[count].inity+dy;
            apply_surface(bp[count].x,bp[count].y,images[image_blackpawn],screen,NULL);
            dx+=69;//空格間的距離
            count+=1;
        }
        dy+=69;
    }
    ////////////////////////////白色棋子
    dy=0;
    count=0;
    for(int i=0; i<2; i++)
    {
        int dx=0;
        for(int j=0; j<8; j++)
        {
            wp[count].x=wp[count].initx+dx;
            wp[count].y=wp[count].inity+dy;
            apply_surface(wp[count].x,wp[count].y,images[image_whitepawn],screen,NULL);
            dx+=69;//空格間的距離
            count+=1;
        }
        dy+=69;
    }
    ////////////////////////////
}
void print_pawn(Blackpawn *bp,Whitepawn *wp,SDL_Surface *screen,SDL_Surface *images[])
{
    for(int i=0; i<16; i++)
    {
        if(!bp[i].dead)
        {
            apply_surface(bp[i].x,bp[i].y,images[image_blackpawn],screen,NULL);
        }
        if(!wp[i].dead)
        {
            apply_surface(wp[i].x,wp[i].y,images[image_whitepawn],screen,NULL);
        }
    }
}
void move(Blackpawn *bp,int index,int position,SDL_Surface *screen,SDL_Surface *images[])
{
    if(position==1)//向前
    {
        if(bp[index].y+69>550)
        {
            return;
        }
        bp[index].y+=69;
        apply_surface(bp[index].x,bp[index].y,images[image_blackpawn],screen,NULL);
    }
    else if(position==2)//向左上
    {
        if(bp[index].y+69>550)
        {
            return;
        }
        if(bp[index].x-69<100)
        {
            return;
        }
        bp[index].x-=69;
        bp[index].y+=69;
        apply_surface(bp[index].x,bp[index].y,images[image_blackpawn],screen,NULL);
    }
    else if(position==3)//向右上
    {
        if(bp[index].y+69>550)
        {
            return;
        }
        if(bp[index].x+69>650)
        {
            return;
        }
        bp[index].x+=69;
        bp[index].y+=69;
        apply_surface(bp[index].x,bp[index].y,images[image_blackpawn],screen,NULL);
    }
}
void move(Whitepawn *wp,int index,int position,SDL_Surface *screen,SDL_Surface *images[])
{
    if(position==1)//向前
    {
        if(wp[index].y-69<10)
        {
            return;
        }
        wp[index].y-=69;
        apply_surface(wp[index].x,wp[index].y,images[image_whitepawn],screen,NULL);
    }
    else if(position==2)//向左上
    {
        if(wp[index].y-69<10)
        {
            return;
        }
        if(wp[index].x-69<100)
        {
            return;
        }
        wp[index].x-=69;
        wp[index].y-=69;
        apply_surface(wp[index].x,wp[index].y,images[image_whitepawn],screen,NULL);
    }
    else if(position==3)//向右上
    {
        if(wp[index].y-69<10)
        {
            return;
        }
        if(wp[index].x+69>650)
        {
            return;
        }
        wp[index].x+=69;
        wp[index].y-=69;
        apply_surface(wp[index].x,wp[index].y,images[image_whitepawn],screen,NULL);
    }
}
template <class T>
bool same_pos(T a,T b)
{
    if(abs(a.x-b.x)<5 && abs(a.y+69-b.y)<5)
    {
        return true;
    }
    return false;
}
bool same_pos(Blackpawn a,Whitepawn b)
{
    if(abs(a.x-b.x)<5 && abs(a.y+69-b.y)<5)
    {
        return true;
    }
    return false;
}
bool same_pos(Whitepawn a,Blackpawn b)
{
    if(abs(a.x-b.x)<5 && abs(a.y+69-b.y)<5)
    {
        return true;
    }
    return false;
}
bool can_move(Blackpawn *bp,Whitepawn *wp,int index,int color,char where)//0=black,1=white//L=左前,R=右前,U=上,A=全部
{
    if(bp[index].dead)
    {
        return false;
    }
    if(wp[index].dead)
    {
        return false;
    }
    for(int i=0; i<16; i++)
    {
        int all_cannot_move=0;
        if(color==0)
        {
            if(where=='U' || where=='A')
            {
                if( same_pos(bp[index],bp[i]) || same_pos(bp[index],wp[i]))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if(bp[index].y+69>550)
                {
                    return false;
                }
            }
            if(where=='L'|| where=='A')
            {
                if((abs(bp[index].x-69-bp[i].x)<5 && abs(bp[index].y+69-bp[i].y)<5 )  ||  (abs(bp[index].x-69-wp[i].x)<5 && abs(bp[index].y+69-wp[i].y)<5))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if(bp[index].y+69>550 || bp[index].x-69<100)
                {
                    return false;
                }
            }
            if(where=='R'|| where=='A')
            {
                if((abs(bp[index].x+69-bp[i].x)<5 && abs(bp[index].y+69-bp[i].y)<5 )  ||  (abs(bp[index].x+69-wp[i].x)<5 && abs(bp[index].y+69-wp[i].y)<5))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if(bp[index].y+69>550 || bp[index].x+69>650)
                {
                    return false;
                }
            }
            if(all_cannot_move==3)
            {
                return false;
            }
        }
        else if(color==1)
        {
            if(where=='U' || where=='A')
            {
                if( (abs(wp[index].x-bp[i].x)<5 && abs(wp[index].y-69-bp[i].y)<5)   ||  (abs(wp[index].x-wp[i].x)<5 && abs(wp[index].y-69-wp[i].y)<5))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }

            }
            if(where=='L' || where=='A')
            {
                if((abs(wp[index].x-69-bp[i].x)<5 && abs(wp[index].y-69-bp[i].y)<5)   ||  (abs(wp[index].x-69-wp[i].x)<5 && abs(wp[index].y-69-wp[i].y)<5))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }

            }
            if(where=='R' || where=='A')
            {
                if((abs(wp[index].x+69-bp[i].x)<5 && abs(wp[index].y-69-bp[i].y)<5)   ||  (abs(wp[index].x+69-wp[i].x)<5 && abs(wp[index].y-69-wp[i].y)<5))
                {
                    if(where=='A')
                    {
                        all_cannot_move+=1;
                    }
                    else
                    {
                        return false;
                    }
                }

            }
            if(all_cannot_move==3)
            {
                return false;
            }
        }
    }

    return true;
}
int can_eat(Blackpawn *bp,Whitepawn *wp,int index,int color,char where)
{
    for(int i=0; i<16; i++)
    {
        if(color==0)
        {
            if(where=='L'||where=='A')
            {
                if(abs(bp[index].x-69-wp[i].x)<5 && abs(bp[index].y+69-wp[i].y)<5)//左前是白色的可以向左前吃
                {
                    wp[i].dead=true;
                    return 1;
                }
            }
            if(where=='R'||where=='A')
            {
                if(abs(bp[index].x+69-wp[i].x)<5 && abs(bp[index].y+69-wp[i].y)<5)//右前是白色的可以向右前吃
                {
                    wp[i].dead=true;
                    return 2;
                }
            }

        }

        if(color==1)
        {
            if(where=='L'||where=='A')
            {
                if(abs(wp[index].x-69-bp[i].x)<5 && abs(wp[index].y-69-bp[i].y)<5)//左前是黑色的可以向左前吃
                {
                    bp[i].dead=true;
                    return 1;
                }
            }
            else if(where=='R'||where=='A')
            {
                if(abs(wp[index].x+69-bp[i].x)<5 && abs(wp[index].y-69-bp[i].y)<5)//右前是黑色的可以向右前吃
                {
                    bp[i].dead=true;
                    return 2;
                }
            }
        }
    }
    return 0;

}
void undo_move(Blackpawn *bp,Whitepawn *wp,int xpos,int ypos,bool turn,int index)
{
    if(turn)
    {
        bp[index].x=xpos;
        bp[index].y=ypos;
    }
    else
    {
        wp[index].x=xpos;
        wp[index].y=ypos;
    }
}
int win(Blackpawn *bp,Whitepawn *wp)
{
    for(int i=0; i<16; i++)
    {
        if(bp[i].y>480)
        {
            return 1;
        }
        if(wp[i].y<25)
        {
            return 2;
        }
    }
    return 0;
}
int max_depth=3;
int evaluation(Blackpawn *bp,Whitepawn *wp)
{
    int black_count=0;
    int white_count=0;
    for(int i=0; i<16; i++)
    {
        if(!bp[i].dead)
        {
            black_count+=1;
        }
        if(!wp[i].dead)
        {
            white_count+=1;
        }
    }

    return black_count-white_count;
}
int com_move(Blackpawn *bp,Whitepawn *wp,SDL_Surface *screen,SDL_Surface *images[])
{
    int eating=0;
    for(int i=0;i<16; i++)
    {
        if(bp[i].dead)
        {
           continue;
        }
        eating=can_eat(bp,wp,i,0,'A');
        if(eating==1)
        {
            move(bp,i,2,screen,images);
            return 1;
        }
        else if(eating==2)
        {
            move(bp,i,3,screen,images);
            return 1;
        }
        else if(can_move(bp,wp,i,0,'U'))
        {
            move(bp,i,1,screen,images);
            return 1;
        }
        else if(can_move(bp,wp,i,0,'L'))
        {
            move(bp,i,2,screen,images);
            return 1;
        }
        else if(can_move(bp,wp,i,0,'R'))
        {
            move(bp,i,3,screen,images);
            return 1;
        }
    }
}
int alpha_beta(int alpha, int beta, int depth,Blackpawn *bp,Whitepawn *wp,bool turn,SDL_Surface *screen,SDL_Surface *images[])
{

    int value=0;
    int eatv=3;
    int eating=0;
    if(depth<=0)
    {
        return 0;
    }
    if(win(bp,wp)==2)//黑色輸
    {
        return -999999-depth;
    }
    if(win(bp,wp)==1)//黑色贏
    {
        return 999999+depth;
    }
    int temp=0;
    int xpos=0;
    int ypos=0;
    for(int i=0; i<16; i++)
    {

        if(turn)
        {
            if(bp[i].dead)
            {
                break;
            }
            xpos=bp[i].x;
            ypos=bp[i].y;
        }
        else
        {
            if(wp[i].dead)
            {
                break;
            }
            xpos=wp[i].x;
            ypos=wp[i].y;
        }
        eating=can_eat(bp,wp,i,turn,'A');
        if(eating!=0)
        {
            if(eating==1)
            {
                move(bp,i,2,screen,images);
            }
            else if(eating==2)
            {
                move(bp,i,3,screen,images);
            }
            value=eatv+depth;
            if(depth==1)
            {
                value-=alpha_beta(-alpha+value,-beta+value,depth,bp,wp,!turn,screen,images);
            }
            else
            {
                value-=alpha_beta(-alpha+value,-beta+value,depth-1,bp,wp,!turn,screen,images);
            }
            undo_move(bp,wp,xpos,ypos,turn,i);
        }
        else if(can_move(bp,wp,i,turn,'A'))
        {
            if(can_move(bp,wp,i,turn,'U'))
            {
                move(bp,i,1,screen,images);
                temp=1;
            }
            else if(can_move(bp,wp,i,turn,'L'))
            {
                move(bp,i,2,screen,images);
                temp=2;
            }
            else if(can_move(bp,wp,i,turn,'R'))
            {
                move(bp,i,3,screen,images);
                temp=3;
            }
            value=evaluation(bp,wp);
            value-=alpha_beta(-alpha+value,-beta+value,depth-1,bp,wp,!turn,screen,images);
            undo_move(bp,wp,xpos,ypos,turn,i);
        }
        if(value>=beta)
        {
            return value;
        }

        if(value>alpha)
        {
            alpha=value;
            if(depth=max_depth)
            {
                move(bp,i,temp,screen,images);
            }
        }

    }
    return alpha;

}
int main(int argc, char* args[])
{
    //initialize
    SDL_Surface *screen = init();
    //Load image & font & music
    TTF_Font *fonts[4];
    SDL_Surface* images[50];
    Mix_Music* music[10];
    Mix_Chunk* effects[4];
    loadFiles(images,fonts,music,effects);

    Blackpawn bp[16]= {};
    Whitepawn wp[16]= {};

    int select=0;//黑色0~15 白色 16~31
    int index=0;
    int color=0;//黑0 白1
    SDL_Event event;
    bool next = false;
    bool quit = false;
    bool click = false;
    bool blackmove = false;
    set_pawns(bp,wp,screen,images);
    bool vshuman = false;
    bool vscom = false;
    bool computer = false;

    apply_surface(0,0,images[image_chess],screen,NULL);
    SDL_Flip(screen);
    while(quit == false && next == false)
    {
        if(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    next=true;
                    break;
                default:
                    break;
                }
            }
        }
    }

    next = false;

    apply_surface(0,0,images[image_chose1],screen,NULL);
    SDL_Flip(screen);
    while(quit == false && vshuman == false && vscom == false)
    {
        if(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    apply_surface(0,0,images[image_chose1],screen,NULL);
                    SDL_Flip(screen);
                    computer = false;
                    break;
                case SDLK_DOWN:
                    apply_surface(0,0,images[image_chose2],screen,NULL);
                    SDL_Flip(screen);
                    computer = true;
                    break;
                case SDLK_SPACE:
                    if(computer == true)
                    {
                        vscom=true;
                    }
                    else
                    {
                        vshuman=true;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    if(vshuman)
    {
        while(quit == false && next == false)
        {
            apply_surface(0,0,images[image_background],screen,NULL);
            if(SDL_PollEvent(&event))
            {
                apply_surface(120,0,images[image_board],screen,NULL);
                print_pawn(bp,wp,screen,images);
                textShow(0,470,screen, {0,0,0},fonts[1],"Turn:");
                if(blackmove)
                {
                    textShow(30,500,screen, {0,0,0},fonts[1],"Black");
                }
                else
                {
                    textShow(30,500,screen, {255,255,255},fonts[1],"White");
                }
                SDL_Flip(screen);
                if(select<16)
                {
                    if(!bp[select].dead)
                    {
                        apply_surface(bp[select].x,bp[select].y,images[image_select],screen,NULL);
                    }
                }
                else
                {
                    if(!wp[select].dead)
                    {
                        apply_surface(wp[select-16].x,wp[select-16].y,images[image_select2],screen,NULL);
                    }
                }

                if(!click)
                {
                    apply_surface(210,250,images[image_start],screen,NULL);
                }
                if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        if(select-8<0)
                        {
                            break;
                        }
                        select-=8;

                        break;
                    case SDLK_LEFT:
                        if(select-1<0)
                        {
                            break;
                        }
                        select-=1;

                        break;
                    case SDLK_RIGHT:
                        if(select+1>31)
                        {
                            break;
                        }
                        select+=1;

                        break;
                    case SDLK_DOWN:
                        if(select+8>31)
                        {
                            break;
                        }
                        select+=8;

                        break;
                    case SDLK_w:
                        if(select>15)
                        {
                            index=select-16;
                            color=1;
                        }
                        else
                        {
                            index=select;
                        }
                        if(can_move(bp,wp,index,color,'U'))
                        {
                            if(color==0 && blackmove)
                            {
                                move(bp,index,1,screen,images);
                                blackmove=false;
                            }
                            else if(color==1 && !blackmove)
                            {
                                move(wp,index,1,screen,images);
                                blackmove=true;
                            }
                        }
                        color=0;
                        break;
                    case SDLK_a:
                        if(select>15)
                        {
                            index=select-16;
                            color=1;
                        }
                        else
                        {
                            index=select;
                        }
                        if(can_move(bp,wp,index,color,'L'))
                        {
                            if(color==0 && blackmove)
                            {
                                move(bp,index,2,screen,images);
                                blackmove=false;
                            }
                            else if(color==1 && !blackmove)
                            {
                                move(wp,index,2,screen,images);
                                blackmove=true;
                            }
                        }
                        else if(can_eat(bp,wp,index,color,'L')==1)
                        {
                            if(color==0 && blackmove)
                            {
                                move(bp,index,2,screen,images);
                                blackmove=false;
                            }
                            else if(color==1 && !blackmove)
                            {
                                move(wp,index,2,screen,images);
                                blackmove=true;
                            }
                        }
                        color=0;
                        break;
                    case SDLK_d:
                        if(select>15)
                        {
                            index=select-16;
                            color=1;
                        }
                        else
                        {
                            index=select;
                        }
                        if(can_move(bp,wp,index,color,'R'))
                        {
                            if(color==0 && blackmove)
                            {
                                move(bp,index,3,screen,images);
                                blackmove=false;
                            }
                            else if(color==1 && !blackmove)
                            {
                                move(wp,index,3,screen,images);
                                blackmove=true;
                            }
                        }
                        else if(can_eat(bp,wp,index,color,'R')==2)
                        {
                            if(color==0 && blackmove)
                            {
                                move(bp,index,3,screen,images);
                                blackmove=false;
                            }
                            else if(color==1 && !blackmove)
                            {
                                move(wp,index,3,screen,images);
                                blackmove=true;
                            }
                        }

                        color=0;
                        break;
                    default:
                        break;
                    }
                }
                if(event.type==SDL_MOUSEBUTTONDOWN)
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        click=true;
                        break;

                    default:

                        break;
                    }
                SDL_Flip(screen);
                if(win(bp,wp)==1)
                {
                    SDL_Delay(1000);
                    next = true;
                    apply_surface(0,0,images[image_blackwin],screen,NULL);
                    SDL_Flip(screen);
                    SDL_Delay(3000);
                    quit = true;
                }
                else if(win(bp,wp)==2)
                {
                    SDL_Delay(1000);
                    next = true;
                    apply_surface(0,0,images[image_whitewin],screen,NULL);
                    SDL_Flip(screen);
                    SDL_Delay(3000);
                    quit = true;
                }


                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }

            }
        }
    }
    if(vscom)
    {
        while(quit == false && next == false)
        {
            apply_surface(0,0,images[image_background],screen,NULL);
            if(SDL_PollEvent(&event))
            {
                apply_surface(120,0,images[image_board],screen,NULL);
                print_pawn(bp,wp,screen,images);

                SDL_Flip(screen);

                if(!wp[select].dead)
                {
                    apply_surface(wp[select].x,wp[select].y,images[image_select2],screen,NULL);
                }


                if(!click)
                {
                    apply_surface(210,250,images[image_start],screen,NULL);
                }

                if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        if(select-8<0)
                        {
                            break;
                        }
                        select-=8;

                        break;
                    case SDLK_LEFT:
                        if(select-1<0)
                        {
                            break;
                        }
                        select-=1;

                        break;
                    case SDLK_RIGHT:
                        if(select+1>15)
                        {
                            break;
                        }
                        select+=1;

                        break;
                    case SDLK_DOWN:
                        if(select+8>15)
                        {
                            break;
                        }
                        select+=8;

                        break;
                    case SDLK_w:

                        index=select;
                        if(can_move(bp,wp,index,1,'U'))
                        {
                            move(wp,index,1,screen,images);
                            blackmove=true;
                        }
                        break;
                    case SDLK_a:


                        index=select;

                        if(can_move(bp,wp,index,1,'L'))
                        {

                            move(wp,index,2,screen,images);
                            blackmove=true;
                        }
                        else if(can_eat(bp,wp,index,1,'L')==1)
                        {
                            move(wp,index,2,screen,images);
                            blackmove=true;
                        }

                        color=0;
                        break;
                    case SDLK_d:

                        index=select;

                        if(can_move(bp,wp,index,1,'R'))
                        {
                            move(wp,index,3,screen,images);
                            blackmove=true;
                        }
                        else if(can_eat(bp,wp,index,1,'R')==2)
                        {
                            move(wp,index,3,screen,images);
                            blackmove=true;
                        }
                        color=0;
                        break;
                    default:
                        break;
                    }
                }
                SDL_Flip(screen);
                if(blackmove)
                {
                    SDL_Delay(500);
                    com_move(bp,wp,screen,images);
                    /*alpha_beta(-99999999,99999999,max_depth,bp,wp,blackmove,screen,images);*/
                    blackmove=false;
                    SDL_Flip(screen);
                }
                if(event.type==SDL_MOUSEBUTTONDOWN)
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        click=true;
                        break;

                    default:

                        break;
                    }
                SDL_Flip(screen);
                if(win(bp,wp)==1)
                {
                    SDL_Delay(1000);
                    next = true;
                    apply_surface(0,0,images[image_blackwin],screen,NULL);
                    SDL_Flip(screen);
                    SDL_Delay(3000);
                    quit = true;
                }
                else if(win(bp,wp)==2)
                {
                    SDL_Delay(1000);
                    next = true;
                    apply_surface(0,0,images[image_whitewin],screen,NULL);
                    SDL_Flip(screen);
                    SDL_Delay(3000);
                    quit = true;
                }


                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }

            }
        }
    }

    //Free the loaded image and quit sdl
    freeAll(images,fonts,music[10],effects);

    return 0;
}
