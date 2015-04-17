#include<simplecpp>
#include<stdlib.h>
#include<ctime>
#include<fstream>
long long timer=0;//stores the time taken by user to complete the game
class beg_game//beginner level
{
public:
int arr[9][9];//double dimensional array which stores the board
int xmine[10];//stores x coordinate of mines
int ymine[10];//stores y coordinate of mines.
int pos[9][9];//stores pos value of each square. The value of the square is displayed if pos value is 1, else it is covered.
int zeroposx[70];//stores x coordinates of all zeros in the grid
int zeroposy[70];//stores y coordinates of all zeros in the grid
int zerocount=0;// stores number of zeros uncovered at that moment.
bool alive=true;// indicates if game is on or off.
int flagger[9][9];//indicates whether there is a flag on that position or not
 bool isMine(int x,int y)// checks whether there is a mine at (x,y)
    {
        for(int i=0;i<=9;i++)
        {
            if(x==xmine[i]&&y==ymine[i])
                return true;
        }
        return false;
    }
bool isValid(int x,int y)//checks wether (x,y) is on the board or not
    {
        if((x>=0&&x<=8)&&(y>=0&&y<=8))
            return true;
        return false;
    }
int countMines(int x, int y)//counts the number of mines in the squares surrounding (x,y)
    {
        int count=0;
        for(int i= x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j))
                {
                    if(arr[i][j]==-1)
                        count++;
                }
            }
        }
        return count;
    }
 void generateboard()//sets up the board
    {
        xmine[0]= rand()%9;// generates a random number as a x coordinate of the mine
        ymine[0]= rand()%9;// generates a random number as a y coordinate of the mine
        arr[xmine[0]][ymine[0]]=-1;
        int count=1;
        for(int i=1;i<10;i++)
        {
            bool flag=true;
            int x= rand()%9;
            int y= rand()%9;
            for(int j=0;j<count;j++)//checks wether a mine is not redundant by comparing with already created mines
            {
                if(xmine[j]==x&& ymine[j]==y)
                {
                    --i;
                    flag=false;
                    break;
                }
            }
            if(flag==false)
            continue;
            xmine[i]=x;
            ymine[i]=y;
            count++;
            arr[x][y]=-1;
        }
        for(int i=0;i<9;i++)//every cell of arr[][] is given values
        {
            for(int j=0;j<9;j++)
            {
                if(isMine(i,j)==false)
                    arr[i][j]=countMines(i,j);
                pos[i][j]=0;
                flagger[i][j]=0;
            }
        }
        }
int countNumber()//counts the number of squares that have been uncovered
    {
        int count=0;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(pos[i][j]==1)
                {
                    count++;
                }
            }
        }
        return count;
    }
bool alreadyChecked(int x, int y)//checks wether the zero() function has been called or not on (x,y) to avoide infinite recursion
    {
        for(int i=0;i<zerocount+1;i++)
        {
            if(zeroposx[i]==x&&zeroposy[i]==y)
            return true;
        }
        return false;
    }
void zero(int x, int y)// makes pos value equal to 1 of all squares surrounding the zero square
    {
        for(int i=x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j)==true)
                {
                    if(arr[i][j]==0&&alreadyChecked(i,j)==false)
                    {
                        zerocount++;
                        zeroposx[zerocount]= i;
                        zeroposy[zerocount]= j;
                        zero(i,j);
                        pos[i][j]=1;
                    }
                    else
                        pos[i][j]=1;
                }
            }
        }
    }
void display()//displays the grid on initCanvas window
{
initCanvas();
for(int i=50;i<=450;i=i+50)
{
for(int j=50;j<=450;j=j+50)
{
Rectangle r1(i,j,50,50);
r1.imprint();
if(flagger[(i/50)-1][(j/50)-1]==1)
{
Text t1(i,j,"M");
t1.setColor(COLOR("red"));
t1.imprint();
}
if(pos[(i/50)-1][(j/50)-1]==1)
{
if(arr[(i/50)-1][(j/50)-1]==0)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==1)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==2)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==3)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}

}
}
}
    }
