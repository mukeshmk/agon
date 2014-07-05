//HEADER FILES
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
#include<process.h>

//FUNCTIONS
void dice();
void hexagon(int,int);
void draw();
void position(int*,int*);
int winchk(int);
void modi(int);
void poschag();

//GLOBAL VARIABLES
const int plyr[2]={1,2};
char nm[2][30];
int poly[14],rw1,cl1,rw2,cl2,ply=1;

			//red   Player:-1
			//green Player:-2
int p1rw[7]={0,0,4,4,8,9,10},p1cl[7]={0,4,0,9,7,0,3};
int p2rw[7]={0,1,2,6,6,10,10},p2cl[7]={2,6,0,0,9,1,5};

//representation of the inital board positions in a variable
int pos[11][11]={
	/* 0 */ {	11,0,2,0,1,0, 	  -1,-1,-1,-1,-1},
	/* 1 */	{      0,0,0,0,0,0,2,	  -1,-1,-1,-1},
	/* 2 */	{     2,0,0,0,0,0,0,0,	  -1,-1,-1},
	/* 3 */	{    0,0,0,0,0,0,0,0,0,	  -1,-1},
	/* 4 */	{   1,0,0,0,0,0,0,0,0,1,  -1},
	/* 5 */	{  0,0,0,0,0,0,0,0,0,0,0    },
	/* 6 */	{   2,0,0,0,0,0,0,0,0,2,  -1},
	/* 7 */	{    0,0,0,0,0,0,0,0,0,	  -1,-1},
	/* 8 */	{     0,0,0,0,0,0,0,1,	  -1,-1,-1},
	/* 9 */ {      1,0,0,0,0,0,0,	  -1,-1,-1,-1},
	/* 10*/ {	0,2,0,1,0,22,	  -1,-1,-1,-1,-1}};


//MAIN FUNCTION
void main()
{
	clrscr();
	int count=0,chk;
	dice();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	draw();
	modi(1);
	char ch;
	do
	{
		draw();
		modi(1);
		if(count%2==0)
		{
			gotoxy(0,0);
			cout<<"player 1"<<endl;
		}
		else
		{
			gotoxy(0,0);
			cout<<"player 2"<<endl;
		}
		cout<<"enter r and c to move from"<<endl;
		cin>>rw1>>cl1;
		cout<<"enter r and c to move to"<<endl;
		cin>>rw2>>cl2;
		poschag();
		chk=winchk(ply);
		if(chk==1)
		{
			if(count%2==0)
				cout<<nm[0]<<"has WON the game"<<endl;
			else
				cout<<nm[0]<<"has WON the game"<<endl;
			delay(800);
			exit(0);
		}
		cout<<"do u want to continue"<<endl;
		cin>>ch;
//		cleardevice();
		clearviewport();
		count++;
	 }while(ch=='y');
	getch();
}

//DICE ROLLING FUNCTION
void dice()
{
	int i,ran[2];
	randomize();
	cout<<"enter the player 1's name:"<<endl;
	cin.getline(nm[0],30);
	cout<<"enter the player 2's name:"<<endl;
	cin.getline(nm[1],30);
start:	for(i=0;i<2;++i)
	{
		cout<<endl<<nm[i]<<endl
		    <<"the dice is being rolled"<<endl
		    <<"and the no obtained is"<<endl;
		delay(700);
		ran[i]=(random(6)+1);
		cout<<ran[i]<<endl;
		delay(700);
	}
	if(ran[0]==ran[1])
	{
		cout<<"both players have got the same"<<endl
		    <<"number on the dice, so rolling again"<<endl;
		delay(700);
		goto start;
	}
	if(ran[0]>ran[1])
		cout<<endl<<nm[0]<<" wins the first chance"<<endl;
	else
		cout<<endl<<nm[1]<<" wins the first chance"<<endl;
	getch();
}

//DRAW FUNCTION
void draw()
{
	int i,j,n=6,x=460,y=10;

	setbkcolor(0);
	setfillstyle(1,8);
	for(j=0,y;j<6;++j,++n)
	{
		for(i=0;i<n;x+=20,++i)
		{
			hexagon(x,y);
			fillpoly(7,poly);
		}
		x=x-10-20*n;
		y+=20;
	}
	x+=20;
	n=n-2;
	for(j=0;j<5;++j,--n)
	{
		for(i=0;i<n;x+=20,++i)
		{
			hexagon(x,y);
			fillpoly(7,poly);
		}
		x=x+10-20*n;
		y+=20;
	}

	getch();
}

