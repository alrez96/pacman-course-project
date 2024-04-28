//============================================================================
// Name        : Pacman.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "hash.h"
using namespace std;
SDL_Surface* screen,*frame[4][10],*eframe[5][4][2],*escape[5][3],*dead[4][11],*eye[5],*number[5],*two;
SDL_Surface* empty,*smalldot,*bigdot,*heart,*text_score,*gameover,*table,*exelent,*notbad,*good,*win;
SDL_Surface* title,*resume,*saveload,*about,*exitbot,*backbut,*help,*resumec,*saveloadc,*aboutc,*one;
SDL_Surface* exitc,*backbutc,*helpc,*help_m,*about_m,*sound,*nosound,*wall;
SDL_Surface* newgame,*newgamec, *load , *loading[11];
Music* begin;
TTF_Font* font;
char buffer_score[10];
short block[2][12][11],ex[4],ey[4],espeed[4],escapetime[4],wx,wy,wv,tmp4,tmp5;
short score[2]={0,0},pframenum=6,eframenum=0,px,py,vector,pspeed=9,timer,lifenum=6,enemyscore=50,leveln;
short a[4][10]={{2,3,3,2,2,3},{2,3,3,2,3,2},{3,2,2,3,2,3},{3,2,2,3,3,2}};
bool isescape[4]={0,0,0,0},estart[4]={1,0,0,0},j[4]={1,1,1,1},h[4]={1,1,1,1},g[4]={1,1,1,1};
bool iseaten[4]={0,0,0,0},o[4]={1,1,1,1},o1[4]={1,1,1,1},j1[4]={1,1,1,1},firstplay;
bool gameexit=0,level1exit=1,level2exit=1,pauseexit=1,menuexit=0,soundon=1,change=1,ready=0,firstenter[2]={1,0};
short q=0;
void tmp1(short& imax , short& jmax,short levelnum)
{
	if(levelnum==1)
	{	imax=12;	jmax=9;}
	else
	{	imax=10; jmax=11;}
}
short tmp(short eynum, short a[4][10], short tmp)
{
	if (!isescape[eynum])
		return tmp;
	else
		return a[eynum][tmp+2];
}
void tmp2(short& xmax,short& ymax ,short levelnum)
{
	if(levelnum==1)
		{xmax=550;ymax=400;}
	else
		{xmax=450;ymax=500;}
}
void tmp3(short& ix,short& iy,short levelnum)
{
	if(levelnum==1)
		{ix=200;iy=200;}
	else
		{ix=150,iy=100;}
}
void tnx_milad_ehsan_mamali(short levelnum)
{
	sprintf(buffer_score , "%d" , score[levelnum-1]);
	text_score = TTF_RenderText_Solid(font , buffer_score , 255 , 255 , 255);
	SDL_BlitSurface (table,screen,575,25);
	SDL_BlitSurface (text_score,screen,675,65);
	for(short i=lifenum;i>0;i--)
		SDL_BlitSurface (heart,screen,610+50*i,145);
	if(levelnum==1)
		SDL_BlitSurface (one,screen,658,237);
	else
		SDL_BlitSurface (two,screen,658,237);
}
void gamedraw (short levelnum)
{
	short imax=0,jmax=0;
	SDL_FillRect(screen , NULL , BLACK);
	SDL_Surface* plan1 = ImgLoader("/home/alireza/workspace/Pacman/src/Image/plan1.png");
	SDL_Surface* plan2 = ImgLoader("/home/alireza/workspace/Pacman/src/Image/plan2.png");
	if(levelnum==1)
		SDL_BlitSurface(plan1 , screen , 0 , 0);
	else
		SDL_BlitSurface(plan2 , screen , 0 , 0);
	tmp1(imax,jmax,levelnum);
	for (short i=0; i<imax; i++)
		for (short j=0; j<jmax; j++)
			switch ( block[levelnum-1][i][j] )
			{
				case 2:{ SDL_Surface* smalldot = ImgLoader ( "/home/alireza/workspace/Pacman/src/Image/dot/dot-small.png", 60 , 240 , 10); SDL_BlitSurface(smalldot , screen , j*50 , i*50);}break;
				case 4:{ SDL_Surface* empty = ImgLoader ( "/home/alireza/workspace/Pacman/src/Image/block/empty.png"); SDL_BlitSurface(empty , screen , j*50 , i*50);}break;
				case 8:{ SDL_Surface* bigdot = ImgLoader ( "/home/alireza/workspace/Pacman/src/Image/dot/dot-big.png" , 60 , 240 , 10); SDL_BlitSurface(bigdot , screen , j*50 , i*50);}break;
			}
}
void pause(short levelnum)
{
	bool back = false;

		SDL_BlitSurface(title , screen , 0 , 0);

			if(Mouse.x > 30 && Mouse.x < 84 && Mouse.y > 452 && Mouse.y < 506)
			{
				SDL_BlitSurface(helpc , screen , 30 , 452);
				if(Mouse.left)
				{
					SDL_FillRect(screen , NULL , BLACK);
					SDL_BlitSurface(help_m , screen , 0 , 0);
					while(!back)
					{
						Update();
						if(Mouse. x > 30 && Mouse.x < 171 && Mouse.y > 30 && Mouse.y < 80)
						{
							SDL_BlitSurface(backbutc , screen , 30 , 30);
							if(Mouse.left)
								back = true;
						}
						else
							SDL_BlitSurface(backbut , screen , 30 , 30);
						SDL_Flip(screen);
					}
				SDL_BlitSurface(title , screen , 0 , 0);
				back = false;
				}
			}
			else
				SDL_BlitSurface(help , screen , 30 , 452);
			if(Mouse.x > 30 && Mouse.x < 84 && Mouse.y > 516 && Mouse.y < 570)
			{
				SDL_BlitSurface(nosound , screen , 30 , 516);
				if(Mouse.left);
				/*{	soundon = !soundon;
					if(soundon)
						PlayMusic(ahang,-1);
					else
						StopMusic();
				}*/
			}
			else
			if(soundon == true)
				SDL_BlitSurface(sound , screen , 30 , 516);
			else
				SDL_BlitSurface(nosound , screen , 30 , 516);
			if(Mouse.x > 185 && Mouse.x < 402 && Mouse.y > 300 && Mouse.y < 377)
			{
				SDL_BlitSurface(resumec , screen , 185 , 300);
				if(Mouse.left)
				{
					if(levelnum==1)
					{	level1exit=0;change=1;pauseexit=1;ready=1;}
					else
					{	level2exit=0;change=1;pauseexit=1;ready=1;}
				}
			}
			else
				SDL_BlitSurface(resume , screen , 185 , 300);
			if(Mouse.x > 440 && Mouse.x < 657 && Mouse.y > 300 && Mouse.y < 377)
			{
				SDL_BlitSurface(saveloadc , screen , 440 , 300);
				//if(Mouse.left)
				//	i = true;
			}
			else
				SDL_BlitSurface(saveload , screen , 440 , 300);
			if(Mouse.x > 160 && Mouse.x < 377 && Mouse.y > 400 && Mouse.y < 477)
			{
				SDL_BlitSurface(aboutc , screen , 185 , 400);
				if(Mouse.left)
				{
					SDL_FillRect(screen , NULL , BLACK);
					SDL_BlitSurface(about_m , screen , 0 , 0);
					while(!back)
					{
						Update();
						if(Mouse. x > 30 && Mouse.x < 171 && Mouse.y > 30 && Mouse.y < 80)
						{
							SDL_BlitSurface(backbutc , screen , 30 , 30);
							if(Mouse.left)
								back = true;
						}
						else
							SDL_BlitSurface(backbut , screen , 30 , 30);
						SDL_Flip(screen);
					}
					SDL_BlitSurface(title , screen , 0 , 0);
					back = false;
				}
			}
			else
				SDL_BlitSurface(about , screen , 185 , 400);
			if(Mouse.x > 440 && Mouse.x < 657 && Mouse.y > 400 && Mouse.y < 477)
			{
				SDL_BlitSurface(exitc , screen , 440 , 400);
				if(Mouse.left)
					gameexit=1;
			}
			else
				SDL_BlitSurface(exitbot , screen , 440 , 400);
}
void menu ()
{
	bool back = false;
	if(firstplay)
	{PlayMusic (begin,-1); firstplay=0;}
	SDL_BlitSurface(title , screen , 0 , 0);

		if(Mouse.x > 30 && Mouse.x < 84 && Mouse.y > 452 && Mouse.y < 506)
		{
			SDL_BlitSurface(helpc , screen , 30 , 452);
			if(Mouse.left){
				SDL_FillRect(screen , NULL , BLACK);
				SDL_BlitSurface(help_m , screen , 0 , 0);
				while(back == false)
				{
					Update();
					if(Mouse. x > 30 && Mouse.x < 171 && Mouse.y > 30 && Mouse.y < 80)
					{
						SDL_BlitSurface(backbutc , screen , 30 , 30);
						if(Mouse.left)
							back = true;
					}
						else
							SDL_BlitSurface(backbut , screen , 30 , 30);
						SDL_Flip(screen);
				}
				SDL_BlitSurface(title , screen , 0 , 0);
				back = false;
			}
		}
		else
			SDL_BlitSurface(help , screen , 30 , 452);
		if(Mouse.x > 30 && Mouse.x < 84 && Mouse.y > 516 && Mouse.y < 570)
		{
			SDL_BlitSurface(nosound , screen , 30 , 516);
			if(Mouse.left);
			{	soundon = !soundon;
				if(soundon)
					PlayMusic(begin,-1);
				else
					{StopMusic();}
			}
		}
		else
		if(soundon)
			SDL_BlitSurface(sound , screen , 30 , 516);
		else
			SDL_BlitSurface(nosound , screen , 30 , 516);
		if(Mouse.x > 185 && Mouse.x < 402 && Mouse.y > 300 && Mouse.y < 377)
		{
			SDL_BlitSurface(newgamec , screen , 185 , 300);
			if(Mouse.left)
			{
				StopMusic();
				SDL_FillRect(screen , NULL , BLACK);
				SDL_BlitSurface(load , screen , 0 , 0);
				for(int j = 0 ; j < 2 ; j++)
					for(int i = 10 ; i >= 0 ; i--)
					{
						SDL_BlitSurface(empty , screen , 670 , 470);
						SDL_BlitSurface(loading[i] , screen , 670 , 470);
						SDL_Flip(screen);
						SDL_Delay(200);
					}
				SDL_FillRect(screen , NULL , BLACK);
				level1exit=0;	menuexit=1;change=1;}
		}
		else
			SDL_BlitSurface(newgame , screen , 185 , 300);
		if(Mouse.x > 440 && Mouse.x < 657 && Mouse.y > 300 && Mouse.y < 377)
		{
			SDL_BlitSurface(saveloadc , screen , 440 , 300);
			//if(Mouse.left)
			//	i = true;
		}
		else
			SDL_BlitSurface(saveload , screen , 440 , 300);
		if(Mouse.x > 185 && Mouse.x < 402 && Mouse.y > 400 && Mouse.y < 477)
		{
			SDL_BlitSurface(aboutc , screen , 185 , 400);
			if(Mouse.left){
				SDL_FillRect(screen , NULL , BLACK);
				SDL_BlitSurface(about_m , screen , 0 , 0);
				while(back == false)
				{
					Update();
					if(Mouse. x > 30 && Mouse.x < 171 && Mouse.y > 30 && Mouse.y < 80)
					{
						SDL_BlitSurface(backbutc , screen , 30 , 30);
						if(Mouse.left)
							back = true;
					}
					else
						SDL_BlitSurface(backbut , screen , 30 , 30);
					SDL_Flip(screen);
				}
			SDL_BlitSurface(title , screen , 0 , 0);
			back = false;
			}
		}
		else
			SDL_BlitSurface(about , screen , 185 , 400);
		if(Mouse.x > 440 && Mouse.x < 657 && Mouse.y > 400 && Mouse.y < 477)
		{
			SDL_BlitSurface(exitc , screen , 440 , 400);
			if(Mouse.left)
				gameexit=1;
		}
		else
			SDL_BlitSurface(exitbot , screen , 440 , 400);

}
void blockvalue(short levelnum)
{
	block[0][0][0] = 1;	block[0][0][1] = 2;	block[0][0][2] = 2;	block[0][0][3] = 2;	block[0][1][4] = 1;
	block[0][1][0] = 1;	block[0][2][1] = 2;	block[0][1][2] = 1;	block[0][1][3] = 1;	block[0][2][4] = 1;
	block[0][2][0] = 8;	block[0][3][1] = 1;	block[0][2][2] = 2;	block[0][2][3] = 2;	block[0][3][4] = 1;
	block[0][3][0] = 2;	block[0][4][1] = 2;	block[0][3][2] = 1;	block[0][3][3] = 2;	block[0][4][4] = 2;
	block[0][4][0] = 2;	block[0][5][1] = 1;	block[0][4][2] = 2;	block[0][4][3] = 2;	block[0][5][4] = 1;
	block[0][5][0] = 1;	block[0][6][1] = 2;	block[0][5][2] = 2;	block[0][5][3] = 1;	block[0][6][4] = 1;
	block[0][6][0] = 8;	block[0][7][1] = 1;	block[0][6][2] = 2;	block[0][6][3] = 1;	block[0][7][4] = 2;
	block[0][7][0] = 2;	block[0][8][1] = 1;	block[0][7][2] = 2;	block[0][7][3] = 2;	block[0][8][4] = 1;
	block[0][8][0] = 2;	block[0][9][1] = 2;	block[0][8][2] = 1;	block[0][8][3] = 2;	block[0][9][4] = 1;
	block[0][9][0] = 2;	block[0][10][1]= 2;	block[0][9][2] = 2;	block[0][9][3] = 2;	block[0][10][4]= 1;
	block[0][10][0]= 1;	block[0][11][1]= 2;	block[0][10][2]= 1;	block[0][10][3]= 1;	block[0][11][4]= 64;
	block[0][11][0]= 1;	block[0][1][1] = 2;	block[0][11][2]= 2;	block[0][11][3]= 2;	block[0][0][4] = 2;
	for (short i=0; i<12; i++)
		for (short j=5; j<9; j++)
			block[0][i][j] = block[0][i][8-j];

	block[1][0][0] = 8; block[1][0][1] = 2; block[1][0][2] = 2; block[1][0][3] = 2; block[1][0][4] = 2;
	block[1][0][5] = 1; block[1][0][6] = 1; block[1][0][7] = 2; block[1][0][8] = 2; block[1][0][9] = 2;
	block[1][0][10] = 8; block[1][1][1] = 1; block[1][1][2] = 1; block[1][1][3] = 1; block[1][1][4] = 2;
	block[1][1][5] = 2; block[1][1][6] = 2; block[1][1][7] = 2; block[1][1][8] = 1; block[1][1][9] = 1;
	block[1][1][10]= 2; block[1][2][0] = 2; block[1][2][1] = 2; block[1][2][2] = 2; block[1][2][3] = 2;
	block[1][2][4] = 2; block[1][2][5] = 1; block[1][2][6] = 2; block[1][2][7] = 1; block[1][2][8] = 1;
	block[1][2][9] = 2; block[1][2][10] =2; block[1][3][0] = 2; block[1][3][1] = 1; block[1][3][2] = 1;
	block[1][3][3] = 1; block[1][3][4] = 2; block[1][3][5] = 2; block[1][3][6] = 2; block[1][3][7] = 2;
	block[1][3][8] = 2; block[1][3][9] = 2; block[1][3][10]= 1; block[1][4][0] = 2; block[1][4][1] = 1;
	block[1][4][2] = 1; block[1][4][3] = 1; block[1][4][4] = 1; block[1][4][5] = 2; block[1][4][6] = 1;
	block[1][4][7] = 1; block[1][4][8] = 2; block[1][4][9] = 1; block[1][4][10]= 1; block[1][5][0] = 2;
	block[1][5][1] = 2; block[1][5][2] = 8; block[1][5][3] = 2; block[1][5][4] = 1; block[1][5][5] = 2;
	block[1][5][6] = 2; block[1][5][7] = 2; block[1][5][8] = 2; block[1][5][9] = 1; block[1][5][10]= 8;

	block[1][6][0] = 1;block[1][6][1] = 2;block[1][6][2] = 1;block[1][6][3] = 2;block[1][6][4] = 1;
	block[1][6][5] = 2;block[1][6][6] = 1;block[1][6][7] = 1;block[1][6][8] = 2;block[1][6][9] = 2;
	block[1][6][10]= 2;block[1][7][0] = 2;block[1][7][1] = 2;block[1][7][2] = 1;block[1][7][3] = 2;
	block[1][7][4] = 2;block[1][7][5] = 2;block[1][7][6] = 2;block[1][7][7] = 1;block[1][7][8] = 2;
	block[1][7][9] = 1;block[1][7][10]= 2;block[1][8][0] = 2;block[1][8][1] = 1;block[1][8][2] = 1;
	block[1][8][3] = 1;block[1][8][4] = 2;block[1][8][5] = 1;block[1][8][6] = 2;block[1][8][7] = 2;
	block[1][8][8] = 2;block[1][8][9] = 1;block[1][8][10]= 2;block[1][9][0] = 2;block[1][9][1] = 2;
	block[1][9][2] =64;block[1][9][3] = 2;block[1][9][4] = 2;block[1][9][5] = 1;block[1][9][6] = 1;
	block[1][9][7] = 1;block[1][9][8] = 2;block[1][9][9] = 2;block[1][9][10]= 2;block[1][1][0] = 2;

	vector=2;timer=0;q=0;firstplay=1;
	if(levelnum==1)
	{
		for(short i=0;i<4;i++)
			{o[i]=1;o1[i]=1;j1[i]=1;j[i]=1;h[i]=1;g[i]=1;
			ex[i]=250;ey[i]=200,espeed[i]=9;estart[i]=0;iseaten[i]=0;isescape[i]=0;}
		px=550;py=200;score[0]=0;
	}
	else
	{
		for(short i=0;i<4;i++)
			{o[i]=1;o1[i]=1;j1[i]=1;j[i]=1;h[i]=1;g[i]=1;
			ex[i]=150;ey[i]=100;espeed[i]=9;estart[i]=0;iseaten[i]=0;isescape[i]=0;}
		px=450;py=100;wx=200;wy=300;wv=3;score[1]=0;
	}


}
inline void value ()
{
	load = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/loading.png");
	title = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/menu.png");
	resume = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/resume.png");
	saveload = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/save.png");
	about = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/about.png");
	exitbot = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/exit.png");
	resumec = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/resumec.png");
	saveloadc = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/savec.png");
	aboutc = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/aboutc.png");
	exitc = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/menu/exitc.png");
	about_m = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/about-m.png");
	backbut = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/back.png");
	backbutc = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/backc.png");
	help = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/help.png");
	helpc = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/helpc.png");
	sound = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/sound.png");
	nosound = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/nosound.png");
	help_m = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/help-m.png");
	newgame = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/new.png");
	newgamec = ImgLoader("/home/alireza/workspace/Pacman/src/Image/menu/newc.png");
	loading[0] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead1.png" , 60 , 240 , 10);
	loading[1] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead2.png" , 60 , 240 , 10);
	loading[2] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead3.png" , 60 , 240 , 10);
	loading[3] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead4.png" , 60 , 240 , 10);
	loading[4] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead5.png" , 60 , 240 , 10);
	loading[5] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead6.png" , 60 , 240 , 10);
	loading[6] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead7.png" , 60 , 240 , 10);
	loading[7] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead8.png" , 60 , 240 , 10);
	loading[8] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead9.png" , 60 , 240 , 10);
	loading[9] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead10.png" , 60 , 240 , 10);
	loading[10] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/load/dead11.png" , 60 , 240 , 10);

	wall = ImgLoader("/home/alireza/workspace/Pacman/src/Image/block/wall.png");

	win = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/win.png");
	notbad = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/notbad.png");
	good = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/good.png");
	exelent = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/exelent.png");
	one = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/one.png");
	two = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/two.png");

	begin = LoadMusic("/home/alireza/workspace/Pacman/src/Sound/begin.wav");

	font = TTF_OpenFont("/home/alireza/workspace/Pacman/src/font/SHOWG.TTF" , 30);

	number[0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/3.png");
	number[1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/2.png");
	number[2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/1.png");
	number[3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/go.png");
	number[4] = ImgLoader("/home/alireza/workspace/Pacman/src/Image/block/empty.png");
	gameover = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/gameover.png");
	table = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/game/table.png");

	eframe[0][0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/b1-d.png", 60 , 240 , 10);
	eframe[0][0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/b2-d.png", 60 , 240 , 10);
	eframe[1][0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/g1-d.png", 60 , 240 , 10);
	eframe[1][0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/g2-d.png", 60 , 240 , 10);
	eframe[2][0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/p1-d.png", 60 , 240 , 10);
	eframe[2][0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/p2-d.png", 60 , 240 , 10);
	eframe[3][0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/r1-d.png", 60 , 240 , 10);
	eframe[3][0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/down/r2-d.png", 60 , 240 , 10);

	eframe[0][1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/b1-u.png", 60 , 240 , 10);
	eframe[0][1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/b2-u.png", 60 , 240 , 10);
	eframe[1][1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/g1-u.png", 60 , 240 , 10);
	eframe[1][1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/g2-u.png", 60 , 240 , 10);
	eframe[2][1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/p1-u.png", 60 , 240 , 10);
	eframe[2][1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/p2-u.png", 60 , 240 , 10);
	eframe[3][1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/r1-u.png", 60 , 240 , 10);
	eframe[3][1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/up/r2-u.png", 60 , 240 , 10);

	eframe[0][2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/b1-l.png", 60 , 240 , 10);
	eframe[0][2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/b2-l.png", 60 , 240 , 10);
	eframe[1][2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/g1-l.png", 60 , 240 , 10);
	eframe[1][2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/g2-l.png", 60 , 240 , 10);
	eframe[2][2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/p1-l.png", 60 , 240 , 10);
	eframe[2][2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/p2-l.png", 60 , 240 , 10);
	eframe[3][2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/r1-l.png", 60 , 240 , 10);
	eframe[3][2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/left/r2-l.png", 60 , 240 , 10);

	eframe[0][3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/b1-r.png", 60 , 240 , 10);
	eframe[0][3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/b2-r.png", 60 , 240 , 10);
	eframe[1][3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/g1-r.png", 60 , 240 , 10);
	eframe[1][3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/g2-r.png", 60 , 240 , 10);
	eframe[2][3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/p1-r.png", 60 , 240 , 10);
	eframe[2][3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/p2-r.png", 60 , 240 , 10);
	eframe[3][3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/r1-r.png", 60 , 240 , 10);
	eframe[3][3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/right/r2-r.png", 60 , 240 , 10);

	eframe[4][0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/b1-f.png",1,255,1);
	eframe[4][0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/b2-f.png",1,255,1);
	eframe[4][1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/g1-f.png",1,255,1);
	eframe[4][1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/g2-f.png",1,255,1);
	eframe[4][2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/p1-f.png",1,255,1);
	eframe[4][2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/p2-f.png",1,255,1);
	eframe[4][3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/r1-f.png",1,255,1);
	eframe[4][3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/fix/r2-f.png",1,255,1);

	escape[0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/down.png");
	escape[0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/down..png");
	escape[0][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/down...png");

	escape[1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/up.png");
	escape[1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/up..png");
	escape[1][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/up...png");

	escape[2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/left.png");
	escape[2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/left..png");
	escape[2][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/left...png");

	escape[3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/right.png");
	escape[3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/right..png");
	escape[3][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/right...png");

	escape[4][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/fix.png");
	escape[4][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/fix..png");
	escape[4][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/escape/fix...png");

	eye[0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/eye/eye-d.png");
	eye[1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/eye/eye-u.png");
	eye[2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/eye/eye-l.png");
	eye[3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/eye/eye-r.png");
	eye[4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/enemy/eye/eye-f.png");

	dead[0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r1.png");
	dead[0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r2.png");
	dead[0][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r3.png");
	dead[0][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r4.png");
	dead[0][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r5.png");
	dead[0][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r6.png");
	dead[0][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r7.png");
	dead[0][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r8.png");
	dead[0][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r9.png");
	dead[0][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r10.png");
	dead[0][10] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/down/r11.png");

	dead[1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r1.png");
	dead[1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r2.png");
	dead[1][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r3.png");
	dead[1][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r4.png");
	dead[1][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r5.png");
	dead[1][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r6.png");
	dead[1][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r7.png");
	dead[1][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r8.png");
	dead[1][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r9.png");
	dead[1][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r10.png");
	dead[1][10] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/up/r11.png");

	dead[2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r1.png");
	dead[2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r2.png");
	dead[2][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r3.png");
	dead[2][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r4.png");
	dead[2][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r5.png");
	dead[2][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r6.png");
	dead[2][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r7.png");
	dead[2][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r8.png");
	dead[2][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r9.png");
	dead[2][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r10.png");
	dead[2][10] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/left/r11.png");

	dead[3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r1.png");
	dead[3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r2.png");
	dead[3][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r3.png");
	dead[3][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r4.png");
	dead[3][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r6.png");
	dead[3][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r7.png");
	dead[3][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r8.png");
	dead[3][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r9.png");
	dead[3][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r10.png");
	dead[3][10] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/dead/right/r11.png");

	frame[0][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d1.png",1,255,1);
	frame[0][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d2.png",1,255,1);
	frame[0][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d3.png",1,255,1);
	frame[0][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d4.png",1,255,1);
	frame[0][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d5.png",1,255,1);
	frame[0][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d6.png",1,255,1);
	frame[0][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d7.png",1,255,1);
	frame[0][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d8.png",1,255,1);
	frame[0][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d9.png",1,255,1);
	frame[0][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/down/d10.png",1,255,1);

	frame[1][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u1.png",1,255,1);
	frame[1][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u2.png",1,255,1);
	frame[1][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u3.png",1,255,1);
	frame[1][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u4.png",1,255,1);
	frame[1][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u5.png",1,255,1);
	frame[1][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u6.png",1,255,1);
	frame[1][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u7.png",1,255,1);
	frame[1][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u8.png",1,255,1);
	frame[1][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u9.png",1,255,1);
	frame[1][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/up/u10.png",1,255,1);

	frame[2][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l1.png",1,255,1);
	frame[2][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l2.png",1,255,1);
	frame[2][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l3.png",1,255,1);
	frame[2][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l4.png",1,255,1);
	frame[2][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l5.png",1,255,1);
	frame[2][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l6.png",1,255,1);
	frame[2][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l7.png",1,255,1);
	frame[2][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l8.png",1,255,1);
	frame[2][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l9.png",1,255,1);
	frame[2][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/left/l10.png",1,255,1);

	frame[3][0] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r1.png",1,255,1);
	frame[3][1] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r2.png",1,255,1);
	frame[3][2] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r3.png",1,255,1);
	frame[3][3] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r4.png",1,255,1);
	frame[3][4] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r5.png",1,255,1);
	frame[3][5] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r6.png",1,255,1);
	frame[3][6] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r7.png",1,255,1);
	frame[3][7] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r8.png",1,255,1);
	frame[3][8] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r9.png",1,255,1);
	frame[3][9] = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/right/r10.png",1,255,1);

	empty = ImgLoader("/home/alireza/workspace/Pacman/src/Image/block/empty.png");
	smalldot = ImgLoader ( "/home/alireza/workspace/Pacman/src/Image/dot/dot-small.png", 60 , 240 , 10);
	bigdot = ImgLoader ( "/home/alireza/workspace/Pacman/src/Image/dot/dot-big.png" , 60 , 240 , 10);
	heart = ImgLoader ("/home/alireza/workspace/Pacman/src/Image/pacman/heart.png", 60 , 240 , 10);

}
bool wmove()
{
	if(wv==3)
		if(wy<350)
		{
			SDL_BlitSurface (empty , screen , wy , wx);
			SDL_BlitSurface (wall , screen , ++wy , wx);
			block[1][4][6]=1;
			if(wy<300)	block[1][4][5]=1;	else	block[1][4][5]=tmp4;
			if(wy==300) {block[1][4][5]=tmp4;tmp5=block[1][4][8];}
			if(block[1][4][5]==2)	SDL_BlitSurface (smalldot , screen , 250 , 200);
		}
		else
			wv=2;
	if(wv==2)
		if(wy>250)
		{
			SDL_BlitSurface (empty , screen , wy+50, wx);
			SDL_BlitSurface (wall , screen , --wy , wx);
			block[1][4][7]=1;
			if(wy>300)	block[1][4][8]=1;	else	block[1][4][8]=tmp5;
			if(wy==300) {block[1][4][8]=tmp5;tmp4=block[1][4][5];}
			if(block[1][4][8]==2)	SDL_BlitSurface (smalldot , screen , 250 , 200);
		}
		else
			wv=3;
}
bool pmove(short levelnum)
{
	short xmax,ymax;
	tmp2(xmax,ymax,levelnum);
	SDL_BlitSurface ( empty , screen , py, px );
	if( GetKey(SDLKey(SDLK_DOWN)) )
		if(block[levelnum-1][((px)/50)+1][(py/50)]!=1 && px<xmax && py%50==0)
		{
			vector = 0;
			if ( px%50==20 && block[levelnum-1][(px+30)/50][py/50] == 2)
			{
				score[levelnum-1]+=10;
				block[levelnum-1][(px+30)/50][py/50]=4;
				SDL_BlitSurface (empty , screen , py , px+30);
			}
			if ( px%50==10 && block[levelnum-1][(px+40)/50][py/50] == 8)
			{
				score[levelnum-1]+=20;
				block[levelnum-1][(px+40)/50][py/50]=4;
				SDL_BlitSurface (empty , screen , py , px+40);
				for(short eynum=0;eynum<4;eynum++)
				{isescape[eynum]= true;	espeed[eynum]=4;	escapetime[eynum]=0;}
			}
			px+=pspeed;
			SDL_BlitSurface ( frame[0][pframenum] , screen , py , ++px);
			return true;
		}
	if ( GetKey(SDLKey(SDLK_UP)) )
		if(block[levelnum-1][((px-1)/50)][(py/50)]!=1 && px>=1  && py%50==0)
		{
			vector = 1;
			if ( px%50==30 && block[levelnum-1][(px+-30)/50][py/50] == 2)
			{
				score[levelnum-1]+=10;
				block[levelnum-1][(px-30)/50][py/50]=4;
				SDL_BlitSurface (empty , screen , py , px-30);
			}
			if ( px%50==40 && block[levelnum-1][(px-40)/50][py/50] == 8)
			{
				score[levelnum-1]+=20;
				block[levelnum-1][(px-40)/50][py/50]=4;
				SDL_BlitSurface (empty , screen , py , px-40);
				for(short eynum=0;eynum<4;eynum++)
				{isescape[eynum]= true;	espeed[eynum]=4;	escapetime[eynum]=0;}
			}
			px-=pspeed;
			SDL_BlitSurface ( frame[1][pframenum] , screen , py , --px);
			return true;
		}
	if( GetKey(SDLKey(SDLK_LEFT)) )
		if(block[levelnum-1][(px/50)][((py-1)/50)]!=1 && py>0 && px%50 == 0)
		{
			vector = 2;
			if ( py%50==30 && block[levelnum-1][px/50][(py-30)/50] == 2)
			{
				score[levelnum-1]+=10;
				block[levelnum-1][px/50][(py-30)/50]=4;
				SDL_BlitSurface (empty , screen , py-30 , px);
			}
			if ( py%50==40 && block[levelnum-1][px/50][(py-40)/50] == 8)
			{
				score[levelnum-1]+=20;
				block[levelnum-1][px/50][(py-40)/50]=4;
				SDL_BlitSurface (empty , screen , py-40 , px);
				for(short eynum=0;eynum<4;eynum++)
				{isescape[eynum]= true;	espeed[eynum]=4;	escapetime[eynum]=0;}
			}
			py-=pspeed;
			SDL_BlitSurface ( frame[2][pframenum] , screen , --py , px);
			return true;
		}
	if ( GetKey(SDLKey(SDLK_RIGHT)) )
		if ( block[levelnum-1][(px/50)][((py)/50)+1]!=1 && py<ymax && px%50==0 )
		{
			vector = 3;
			if ( py%50==20 && block[levelnum-1][px/50][(py+30)/50] == 2)
			{
				score[levelnum-1]+=10;
				block[levelnum-1][px/50][(py+30)/50]=4;
				SDL_BlitSurface (empty , screen , py+30 , px);
			}
			if ( py%50==10 && block[levelnum-1][px/50][(py+40)/50] == 8)
			{
				score[levelnum-1]+=20;
				block[levelnum-1][px/50][(py+40)/50]=4;
				SDL_BlitSurface (empty , screen , py+40 , px);
				for(short eynum=0;eynum<4;eynum++)
				{isescape[eynum]= true;	espeed[eynum]=4;	escapetime[eynum]=0;}
			}
			py+=pspeed;
			SDL_BlitSurface ( frame[3][pframenum] , screen , ++py , px);
			return true;
		}
	if ( GetKey(SDLKey(SDLK_ESCAPE)) )
	{
		for(short i=0;i<4;i++)
			estart[i]=0;
		change=1;
		pauseexit=0;
		if(levelnum==1)
			level1exit=1;
		else
			level2exit=1;
		return false;
	}
	SDL_BlitSurface ( frame[vector][pframenum] , screen , py , px);
	change=0;
	return true;
}
bool emove(short eynum,short a,short levelnum)
{
	short xmax,ymax;
	tmp2(xmax,ymax,levelnum);
	SDL_BlitSurface ( empty , screen , ey[eynum], ex[eynum] );
	switch (a)
	{
		case 0:
		{
			if ( ex[eynum]<xmax && ey[eynum]%50==0&&(block[levelnum-1][(ex[eynum]/50)+1][ey[eynum]/50]!=1||ex[eynum]%50!=0))
			{
				if ( ex[eynum]%50==30 && block[levelnum-1][(ex[eynum]-30)/50][ey[eynum]/50]==2 )
					SDL_BlitSurface ( smalldot , screen , ey[eynum] , ex[eynum]-30);
				if ( ex[eynum]%50==40 && block[levelnum-1][(ex[eynum]-40)/50][ey[eynum]/50]==8 )
					SDL_BlitSurface ( bigdot , screen , ey[eynum] , ex[eynum]-40);
				if(isescape[eynum])
				{	if(escapetime[eynum]>104)
						{ex[eynum]+=4;SDL_BlitSurface(escape[0][eframenum+1],screen,ey[eynum],++ex[eynum]);}
					else
						{ex[eynum]+=4;SDL_BlitSurface(escape[0][eframenum],screen,ey[eynum],++ex[eynum]);}}
				else
					if(iseaten[eynum])
						{ex[eynum]+=9;SDL_BlitSurface(eye[0],screen,ey[eynum],++ex[eynum]);}
					else
						{ex[eynum]+=9;SDL_BlitSurface(eframe[eynum][a][eframenum],screen,ey[eynum],++ex[eynum]);}
				return true;
			}
			break;
		}
		case 1:
		{
			if(ey[eynum]%50==0 && ex[eynum]>0 && (ex[eynum]%50!=0||block[levelnum-1][(ex[eynum]/50)-1][ey[eynum]/50]!=1))
			{

				if ( ex[eynum]%50==20 && block[levelnum-1][(ex[eynum]+30)/50][ey[eynum]/50]==2  )
					SDL_BlitSurface ( smalldot , screen , ey[eynum] , ex[eynum]+30);
				if ( ex[eynum]%50==10 && block[levelnum-1][(ex[eynum]+40)/50][ey[eynum]/50]==8  )
					SDL_BlitSurface ( bigdot , screen , ey[eynum] , ex[eynum]+40);

				if(isescape[eynum])
				{	if(escapetime[eynum]>104)
						{ex[eynum]-=4;SDL_BlitSurface(escape[0][eframenum+1],screen,ey[eynum],--ex[eynum]);}
					else
						{ex[eynum]-=4;SDL_BlitSurface(escape[0][eframenum],screen,ey[eynum],--ex[eynum]);}}
				else
					if(iseaten[eynum])
						{ex[eynum]-=9;SDL_BlitSurface(eye[1],screen,ey[eynum],--ex[eynum]);}
					else
						{ex[eynum]-=9;SDL_BlitSurface(eframe[eynum][a][eframenum],screen,ey[eynum],--ex[eynum]);}
				return true;
			}
			break;
		}
		case 2:
		{
			if (ex[eynum]%50==0 && ey[eynum]>0 &&(ey[eynum]%50!=0||block[levelnum-1][(ex[eynum]/50)][(ey[eynum]/50)-1]!=1))
			{
				if ( ey[eynum]%50==20 && block[levelnum-1][ex[eynum]/50][(ey[eynum]+30)/50]== 2)
					SDL_BlitSurface ( smalldot , screen , ey[eynum]+30 , ex[eynum]);
				if ( ey[eynum]%50==10 && block[levelnum-1][ex[eynum]/50][(ey[eynum]+40)/50]== 8)
					SDL_BlitSurface ( bigdot , screen , ey[eynum]+40 , ex[eynum]);
				if(isescape[eynum])
				{	if(escapetime[eynum]>104)
						{ey[eynum]-=4;SDL_BlitSurface(escape[0][eframenum+1],screen,--ey[eynum],ex[eynum]);}
					else
						{ey[eynum]-=4;SDL_BlitSurface(escape[0][eframenum],screen,--ey[eynum],ex[eynum]);}}
				else
					if(iseaten[eynum])
						{ey[eynum]-=9;SDL_BlitSurface(eye[2],screen,--ey[eynum],ex[eynum]);}
					else
						{ey[eynum]-=9;SDL_BlitSurface(eframe[eynum][a][eframenum],screen,--ey[eynum],ex[eynum]);}
				return true;
			}
			break;
		}
		case 3:
		{
			if (ex[eynum]%50==0 && ey[eynum]<ymax&&(ey[eynum]%50!=0||block[levelnum-1][(ex[eynum]/50)][(ey[eynum]/50)+1]!=1))
			{
				if ( ey[eynum]%50==30 && block[levelnum-1][ex[eynum]/50][(ey[eynum]-30)/50]==2)
					SDL_BlitSurface ( smalldot , screen , ey[eynum]-30 , ex[eynum]);
				if ( ey[eynum]%50==40 && block[levelnum-1][ex[eynum]/50][(ey[eynum]-40)/50]==8)
					SDL_BlitSurface ( bigdot , screen , ey[eynum]-40 , ex[eynum]);
				if(isescape[eynum])
				{	if(escapetime[eynum]>104)
						{ey[eynum]+=4;SDL_BlitSurface(escape[0][eframenum+1],screen,++ey[eynum],ex[eynum]);}
					else
						{ey[eynum]+=4;SDL_BlitSurface(escape[0][eframenum],screen,++ey[eynum],ex[eynum]);}}
				else
					if(iseaten[eynum])
						{ey[eynum]+=9;SDL_BlitSurface(eye[3],screen,++ey[eynum],ex[eynum]);}
					else
						{ey[eynum]+=9;SDL_BlitSurface(eframe[eynum][a][eframenum],screen,++ey[eynum],ex[eynum]);}
				return true;
			}
			break;
		}
	}
	if(isescape[eynum])
		SDL_BlitSurface ( escape[4][eframenum] , screen , ey[eynum] , ex[eynum]);
	else
		SDL_BlitSurface ( eframe[4][eynum][eframenum] , screen , ey[eynum] , ex[eynum]);
	return false;
}
bool follow_escape(short eynum,short a[4][10],short xtarget,short ytarget,short levelnum)
{
	if(estart[eynum])
	{
	if(iseaten[eynum]&&ex[eynum]>199&&ey[eynum]==200&&ex[eynum]<241&&levelnum==1)
	{
		SDL_BlitSurface(empty,screen,ey[eynum],ex[eynum]);
		ex[eynum]+=9;
		SDL_BlitSurface(eye[0],screen,ey[eynum],ex[eynum]++);
		return true;
	}
	if(iseaten[eynum]&&ex[eynum]==250&&ey[eynum]==200&&levelnum==1)
		iseaten[eynum]=0;
	if (!iseaten[eynum]&&ey[eynum]==200 && ex[eynum]<251 && ex[eynum]>200&&levelnum==1)
		{emove(eynum,1,levelnum);return true;}

	if(iseaten[eynum]&&ex[eynum]>99&&ey[eynum]==100&&ex[eynum]<141&&levelnum==2)
		{
			SDL_BlitSurface(empty,screen,ey[eynum],ex[eynum]);
			ex[eynum]+=9;
			SDL_BlitSurface(eye[0],screen,ey[eynum],ex[eynum]++);
			return true;
		}
		if(iseaten[eynum]&&ex[eynum]==150&&ey[eynum]==100&&levelnum==2)
			iseaten[eynum]=0;
		if (!iseaten[eynum]&&ey[eynum]==100 && ex[eynum]<151 && ex[eynum]>100&&levelnum==2)
			{emove(eynum,1,levelnum);return true;}
	if (xtarget>ex[eynum] && j[eynum] && j1[eynum])
	{
		if ( emove(eynum,isescape[eynum],levelnum) )
			h[eynum]=1;
		else
			if ( (h[eynum] && !emove(eynum,a[eynum][0],levelnum) ) || !h[eynum] )
			{
				h[eynum]=0;
				emove(eynum,a[eynum][1],levelnum);
			}
		return true;
	}
	else
		if (xtarget<ex[eynum] && j[eynum] && j1[eynum])
		{
			if ( emove(eynum,!isescape[eynum],levelnum) )
				g[eynum]=1;
			else
				if ( (g[eynum] && !emove(eynum,a[eynum][2],levelnum) ) || !g[eynum] )
				{
					g[eynum]=0;
					emove(eynum,a[eynum][3],levelnum);
				}
			return true;
		}
		else
				if(ytarget<ey[eynum])
				{
					if( o1[eynum] && emove(eynum,tmp(eynum,a,2),levelnum) )
						{ j1[eynum]=1;return true;}
					else
						{
							if(a[eynum][0]==tmp(eynum,a,2))
							{	if(emove(eynum,1,levelnum))
									{j1[eynum]=0;o1[eynum]=1;return true;}
								else
									{o1[eynum]=0;emove(eynum,5-tmp(eynum,a,2),levelnum);return true;}
							}
							else
							{	if(emove(eynum,0,levelnum))
									{j1[eynum]=0;o1[eynum]=1;return true;}
								else
									{o1[eynum]=0;emove(eynum,5-tmp(eynum,a,2),levelnum);return true;}
							}
						}
				}
				else
					if (ytarget>ey[eynum])
					{
						if( o[eynum] && emove(eynum,tmp(eynum,a,3),levelnum) )
						{ j[eynum]=1;return true;}
						else
						{
							if(a[eynum][0]==tmp(eynum,a,3))
							{	if(emove(eynum,1,levelnum))
									{j[eynum]=0;o[eynum]=1;return true;}
								else
								{o[eynum]=0;emove(eynum,5-tmp(eynum,a,3),levelnum);return true;}

							}
							else
							{	if(emove(eynum,0,levelnum))
									{j[eynum]=0;o[eynum]=1;return true;}
								else
									{o[eynum]=0;emove(eynum,5-tmp(eynum,a,3),levelnum);return true;}
							}
						}
					}
	}
}
void wingame()
{
	SDL_FillRect(screen,NULL,BLACK);
	SDL_BlitSurface(win,screen,0,0);
	sprintf(buffer_score,"%d",score[0]);
	text_score=TTF_RenderText_Solid (font,buffer_score,255,255,255);
	SDL_BlitSurface(text_score,screen,475,230);
	sprintf(buffer_score,"%d",score[1]);
	text_score=TTF_RenderText_Solid (font,buffer_score,255,255,255);
	SDL_BlitSurface(text_score,screen,475,295);
	sprintf(buffer_score,"%d",score[1]+score[0]);
	text_score=TTF_RenderText_Solid (font,buffer_score,255,255,255);
	SDL_BlitSurface(text_score,screen,475,360);
	if(score[1]+score[0]>1430)
		if(score[1]+score[0]<1950)
			SDL_BlitSurface(good,screen,250,410);
		else
			SDL_BlitSurface(exelent,screen,250,410);
	else
		SDL_BlitSurface(notbad,screen,250,410);
	SDL_Flip(screen);
	SDL_Delay(10000);
	gameexit=1;
}
bool managegame (short a[4][10],short levelnum)
{
	bool s=1;
	short ix,jy;
	tmp3(ix,jy,levelnum);
	if(timer==0&&lifenum!=0)
	for(short i=0;i<5;i++)
	{
		SDL_BlitSurface(number[i],screen,jy,ix);
		SDL_Flip(screen);
		if(i!=4)	SDL_Delay(750);
	}
	if(lifenum==0)
	{
		blockvalue(levelnum);
		levelnum=1;change=1;
		SDL_FillRect(screen,NULL,BLACK);
		SDL_BlitSurface(gameover,screen,0,0);
		level1exit=1; menuexit=0; lifenum=3;level2exit=1;
		SDL_Flip(screen);
		SDL_Delay(3000);
		return true;
	}
	tmp1(ix,jy,levelnum);
	if ((timer++) %70 == 0 && q<4)
		estart[q++]= 1;
	for(short i=0;i<ix;i++)
		for(short j=0;j<jy;j++)
			if(block[levelnum-1][i][j]==2 || block[levelnum-1][i][j]==8)
				{s=0;break;}
	if(s)
		if(levelnum==1)
		{
			level1exit=1;level2exit=0;firstenter[1]=1;change=1;
			SDL_FillRect(screen , NULL , BLACK);
			SDL_BlitSurface(load , screen , 0 , 0);
			for(int j = 0 ; j < 2 ; j++)
				for(int i = 10 ; i >= 0 ; i--)
				{
					SDL_BlitSurface(empty , screen , 670 , 470);
					SDL_BlitSurface(loading[i] , screen , 670 , 470);
					SDL_Flip(screen);
					SDL_Delay(200);
				}
		}
		else
			wingame();

	if ( ex[0]-ex[2]<50 && ex[0]-ey[2]>-50 && ey[0]-ey[2]<50 && ey[0]-ey[2]>-50 ){
		estart[0] = 0;
		estart[2] = 0;}


	for(short eynum=0; eynum<4; eynum++)
	{
		if ( px-wx<50 && px-wx>-50 && py-wy<50 && py-wy>-50 )
		{
			lifenum--;
			for(short i=0;i<4;i++)
			{
				SDL_BlitSurface (empty,screen,ey[i],ex[i]);
				if(block[levelnum-1][ex[i]/50][ey[i]/50]==2)
					SDL_BlitSurface(smalldot,screen,ey[i],ex[i]);
				if(block[levelnum-1][ex[i]/50][ey[i]/50]==8)
					SDL_BlitSurface(bigdot,screen,ey[i],ex[i]);
				isescape[i]=0;	iseaten[i]=0; estart[i]=0;
				if(levelnum==1)
					{ex[i]=250; ey[i]=200;}
				else
					{ex[i]=150; ey[i]=100;}
			}
			if(pframenum>5)
				pframenum=10-pframenum;
			for(short i=pframenum;i<11;i++)
			{
				SDL_BlitSurface(dead[vector][i],screen,py,px);
				SDL_Flip(screen);
				SDL_Delay(150);
			}
			SDL_BlitSurface (empty,screen,py,px);
			timer=0;	q=0; vector=2;
			if(levelnum==1)
				{px=550;py=200;}
			else
				{px=450;py=100;}
		}
		if( estart[eynum] )
		{
			if(!iseaten[eynum])
			{
				if ( px-ex[eynum]<50 && px-ex[eynum]>-50 && py-ey[eynum]<50 && py-ey[eynum]>-50 )
				{	if ( isescape[eynum] )
					{
						enemyscore *=2; score[levelnum-1]+=enemyscore;
						isescape[eynum]=0;	iseaten[eynum]=1;
						if(ex[eynum]%10!=0)
							ex[eynum]+=5;
						if(ey[eynum]%10!=0)
							ey[eynum]+=5;
					}
					else
					{	lifenum--;
						for(short i=0;i<4;i++)
						{
							SDL_BlitSurface (empty,screen,ey[i],ex[i]);
							if(block[levelnum-1][ex[i]/50][ey[i]/50]==2)
								SDL_BlitSurface(smalldot,screen,ey[i],ex[i]);
							if(block[levelnum-1][ex[i]/50][ey[i]/50]==8)
								SDL_BlitSurface(bigdot,screen,ey[i],ex[i]);
							isescape[i]=0;	iseaten[i]=0; estart[i]=0;
							if(levelnum==1)
								{ex[i]=250; ey[i]=200;}
							else
								{ex[i]=150; ey[i]=100;}
						}
						if(pframenum>5)
							pframenum=10-pframenum;
						for(short i=pframenum;i<11;i++)
						{
							SDL_BlitSurface(dead[vector][i],screen,py,px);
							SDL_Flip(screen);
							SDL_Delay(150);
						}
						SDL_BlitSurface (empty,screen,py,px);
						timer=0;	q=0; vector=2;
						if(levelnum==1)
							{px=550;py=200;}
						else
							{px=450;py=100;}
				}	}
		}	}
		if (isescape[eynum])
		{
			escapetime[eynum]++;
			if( escapetime[eynum]>130 )
			{
				enemyscore=50;
				isescape[eynum]=false;
				if(ex[eynum]%10!=0)
					ex[eynum]+=5;
				if(ey[eynum]%10!=0)
					ey[eynum]+=5;
			}
		}
	}
}
void level (short levelnum)
{
	leveln=levelnum;
	short ix,jy;
	tmp3(ix,jy,levelnum);
	if(firstenter[levelnum-1]==1)
	{	blockvalue(levelnum); firstenter[levelnum-1]=0;}
	if(change)
		gamedraw(levelnum);
	if(levelnum==2)
		wmove();
	pmove(levelnum);
	for(short eynum=0;eynum< 4;eynum++)
		if(iseaten[eynum])
			{follow_escape(eynum,a,jy,ix-50,levelnum);}
		else
			{follow_escape(eynum,a,px,py,levelnum);}
	managegame(a,levelnum);
	tnx_milad_ehsan_mamali(levelnum);
	if(ready)
	{
		for(short i=0;i<5;i++)
		{
			SDL_BlitSurface(number[i],screen,200,250);
			SDL_Flip(screen);
			if(i!=4)	SDL_Delay(750);
		}
		ready=0;
	}
}

int main()
{
	InitEngine(screen);
	value();
	PlayMusic (begin,-1);
	SDL_Surface* textscore;
	short a[4][10]={	{2,3,3,2,2,3},{2,3,3,2,3,2},{3,2,2,3,2,3},{3,2,2,3,3,2}	};
	gamedraw(2);
	while(!gameexit)
	{
	/*	for(int i = 0 ; i < 4 ; i++)
			for(int j = 0 ; j < 4 ; j++)
			{
				if(ex[i] == ex[j] && ey [i])

			}*/
		eframenum++;
		eframenum%=2;
		pframenum++;
		pframenum%=10;
		Update();
		if(!menuexit)
			menu();
		if(!pauseexit)
			pause(leveln);
		if(!level1exit)
			level(1);
		if(!level2exit)
			level(2);
		SDL_Flip(screen);
		SDL_Delay(50);
	}
	return 0;
}
