#include<iostream.h>
#include<conio.h>
#include<graphics.h>

void hexagon(int,int);
void draw();
void inipos();
void position(int,int,int,int);
void player1(int,int,int,int);

int poly[14];

void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");

	int rw1,cl1,rw2,cl2,flag=0;
	char ch;
	do
	{
		cout<<"enter r and c to move from"<<endl;
		cin>>rw1>>cl1;
		cout<<"enter r and c to move to"<<endl;
		cin>>rw2>>cl2;
		draw();
		if(flag==0);
		inipos();
		position(rw1,cl1,rw2,cl2);
		player1(rw1,cl1,rw2,cl2);
		cout<<"do u want to continue"<<endl;
		cin>>ch;
		flag++;
	 }while(ch=='y');
	getch();
}

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
void inipos()
{
	int x=460,y=10,r=5;
	//red 1 green 2
	setfillstyle(1,4);
	fillellipse(x+10,y+15,r,r);//red queen
	fillellipse(x+70,y+215,r,r);//red 10,3
	fillellipse(x,y+195,r,r);//red 9,0
	fillellipse(x+130,y+175,r,r);//red 8,7
	fillellipse(x+150,y+95,r,r);//red 4,9
	fillellipse(x+90,y+15,r,r);//red 0,4
	fillellipse(x-30,y+95,r,r);//red 6,9

	setfillstyle(1,2);
	fillellipse(x+30,y+215,r,r);//green 10,1
	fillellipse(x+120,y+35,r,r);//green 10,1
	fillellipse(x-10,y+55,r,r);//green 2,0
	fillellipse(x+110,y+215,r,r);//green queen
	fillellipse(x+150,y+135,r,r);//green 6,9
	fillellipse(x+50,y+15,r,r);//green 0,2
	fillellipse(x-30,y+135,r,r);//green 6,0
}

void player1(int rw1,int cl1,int rw2,int cl2)
{
	int x=460,y=10,r=5,X,Y;
	int rw[7]={0,10,9,8,4,0,6},cl[7]={0,3,0,7,9,4,9};
	setfillstyle(1,4);
	for(int i=0;i<rw1;++i)
		if(rw[i]==rw1)
			break;
	for(int j=0;j<cl1;++j)
		if(cl[j]==cl1)
			break;
	cout<<i<<endl<<j<<endl;
	if(rw[0]==rw1&&cl[0]==cl1)
	{
		X=x+10*(2*cl1+1)-10*rw1;
		Y=y+15+20*rw1;
		fillellipse(X,Y,r,r);
		rw[0]=rw2;
		cl[0]=cl2;
	}
	if(rw[1]==rw1&&cl[1]==cl1)
	{
		fillellipse(x+70,y+215,r,r);//red 10,3
		rw[1]=rw2;
		cl[1]=cl2;
	}
	if(rw[2]==rw1&&cl[2]==cl1)
	{
		fillellipse(x,y+195,r,r);//red 9,0
		rw[2]=rw2;
		cl[2]=cl2;
	}
	if(rw[3]==rw1&&cl[3]==cl1)
	{
		fillellipse(x+130,y+175,r,r);//red 8,7
		rw[3]=rw2;
		cl[3]=cl2;
	}
	if(rw[4]==rw1&&cl[4]==cl1)
	{
		fillellipse(x+150,y+95,r,r);//red 4,9
		rw[4]=rw2;
		cl[4]=cl2;
	}
	if(rw[5]==rw1&&cl[5]==cl1)
	{
		fillellipse(x+90,y+15,r,r);//red 0,4
		rw[5]=rw2;
		cl[5]=cl2;
	}
	if(rw[1]==rw1&&cl[1]==cl1)
	{
		fillellipse(x-30,y+95,r,r);//red 6,9
		rw[6]=rw2;
		cl[6]=cl2;
	}

}

void position(int rw1,int cl1,int rw2,int cl2)
{
	int x=460,y=10,r=5,X,Y;
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
		if(rw1)
		{
			X=x+10*(2*cl1+1)-10*rw1+20*(re+1);
			Y=y+135+20*re;
			fillellipse(X,Y,r,r);
		}
	}
	setcolor(15);
	setfillstyle(1,1);
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
		if(rw2)
		{
			X=x+10*(2*cl2+1)-10*rw2+20*(re+1);
			Y=y+135+20*re;
			fillellipse(X,Y,r,r);
		}
	}
}