void completeDisplay()// completely displays the grid on exploding a mine
{
initCanvas();
for(int i=50;i<=450;i=i+50)
{
for(int j=50;j<=450;j=j+50)
{
Rectangle r1(i,j,50,50);
r1.imprint();
if(arr[(i/50)-1][(j/50)-1]==0)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==1)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==2)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==3)
{
Text t1(i,j,arr[(i/50)-1][(j/50)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
if(arr[(i/50)-1][(j/50)-1]==-1)
{
r1.setColor(COLOR("red"));
r1.setFill(true);
r1.imprint();
Circle c(i,j,15);
c.setColor(COLOR("black"));
c.setFill(true);
c.imprint();
}
}
}
}
int play()//prompts the user to click on a square on the grid
{
time_t now = time(0);
long long t= now;
XEvent event;
while(countNumber()<71&&alive==true)
{
display();
int click=0;
int s= getClick();
nextEvent(event);
click= event.xbutton.button;
closeCanvas();
int s1=s/65536;
int s2=s%65536;
int count=0;
int xco=25;
int yco=25;
for(int i=0;i<9;i++)
{
for(int j=0;j<9;j++)
{
if(s1>xco&&s1<(xco+50)&&s2>yco&&s2<(yco+50))
{
if(click==1&&flagger[i][j]==0)
check(i,j);
if(click==3&&pos[i][j]==0)
flagMine(i,j);
count=1;
break;
}
yco+=50;
}
if(count==1)
break;
xco+=50;
yco=25;
}

}
if(countNumber()==71&&alive==true)//minesweeper completed when only mines are left
{
time_t now1 = time(0);
long long c= now1;
timer= c-t;
initCanvas("MINESWEEPER",700,700);
Text m(300,250,"Congratulation, you completed minesweeper!");
Text t(250,300,"TIME TAKEN:");
Text t1(400,300,timer);
cout<<"ENTER YOUR NAME"<<endl;
string name;
cin>>name;
ofstream output;
output.open("highscoresbeg.txt", std::ios_base::app);//stores high score
output<<name<<endl;
output<<timer<<endl;
getClick();
}
return 0;
}
int flagMine(int x, int y)//puts flagger value to 1 or 0
{
if(flagger[x][y]==0)
{
flagger[x][y]=1;
return 0;
}
if(flagger[x][y]==1)
{
flagger[x][y]=0;
return 0;
}
}
void check(int a,int b)//checks wether (x,y) is a mine or else puts its pos value as 1
{
if(arr[a][b]==-1)
{
completeDisplay();
getClick();
closeCanvas();
initCanvas();
Text t(300,300,"GAME OVER");
t.imprint();
alive=false;
}
if(arr[a][b]== 0)
            {
                zeroposx[zerocount]= a;
                zeroposy[zerocount]= b;
                zero(a,b);

            }
            else
            {
                pos[a][b]=1;
            }
            }
void flusher()//flushes all data members for the next game
{
zerocount=0;
alive=true;
for(int i=0;i<9;i++)
{
for(int j=0;j<9;j++)
{
arr[i][j]=0;
pos[i][j]=0;
flagger[i][j]=0;
}
}
for(int i=0;i<10;i++)
{
xmine[i]=0;
ymine[i]=0;
}
for(int i=0;i<70;i++)
{
zeroposx[i]=0;
zeroposy[i]=0;
}
}
};
class inter_game//intermediate level
{
public:
int arr[16][16];//double dimensional array which stores the board
int xmine[40];//stores x coordinate of mines
int ymine[40];//stores y coordinate of mines.
int pos[16][16];//stores pos value of each square. The value of the square is displayed if pos value is 1, else it is covered.
int zeroposx[215];//stores x coordinates of all zeros in the grid
int zeroposy[215];//stores y coordinates of all zeros in the grid
int zerocount=0;// stores number of zeros uncovered at that moment.
bool alive=true;// indicates if game is on or off.
int flagger[16][16];//indicates whether there is a flag on that position or not
 bool isMine(int x,int y)// checks whether there is a mine at (x,y)
    {
        for(int i=0;i<=39;i++)
        {
            if(x==xmine[i]&&y==ymine[i])
                return true;
        }
        return false;
    }
bool isValid(int x,int y)//checks wether (x,y) is on the board or not
    {
        if((x>=0&&x<=15)&&(y>=0&&y<=15))
            return true;
        return false;
    }
int countMines(int x, int y)//counts the number of mines in the squares surrounding (x,y)
    {
        int count=0;
        for(int i= x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j))
                {
                    if(arr[i][j]==-1)
                        count++;
                }
            }
        }
        return count;
    }
 void generateboard()//sets up the board
    {
        xmine[0]= rand()%16;
        ymine[0]= rand()%16;
        arr[xmine[0]][ymine[0]]=-1;
        int count=1;
        for(int i=1;i<40;i++)
        {
            bool flag=true;
            int x= rand()%16;// generates a random number as a x coordinate of the mine
            int y= rand()%16;// generates a random number as a y coordinate of the mine
            for(int j=0;j<count;j++)
            {
                if(xmine[j]==x&& ymine[j]==y)//checks wether a mine is not redundant by comparing with already created mines
                {
                    --i;
                    flag=false;
                    break;
                }
            }
            if(flag==false)
            continue;
            xmine[i]=x;
            ymine[i]=y;
            count++;
            arr[x][y]=-1;
        }
        for(int i=0;i<16;i++)//every cell of arr[][] is given values
        {
            for(int j=0;j<16;j++)
            {
                if(isMine(i,j)==false)
                    arr[i][j]=countMines(i,j);
                pos[i][j]=0;
                flagger[i][j]=0;
            }
        }
        }
int countNumber()//counts the number of squares that have been uncovered
    {
        int count=0;
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(pos[i][j]==1)
                {
                    count++;
                }
            }
        }
        return count;
    }
