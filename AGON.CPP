//HEADER FILES
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
#include<process.h>

//FUNCTIONS USED
void rules();			//FUNCTION TO DISPLAY RULES OF THE GAME
void dice();                    //FUNCTION FOR ROLLING THE DICE
void hexagon(int,int);          //FUNCTION TO CHANGE THE COORDINATES
void draw();                    //FUNCTION TO DRAW THE HEXAGON
void position(int*,int*);       //FUNCTION TO PRINT THE POSITIONS
int winchk(int);                //FUNCTION TO CHECK FOR WIN
int capchk();                   //FUNCTION TO CHECK FOR CAPTURE
void modi(int);                 //FUNCTION FOR POSTION MODIFICATION
void poschag(int);              //FUNCTION FOR POISTION CHANGING
int moves();			//FUNCTION TO CHECK FOR CORRECT MOVES

//GLOBAL VARIABLES
const int plyr[2]={1,2};
char nm[2][30];
int poly[14],rw1,cl1,rw2,cl2,ply=1;

		//Red   Player:-1 Green Player:-2
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
	int count=0,chk,mov,cap;
/*	rules();
	clrscr();
	dice();
*/	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	char ch;
	do
	{
		draw();
		modi(1);
		if(count%2==0)
		{
			cout<<"player 1"<<endl;
			ply=1;
		}
		else
		{
			cout<<"player 2"<<endl;
			ply=2;
		}
		cout<<"enter r and c to \"move from\""<<endl;
		cin>>rw1>>cl1;
again:		cout<<"enter r and c to \"move to\""<<endl;
		cin>>rw2>>cl2;
/*		mov=moves();
		if(mov==0)
		{
			cout<<"\"illegal move\" you can only move"<<endl
			    <<"one step at a time"<<endl;
			goto again;
		}
*/		poschag(1);
/*		cap=capchk();
		if(cap==1)
		{
			cout<<"your queen has been captured"<<endl;
			cout<<"your queen will be moved by your opponent"<<endl;
			poschag(0);
		}
		else if(cap==2)
		{
			cout<<"your guard has been captured"<<endl;
			cout<<"your guard will be moved by you"<<endl;
			poschag(0);
		}
*/		chk=winchk(ply);
		if(chk==1)
		{
			if(count%2==0)
				cout<<nm[0]<<" has WON the game"<<endl;
			else
				cout<<nm[0]<<" has WON the game"<<endl;
			delay(800);
			exit(0);
		}
		cout<<"do u want to continue"<<endl;
		cin>>ch;
		clearviewport();
		count++;
	 }while(ch=='y');
	getch();
}

//FUNCTION TO DISPLAY RULES OF THE GAME
void rules()
{
	cout<<endl<<"\t\t\t\"RULES\""<<endl<<endl
	    <<"Each player has one Queen and six Guards"<<endl
	    <<"which are placed on the outer ring of the board"<<endl<<endl
	    <<"The goal of each player is to put the Queen on the center"<<endl
	    <<"and surround her with her Guards"<<endl<<endl
	    <<"The first player being selected by the throw of a die"<<endl<<endl
	    <<"Pieces can only be moved one cell forwards or sideways"<<endl
	    <<"they cannot be moved back away from the center of the board"<<endl
	    <<"Only a Queen may move onto the centre cell"<<endl<<endl
	    <<"If you try to move your oppnents piece you wil loose your turn"<<endl<<endl
	    <<"If a Guard is trapped between two opposing pieces,"<<endl
	    <<"the owner of the captured Guard must move it"<<endl
	    <<"to any cell of his own choosing on the outermost ring"<<endl<<endl
	    <<"If a Queen is trapped between two opposing pieces"<<endl
	    <<"the owner of a captured Queen must move it to any cell"<<endl
	    <<"of his opponent's choosing"<<endl;
	getch();

}

//FUNCTION FOR ROLLING THE DICE
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
	cout<<"You are the first Player"<<endl
	    <<"your conis are the red once"<<endl;
	getch();
}

//FUNCTION TO DRAW THE HEXAGON
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

//FUNCTION TO CHANGE THE COORDINATES
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

//FUNCTION FOR POSTION MODIFICATION
void modi(int z)
{
	int prw[7],pcl[7];
	for(int j=0;j<2;++j)
	{
		for(int k=0;k<7;++k)
			if(plyr[j]==1)
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
				if(j==0&&ply==1)
				{
					p1rw[a]=rw2;
					p1cl[a]=cl2;
				}
				else if(j==1&&ply==2)
				{
					p2rw[a]=rw2;
					p2cl[a]=cl2;
				}
	}
}

//FUNCTION TO PRINT THE POSITIONS
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

