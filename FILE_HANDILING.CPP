#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

char nm[2][30];
int poly[14],rw1,cl1,rw2,cl2,ply=1;
int clr1=4,clr2=2;
int flag=1,cho,count=1;
int p1rw[7]={0,0,4,4,8,9,10},p1cl[7]={0,4,0,9,7,0,3};
int p2rw[7]={0,1,2,6,6,10,10},p2cl[7]={2,6,0,0,9,1,5};

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

fstream file;

void file_save();
int file_read();

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
	void input();
	void output();
} s;

save::save()
{
	int i,j,k=5,p,q;

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
	for(p=10;p>5;p--)
	{
		for(q=10;q<k;q++)
			pos[p][q]=-1;
		k++;
	}

}

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

void save::output()
{
	cout<<"nm[0]"<<nm[0]<<endl
	    <<"clr1="<<clr1<<endl
	    <<"clr2="<<clr2<<endl
	    <<"p1rw[0]="<<p1rw[0]<<endl
	    <<"p1cl[2]="<<p1cl[2]<<endl
	    <<"p2rw[0]="<<p2rw[0]<<endl
	    <<"p2cl[3]="<<p2cl[3]<<endl
	    <<"pos[3][5]="<<pos[3][5]<<endl
	    <<"pos[5][3]="<<pos[5][3]<<endl
	    <<"pos[6][6]="<<pos[6][6]<<endl;
}

void save::input()
{
	cout<<"nm[0]";
	gets(nm[0]);
	cout<<"clr1=";
	cin>>clr1;
	cout<<"clr2=";
	cin>>clr2;
	cout<<"p1rw[0]=";
	cin>>p1rw[0];
	cout<<"p1cl[2]=";
	cin>>p1cl[2];
	cout<<"p2rw[0]=";
	cin>>p2rw[0];
	cout<<"p2cl[3]=";
	cin>>p2cl[3];
	cout<<"pos[3][5]=";
	cin>>pos[3][5];
	cout<<"pos[5][3]=";
	cin>>pos[5][3];
	cout<<"pos[6][6]=";
	cin>>pos[6][6];
}

void file_save()
{
	count++;
	s.copy_to();
	count--;
	file.open("savdat.dat",ios::out|ios::binary);
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

int file_read()
{
	file.open("savdat.dat",ios::in|ios::binary);
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

void main()
{
	int opt,gm_ch;
	clrscr();
	do
	{
		cout<<"do you want to\n1.Write\n2.Read\n"
		    <<"3.exit\nchoose:";
		cin>>opt;
		if(opt==1)
		{
			s.input();
			file_save();
			s.output();
		}
		else if(opt==2)
		{
			file_read();
			s.output();
		}
		else if(opt<3)
			cout<<"wrong choice";
	}while(opt!=3);
	getch();
}