bool alreadyChecked(int x, int y)//checks wether the zero() function has been called or not on (x,y) to avoide infinite recursion
    {
        for(int i=0;i<zerocount+1;i++)
        {
            if(zeroposx[i]==x&&zeroposy[i]==y)
            return true;
        }
        return false;
    }
void zero(int x, int y)// makes pos value equal to 1 of all squares surrounding the zero square
    {
        for(int i=x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j)==true)
                {
                    if(arr[i][j]==0&&alreadyChecked(i,j)==false)
                    {
                        zerocount++;
                        zeroposx[zerocount]= i;
                        zeroposy[zerocount]= j;
                        zero(i,j);
                        pos[i][j]=1;
                    }
                    else
                        pos[i][j]=1;
                }
            }
        }
    }
void display()//displays the grid on initCanvas window
{
initCanvas("MINESWEEPER",700,700);
for(int i=40;i<=640;i=i+40)
{
for(int j=40;j<=640;j=j+40)
{
Rectangle r1(i,j,40,40);
r1.imprint();
if(flagger[(i/40)-1][(j/40)-1]==1)
{
Text t1(i,j,"M");
t1.setColor(COLOR("red"));
t1.imprint();
}
if(pos[(i/40)-1][(j/40)-1]==1)
{
if(arr[(i/40)-1][(j/40)-1]==0)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==1)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==2)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==3)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
}
}
}
    }
void completeDisplay()// completely displays the grid on exploding a mine
{
initCanvas("MINESWEEPER",700,700);
for(int i=40;i<=640;i=i+40)
{
for(int j=40;j<=640;j=j+40)
{
Rectangle r1(i,j,40,40);
r1.imprint();
if(arr[(i/40)-1][(j/40)-1]==0)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==1)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==2)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==3)
{
Text t1(i,j,arr[(i/40)-1][(j/40)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
if(arr[(i/40)-1][(j/40)-1]==-1)
{
r1.setColor(COLOR("red"));
r1.setFill(true);
r1.imprint();
Circle c(i,j,10);
c.setColor(COLOR("black"));
c.setFill(true);
c.imprint();
}
}
}
}
int play()//prompts the user to click on a square on the grid
{
time_t now = time(0);
long long t= now;
XEvent event;
while(countNumber()<216&&alive==true)
{
display();
int click=0;
int s= getClick();
nextEvent(event);
click= event.xbutton.button;
closeCanvas();
int s1=s/65536;
int s2=s%65536;
int count=0;
int xco=20;
int yco=20;
for(int i=0;i<16;i++)
{
for(int j=0;j<16;j++)
{
if(s1>xco&&s1<(xco+40)&&s2>yco&&s2<(yco+40))
{
if(click==1&&flagger[i][j]==0)
check(i,j);
if(click==3&&pos[i][j]==0)
flagMine(i,j);
count=1;
break;
}
yco+=40;
}
if(count==1)
break;
xco+=40;
yco=20;
}

}
if(countNumber()==216&&alive==true)//minesweeper completed when only mines are left
{
time_t now1 = time(0);
long long c= now1;
timer= c-t;
initCanvas();
Text m(250,250,"Congratulation, you completed minesweeper!");
Text t(250,300,"TIME TAKEN:");
Text t1(400,300,timer);
cout<<"ENTER YOUR NAME"<<endl;
string name;
cin>>name;
ofstream output;
output.open("highscoresintermediate.txt", std::ios_base::app);//stores high score
output<<name<<endl;
output<<timer<<endl;
getClick();

}
return 0;
}
int flagMine(int x, int y)//puts flagger value to 1 or 0
{
if(flagger[x][y]==0)
{
flagger[x][y]=1;
return 0;
}
if(flagger[x][y]==1)
{
flagger[x][y]=0;
return 0;
}
}
void check(int a,int b)//checks wether (x,y) is a mine or else puts its pos value as 1
{
if(arr[a][b]==-1)
{
completeDisplay();
getClick();
closeCanvas();
initCanvas();
Text t(300,300,"GAME OVER");
t.imprint();
alive=false;
}
if(arr[a][b]== 0)
            {
                zeroposx[zerocount]= a;
                zeroposy[zerocount]= b;
                zero(a,b);

            }
            else
            {
                pos[a][b]=1;
            }
            }