//HEXAGON FUNCTION
void hexagon (int x, int y)
{
	poly[0]=x+10;
	poly[1]=y;
	poly[2]=x+20;
	poly[3]=y+10;
	poly[4]=x+20;
	poly[5]=y+20;
	poly[6]=x+10;
	poly[7]=y+30;
	poly[8]=x;
	poly[9]=y+20;
	poly[10]=x;
	poly[11]=y+10;
	poly[12]=x+10;
	poly[13]=y;
}

//POSTION MODIFICATION FUNCTION
void modi(int z=1)
{
	int prw[7],pcl[7];
	for(int j=0;j<2;++j)
	{
		for(int k=0;k<7;++k)
			if(plyr[j]==1&&ply==1)
			{
				setfillstyle(1,4);
				prw[k]=p1rw[k];
				pcl[k]=p1cl[k];
			}
			else
			{
				setfillstyle(1,2);
				prw[k]=p2rw[k];
				pcl[k]=p2cl[k];
			}
		if(z==1)
			position(prw,pcl);
		for(int a=0;a<=rw1;++a)
			if(prw[a]==rw1&&pcl[a]==cl1)
				if(j==0)
				{
					p1rw[a]=rw2;
					p1cl[a]=cl2;
				}
				else if(j==1)
				{
					p2rw[a]=rw2;
					p2cl[a]=cl2;
				}
	      }
}

//POSITION PRINTING FUNTION
void position(int*prw,int*pcl)
{
	int x=460,y=10,r=5,X,Y;
	for(int i=0;i<7;++i)
	if(prw[i]<=5)
	{
		X=x+10*(2*pcl[i]+1)-10*prw[i];
		Y=y+15+20*prw[i];
		fillellipse(X,Y,r,r);
	}
	else if(prw[i]>5)
	{
		int re;
		re=prw[i]-6;
		X=x+10*(2*pcl[i]+1)-10*prw[i]+20*(re+1);
		Y=y+135+20*re;
		fillellipse(X,Y,r,r);
	}
}

//POISTION CHANGING FUNCTION
void poschag()
{
	int a,b,i,j,x=460,y=10,r=5,X,Y,flag=0;
	if(ply==1)
	{
		a=11;
		b=1;
	}
	else
	{
		a=22;
		b=2;
	}
	if((pos[rw1][cl1]==b||pos[rw1][cl1]==a)&&pos[rw2][cl2]==0)
	{
		if(pos[rw1][cl1]==b)
			flag=1;
		if(pos[rw1][cl1]==a)
			flag=11;
		setcolor(8);
		setfillstyle(1,8);

		if(rw1<=5)
			if(cl1<=(rw1+1))
			{
				X=x+10*(2*cl1+1)-10*rw1;
				Y=y+15+20*rw1;
				fillellipse(X,Y,r,r);
			}
		if(rw1>5)
		{
			int re;
			re=rw1-6;
			X=x+10*(2*cl1+1)-10*rw1+20*(re+1);
			Y=y+135+20*re;
			fillellipse(X,Y,r,r);
		}
		setcolor(15);
		if(ply==1)
			setfillstyle(1,4);
		else
			setfillstyle(1,2);
		if(rw2<=5)
			if(cl2<=(rw2+1))
			{
				X=x+10*(2*cl2+1)-10*rw2;
				Y=y+15+20*rw2;
				fillellipse(X,Y,r,r);
			}
		if(rw2>5)
		{
			int re;
			re=rw2-6;
			X=x+10*(2*cl2+1)-10*rw2+20*(re+1);
			Y=y+135+(20*re);
			fillellipse(X,Y,r,r);
		}
		pos[rw1][cl1]=0;
		pos[rw2][cl2]=flag;
		modi(0);
	}
	else
		cout<<"illegal move"<<endl;
}

//WIN CHECKING FUNCTION
int winchk(int ply)
{
	int x,y;
	if(ply==1)
	{
		x=11;
		y=1;
	}
	else
	{
		x=22;
		y=2;
	}
	if(pos[5][5]==x&&pos[4][4]==y&&pos[4][5]==y&&pos[5][4]==y&&pos[5][6]==y&&pos[6][4]==y&&pos[6][5]==y)
		return(1);
	else
		return(0);
}