//FUNCTION FOR POISTION CHANGING
void poschag(int z)
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
	if(z==0)
	{
		cout<<"enter r and c to move the captured peice too"<<endl;
		cin>>rw2>>cl2;
	}
	if((pos[rw1][cl1]==a||pos[rw1][cl1]==b)&&pos[rw2][cl2]==0)
	{
		if(pos[rw1][cl1]==b)
			flag=1;
		if(pos[rw1][cl1]==a)
			flag=11;
//		To errase the circle
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
//		To make the new circle
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

//FUNCTION TO CHECK FOR WIN
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

//FUNCTION TO CHECK FOR CAPTURE
int capchk()
{
	int a1,b1,b2,x=rw2,y=cl2,flag;
	if(ply==1)
	{
		a1=11;
		b1=1;
		b2=2;

	}
	else
	{
		a1=22;
		b1=2;
		b2=1;
	}
	if(x<=5)
	{
/*Center up  */	if((pos[x][y]==a1||pos[x][y]==b1)&&(pos[x-1][y]==b2||pos[x][y+1]==b2||pos[x+1][y+1]==b2)&&(pos[x-1][y-1]==b2||pos[x][y-1]==b2||pos[x+1][y]==b2))
		{       cout<<"1"<<endl;
			if(pos[x][y]==a1)
				return(1);
			else if(pos[x][y]==b1)
				return(2);
		}
/*Corner up 1*/	else if((pos[x-1][y]==a1||pos[x-1][y]==b1)&&(pos[x-2][y]==b2||pos[x-1][y+1]==b2||pos[x][y+1]==b2)&&(pos[x-2][y-1]==b2||pos[x-1][y-1]==b2||pos[x][y]==b2))
		{       cout<<"2"<<endl;
			rw1=x-1;
			cl1=y;
			if(pos[x-1][y]==a1)
				return(1);
			else if(pos[x-1][y]==b1)
				return(2);
		}
/*Corner up 2*/	else if((pos[x-1][y-1]==a1||pos[x-1][y-1]==b1)&&(pos[x-2][y-1]==b2||pos[x-1][y]==b2||pos[x][y]==b2)&&(pos[x-2][y-2]==b2||pos[x-1][y-2]==b2||pos[x][y-1]==b2))
		{       cout<<"3"<<endl;
			rw1=x-1;
			cl1=y-1;
			if(pos[x-1][y-1]==a1)
				return(1);
			else if(pos[x-1][y-1]==b1)
				return(2);
		}
/*Corner up 3*/	else if((pos[x][y-1]==a1||pos[x][y-1]==b1)&&(pos[x-1][y-1]==b2||pos[x][y]==b2||pos[x+1][y]==b2)&&(pos[x-1][y-2]==b2||pos[x][y-2]==b2||pos[x+1][y-1]==b2))
		{       cout<<"4"<<endl;
			rw1=x;
			cl1=y-1;
			if(pos[x][y-1]==a1)
				return(1);
			else if(pos[x][y-1]==b1)
				return(2);
		}
/*Corner up 4*/	else if((pos[x+1][y]==a1||pos[x+1][y]==b1)&&(pos[x][y]==b2||pos[x+1][y+1]==b2||pos[x+2][y+1]==b2)&&(pos[x][y-1]==b2||pos[x+1][y-1]==b2||pos[x+2][y]==b2))
		{       cout<<"5"<<endl;
			rw1=x+1;
			cl1=y;
			if(pos[x+1][y]==a1)
				return(1);
			else if(pos[x+1][y]==b1)
				return(2);
		}
/*Corner up 5*/	else if((pos[x+1][y+1]==a1||pos[x+1][y+1]==b1)&&(pos[x][y+1]==b2||pos[x+1][y+2]==b2||pos[x+2][y+2]==b2)&&(pos[x][y]==b2||pos[x+1][y]==b2||pos[x+2][y]==b2))
		{       cout<<"6"<<endl;
			rw1=x+1;
			cl1=y+1;
			if(pos[x+1][y+1]==a1)
				return(1);
			else if(pos[x+1][y+1]==b1)
				return(2);
		}
/*Corner up 6*/	else if((pos[x][y+1]==a1||pos[x][y+1]==b1)&&(pos[x-1][y+1]==b2||pos[x][y+2]==b2||pos[x+1][y+2]==b2)&&(pos[x-1][y]==b2||pos[x][y]==b2||pos[x+1][y+1]==b2))
		{       cout<<"7"<<endl;
			rw1=x;
			cl1=y+1;
			if(pos[x][y+1]==a1)
				return(1);
			else if(pos[x][y+1]==b1)
				return(2);
		}
	}
	else
	{
/*Center down*/	if((pos[x][y]==a1||pos[x][y]==b1)&&(pos[x-1][y+1]==b2||pos[x][y+1]==b2||pos[x+1][y]==b2)&&(pos[x-1][y]==b2||pos[x][y-1]==b2||pos[x+1][y-1]==b2))
		{       cout<<"8"<<endl;
			rw1=x;
			cl1=y;
			if(pos[x][y]==a1)
				return(1);
			else if(pos[x][y]==b1)
				return(2);
		}
/*Corner down1*/else if((pos[x-1][y+1]==a1||pos[x-1][y+1]==b1)&&(pos[x-2][y+2]==b2||pos[x-1][y+2]==b2||pos[x][y+1]==b2)&&(pos[x-2][y+1]==b2||pos[x-1][y]==b2||pos[x][y]==b2))
		{       cout<<"9"<<endl;
			rw1=x-1;
			cl1=y+1;
			if(pos[x-1][y+1]==a1)
				return(1);
			else if(pos[x-1][y+1]==b1)
				return(2);
		}
/*Corner down2*/else if((pos[x][y+1]==a1||pos[x][y+1]==b1)&&(pos[x-1][y+2]==b2||pos[x][y+2]==b2||pos[x+1][y+1]==b2)&&(pos[x-1][y+1]==b2||pos[x][y]==b2||pos[x+1][y]==b2))
		{       cout<<"10"<<endl;
			rw1=x;
			cl1=y+1;
			if(pos[x][y+1]==a1)
				return(1);
			else if(pos[x][y+1]==b1)
				return(2);
		}
/*Corner down3*/else if((pos[x+1][y]==a1||pos[x+1][y]==b1)&&(pos[x][y+1]==b2||pos[x+1][y+1]==b2||pos[x+2][y]==b2)&&(pos[x][y]==b2||pos[x+1][y-1]==b2||pos[x+2][y-1]==b2))
		{       cout<<"11"<<endl;
			rw1=x+1;
			cl1=y;
			if(pos[x+1][y]==a1)
				return(1);
			else if(pos[x+1][y]==b1)
				return(2);
		}
/*Corner down4*/else if((pos[x+1][y-1]==a1||pos[x+1][y-1]==b1)&&(pos[x][y]==b2||pos[x+1][y]==b2||pos[x+2][y-1]==b2)&&(pos[x][y-1]==b2||pos[x-1][y-2]==b2||pos[x+2][y-2]==b2))
		{       cout<<"13"<<endl;
			rw1=x+1;
			cl1=y-1;
			if(pos[x+1][y-1]==a1)
				return(1);
			else if(pos[x+1][y-1]==b1)
				return(2);
		}
/*Corner down5*/else if((pos[x][y-1]==a1||pos[x][y-1]==b1)&&(pos[x-1][y]==b2||pos[x][y]==b2||pos[x+1][y-1]==b2)&&(pos[x-1][y-1]==b2||pos[x][y-2]==b2||pos[x-1][y-2]==b2))
		{       cout<<"14"<<endl;
			rw1=x;
			cl1=y-1;
			if(pos[x][y-1]==a1)
				return(1);
			else if(pos[x][y-1]==b1)
				return(2);
		}
/*Corner down6*/else if((pos[x-1][y]==a1||pos[x-1][y]==b1)&&(pos[x-2][y+1]==b2||pos[x-1][y+1]==b2||pos[x][y]==b2)&&(pos[x-2][y]==b2||pos[x-1][y-1]==b2||pos[x][y-1]==b2))
		{       cout<<"15"<<endl;
			rw1=x-1;
			cl1=y;
			if(pos[x-1][y]==a1)
				return(1);
			else if(pos[x-1][y]==b1)
				return(1);
		}
	}
	return(0);
}

//FUNCTION TO CHECK FOR CORRECT MOVES
int moves()
{
	int x=rw1,y=cl1,i,j;

	if(x==y)			//diagonal (0,0) to (4,4)
	{
		if(x<5)
			if((rw2==(x+1)&&cl2==(y+1))||(rw2==x&&cl2==(y+1))||(rw2==(x+1)&&cl2==y))
				return(1);
	}
	for(i=0;i<5;i++)
	{
		if(rw1==5&&cl1==i)      //diagonal (5,0) to (5,4)
		{
			if((rw2==4&&cl2==i)||(rw2==5&&cl2==(i+1))||(rw2==6&&cl2==i))
				return(1);
		}
		else if(rw1==i&&cl1==5) //diagonal (0,5) to (4,5)
		{
			if((rw2==i&&cl2==4)||(rw2==(i+1)&&cl2==5)||(rw2==(i+1)&&cl2==6))
				return(1);
		}
	}
	for(i=10,j=0;i>j;--i,++j)
	{
		if(rw1==i&&cl1==j)      //diagonal (10,0) to (6,0)
		{
			if((rw2==(i-1)&&cl2==j)||(rw2==(i-1)&&cl2==(j+1))||(rw2==i&&cl2==(j+1)))
				return(1);
		}
	}
	for(i=10;i<5;--i)
	{
		if(rw1==i&&cl1==5)      //diagoanl (10,5) to (6,5)
		{
			if((rw2==i&&cl2==4)||(rw2==(i-1)&&cl2==5)||(rw2==(i-1)&&cl2==6))
				return(1);
		}
		if(rw1==5&&cl1==i) //diagonal (5,10) to (5,6)
		{
			if((rw2==4&&cl2==(i-1))||(rw2==5&&cl2==i)||(rw2==6&&cl2==(i-1)))
				return(1);
		}
	}
/*	for(i=n;i>0;--i)	//Triangle 1
		for(j=0;j<i;j++)
		{
			if(
		}
*/

	return(0);
}