void flusher()//flushes all data members for the next game
{
zerocount=0;
alive=true;
for(int i=0;i<16;i++)
{
for(int j=0;j<16;j++)
{
arr[i][j]=0;
pos[i][j]=0;
flagger[i][j]=0;
}
}
for(int i=0;i<40;i++)
{
xmine[i]=0;
ymine[i]=0;
}
for(int i=0;i<215;i++)
{
zeroposx[i]=0;
zeroposy[i]=0;
}
}
};
class adv_game//advanced level
{
public:
int arr[16][30];//double dimensional array which stores the board
int xmine[99];//stores x coordinate of mines
int ymine[99];//stores y coordinate of mines.
int pos[16][30];;//stores pos value of each square. The value of the square is displayed if pos value is 1, else it is covered.
int zeroposx[380];//stores x coordinates of all zeros in the grid
int zeroposy[380];//stores y coordinates of all zeros in the grid
int zerocount=0;// stores number of zeros uncovered at that moment.
int flagger[16][30];//indicates whether there is a flag on that position or not
bool alive=true;// indicates if game is on or off.
 bool isMine(int x,int y)// checks whether there is a mine at (x,y)
    {
        for(int i=0;i<=98;i++)
        {
            if(x==xmine[i]&&y==ymine[i])
                return true;
        }
        return false;
    }
bool isValid(int x,int y)//checks wether (x,y) is on the board or not
    {
        if((x>=0&&x<=15)&&(y>=0&&y<=29))
            return true;
        return false;
    }
int countMines(int x, int y)//counts the number of mines in the squares surrounding (x,y)
    {
        int count=0;
        for(int i= x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j))
                {
                    if(arr[i][j]==-1)
                        count++;
                }
            }
        }
        return count;
    }
 void generateboard()//sets up the board
    {

        xmine[0]= rand()%16;// generates a random number as a x coordinate of the mine
        ymine[0]= rand()%30;// generates a random number as a y coordinate of the mine
        arr[xmine[0]][ymine[0]]=-1;
        int count=1;
        for(int i=1;i<99;i++)
        {
            bool flag=true;
            int x= rand()%16;
            int y= rand()%30;
            for(int j=0;j<count;j++)
            {
                if(xmine[j]==x&& ymine[j]==y)//checks wether a mine is not redundant by comparing with already created mines
                {
                    --i;
                    flag=false;
                    break;
                }
            }
            if(flag==false)
            continue;
            xmine[i]=x;
            ymine[i]=y;
            count++;
            arr[x][y]=-1;
        }
        for(int i=0;i<16;i++)//every cell of arr[][] is given values
        {
            for(int j=0;j<30;j++)
            {
                if(isMine(i,j)==false)
                    arr[i][j]=countMines(i,j);
                pos[i][j]=0;
                flagger[i][j]=0;
            }
        }
        }
int countNumber()//counts the number of squares that have been uncovered
    {
        int count=0;
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<30;j++)
            {
                if(pos[i][j]==1)
                {
                    count++;
                }
            }
        }
        return count;
    }
bool alreadyChecked(int x, int y)//checks wether the zero() function has been called or not on (x,y) to avoide infinite recursion
    {
        for(int i=0;i<zerocount+1;i++)
        {
            if(zeroposx[i]==x&&zeroposy[i]==y)
            return true;
        }
        return false;
    }
void zero(int x, int y)// makes pos value equal to 1 of all squares surrounding the zero square
    {
        for(int i=x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j)==true)
                {
                    if(arr[i][j]==0&&alreadyChecked(i,j)==false)
                    {
                        zerocount++;
                        zeroposx[zerocount]= i;
                        zeroposy[zerocount]= j;
                        zero(i,j);
                        pos[i][j]=1;
                    }
                    else
                        pos[i][j]=1;
                }
            }
        }
    }
void display()//displays the grid on initCanvas window
{
initCanvas("MINESWEEPER",1000,600);
for(int i=30;i<=900;i=i+30)
{
for(int j=30;j<=480;j=j+30)
{
Rectangle r1(i,j,30,30);
r1.imprint();
if(flagger[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,"M");
t1.setColor(COLOR("red"));
t1.imprint();
}
if(pos[(j/30)-1][(i/30)-1]==1)
{
if(arr[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==2)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==3)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
else
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.imprint();
}
}
}
}
    }
void completeDisplay()// completely displays the grid on exploding a mine
{
initCanvas("MINESWEEPER",1000,600);
for(int i=30;i<=900;i=i+30)
{
for(int j=30;j<=480;j=j+30)
{
Rectangle r1(i,j,30,30);
r1.imprint();
if(arr[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==2)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==3)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==-1)
{
r1.setColor(COLOR("red"));
r1.setFill(true);
r1.imprint();
Circle c(i,j,10);
c.setColor(COLOR("black"));
c.setFill(true);
c.imprint();
}
else
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.imprint();
}
}
}
}
int play()//prompts the user to click on a square on the grid
{
time_t now = time(0);
long long t= now;
XEvent event;
while(countNumber()<381&&alive==true)
{
display();
int click=0;
int s= getClick();
nextEvent(event);
click= event.xbutton.button;
closeCanvas();
int s1=s/65536;
int s2=s%65536;
int count=0;
int xco=15;
int yco=15;
for(int i=0;i<30;i++)
{
for(int j=0;j<16;j++)
{
if(s1>xco&&s1<(xco+30)&&s2>yco&&s2<(yco+30))
{
if(click==1&&flagger[j][i]==0)
check(i,j);
if(click==3&&pos[j][i]==0)
flagMine(j,i);
count=1;
break;
}
yco+=30;
}
if(count==1)
break;
xco+=30;
yco=15;
}

}
if(countNumber()==381&&alive==true)//minesweeper completed when only mines are left
{
time_t now1 = time(0);
long long c= now1;
timer= c-t;
initCanvas();
Text m(250,250,"Congratulation, you completed minesweeper!");
Text t(250,300,"TIME TAKEN:");
Text t1(400,300,timer);
cout<<"ENTER YOUR NAME"<<endl;
string name;
cin>>name;
ofstream output;
output.open("highscoresadvanced.txt", std::ios_base::app);//stores high score
output<<name<<endl;
output<<timer<<endl;
getClick();

}
return 0;
}
int flagMine(int x, int y)//puts flagger value to 1 or 0
{
if(flagger[x][y]==0)
{
flagger[x][y]=1;
return 0;
}
if(flagger[x][y]==1)
{
flagger[x][y]=0;
return 0;
}
}
void check(int a,int b)//checks wether (x,y) is a mine or else puts its pos value as 1
{
if(arr[a][b]==-1)
{
completeDisplay();
getClick();
closeCanvas();
initCanvas();
Text t(300,300,"GAME OVER");
t.imprint();//exploded a mine
alive=false;
}
if(arr[a][b]== 0)
            {
                zeroposx[zerocount]= a;
                zeroposy[zerocount]= b;
                zero(a,b);

            }
            else
            {
                pos[a][b]=1;
            }
            }
