#include "taxi.h"
#include <QDebug>

char Taxi::getNextMove()
{
 return path.top();
}

int Taxi::getx()
{
    return x;
}

int Taxi::gety()
{
    return y;
}

void Taxi::setx(int x)
{
    this->x=x;
}

void Taxi::sety(int y)
{
    this->y=y;
}
Taxi::Taxi(int x,int y)
{
    this->x=x;
    this->y=y;
    occupied=0;
}

bool Taxi::isOccupied()
{
    return occupied;
}

void Taxi::move()
{
    if(path.empty())
    {
        //search
    }
    else
    {
        path.pop();
        char dir=path.top();
        if(dir== 'r')
        {

        }
        else if(dir == 'l')
        {

        }
        else if(dir == 'u')
        {

        }
        else if(dir == 'd')
        {

        }
    }
}

std::stack<char> Taxi::findPath(int desx,int desy,std::vector<std::vector<cell*>> v)
{
   std::stack<char> taxi_path;
   int numRows=v.size();
   int numCols=v[0].size();

   std::vector<std::vector<char>>par(numRows,std::vector<char>(numCols,'s'));
   std::vector<std::vector<bool>>vis(numRows,std::vector<bool>(numCols));

   std::queue<std::pair<int,int>>q;
   q.push(std::make_pair(this->x,this->y));

   while(!q.empty())
   {
       int curx = q.front().first,cury=q.front().second; q.pop();
       vis[curx][cury]=1;
       qDebug()<<"curx"<<curx<<"cury"<<cury;

       /*   r
        * r p r
        *   r
        */
       if((abs(curx-desx)+abs(cury-desy))==1)
       {
           qDebug()<<"done";
           while(!q.empty())
               q.pop();

           while(par[curx][cury] != 's')
           {
               if(par[curx][cury]=='u')
               {
                  curx++;
                  taxi_path.push('u');
               }
               else if(par[curx][cury]=='d')
               {
                  curx--;
                  taxi_path.push('d');
               }
               else if (par[curx][cury]=='l')
               {
                    cury++;
                    taxi_path.push('l');
               }
               else if(par[curx][cury]=='r')
               {
                    cury--;
                    taxi_path.push('r');
               }
            }
           return taxi_path;
        }

       if(curx+1 <numRows)
       {
           if(!vis[curx+1][cury] && v[curx+1][cury]->isRoad()){
               q.push(std::make_pair(curx+1,cury)); par[curx+1][cury]='d';
           }
       }
       if(curx-1 >=0)
       {
           if(!vis[curx-1][cury] && v[curx-1][cury]->isRoad()){
               q.push(std::make_pair(curx-1,cury)); par[curx-1][cury]='u';
           }
       }
       if(cury+1 <numCols)
       {
           if(!vis[curx][cury+1] && v[curx][cury+1]->isRoad()){
               q.push(std::make_pair(curx,cury+1));par[curx][cury+1]='r';
           }
       }
       if(cury-1 >=0)
       {
           if(!vis[curx][cury-1] && v[curx][cury-1]->isRoad()){
               q.push(std::make_pair(curx,cury-1));par[curx][cury-1]='l';
           }
       }

    }
}

void Taxi::setPath(std::stack<char> p)
{
    path=p;
}


