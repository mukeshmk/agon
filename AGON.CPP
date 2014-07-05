/*********************************************************************
			HEADER FILES USED
*********************************************************************/

#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
#include<process.h>

/*********************************************************************
			FUNCTIONS USED
*********************************************************************/

void rules();			//FUNCTION TO DISPLAY RULES OF THE GAME
void dice();                    //FUNCTION FOR ROLLING THE DICE
void hexagon(int,int);          //FUNCTION TO CHANGE THE COORDINATES
void draw();                    //FUNCTION TO DRAW THE HEXAGON
void position(int*,int*);       //FUNCTION TO PRINT THE POSITIONS
int winchk(int);                //FUNCTION TO CHECK FOR WIN
int capchk();                   //FUNCTION TO CHECK FOR CAPTURE
void modi(int);                 //FUNCTION FOR POSTION MODIFICATION
int poschag(int);               //FUNCTION FOR POISTION CHANGING
int moves();			//FUNCTION TO CHECK FOR CORRECT MOVES
int lstrw();			//FUNCTION MOVE TO LAST ROW

/*********************************************************************
			GLOBAL VARIABLES
*********************************************************************/

const int plyr[2]={1,2};
char nm[2][30];
int poly[14],rw1,cl1,rw2,cl2,ply=1;

		//Red   Player:-1 Green Player:-2
int p1rw[7]={0,0,4,4,8,9,10},p1cl[7]={0,4,0,9,7,0,3};
int p2rw[7]={0,1,2,6,6,10,10},p2cl[7]={2,6,0,0,9,1,5};

/*********************************************************************
	Representation of the inital board positions as a variable
*********************************************************************/

int pos[11][11]={
	/* 0 */ {      11,0,2,0,1,0, 	  -1,-1,-1,-1,-1},
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


/*********************************************************************
			MAIN FUNCTION
*********************************************************************/

void main()
{
	clrscr();

	int count=0,chk,mov,cap,i,poschg;

	rules();			//calling of rules function
	clrscr();
	dice();         		//calling of dice function

	//Graphics initialisation
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");

	draw();			//calling of draw function
	modi(1);		//calling of modi function


	char ch;
	do
	{
		gotoxy(1,1);
		for(i=0;i<25;++i)
			cout<<"\t\t\t\t\t\t   "<<endl;

		if(count%2==0)
		{
			gotoxy(1,1);
			cout<<"player 1"<<endl;
			ply=1;
		}
		else
		{
			gotoxy(1,1);
			cout<<"player 2"<<endl;
			ply=2;
		}

top:		cout<<"enter r and c to \"move from\""<<endl;
		cin>>rw1>>cl1;
		if(pos[rw1][cl1]==0||pos[rw1][cl1]==(-1))
		{
			cout<<"entered coordinates are wrong"<<endl
			    <<"enter the coordinates again"<<endl;
			    goto top;
		}

again:		cout<<"enter r and c to \"move to\""<<endl;
		cin>>rw2>>cl2;
		mov=moves();		//calling of moves function
		if(mov==0)
		{
			cout<<"\"illegal move\" you can only move"<<endl
			    <<"one step at a time"<<endl;
			goto again;
		}

		poschg=poschag(1);	//calling of poschag function
		if(poschg==1)
		{
			cout<<"illegal move"<<endl
			    <<"try again"<<endl;
			goto top;
		}

		cap=capchk();		//calling of capchk function
		if(cap==1||cap==3)
		{
			if(cap==1)
				if(ply==2)
					ply--;
				else
					ply++;
			cout<<"your \"queen\" has been captured"<<endl
			    <<"your queen will be moved by"<<endl
			    <<"your \"opponent\""<<endl;
			poschag(0);
		}
		else if(cap==2||cap==4)
		{
			if(cap==2)
				if(ply==2)
					ply--;
				else
					ply++;
			cout<<"your \"guard\" has been captured"<<endl
			    <<"your guard will be moved "<<endl
			    <<"by \"you\""<<endl;
			poschag(0);
		}

		chk=winchk(ply);	//calling of winchk function
		if(chk==1)
		{
			if(count%2==0)
				cout<<nm[0]<<" has WON the game"<<endl;
			else
				cout<<nm[0]<<" has WON the game"<<endl;
			getch();
			delay(800);
			exit(0);
		}

		cout<<"do u want to continue"<<endl;
		cin>>ch;

		count++;
	 }while(ch=='y'||ch=='Y');

	getch();

}

/*********************************************************************
		FUNCTION TO DISPLAY RULES OF THE GAME
*********************************************************************/

void rules()
{
	cout<<endl<<"\t\t\t\t\"RULES\""<<endl<<endl
	    <<"\tEach player has one Queen and six Guards"<<endl
	    <<"\twhich are placed on the outer ring of the board"<<endl<<endl
	    <<"\tThe goal of each player is to put the Queen on the center"<<endl
	    <<"\tand surround her with her Guards"<<endl<<endl
	    <<"\tThe first player being selected by the throw of a die"<<endl<<endl
	    <<"\tPieces can only be moved one cell forwards or sideways"<<endl
	    <<"\tthey cannot be moved back away from the center of the board"<<endl
	    <<"\tOnly a Queen may move onto the centre cell"<<endl<<endl
	    <<"\tIf you try to move your oppnents piece you wil loose your turn"<<endl<<endl
	    <<"\tIf a Guard is trapped between two opposing pieces,"<<endl
	    <<"\tthe owner of the captured Guard must move it"<<endl
	    <<"\tto any cell of his own choosing on the outermost ring"<<endl<<endl
	    <<"\tIf a Queen is trapped between two opposing pieces"<<endl
	    <<"\tthe owner of a captured Queen must move it to any cell"<<endl
	    <<"\tof his opponent's choosing"<<endl;
	getch();
	delay(800);
}

/*********************************************************************
		FUNCTION FOR ROLLING THE DICE
*********************************************************************/

void dice()
{
	int i,ran[2];
	randomize();
	cout<<"enter the player 1's name:"<<endl;
	cin.getline(nm[0],30);
	cout<<"enter the player 2's name:"<<endl;
	cin.getline(nm[1],30);

roll:	for(i=0;i<2;++i)
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
		cout<<"both players have got the \"same\""<<endl
		    <<"number on the dice, so \"rolling again\""<<endl;
		delay(700);
		goto roll;
	}

	if(ran[0]>ran[1])
		cout<<endl<<nm[0]<<" wins the \"first chance\""<<endl;
	else
		cout<<endl<<nm[1]<<" wins the \"first chance\""<<endl;

	cout<<endl<<"You are the \"first Player\""<<endl
	    <<"your conis are the \"red\" once"<<endl;
	getch();
}