void flusher()//flushes all data members for the next game
{
zerocount=0;
alive=true;
for(int i=0;i<16;i++)
{
for(int j=0;j<30;j++)
{
arr[i][j]=0;
pos[i][j]=0;
flagger[i][j]=0;
}
}
for(int i=0;i<99;i++)
{
xmine[i]=0;
ymine[i]=0;
}
for(int i=0;i<380;i++)
{
zeroposx[i]=0;
zeroposy[i]=0;
}
}
};

class custom_game//custom level
{
public:
int* mines;// stores nmber of mines in the grid
int* columns;// stores number of columns in thr grid
int* rows;//stores numer of rows in thr grid
int** arr;//double dimensional array which stores the board
int* xmine;//stores x coordinate of mines
int* ymine;//stores y coordinate of mines.
int** pos;//stores pos value of each square. The value of the square is displayed if pos value is 1, else it is covered.
int* zeroposx;//stores x coordinates of all zeros in the grid
int* zeroposy;//stores y coordinates of all zeros in the grid
int zerocount=0;// stores number of zeros uncovered at that moment.
int** flagger;//indicates whether there is a flag on that position or not
bool alive=true;// indicates if game is on or off.
 bool isMine(int x,int y)// checks whether there is a mine at (x,y)
    {
        for(int i=0;i<=(*mines-1);i++)
        {
            if(x==xmine[i]&&y==ymine[i])
                return true;
        }
        return false;
    }
bool isValid(int x,int y)//checks wether (x,y) is on the board or not
    {
        if((x>=0&&x<=*rows-1)&&(y>=0&&y<=*columns-1))
            return true;
        return false;
    }
int countMines(int x, int y)//counts the number of mines in the squares surrounding (x,y)
    {
        int count=0;
        for(int i= x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j))
                {
                    if(arr[i][j]==-1)
                        count++;
                }
            }
        }
        return count;
    }
 void generateboard()//sets up the board
    {

        xmine[0]= rand()%(*rows);// generates a random number as a x coordinate of the mine
        ymine[0]= rand()%(*columns);// generates a random number as a y coordinate of the mine
        arr[xmine[0]][ymine[0]]=-1;
        int count=1;
        for(int i=1;i<*mines;i++)
        {
            bool flag=true;
            int x= rand()%(*rows);
            int y= rand()%(*columns);
            for(int j=0;j<count;j++)//checks wether a mine is not redundant by comparing with already created mines
            {
                if(xmine[j]==x&& ymine[j]==y)
                {
                    --i;
                    flag=false;
                    break;
                }
            }
            if(flag==false)
            continue;
            xmine[i]=x;
            ymine[i]=y;
            count++;
            arr[x][y]=-1;
        }
        for(int i=0;i<(*rows);i++)//every cell of arr[][] is given values
        {
            for(int j=0;j<(*columns);j++)
            {
                if(isMine(i,j)==false)
                    arr[i][j]=countMines(i,j);
                pos[i][j]=0;
                flagger[i][j]=0;
            }
        }
        }
int countNumber()//counts the number of squares that have been uncovered
    {
        int count=0;
        for(int i=0;i<(*rows);i++)
        {
            for(int j=0;j<(*columns);j++)
            {
                if(pos[i][j]==1)
                {
                    count++;
                }
            }
        }
        return count;
    }
bool alreadyChecked(int x, int y)//checks wether the zero() function has been called or not on (x,y) to avoide infinite recursion
    {
        for(int i=0;i<zerocount+1;i++)
        {
            if(zeroposx[i]==x&&zeroposy[i]==y)
            return true;
        }
        return false;
    }
