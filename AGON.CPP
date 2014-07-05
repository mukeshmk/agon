/*********************************************************************
			HEADER FILES USED
*********************************************************************/

#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<process.h>
#include<string.h>
#include<stdio.h>

/*********************************************************************
			FUNCTIONS USED
*********************************************************************/

void rules();			//FUNCTION TO DISPLAY RULES OF THE GAME
void dice();                    //FUNCTION FOR ROLLING THE DICE
void hexagon(int,int);          //FUNCTION TO CHANGE THE COORDINATES
void draw();		        //FUNCTION TO DRAW THE HEXAGON
void colour();			//FUNCTION TO CHOOSE COLOUR FOR COINS
void position(int*,int*);       //FUNCTION TO PRINT THE POSITIONS
int winchk(int);                //FUNCTION TO CHECK FOR WIN
int capchk();                   //FUNCTION TO CHECK FOR CAPTURE
void modi(int);                 //FUNCTION FOR POSTION MODIFICATION
int poschag(int);               //FUNCTION FOR POISTION CHANGING
int moves();			//FUNCTION TO CHECK FOR CORRECT MOVES
int lstrw();			//FUNCTION MOVE TO LAST ROW
int game_choose();              //FUNCTION TO CHOOSE THE GAME
void file_save();               //FUNCTION TO SAVE THE GAME
int file_read();		//FUNCTION TO READ THE SAVE FILE
void credits();			//FUNCTION TO DISPLAY CREDITS

/*********************************************************************
			GLOBAL VARIABLES
*********************************************************************/

const int plyr[2]={1,2};
char nm[2][30];
int poly[14],rw1,cl1,rw2,cl2,ply=1,count=0;
int clr1=4,clr2=2,flag,cho;
fstream file;
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
			CLASS DECLRATION
*********************************************************************/

class save
{
	char nm[2][30];
	int poly[14],count,ply;
	int clr1,clr2;
	int p1rw[7],p1cl[7];
	int p2rw[7],p2cl[7];
	int pos[11][11];
   public:
	save();
	void copy_to();
	void copy_4m();
} s;

/*********************************************************************
			CONSTRUCTOR OF CLASS
*********************************************************************/

save::save()
{
	int i,j;

	strcpy(nm[0],"Player 1");
	strcpy(nm[1],"Player 2");
	count=0;
	ply=1;
	clr1=4;
	clr2=2;
	for(i=0;i<7;i++)
		p1rw[i]=p1cl[i]=p2rw[i]=p1cl[i]=0;
	p1rw[2]=p1rw[3]=p1cl[1]=4;
	p1rw[6]=p2rw[5]=p2rw[6]=10;
	p1rw[5]=p1cl[3]=p2cl[4]=9;
	p2rw[3]=p2rw[4]=p2cl[1]=6;
	p2rw[2]=p2cl[0]=2;
	p2rw[1]=p2cl[5]=1;
	p1rw[4]=8;
	p1cl[4]=7;
	p1cl[6]=3;
	p2cl[6]=5;

	for(i=0;i<11;i++)
		for(j=0;j<11;j++)
			pos[i][j]=0;
	pos[0][0]=11;
	pos[10][5]=22;
	pos[0][4]=pos[4][0]=pos[4][9]=pos[8][7]=pos[9][0]=pos[10][3]=1;
	pos[0][2]=pos[1][6]=pos[2][0]=pos[6][0]=pos[6][9]=pos[10][1]=2;
	for(i=0;i<5;i++)
		for(j=6;j<11-i;j++)
			pos[i][j]=-1;
	for(i=10;i>=6;i--)
		for(j=6;j<=i;j++)
			pos[i][j]=-1;
	}

/*********************************************************************
			CLASS FUNTION COPY_TO
*********************************************************************/

void save::copy_to()
{
	int i,j;

	strcpy(nm[0],::nm[0]);
	strcpy(nm[1],::nm[1]);
	count=::count;
	ply=::ply;
	clr1=::clr1;
	clr2=::clr2;
	for(i=0;i<7;i++)
	{
		poly[i]=::poly[i];
		poly[i+7]=::poly[i+7];
		p1rw[i]=::p1rw[i];
		p1cl[i]=::p1cl[i];
		p2rw[i]=::p2rw[i];
		p2cl[i]=::p2cl[i];
	}
	for(i=0;i<11;i++)
		for(j=0;j<11;j++)
			pos[i][j]=::pos[i][j];
}

/*********************************************************************
			CLASS FUNTION COPY_4M
*********************************************************************/

void save::copy_4m()
{
	int i,j;

	strcpy(::nm[0],nm[0]);
	strcpy(::nm[1],nm[1]);
	::count=count;
	::ply=ply;
	::clr1=clr1;
	::clr2=clr2;
	for(i=0;i<7;i++)
	{
		::poly[i]=poly[i];
		::poly[i+7]=poly[i+7];
		::p1rw[i]=p1rw[i];
		::p1cl[i]=p1cl[i];
		::p2rw[i]=p2rw[i];
		::p2cl[i]=p2cl[i];
	}
	for(i=0;i<11;i++)
		for(j=0;j<11;j++)
			::pos[i][j]=pos[i][j];
}

