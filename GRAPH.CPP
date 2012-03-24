#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>

void run();

char fx[100][50];    //Our 2-d Array with functions on each sep. array.
char str[100];	     //User Entered Complex Functions.


void getfx()	     //Get Valid Function.
{
clrscr();
cout<<"Write A Mathematical Function\nPut brackets Everywhere u think there should be one\nProgram Doesnt Follow BODMAS Rule\nDont Use Negative Numbers in the function definition.\nYou can give negative values by using (0)-(value)\n";
cout<<"Ex:-\n((2)^((cos(sin(((x)^(2))+(x))))+((cos(x))*(sin(x)))))";
cout<<"\n\n\n\n\ty  =  ";
int valid=0;
while(valid!=1)
{
int c1=0,c2=0;
gotoxy(15,11);
clreol();
gets(str);
for(int i=0;str[i]!='\0';i++)
{
if(str[i]=='(')c1++;
else if(str[i]==')')c2++;
}
if(c1==c2)                           //no of '(' = no of ')'
{
valid=1;
}
}
}

void ic(int pos,char a)
{
int i=strlen(str);
while(i>=pos)
{
str[i+1]=str[i];
i--;
}
str[i+1]=a;
}

void putbrac()
{
ic(0,'('); ic(strlen(str),')');

for(int i=0;str[i]!='\0';i++)
{

if(str[i]=='x')
{
ic(i,'(');
ic(i+2,')');    i+=2;
}

else if(str[i]=='('||str[i]==')')
{
ic(i,str[i]);  i++;
}

else if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')
{
ic(i,')');
ic(i+2,'(');       i+=2;
}

else if(isdigit(str[i]))
{
ic(i,'(');
int j=i+1;
while(isdigit(str[j]))
{
j++;
}
ic(j,')'); i=j;
}

}
}






void readfx()                   // read the given fx
{
int l=0,m=0;
for(int i=0;str[i]!='\0';i++)    // master stroke!! separating different fx's.
{
if(str[i]==')')
{
for(int j=i;str[j]!='(';j--);
for(int k=j;k<=i;k++)
{
if(str[k]!='z')
{
fx[l][m]=str[k];
str[k]='z';
m++;
}
}
fx[l][m]='\0';
if(strlen(fx[l])>2)
{l++;}
m=0;
}
}
fx[l][m]='z';
}

void rembrac()                     //convert (sin) to sin in fx[][]
{
int j;
for(int i=0;fx[i][0]!='z';i++)
{
if(fx[i][0]=='(')
{
j=0;
while(fx[i][j]!='\0')
{
fx[i][j]=fx[i][j+1];
j++;
}
fx[i][strlen(fx[i])-1]='\0';
}
}
}

int grt(double x)           // greatest int fx
{
int y;
if(x>=0)y=x;
else y=x-1;
return y;
}


double eval(double x)           //Evaluate the value of fx for a 'x'
{                                //Stack like operations
double y[100]; int j=-1;        //(postfix to infix) type
for(int i=0;fx[i][0]!='z';i++)  //indentifying the functions and
{                               //applying appropriate operations.

if(fx[i][0]=='x')
{
j++;
y[j]=x;
}

else if(isdigit(fx[i][0]))
{
j++;
y[j]=atoi(fx[i]);
}

else if(fx[i][0]=='+')
{
y[j-1]+=y[j];
j--;
}

else if(fx[i][0]=='-')
{
y[j-1]-=y[j];
j--;
}

else if(fx[i][0]=='*')
{
y[j-1]*=y[j];
j--;
}

else if(fx[i][0]=='/')
{
y[j-1]/=y[j];
j--;
}

else if(fx[i][0]=='^')
{
y[j-1]=pow(y[j-1],y[j]);
j--;
}

else if(strcmpi(fx[i],"sin")==0)
{
y[j]=sin(y[j]);
}

else if(strcmpi(fx[i],"cos")==0)
{
y[j]=cos(y[j]);
}

else if(strcmpi(fx[i],"tan")==0)
{
y[j]=tan(y[j]);
}

else if(strcmpi(fx[i],"cot")==0)
{
y[j]=1/tan(y[j]);
}

else if(strcmpi(fx[i],"cosec")==0)
{
y[j]=1/sin(y[j]);
}

else if(strcmpi(fx[i],"sec")==0)
{
y[j]=1/cos(y[j]);
}

else if(strcmpi(fx[i],"log")==0)
{
y[j]=log(y[j]);
}

else if(strcmpi(fx[i],"grt")==0)
{
y[j]=grt(y[j]);
}

else if(strcmpi(fx[i],"fra")==0)
{
y[j]-=grt(y[j]);
}

else if(strcmpi(fx[i],"sgn")==0)
{
if(y[j]>0)y[j]=1;
else if(y[j]<0)y[j]=-1;
else y[j]=0;
}

else
{
cout<<"\nCheck\n";
}
}
return y[0];
}


void putpt(int x,int y)        //put a point acc to new axis with (0,0) at middle
{
x+=315;
y=239-y;
putpixel(x,y,4);
}

void axis(int sx,int sy)        // make axis with app scale.
{
char a[5];
setgraphmode(getgraphmode());
line(315,0,315,480);		//vertical line
line(0,239,630,239);            //horizontol line

outtextxy(308,240,"0");

for(int n=-350/sx;n*sx<=400;n++)      //markings for horizontol axis
{
if(n==0)continue;
putpt(sx*n,0);

itoa(n,a,10);                   //integer to string, used for outtextxy.
if(n<0)                        // '-' sign in the axis creates prblms,so 305 and not 315.
outtextxy(sx*n+305,240,a);    //writes a string in graphics mode.
else
outtextxy(sx*n+315,240,a);
}


for(n=-300/sy;n*sy<=400;n++)      //markings for horizontol axis
{
if(n==0)continue;
putpt(0,n*sy);

itoa(n,a,10);                   //integer to string, used for outtextxy.
outtextxy(317,236-n*sy,a);    //writes a string in graphics mode.
}



}
void graph(int sx,int sy)          // make the graph
{
for(double x=-320/sx;sx*x<=320;x+=0.01)
{
putpt(sx*x,sy*eval(x));
}
}

void menu()
{
clrscr();
int ans;
cout<<"\n\n\t\t\tWelcome\n\t\t1.Graph\n\t\t2.Evaluate\n\t\t3.Exit\nEnter Your Choice\t";
cin>>ans;
switch(ans)
{
case 1:
int sx,sy;
getfx();
putbrac();
readfx();
rembrac();
cout<<"\nEnter Scale For X & Y Axis\n";cin>>sx>>sy;
axis(sx,sy);
graph(sx,sy);
getch();
break;

case 2:
getfx();
putbrac();
readfx();
rembrac();
double x;
cout<<"\nEnter A Value\n";
cin>>x;
cout<<eval(x);
getch();
break;

case 3: exit(0);

}

}

void main()
{
int gdriver = DETECT, gmode;

initgraph(&gdriver, &gmode, "E:\\praveen\\tc\\bgi");

while(42==42)
{
restorecrtmode();
menu();
}


getch();
closegraph();
}