void zero(int x, int y)// makes pos value equal to 1 of all squares surrounding the zero square
    {
        for(int i=x-1;i<x+2;i++)
        {
            for(int j=y-1;j<y+2;j++)
            {
                if(isValid(i,j)==true)
                {
                    if(arr[i][j]==0&&alreadyChecked(i,j)==false)
                    {
                        zerocount++;
                        zeroposx[zerocount]= i;
                        zeroposy[zerocount]= j;
                        zero(i,j);
                        pos[i][j]=1;
                    }
                    else
                        pos[i][j]=1;
                }
            }
        }
    }
void display()//displays the grid on initCanvas window
{
initCanvas("MINESWEEPER",1500,700);
for(int i=30;i<=(*columns * 30);i=i+30)
{
for(int j=30;j<=(*rows * 30);j=j+30)
{
Rectangle r1(i,j,30,30);
r1.imprint();
if(flagger[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,"M");
t1.setColor(COLOR("red"));
t1.imprint();
}
if(pos[(j/30)-1][(i/30)-1]==1)
{
if(arr[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==2)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==3)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
else
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.imprint();
}
}
}
}
    }
void completeDisplay()// completely displays the grid on exploding a mine
{
initCanvas("MINESWEEPER",1500,700);
for(int i=30;i<=(*columns * 30);i=i+30)
{
for(int j=30;j<=(*rows * 30);j=j+30)
{
Rectangle r1(i,j,30,30);
r1.imprint();
if(arr[(j/30)-1][(i/30)-1]==1)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("blue"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==2)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("green"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==3)
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.setColor(COLOR("red"));
t1.imprint();
}
else if(arr[(j/30)-1][(i/30)-1]==-1)
{
r1.setColor(COLOR("red"));
r1.setFill(true);
r1.imprint();
Circle c(i,j,10);
c.setColor(COLOR("black"));
c.setFill(true);
c.imprint();
}
else
{
Text t1(i,j,arr[(j/30)-1][(i/30)-1]);
t1.imprint();
}
}
}
}
int play()//prompts the user to click on a square on the grid
{
time_t now = time(0);
long long t= now;
XEvent event;
while(countNumber()<((*rows) * (*columns)-(*mines))&&alive==true)
{
display();
int click=0;
int s= getClick();
nextEvent(event);
click= event.xbutton.button;
closeCanvas();
int s1=s/65536;
int s2=s%65536;
int count=0;
int xco=15;
int yco=15;
for(int i=0;i<(*columns);i++)
{
for(int j=0;j<(*rows);j++)
{
if(s1>xco&&s1<(xco+30)&&s2>yco&&s2<(yco+30))
{
if(click==1&&flagger[j][i]==0)
check(j,i);
if(click==3&&pos[j][i]==0)
flagMine(j,i);
count=1;
break;
}
yco+=30;
}
if(count==1)
break;
xco+=30;
yco=15;
}

}
if(countNumber()==((*rows)*(*columns)-(*mines))&&alive==true)//minesweeper completed when only mines are left
{
time_t now1 = time(0);
long long c= now1;
timer= c-t;
initCanvas();
Text m(250,250,"Congratulation, you completed minesweeper!");
Text t(250,300,"TIME TAKEN:");
Text t1(400,300,timer);
cout<<"ENTER YOUR NAME"<<endl;
string name;
cin>>name;
ofstream output;
output.open("highscorescustom.txt", std::ios_base::app);//stores high score
output<<name<<endl;
output<<timer<<endl;
getClick();
}
return 0;
}
int flagMine(int x, int y)//puts flagger value to 1 or 0
{
if(flagger[x][y]==0)
{
flagger[x][y]=1;
return 0;
}
if(flagger[x][y]==1)
{
flagger[x][y]=0;
return 0;
}
}
void check(int a,int b)//checks wether (x,y) is a mine or else puts its pos value as 1
{
if(arr[a][b]==-1)
{
completeDisplay();
getClick();
closeCanvas();
initCanvas();
Text t(300,300,"GAME OVER");
t.imprint();
//exploded a mine
alive=false;
}
if(arr[a][b]== 0)
            {
                zeroposx[zerocount]= a;
                zeroposy[zerocount]= b;
                zero(a,b);

            }
            else
            {
                pos[a][b]=1;
            }
            }