/*********************************************************************
		FUNCTION TO DRAW THE HEXAGON
*********************************************************************/

void draw()
{
	int i,j,n=6,x=460,y=10;

	setbkcolor(0);
	setfillstyle(1,8);

	for(j=0,y;j<6;++j,++n)
	{
		for(i=0;i<n;x+=20,++i)
		{
			hexagon(x,y);	//calling of hexagon function
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
			hexagon(x,y);	//calling of hexagon function
			fillpoly(7,poly);
		}
		x=x+10-20*n;
		y+=20;
	}

	getch();
}

/*********************************************************************
		FUNCTION TO CHANGE THE COORDINATES
*********************************************************************/

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

/*********************************************************************
		FUNCTION TO CHECK FOR CORRECT MOVES
*********************************************************************/

int moves()
{
	int x=rw1,y=cl1,i,j,k;

	if(x==y)			//diagonal (0,0) to (4,4)
	{
		if(x<5)
			if((rw2==(x+1)&&cl2==(y+1))||(rw2==x&&
			    cl2==(y+1))||(rw2==(x+1)&&cl2==y))
				return(1);
	}

	for(i=0;i<5;i++)
	{
		if(rw1==5&&cl1==i)      //diagonal (5,0) to (5,4)
			if((rw2==4&&cl2==i)||(rw2==5&&
			    cl2==(i+1))||(rw2==6&&cl2==i))
				return(1);

		if(rw1==i&&cl1==5)     //diagonal (0,5) to (4,5)
			if((rw2==i&&cl2==4)||(rw2==(i+1)&&
			    cl2==5)||(rw2==(i+1)&&cl2==6))
				return(1);
	}

	for(i=10,j=0;i>j;--i,++j)
	{
		if(rw1==i&&cl1==j)      //diagonal (10,0) to (6,0)
			if((rw2==(i-1)&&cl2==j)||(rw2==(i-1)&&
			    cl2==(j+1))||(rw2==i&&cl2==(j+1)))
				return(1);
	}

	for(i=10;i>5;--i)
	{
		if(rw1==i&&cl1==5)      //diagoanl (10,5) to (6,5)
			if((rw2==i&&cl2==4)||(rw2==(i-1)&&
			    cl2==5)||(rw2==(i-1)&&cl2==6))
				return(1);

		if(rw1==5&&cl1==i) //diagonal (5,10) to (5,6)
			if((rw2==4&&cl2==(i-1))||(rw2==5&&
			    cl2==i)||(rw2==6&&cl2==(i-1)))
				return(1);
	}

	for(i=0;i<4;++i)	//Triangle 1
		for(j=4;j>0;--j)
		{
			if(rw1==j&&cl1==i)
				if((rw2==(j-1)&&cl2==i)||
				   (rw2==j&&cl2==(i+1))||(rw2==(j+1)&&
				    cl2==(i+1))||rw2==(j+1)&&cl2==i)
					return(1);
		}

	for(i=6;i<10;++i)	//Triangle 2
		for(k=9,j=0;k>=i;++j,--k)
		{
			if(rw1==i&&cl1==j)
				if((rw2==(i-1)&&cl2==j)||(rw2==(i-1)&&
				    cl2==(j+1))||(rw2==i&&cl2==(j+1))||
				   (rw2==(i+1)&&cl2==j))
					return(1);
		}

	for(i=10;i>6;--i)      //Triangle 3
		for(j=4,k=6;k<i;++k,--j)
		{
			if(rw1==i&&cl1==j)
				if((rw2==i&&cl2==(j-1))||(rw2==(i-1)&&
				    cl2==j)||(rw2==(i-1)&&cl2==(j+1))||
				    (rw2==i&&cl2==(j+1)))
					return(1);
		}

	for(i=6;i<10;++i)      //Triangle 4
		for(j=6,k=9;k>=i;--k,++j)
		{
			if(rw1==i&&cl1==j)
				if((rw2==(i+1)&&cl2==(j-1))||(rw2==i&&
				    cl2==(j-1))||(rw2==(i-1)&&cl2==j)||
				    (rw2==(i-1)&&cl2==(j+1)))
					return(1);
		}

	for(i=4;i>0;--i)      //Triangle 5
		for(k=0,j=6;k<i;++j,++k)
		{
			if(rw1==i&&cl1==j)
				if((rw2==(i+1)&&cl2==(j+1))||(rw2==(i+1)&&
				    cl2==j)||(rw2==i&&cl2==(j-1))||
				    (rw2==(i-1)&&cl2==(j-1)))
					return(1);
		}

	for(i=0;i<4;++i)      //Triangle 6
		for(k=4,j=4;k>i;--k,--j)
		{
			if(rw1==i&&cl1==j)
				if((rw2==i&&cl2==(j+1))||(rw2==(i+1)&&
				    cl2==(j+1))||(rw2==(i+1)&&cl2==j)||
				    (rw2==i&&cl2==(j-1)))
					return(1);
		}
	return(0);
}

