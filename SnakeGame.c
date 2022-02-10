#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 20
#define M 40

int i,j,Field[N][M],x,y,Gy,Head,Tail,Game,Frog,a,b,var,dir,score,Highscore,Speed;

FILE *f;

void snakeInitialization()
{
    f=fopen("highscore.txt","r");
    fscanf(f,"%d",&Highscore);
    fclose(f);

    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            Field[i][j]=0;
    x=N/2;
    y=M/2;
    Gy=y;
    Head=5;
    Tail=1;
    Game=0;
    Frog=0;
    dir='d'; ///why
    score=0;          ///why???
    Speed=99;

    for(i=0;i<Head;i++)
    {
        Gy++;
        Field[x][Gy-Head]=i+1;
    }
}

void print()
{
    for(int i=0;i<=M+1;i++)
    {
        if(i==0)
            printf("%c",201);
        else if(i==M+1)
            printf("%c",187);
        else
            printf("%c",205);
    }

    printf("  Current Score: %d   High Score: %d",score,Highscore);

    printf("\n");

    for(int i=0;i<N;i++)
    {
        printf("%c",186);
        for(j=0;j<M;j++)
        {
            if(Field[i][j]==0)
                printf(" ");
            if(Field[i][j]>0 && Field[i][j]!=Head)     ///tail print
                printf("%c",176);
            if(Field[i][j]==Head)
                printf("%c",178);
            if(Field[i][j]==-1)
                printf("%c",155);
            if(j==M-1)
                printf("%c\n",186);
        }
    }

    for(int i=0;i<=M+1;i++)
    {
        if(i==0)
            printf("%c",200);
        else if(i==M +1)
            printf("%c",188);
        else
            printf("%c",205);
    }
}

void ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X=0;
    Position.Y=0;
    SetConsoleCursorPosition(hOut,Position);
}

Random()
{
    srand(time(0)); ///rand is predictable

    a=1 + rand() % 18;
    b=1 + rand() % 38;

    if(Frog==0 && Field[a][b]==0)
    {
        Field[a][b] = -1 ;     ///-1 is frog
        Frog = 1 ;   ///why?
        if(Speed>10 && score!=0)
            Speed=Speed-5;
    }
}

int getch_noblock()   ///why not scanf or getchar
{
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement()
{
    var=getch_noblock();
    var=tolower(var);  ///capslock

    if(((var=='a' || var=='s') || (var=='d' || var=='w')) && (abs(dir-var)>5))              ///for at a time up down/left right
        dir=var;          ///continuous movement for dir
    if(dir=='d')
    {
        y++;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            GameOver();
        if(y==M-1)                          ///come from same line
            y=0;
        if(Field[x][y]==-1)
        {
            Frog=0;
            score+=5;                     ///we want more frog
            Tail-=2;
        }
        Head++;
        Field[x][y]=Head;
    }

    if(dir=='a')
    {
        y--;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            GameOver();
        if(y==0)
            y=M-1;
        if(Field[x][y]==-1)
        {
            Frog=0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y]=Head;
    }

    if(dir=='w')
    {
        x--;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            GameOver();
        if(x==-1)
            x=N-1;
        if(Field[x][y]==-1)
        {
            Frog=0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y]=Head;
    }

    if(dir=='s')
    {
        x++;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            GameOver();
        if(x==N-1)
            x=0;
        if(Field[x][y]==-1)
        {
            Frog=0;
            Tail-=2;
            score+=5;
        }

        Head++;
        Field[x][y]=Head;
    }
}

TailRemove()
{
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            if(Field[i][j]==Tail)
                Field[i][j]=0;
    Tail++;
}

void GameOver()
{
    printf("\a");
    Sleep(1500);
    system("Cls");

    if(score>Highscore)
    {
        printf("    New High Score %d !!!!!!!\n\n",score);
        system("pause");
        f=fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }

    system("Cls");     ///clear the screen

    printf("\n\n               GAME OVER!!!!!!!!!!\n\n");
    printf("                   Score : %d \n\n",score);
    printf("                   Press Enter to play again or ESC to exit ... \n");

    while(1)
    {
        var=getch_noblock();
        if(var==13)               ///13=Enter
        {
            Game=0;
            snakeInitialization();
            break;
        }
        else if(var==27)
        {
            Game=1;
            break;
        }
    }
    system("Cls");
}

void main()
{
    snakeInitialization();

    while(Game==0)
    {
         print();
         ResetScreenPosition();
         Random();
         movement();          ///snake moves by head=5 to tail=1 then head=6 to tail=2
         TailRemove();
         Sleep(Speed);
    }
}