/*********************************************************************
			MAIN FUNCTION
*********************************************************************/

void main()
{
	clrscr();

	int chk,mov,cap,i,poschg,gm_ch;
	char sav;
	count=::count;

	gm_ch=game_choose();		//calling of game choose
	if(gm_ch==1)
		goto cont;
	rules();			//calling of rules function
	clrscr();
	dice();         		//calling of dice function
	colour();			//calling of colour function

cont:	//Graphics initialisation
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

		cout<<"do u want to save"<<endl;
		cin>>sav;
		if(sav=='y')
			file_save();
		cout<<"do u want to continue"<<endl;
		cin>>ch;
		if(ch!='y'&&ch!='Y')
		{
			closegraph();
			credits();
			delay(2000);
			exit(0);
		}
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
	gets(nm[0]);
	cout<<"enter the player 2's name:"<<endl;
	gets(nm[1]);

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

	cout<<endl<<"You are the \"first Player\""<<endl;
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
		FUNCTION TO CHOOSE COLOUR FOR COINS
*********************************************************************/
void colour()
{
	int i=0;
	char cho;
	char ch[12][3]={"1","2","3","4","5","6","7"
			,"8","9","10","11","12"};
	clrscr();

	cout<<"Do you want to choose colours for your coins"<<endl
	    <<"by Default"<<endl
	    <<"Player 1 gets \"RED\" coins"<<endl
	    <<"Player 2 gets \"GREEN\" coins"<<endl
	    <<"do you want to change ?? (y\\n)"<<endl;
	cin>>cho;
	if(cho=='y')
	{
		int gd=DETECT,gm;
		initgraph(&gd,&gm,"c:\\turboc3\\bgi");

		cout<<"\t\t Enter the colours you want for your coins"<<endl;
		for(i=0;i<6;i++)
		{
			outtextxy(88+80*i,185,ch[i]);
			outtextxy(88+80*i,285,ch[i+6]);
		}
		for(i=0;i<6;i++)
		{
			setcolor(i+1);
			setfillstyle(1,i+1);
			fillellipse(90+i*80,160,20,20);
		}
		for(i=8;i<14;i++)
		{
			setcolor(i+1);
			setfillstyle(1,i+1);
			fillellipse(90+(i-8)*80,260,20,20);
		}
enter:		gotoxy(1,5);
		cout<<nm[0]<<"-choose the colour :";
		cin>>clr1;
		cout<<nm[1]<<"-choose the colour :";
		cin>>clr2;

		if((clr1==clr2)||(clr1>13||clr2>13))
		{
			gotoxy(1,5);
			for(i=0;i<4;i++)
				cout<<"\t\t\t\t\t\t\t\t"<<endl;
			gotoxy(1,4);
			cout<<"enter again as chooses are wrong or same"<<endl;
			goto enter;
		}
		if(clr1>6)
			clr1+=2;
		if(clr2>6)
			clr2+=2;

		closegraph();
	}
}

/*********************************************************************
			FUNCTION TO SAVE THE GAME
*********************************************************************/

void file_save()
{
	count++;
	s.copy_to();
	count--;
	file.open("mk1.dat",ios::out|ios::binary);
	if(!file)
	{
		cout<<"file not opened"<<endl;
		flag=0;
		getch();
		return;
	}
	file.write((char*)&s,sizeof(s));
	cout<<"save successful"<<endl;
	file.close();
	return;
}

/*********************************************************************
			FUNCTION TO READ FROM SAVE FILE
*********************************************************************/

int file_read()
{
	file.open("mk1.dat",ios::in|ios::binary);
	if(!file)
	{
		cout<<"file not opened"<<endl;
		flag=0;
		getch();
		return(0);
	}
	file.read((char*)&s,sizeof(s));
	s.copy_4m();
	cout<<"data retreaved successfully"<<endl;
	file.close();
	return(1);
}

/*********************************************************************
			FUNCTION TO CHOOSE THE GAME
*********************************************************************/

int game_choose()
{
	int fr;
	cho=0;
	cout<<"Do you you want to \n"
	    <<"1.Play the saved game  OR\n"
	    <<"2.Play the new game\n"
	    <<"enter ur choice:";
	cin>>cho;
	if(cho==1)
	{
		fr=file_read();
		if(fr==0)
			goto nw_gm;
		else
			return(1);
	}
	else
	{
nw_gm:		clrscr();
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t";
		cout<<"NEW GAME STARTED";
		return(0);
	}
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
				setfillstyle(1,clr1);
				prw[k]=p1rw[k];
				pcl[k]=p1cl[k];
			}
			else
			{
				setfillstyle(1,clr2);
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
			setfillstyle(1,clr1);
		else
			setfillstyle(1,clr2);
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

/*********************************************************************
			FUNCTION TO DISPLAY CREDITS
*********************************************************************/

void credits()
{
	cout<<"\n\nthanks for playing"<<endl;
}