/*********************************************************************
		FUNCTION FOR POSTION MODIFICATION
*********************************************************************/

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
			position(prw,pcl);//calling of position function

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

/*********************************************************************
		FUNCTION TO PRINT THE POSITIONS
*********************************************************************/

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

/*********************************************************************
		FUNCTION FOR POISTION CHANGING
*********************************************************************/

int poschag(int z)
{
	int a,b,i,j,x=460,y=10,r=5,X,Y,flag=0,lst;

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
agn:		lst=lstrw();
		if(lst==0)
			goto agn;
	}

	if((pos[rw1][cl1]==a||pos[rw1][cl1]==b)&&pos[rw2][cl2]==0)
	{
		if(pos[rw1][cl1]==a)
		{
			if(ply==1)
				flag=11;
			else
				flag=22;
		}
		if(pos[rw1][cl1]==b)
		{
			if(ply==1)
				flag=1;
			else
				flag=2;
		}
//To errase the circle
		setcolor(8);
		setfillstyle(1,8);
		if(rw1<=5)
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
//To make the new circle
		setcolor(15);
		if(ply==1)
			setfillstyle(1,4);
		else
			setfillstyle(1,2);
		if(rw2<=5)
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
		modi(0);               //calling of modi function
	}
	else
		return(1);
	return(0);
}