void flusher()//flushes all data members for the next game
{
zerocount=0;
alive=true;
for(int i=0;i<(*rows);i++)
{
for(int j=0;j<(*columns);j++)
{
arr[i][j]=0;
pos[i][j]=0;
flagger[i][j]=0;
}
}
for(int i=0;i<(*mines);i++)
{
xmine[i]=0;
ymine[i]=0;
}
for(int i=0;i<((*columns)*(*rows))+1-(*mines);i++)
{
zeroposx[i]=0;
zeroposy[i]=0;
}
}
};
void selectLevel()// to select level
{
initCanvas();
while(true)
{
Rectangle r1(250,100,400,70);
Text t1(250,100,"BEGINNER");
Rectangle r2(250,200,400,70);
Text t2(250,200,"INTERMEDIATE");
Rectangle r3(250,300,400,70);
Text t3(250,300,"ADVANCED");
Rectangle r4(250,400,400,70);
Text t4(250,400,"CUSTOM");
int s=getClick();
int s1= s/65536;
int s2= s%65536;
if(s1>50&&s1<450&&s2<135&&s2>65)//beginner
{
closeCanvas();
beg_game g;
g.generateboard();
g.play();
g.flusher();
break;
}
if(s1>50&&s1<450&&s2<235&&s2>165)//intermediate
{
closeCanvas();
inter_game g;
g.generateboard();
g.play();
g.flusher();
break;
}
if(s1>50&&s1<450&&s2<335&&s2>265)//advanced
{
closeCanvas();
adv_game g;
g.generateboard();
g.play();
g.flusher();
break;
}
if(s1>50&&s1<450&&s2<435&&s2>365)//custom
{
int keypad[4][3];// keypad to enter data
int counter=1;
for(int i=0;i<3;i++)
{
for(int j=0;j<3;j++)
{
keypad[i][j]=counter;
counter++;
}
}
keypad[3][0]=0;
keypad[3][1]=-1;
keypad[3][2]=10;
closeCanvas();
initCanvas();
Text r(250,50," ENTER THE NUMBER OF ROWS");
r.imprint();
Text c(250,120," ENTER THE NUMBER OF COLUMNS");
c.imprint();
Text m(250,190," ENTER THE NUMBER OF MINES");
m.imprint();
for(int i=150;i<300;i=i+50)
{
for(int j=300;j<=450;j=j+50)
{
Rectangle r1(i,j,50,50);
r1.imprint();
if(i==200&&j==450)
{
Text temp(i,j,"C");
temp.imprint();
}
else if(i==250&&j==450)
{
Text temp(i,j,"OK");
temp.imprint();
}
else
{
Text temp(i,j,keypad[(j-300)/50][(i-150)/50]);
temp.imprint();
}
}
}
int rowno=0,columno=0,mino=0,choose=0;
while(choose==0)// number of rows
{
int xco=125;
int yco=275;
int s= getClick();
int s1=s/65536;
int s2=s%65536;
bool flag= false;
for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
if(s1>xco&&s1<(xco+50)&&s2>yco&&s2<(yco+50))
{
if(keypad[j][i]==10)
{
if(rowno>0&&rowno<23)
{
choose++;
flag= true;;
break;
}
else
{
Rectangle eraser(250,95,60,40);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
rowno=0;
flag=true;
break;
}
}
if(keypad[j][i]==-1)
{
Rectangle eraser(250,95,60,40);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
rowno=0;
flag=true;
break;
}
else
{
rowno= rowno*10+keypad[j][i];
flag=true;
break;
}
}
yco+=50;
}
if(flag==true)
{
Rectangle eraser(250,95,60,40);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
Text row(250,95,rowno);
row.imprint();
break;
}
xco+=50;
yco=275;
}
}
while(choose==1)//number of colummns
{
int xco=125;
int yco=275;
int s= getClick();
int s1=s/65536;
int s2=s%65536;
bool flag= false;
for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
if(s1>xco&&s1<(xco+50)&&s2>yco&&s2<(yco+50))
{
if(keypad[j][i]==10)
{
if(columno>0&&columno<44)
{
choose++;
flag= true;
break;
}
else
{
Rectangle eraser(250,155,50,30);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
columno=0;
flag=true;
break;
}
}
if(keypad[j][i]==-1)
{
Rectangle eraser(250,155,50,30);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
columno=0;
flag=true;
break;
}
else
{
columno= columno*10+keypad[j][i];
flag=true;
break;
}
}
yco+=50;
}
if(flag==true)
{
Rectangle eraser(250,155,60,40);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
Text col(250,155,columno);
col.imprint();
break;
}
xco+=50;
yco=275;
}
}
while(choose==2)//number of mines
{
int xco=125;
int yco=275;
int s= getClick();
int s1=s/65536;
int s2=s%65536;
bool flag= false;
for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
if(s1>xco&&s1<(xco+50)&&s2>yco&&s2<(yco+50))
{
if(keypad[j][i]==10)
{
if(mino>0&&mino<(columno*rowno))
{
choose++;
flag= true;
break;
}
else
{
Rectangle eraser(250,225,50,30);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
mino=0;
flag=true;
break;
}
}
if(keypad[j][i]==-1)
{
Rectangle eraser(250,225,50,30);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
mino=0;
flag=true;
break;
}
else
{
mino= mino*10+keypad[j][i];
flag=true;
break;
}
}
yco+=50;
}
if(flag==true)
{
Rectangle eraser(250,225,60,40);
eraser.setColor(COLOR("white"));
eraser.setFill(true);
eraser.imprint();
Text mine(250,225,mino);
mine.imprint();
break;
}
xco+=50;
yco=275;
}
}
closeCanvas();
custom_game g;
//heap memory used to allocate values to data memebers of object g of class custom_game
g.rows= new int;
*g.rows= rowno;
g.columns= new int;
*g.columns= columno;
g.mines= new int;
*g.mines= mino;
g.arr= new int*[rowno];
for(int i = 0; i <rowno;i++)
g.arr[i] = new int[columno];
g.flagger= new int*[rowno];
for(int i = 0; i <rowno;i++)
g.flagger[i] = new int[columno];
g.xmine= new int[mino];
g.ymine= new int[mino];
g.pos= new int*[rowno];
for(int i = 0; i <rowno;i++)
g.pos[i] = new int[columno];
g.zeroposx= new int[(columno*rowno)+1-mino];
g.zeroposy= new int[(columno*rowno)+1-mino];
g.generateboard();
g.play();
g.flusher();
//heap memory returned after use
delete g.rows;
delete g.columns;
delete g.mines;
delete[] g.zeroposx;
delete[] g.zeroposy;
delete[] g.xmine;
delete[] g.ymine;
delete[] g.arr;
delete[] g.flagger;
delete[] g.pos;
break;
}
}
}

void displayInstructions()// displays instructions regarding the game
{
closeCanvas();
initCanvas("INSTRUCTIONS",900,900);
Text i1(400,100,"MINESWEEPER IS A SINGLE PLAYER GAME .");
Text i2(400,150,"THE OBJECTIVE OF THE GAME IS TO CLEAR AN ");
Text p1(400,200,"ABSTRACT MINEFIELD WITHOUT DETONATING A MINE.");
Text i3(400,250,"THE NUMBER DISPLAYED INDICATES THE NUMBER ");
Text p2(400,300,"OF MINES SURROUNDING THE SQUARE.");
Text i4(400,350,"TRY TO CLEAR THE FIELD IN THE SHORTEST TIME POSSIBLE.");
Text i5(400,400,"YOU CAN FLAG A MINE BY USING THE RIGHT ");
Text p3(400,450,"CLICK OF THE MOUSE BUTTON.");
getClick();
}
void displayScore()//displays highscores of various levels
{
initCanvas();
while(true)
{
Rectangle r1(250,100,400,70);
Text t1(250,100,"BEGINNER");
Rectangle r2(250,200,400,70);
Text t2(250,200,"INTERMEDIATE");
Rectangle r3(250,300,400,70);
Text t3(250,300,"ADVANCED");
Rectangle r4(250,400,400,70);
Text t4(250,400,"CUSTOM");
int s=getClick();
int s1= s/65536;
int s2= s%65536;
if(s1>50&&s1<450&&s2<135&&s2>65)//beginner
{
closeCanvas();
initCanvas();
ifstream input("highscoresbeg.txt");
while (true) {
string s;
input >>s;
    double x;
    input >> x;
    if( input.eof() ) break;
    cout<<s<<"      ";
    cout << x << endl;
}
break;
}
if(s1>50&&s1<450&&s2<235&&s2>165)//intermediate
{
   closeCanvas();
   initCanvas();
ifstream input("highscoresintermediate.txt");
while (true) {
string s;
input >>s;
    double x;
    input >> x;
    if( input.eof() ) break;
    cout<<s<<"      ";
    cout << x << endl;
}
break;
}
if(s1>50&&s1<450&&s2<335&&s2>265)//advanced
{
closeCanvas();
initCanvas();
ifstream input("highscoresadvanced.txt");
while (true) {
string s;
input >>s;
    double x;
    input >> x;
    if( input.eof() ) break;
    cout<<s<<"      ";
    cout << x << endl;
}
break;
}
if(s1>50&&s1<450&&s2<435&&s2>365)//custom
{
closeCanvas();
initCanvas();
ifstream input("highscorescustom.txt");
while (true) {
string s;
input >>s;
    double x;
    input >> x;
    if( input.eof() ) break;
    cout<<s<<"      ";
    cout << x << endl;
}
break;
}
}
}
main_program{
initCanvas();
while(true)
{
//welcome screen
Text t(250,50,"MINESWEEPER");
Rectangle r1(250,100,400,70);
Text t1(250,100,"NEW GAME");
Rectangle r2(250,200,400,70);
Text t2(250,200,"INSTRUCTIONS");
Rectangle r3(250,300,400,70);
Text t3(250,300,"HIGH SCORES");
Rectangle r4(250,400,400,70);
Text t4(250,400,"QUIT");
int s=getClick();
int s1= s/65536;
int s2= s%65536;
if((s1>50&&s1<450)&&(s2<135&&s2>65))//new game
{
closeCanvas();
selectLevel();
getClick();
closeCanvas();
initCanvas();
}
if((s1>50&&s1<450)&&(s2<235&&s2>165))//displayInstructions
{
displayInstructions();
}
if((s1>50&&s1<450)&&(s2<335&&s2>265))//displayScore
{
closeCanvas();
displayScore();
}
if((s1>50&&s1<450)&&(s2<435&&s2>365))//quit game
{
break;
}
}
}