/*********************************************************************
		FUNCTION TO CHECK FOR WIN
**********************************************************************/

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

	if(pos[5][5]==x&&pos[4][4]==y&&pos[4][5]==y&&
	   pos[5][4]==y&&pos[5][6]==y&&pos[6][4]==y&&pos[6][5]==y)
		return(1);
	else
		return(0);
}

/*********************************************************************
			FUNCTION TO CHECK FOR CAPTURE
*********************************************************************/

int capchk()
{
	int a1,a2,b1,b2,x=rw2,y=cl2,flag,flag_cap;

	if(ply==2)
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

		if(x-1!=-1&&y-1!=-1&&y!=x+6)
/*Centre up*/	if((pos[x][y]==a1||pos[x][y]==b1)&&
		   ((pos[x-1][y]==b2&&pos[x+1][y]==b2)||
		    (pos[x][y+1]==b2&&pos[x][y-1]==b2)||
		    (pos[x+1][y+1]==b2&&pos[x-1][y-1]==b2)))
		{
			rw1=x;
			cl1=y;
			if(pos[x][y]==a1)
				return(1);
			else if(pos[x][y]==b1)
				return(2);
		}
		if(x-1!=-1&&x-2!=-1)
/*Corner up 1*/	if((pos[x][y]==b2)&&(pos[x-2][y]==b2)&&
		   (pos[x-1][y]==a1||pos[x-1][y]==b1))
		{
			rw1=x-1;
			cl1=y;
			if(pos[x-1][y]==a1)
				return(1);
			else if(pos[x-1][y]==b1)
				return(2);
		}
		if(x-1!=-1&&y-1!=-1&&x-2!=-1&&y-2!=-1)
/*Corner up 2*/	if((pos[x-1][y-1]==a1||pos[x-1][y-1]==b1)&&
		    (pos[x][y]==b2)&&(pos[x-2][y-2]==b2))
		{
			rw1=x-1;
			cl1=y-1;
			if(pos[x-1][y-1]==a1)
				return(1);
			else if(pos[x-1][y-1]==b1)
				return(2);
		}
		if(y-1!=-1&&y-2!=-1)
/*Corner up 3*/	if((pos[x][y-1]==a1||pos[x][y-1]==b1)&&
		    (pos[x][y]==b2)&&(pos[x][y-2]==b2))
		{
			rw1=x;
			cl1=y-1;
			if(pos[x][y-1]==a1)
				return(1);
			else if(pos[x][y-1]==b1)
				return(2);
		}
/*Corner up 4*/	if((pos[x+1][y]==a1||pos[x+1][y]==b1)&&
		   (pos[x][y]==b2)&&(pos[x+2][y]==b2))
		{
			rw1=x+1;
			cl1=y;
			if(pos[x+1][y]==a1)
				return(1);
			else if(pos[x+1][y]==b1)
				return(2);
		}
		if(y!=x+6)
/*Corner up 5*/	if((pos[x+1][y+1]==a1||pos[x+1][y+1]==b1)&&
		   (pos[x+2][y+2]==b2)&&(pos[x][y]==b2))
		{
			rw1=x+1;
			cl1=y+1;
			if(pos[x+1][y+1]==a1)
				return(1);
			else if(pos[x+1][y+1]==b1)
				return(2);
		}
		if(y!=x+6)
/*Corner up 6*/	if((pos[x][y+1]==a1||pos[x][y+1]==b1)&&
		   (pos[x][y+2]==b2)&&(pos[x][y]==b2))
		{
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

/*Center down*/	if((pos[x][y]==a1||pos[x][y]==b1)&&
		   ((pos[x-1][y+1]==b2&&pos[x+1][y-1]==b2)||
		    (pos[x][y+1]==b2&&pos[x][y-1]==b2)||
		    (pos[x+1][y]==b2&&pos[x-1][y]==b2)))
		{
			rw1=x;
			cl1=y;
			if(pos[x][y]==a1)
				return(1);
			else if(pos[x][y]==b1)
				return(2);
		}
		if(x-1!=-1&&x-2!=-1&&x+y!=16)
/*Corner down1*/if((pos[x-1][y+1]==a1||pos[x-1][y+1]==b1)&&
		   (pos[x-2][y+2]==b2)&&(pos[x][y]==b2))
		{
			rw1=x-1;
			cl1=y+1;
			if(pos[x-1][y+1]==a1)
				return(1);
			else if(pos[x-1][y+1]==b1)
				return(2);
		}
		if(x+y!=16)
/*Corner down2*/if((pos[x][y+1]==a1||pos[x][y+1]==b1)&&
		   (pos[x][y+2]==b2)&&(pos[x][y]==b2))
		{
			rw1=x;
			cl1=y+1;
			if(pos[x][y+1]==a1)
				return(1);
			else if(pos[x][y+1]==b1)
				return(2);
		}
		if(x+1!=11&&x+2!=11)
/*Corner down3*/if((pos[x+1][y]==a1||pos[x+1][y]==b1)&&
		    (pos[x+2][y]==b2)&&(pos[x][y]==b2))
		{
			rw1=x+1;
			cl1=y;
			if(pos[x+1][y]==a1)
				return(1);
			else if(pos[x+1][y]==b1)
				return(2);
		}
		if(x+1!=11&&y-1!=-1&&x+2!=11&&y-2!=-1)
/*Corner down4*/if((pos[x+1][y-1]==a1||pos[x+1][y-1]==b1)&&
		   (pos[x][y]==b2)&&(pos[x+2][y-2]==b2))
		{
			rw1=x+1;
			cl1=y-1;
			if(pos[x+1][y-1]==a1)
				return(1);
			else if(pos[x+1][y-1]==b1)
				return(2);
		}
		if(y-1!=-1&&y-2!=-1)
/*Corner down5*/if((pos[x][y-1]==a1||pos[x][y-1]==b1)&&
		   (pos[x][y]==b2)&&(pos[x][y-2]==b2))
		{
			rw1=x;
			cl1=y-1;
			if(pos[x][y-1]==a1)
				return(1);
			else if(pos[x][y-1]==b1)
				return(2);
		}
		if(x-2!=-1&&x-1!=-1)
/*Corner down6*/if((pos[x-1][y]==a1||pos[x-1][y]==b1)&&
		   (pos[x][y]==b2)&&(pos[x-2][y]==b2))
		{
			rw1=x-1;
			cl1=y;
			if(pos[x-1][y]==a1)
				return(1);
			else if(pos[x-1][y]==b1)
				return(1);
		}
	}

/*Center up  */
	a1=11;
	b1=1;
	b2=2;

	if(pos[x][y]==a1||pos[x][y]==b1)
	{
		if(x-1!=-1&&y-1!=-1)
		{
			if(pos[x-1][y]==b2&&pos[x+1][y]==b2)
				flag_cap=1;
			if(pos[x+1][y+1]==b2&&pos[x-1][y-1]==b2)
				flag_cap=1;
			if(pos[x][y+1]==b2&&pos[x][y-1]==b2)
				flag_cap=1;
		}
		if(flag_cap==1)
		{       cout<<"";
			rw1=x;
			cl1=y;
			if(pos[x][y]==a1)
				return(1);
			else if(pos[x][y]==b1)
				return(2);
		}
	}

/*Center down*/
	a1=22;
	b1=2;
	b2=1;

	if((pos[x][y]==a1||pos[x][y]==b1)&&
	   ((pos[x-1][y+1]==b2&&pos[x+1][y-1]==b2)||
	    (pos[x][y+1]==b2&&pos[x][y-1]==b2)||
	    (pos[x+1][y]==b2&&pos[x-1][y]==b2)))
	{
		rw1=x;
		cl1=y;
		if(pos[x][y]==a1)
			return(3);
		else if(pos[x][y]==b1)
			return(4);
	}
	return(0);
}

/*********************************************************************
			FUNCTION MOVE TO LAST ROW
*********************************************************************/

int lstrw()
{
	int i,j;

	cout<<"enter r and c to move the \"captured peice\" too"<<endl
	    <<"make sure that the piece is "<<endl
	    <<"movied to the \"last ring\""<<endl;
	cin>>rw2>>cl2;

	if(pos[rw2][cl2]==0)
	{
		for(i=0;i<11;++i)
			if(rw2==i&&cl2==0)//left up & dwn
				return(1);

		for(i=0;i<6;++i)
		{
			if(rw2==10&&cl2==i)//dwn
				return(1);
			if(rw2==0&&cl2==i)//up
				return(1);
		}
		for(i=0,j=5;i<6;++i,++j)
			if(rw2==i&&cl2==j)//right up
				return(1);

		for(i=5,j=10;i<11;++i,--j)
			if(rw2==i&&cl2==j)//right down
				return(1);
	}
	return(0);
}